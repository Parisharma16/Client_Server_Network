/*
 * server.cc
 *
 *  Created on: Mar 19, 2025
 *      Author: pari
 */

#include <omnetpp.h>
#include <vector>
#include <sstream>
#include <algorithm>
#include <utility>
#include "message_m.h"
using namespace omnetpp;
using namespace std;


class Server: public cSimpleModule{

    vector<int> arr; // input subtask
    bool is_mal;

protected:

    void initialize() override;
    void handleMessage(cMessage *msg) override;
    int maxElement(vector<int> & arr);

};


Define_Module(Server);

void Server::initialize(){
    EV << "Server " << getIndex() << " initialized.\n";

}



void Server::handleMessage(cMessage *msg) {

    if(SubtaskRequest * Request=dynamic_cast<SubtaskRequest *>(msg)){
        // server recives the msg from client , find the subtask ID, the subtask ARR, and also finds whether it needs to
        //behave malicoiusly or honestly, uske baad depdning on the reply, it calculate the maximum depnding on the subtask array
        //and then adds a results parameter and then sends subtask reply

        int subtaskID=Request->getSubtaskID() ;
        int serverID=Request->getServerID() ;
        int is_honest=Request->isMalicious();
        string s=Request->getSubtaskArr() ;



        vector<int> subtaskArr;

        istringstream iss(s);

        int num;

        while(iss>>num){
            subtaskArr.push_back(num);
        }

        // Log received task
        EV << "Server " << getIndex() << " received subtask " << subtaskID
           << " from Client at gate " << msg->getArrivalGate()->getIndex() << "\n";


        int maxVal;

        if(is_honest==0){
            // server acts maliciously
            maxVal=this->maxElement(subtaskArr)- intuniform(1, 5);
            EV << "Server " << getIndex() << " is acting MALICIOUSLY for subtask "
               << subtaskID << ". Sending incorrect result: " << maxVal << "\n";

        }
        else{
            //server is honest
            maxVal=this->maxElement(subtaskArr);

            EV << "Server " << getIndex() << " is acting HONESTLY for subtask "
               << subtaskID << ". Sending correct result: " << maxVal << "\n";

        }


        SubtaskReply *reply_msg = new SubtaskReply();
        reply_msg->setSubtaskID(subtaskID);
        reply_msg->setServerID(serverID);
        reply_msg->setResult(maxVal);


        int clientGateIndex = msg->getArrivalGate()->getIndex();
        send(reply_msg, "out", clientGateIndex);

        EV << "Server " << getIndex() << " sending result " << maxVal
           << " for subtask " << subtaskID << " to client via gate " << clientGateIndex << "\n";


    }
}




int Server::maxElement(vector<int> & arr){
    int maxi=arr[0];

    for(auto it:arr){
        maxi=max(maxi,it);
    }

    return maxi;
}
