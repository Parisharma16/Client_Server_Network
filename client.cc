/*
 * client.cc
 *
 *  Created on: Mar 17, 2025
 *      Author: pari
 */


#include <omnetpp.h>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include <set>
#include <cmath>

#include <functional>
#include <sstream>

#include "message_m.h"
using namespace omnetpp;
using namespace std;

class Client: public cSimpleModule{
   vector<int> task;
   //vector<bool> servers_nature; // honest or malicious
   vector<int> score;
   map<int,vector<pair<int,int>>> mapp;
   int n;
   int subtask_completed;
   int total_subtasks;
   int total_clients;

   string IP;

   int cumulative_result=INT_MIN; // max element
   bool taskDone=0;
   set<string> receivedMessages;
   int start_ind=1;
   int gossip_cnt;
   vector<int> avg_score;
   vector<int> topServers;

   bool round1done=false;

protected:

    void initialize() override;
    void handleMessage(cMessage *msg) override;
    int majorityVoting(vector<pair<int,int>> arr);
    void broadcastScores();
    void beginSecondRound();
};


Define_Module(Client);


void Client::initialize(){



    n = getParentModule()->par("numServers").intValue();  // Read num_servers from omnetpp.ini
    this->subtask_completed=0;
    this->score.resize(n,0);
    this->avg_score.resize(n,0);
    gossip_cnt=0;
    this->total_clients=getParentModule()->par("numClients").intValue()-1;  // total-1 clients to check how many gossip msgs received

    this->IP=par("IP").stringValue();

    string taskStr = par("task").stringValue();



    EV << "Client " << getIndex() << " initialized with task: " << taskStr << "\n";

    if (taskStr.empty()) {
        EV << "Client " << getIndex() << " has no task assigned. Exiting initialization.\n";
        return;
    }


    istringstream iss(taskStr);
        int num;
        while (iss >> num) {
            task.push_back(num);
        }



    this->total_subtasks=n;

    int x=task.size();
    int subtask_ID=0;
    int chunkSize = ceil(static_cast<double>(x) / n);

    for (int i = 0; i < x; i += chunkSize) {  // Proper subtask division
        // for a subtask
        // chose start_ind

        int choose=start_ind;
        int endIdx = min(static_cast<size_t>(i + x / n), task.size());
        vector<int> subtask(task.begin() + i, task.begin() + endIdx);

        string subTask="";

        for(int i=0;i<subtask.size();i++){
            subTask+=to_string(subtask[i]);
            if(i!=subtask.size()-1) subTask+=" ";
        }


        // now choose n/2+1 servers at random and send the subtask to them
        // choose n/2+1 servers randomly, basically make a set of this size and dont choose repttsve elemnts

        int numServersToUse = n/2 + 1;
        set<int> selectedServers;
        while (selectedServers.size() < numServersToUse) {
            int serverId = intuniform(0, n - 1);
            selectedServers.insert(serverId);
        }

        for(auto it:selectedServers){
            SubtaskRequest *msg = new SubtaskRequest();
            msg->setSubtaskID(subtask_ID);
            msg->setSubtaskArr(subTask.c_str());
            msg->setServerID(it);
            msg->setIsMalicious(choose%4);  // Honest by default
            choose++;

            send(msg, "out", it);
            EV << "Client " << getIndex() << " sent subtask " <<subTask.c_str() <<" to" << subtask_ID << " to Server " << it << "\n";

        }

        subtask_ID++;
        start_ind++;
    }
}

