#include <iostream>
#include <pistache/endpoint.h>
#include "Header/Server.h"

using namespace std;

Server* globalServerPtr = nullptr;

void handleSignal(int signal) {
    if (globalServerPtr) {
        cout << "\n🛑 Received termination signal (" << signal << "). Stopping server..." << endl;
        globalServerPtr->shutdown();
    }
    exit(0);
}

int main() {
    try {
        Pistache::Address addr( Pistache::Ipv4::any(), Pistache::Port(8080) );
        Server server(addr);
        globalServerPtr = &server;

        signal(SIGINT, handleSignal);
        signal(SIGTERM, handleSignal);

        cout << "Starting C++ Pistache Server on port 8080" << endl;
        server.start();
    }
    catch ( const exception &e )
    {
        cerr << "Server error: " << e.what() << endl;
    }
    return 0;
}
