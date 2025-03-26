package try1;

import ned.IdealChannel;

network Connections
{
    parameters:
        int numClients;
        int numServers;

    types:
        simple Client
        {
            parameters:
                string task;  // Removed default value to ensure it's set explicitly
                string IP;
                

            gates:
                input in[]; // Vector gate for server-to-client connections
                output out[]; // Vector gate for client-to-server connections
                input peerIn[]; // Vector gate for client-to-client input
                output peerOut[]; // Vector gate for client-to-client output
        }

        simple Server
        {
            gates:
                input in[]; // Vector gate for client-to-server connections
                output out[]; // Vector gate for server-to-client connections
        }

    submodules:
        clients[numClients]: Client {
            parameters:
                task = default("");  // Default empty task for all clients
        }
        servers[numServers]: Server;

    connections allowunconnected:
        // Each client connects to all servers using vector gates
        for i=0..numClients-1, for j=0..numServers-1 {
            clients[i].out++ --> IdealChannel --> servers[j].in++;
            servers[j].out++ --> IdealChannel --> clients[i].in++;
        }

        // All clients are connected together in a ring
        for i=0..numClients-1 {
            clients[i].peerOut++ --> IdealChannel --> clients[(i+1)%numClients].peerIn++;
            clients[(i+1)%numClients].peerOut++ --> IdealChannel --> clients[i].peerIn++;
        }
}