
#ifndef CRUD_SERVER_H
#define CRUD_SERVER_H

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include "Database.h"

using namespace Pistache;
using json = nlohmann::json;

using namespace std;

class Server {
public:
    explicit Server(Pistache::Address addr);
    void start();

private:
    void setupRoutes();
    void handleCreateUser(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void handleGetUsers(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);

    std::shared_ptr<Pistache::Http::Endpoint> httpEndpoint;
    Pistache::Rest::Router router;
    Database database;
};

#endif //CRUD_SERVER_H
