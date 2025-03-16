#include <iostream>
#include <pistache/endpoint.h>
#include "Header/Server.h"

int main() {
    try {
        Pistache::Address addr( Pistache::Ipv4::any(), Pistache::Port(8080) );
        Server server(addr);

        cout << "Starting C++ Pistache Server on port 8080" << endl;
        server.start();
    }
    catch ( const exception &e )
    {
        cerr << "Server error: " << e.what() << endl;
    }
    return 0;
}
