# **Client-Server Network with Malicious Server Functionality**

\-By [Pari Sharma (B22CS039)](mailto:b22cs039@iitj.ac.in)

1. # **Overview**

In this project, we implement a peer-to-peer network with two types of nodes: Client nodes and Server nodes. The clients distribute computational tasks among servers, and servers process these tasks collaboratively. The system ensures resilience against malicious servers using majority voting and a controlled selection mechanism for malicious behavior.

### **1.1 Client nodes:**

* Divide computational tasks into subtasks.  
* Distribute each subtask to a subset of servers.  
* Collect responses and perform majority voting for correctness.  
* Gossip scores with peer clients to maintain reputation metrics.  
* Finally selecting the top servers and calculating the maximum value of the task.

### **1.2 Server nodes:**

* Receive subtasks from clients and compute results.  
* Reply to clients with computed results.  
* Some servers may behave maliciously 

2. ## **Project Structure**

├── client.cc          \# Client node implementation

├── server.cc          \# Server node implementation

├── message.msg        \# Message definitions for OMNeT++

├──connections.ned        \# Network topology definition

├──omnetpp.ini         \# Configuration settings for simulation

├── client\_debug\_log.txt  \# Log file for client operations

└── server\_debug\_log.txt  \# Log file for server operations

3. ## **Code Explanation**

### **3.1 Client Class Data Members**

* `mapp`: Stores subtask results received from servers.  
* `subtask_completed`: Tracks the number of completed subtasks.  
* `taskDone`: Indicates if the complete task is finished.  
* `cumulative_result`: Stores the cumulative result of all subtasks.  
* `secondRoundgoing`: Indicates if the second round of computation is in progress.  
* `task`: Vector storing the main task to be divided.  
* `topServers`: Set of selected servers for subtask distribution.  
* `start_ind`: Initial server assignment index( to decide malicious or honest)  
* `score[n]`: Stores individual scores of clients.  
* `avg_score[n]`: Stores accumulated scores for averaging.  
* `receivedMessages`: Set to track already broadcasted messages.

### **3.2 Server Class Data Members**

* `serverID`: Unique identifier for each server.  
* `isMalicious`: Boolean flag indicating if a server is malicious.  
* `subtasks`: Stores incoming subtasks.  
* `results`: Stores computed results.

### **3.3 Client Class Methods**

* `beginSecondRound()`: Clears previous results, reinitializes subtask management, and redistributes subtasks to selected servers, ensuring some servers act maliciously.  
* `broadcastScores()`: Constructs a gossip message containing client scores and broadcasts it to peer clients while avoiding redundant messages.  
* `majorityVoting()`: Performs a majority vote on received subtask results to determine the final result, reducing the effect of malicious responses.

### **3.4 Server Class Methods**

* `handleSubtaskRequest()`: Processes received subtasks and computes or manipulates the result if the server is malicious.  
* `sendReply()`: Sends computed results back to the client.

##  

### **3.5 Malicious Server Functionality**

* Each server receives a `choose` value, which starts from `start_ind` and increments sequentially.  
* The server is assigned `choose % 4`, determining its malicious status.  
* If `choose % 4 == 0`, the server is marked as malicious.  
* Given `n/2+1 = 6`, the total number of servers (`n`) is 10\.  
* The number of malicious servers is limited to `n/4`, ensuring a maximum of `2` malicious servers at any time.

### **3.6 Message Structure (message.msg)**

The system defines three custom messages to facilitate communication between clients and servers.

1. **SubtaskRequest**  
   * `int subtaskID`: Unique identifier for each subtask.  
   * `string subtaskArr`: Serialized subtask data.  
   * `int serverID`: Server assigned to process the subtask.  
   * `bool isMalicious`: Indicates whether the server processing the subtask is malicious.  
2. **SubtaskReply**  
   * `int subtaskID`: ID of the completed subtask.  
   * `int result`: Computed result of the subtask.  
   * `int serverID`: ID of the server that processed the subtask.  
3. **GossipMessage**  
   * `string content`: Message content used for score sharing among clients.  
     

### **3.7.ned File (Network Topology)**

The `.ned` file defines the network structure and connections between **clients** and **servers** in the simulation. The key aspects of the `.ned` file are:

1. **Client-Server Connections**  
   * Each client is connected to all servers to distribute tasks effectively.  
   * Clients send subtasks to servers and receive computed results.

2. **Client-Client Circular Topology**  
   * Clients are arranged in a circular fashion, meaning each client is connected to two other clients:  
     * C1 is connected to C0 and C2  
     * C2 is connected to C1 and C3, and so on.  
   * This ensures efficient gossip propagation while preventing isolated clients.

3. **Message Flow Management**  
   * Each client maintains a message list to prevent infinite message loops.  
   * When a client receives a gossip message, it checks if the message was seen before. If yes, it discards it; otherwise, it forwards it.

4. **Dynamic Network Creation**  
   * The `.ned` file does not define a fixed number of clients and servers. Instead, it uses placeholders (NUM\_CLIENTS, NUM\_SERVERS) so that the actual number is set dynamically via the `.ini` file.

### **3.8 .ini File (Network Configuration)**

The .ini file controls the dynamic initialization of the network by specifying:

1. **Number of Clients and Servers**  
   * Example: NUM\_CLIENTS \= 5, NUM\_SERVERS \= 10  
   * These values are used in the .ned file to create the network dynamically.  
2. **Malicious Server Selection**  
   * The algorithm ensures that only at most n/4 servers are malicious at any time.  
   * The .ini file specifies:  
     * A starting index (start\_ind) to determine which servers may be malicious.  
     * Each server gets assigned choose \= start\_ind \+ i, and the malicious servers are the ones where choose % 4 \== 0\.  
3. **Gossip Message Behavior**  
   * Defines gossip intervals, i.e., how often clients broadcast their collected scores.  
   * Controls message propagation delay to simulate network latency.  
4. **Task Execution Rounds**  
   * The simulation is set to run for two rounds:  
     * Round 1: Tasks are distributed randomly among servers.  
     * Round 2: Tasks are assigned based on gossip scores collected in Round 1\.

## **4\. Message Workflow**

1. **Task Assignment:** Each client splits a task into subtasks and assigns them to `n/2 + 1` servers.  
2. **Malicious Response Handling:** Clients collect responses and apply **majority voting** to filter incorrect results.  
3. **Gossiping Scores:** Clients broadcast server scores using **Gossip Protocol** to update the network.  
4. **New Task Round:** The top `n/2 + 1` servers with the highest scores are selected for the next round.  
   

## **5\. Running the project**

* To compile and run the simulation, first open the terminal and navigate to the OMNeT++ project folder using **`cd omnet_project_folder`**`.`   
* Set the environment variables by running **`source setenv`**.  
*  After that, launch the OMNeT++ IDE by typing `omnetpp`.  
*  Once the IDE is open, **modify the `.ini` file to specify the required number of clients, servers, and tasks.**   
* Finally, run the simulation using the **Run** button in OMNeT++.