void Client::handleMessage(cMessage * msg){
    //send(msg,"out");

    if (SubtaskReply *replyMsg = dynamic_cast<SubtaskReply *>(msg)) {  // reply coming from the server
        //SubtaskReply *replyMsg = check_and_cast<SubtaskReply*>(msg);

        int subtaskID = replyMsg->getSubtaskID();
        int result = replyMsg->getResult();
        int serverID = replyMsg->getServerID();
        mapp[subtaskID].push_back({result,serverID});

        EV << "Client " << getIndex() << " received reply for subtask " << subtaskID << " from Server " << serverID<< "\n";

        if (mapp[subtaskID].size() == (n / 2 + 1)) {  // All required servers replied for this subtask
            this->subtask_completed++;

            EV << "Subtask " << subtaskID << " has received enough replies (" << n / 2 + 1 << ").\n";
            EV << "Total completed subtasks so far: " << this->subtask_completed << "/" << this->total_subtasks << "\n";

            int final_val = majorityVoting(mapp[subtaskID]);
            EV << "Final computed value for subtask " << subtaskID << " is: " << final_val << "\n";

            this->cumulative_result = max(this->cumulative_result, final_val);

            // update scores of the servers
            for(auto it:mapp[subtaskID]){
                if(it.first==final_val){
                    score[it.second]++;
                }
            }
        }
    }



     // reply coming from clients, after task is finished, telling about the servers it thinks is malicious or not

    if(this->subtask_completed==this->total_subtasks && !taskDone){
        // this means all subtasks are completed and
        // it can send the cumulative score to fellow clients
        // also need to maintain a hashed list of messages to make sure we dont send the same message again
        EV << "Client " << getIndex() << " has got the maximum value for the task which is " << this->cumulative_result << "\n";

        // message formt: <self.timestamp>:<self.IP>:<self.Score#>
        broadcastScores();
        this->taskDone=1;
    }


    //this is transfer of the received mesg (check this code)

    if (GossipMessage *gossipMsg = dynamic_cast<GossipMessage *>(msg) ) {

        if(!round1done){
            string content = gossipMsg->getContent();
            int incomingGateIndex = msg->getArrivalGate()->getIndex();  // Get the gate index of the sender

            // Compute hash of the message
            size_t messageHash = std::hash<string>{}(content);

            if (receivedMessages.find(content) == receivedMessages.end()) { // new gossip msg;
                gossip_cnt++;
                receivedMessages.insert(content);
                size_t pos = content.find(":");
                string sender = (pos != string::npos) ? content.substr(0, pos) : "Unknown";
                EV << "Client " << getIndex() << " received gossip from " << sender << "\n";
                EV << "Message content: " << content << "\n";


                vector<int> receivedScores(n, 0);
                istringstream iss(content.substr(pos + 1));  // Extract scores part after `IP:`
                for (int i = 0; i < n; i++) {
                    if (!(iss >> receivedScores[i])) break;  // Read scores
                }

                // Accumulate scores into avg_score array
                for (int i = 0; i < n; i++) {
                    avg_score[i] += receivedScores[i];
                }

                EV << "Updated avg_score array: ";
                for (int i = 0; i < n; i++) {
                    EV << "Server " << i << " -> " << avg_score[i] << " | ";
                }
                EV << "\n";

                // Forward message to all peers except sender
                for (int i = 0; i < gateSize("peerOut"); i++) {
                    if (i != incomingGateIndex) {
                        GossipMessage *forwardMsg = gossipMsg->dup();
                        send(forwardMsg, "peerOut", i);
                    }
                }
            }

            if(gossip_cnt==total_clients){
                // received gossip msgs from all the clients, can start second round of subtask transfer
                round1done=true;

                int numServersToUse = n / 2 + 1;
                vector<pair<int, int>> sortedScores;  // {score, serverIndex}

                for (int i = 0; i < n; i++) {
                    sortedScores.push_back({avg_score[i], i});
                }

                // Sort in descending order of scores
                sort(sortedScores.rbegin(), sortedScores.rend());


                for (int i = 0; i < numServersToUse; i++) {
                    topServers.push_back(sortedScores[i].second);
                }

                EV << "Selected top " << numServersToUse << " servers for second round: ";
                for (int server : topServers) {
                    EV << server << " ";
                }
                EV << "\n";

                beginSecondRound();

            }
        }
        // second round, compute the final result and print it

    }
    delete msg;
}



void Client::beginSecondRound(){
    EV << "Client " << getIndex() << " starting second round \n";
    EV << "Clearing previous subtask results and starting second round...\n";

    // Clear all previous subtask results
    mapp.clear();

    this->cumulative_result=INT_MIN;

    int x=task.size();
    int subtask_ID=0;
    int chunkSize = ceil(static_cast<double>(x) / n);

    for (int i = 0; i < x; i += chunkSize) {  // Proper subtask division
        // for a subtask
        // chose start_ind

        int choose=start_ind;
        int endIdx = min(static_cast<size_t>(i + x / n), task.size());
        vector<int> subtask(task.begin() + i, task.begin() + endIdx);

        string subTask="";

        for(int i=0;i<subtask.size();i++){
            subTask+=to_string(subtask[i]);
            if(i!=subtask.size()-1) subTask+=" ";
        }


        // now choose n/2+1 servers at random and send the subtask to them
        // choose n/2+1 servers randomly, basically make a set of this size and dont choose repttsve elemnts


        for(auto it:topServers){
            SubtaskRequest *msg = new SubtaskRequest();
            msg->setSubtaskID(subtask_ID);
            msg->setSubtaskArr(subTask.c_str());
            msg->setServerID(it);
            msg->setIsMalicious(choose%4);  // Honest by default
            choose++;

            send(msg, "out", it);
            EV << "Client " << getIndex() << " sent subtask " <<subTask.c_str() <<" to" << subtask_ID << " to Server " << it << "\n";

        }

        subtask_ID++;
        start_ind++;
    }

    return;
}


void Client::broadcastScores(){
    EV << "Starting broadcastScores()" << endl;

    string gossipMessage = IP + ":";
    for (int i = 0; i < n; i++) {
        gossipMessage += to_string(score[i]) + " ";
    }



    EV << "Constructed gossip message: " << gossipMessage << endl;


    for (int i = 0; i < n; i++) {
        avg_score[i] += score[i]; // upadting the avg score array with the current scores
    }


// Check if this message has already been sent
    if (receivedMessages.find(gossipMessage) != receivedMessages.end()) {
        EV << "Skipping broadcast: Message already sent." << endl;
        return;  // Prevents redundant broadcasts
    }

    receivedMessages.insert(gossipMessage);

    GossipMessage *msg = new GossipMessage();
    msg->setContent(gossipMessage.c_str());

    // Send the message to all peer clients
    for (int i = 0; i < gateSize("peerOut"); i++) {
        GossipMessage *msgCopy = msg->dup();
        EV << "Sending message copy to peerOut[" << i << "]" << endl;
        send(msgCopy, "peerOut", i);
    }

    // Delete only the original message (copies are managed by OMNeT++)
    delete msg;
    EV << "Original message deleted after broadcasting." << endl;
}



int Client::majorityVoting(vector<pair<int,int>> arr){

    std::map<int, int> countMap; // result,
    for (auto it: arr) {
        countMap[it.first]++;
    }

    EV << " Voting results: ";
    for (auto it : countMap) {
        EV << it.first << " -> " << it.second << " votes | ";
    }
    EV << "\n";


    int majorityResult = -1, maxCount = 0;
    for (auto it : countMap) {
        if (it.second > maxCount) {
            maxCount = it.second;
            majorityResult = it.first;
        }
    }

    return majorityResult;
}


