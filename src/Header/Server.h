
#ifndef CRUD_SERVER_H
#define CRUD_SERVER_H

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include "Database.h"
#include "JwtUtil.h"

using namespace Pistache;
using json = nlohmann::json;

using namespace std;

class Server {
public:
    explicit Server(Pistache::Address addr);
    void start();
    void shutdown();

private:
    void setupRoutes();
    void handleRegister(const Rest::Request &request, Http::ResponseWriter response);
    void handleLogin(const Rest::Request &request, Http::ResponseWriter response);
    void handleGetUsers(const Rest::Request &request, Http::ResponseWriter response);
    void handleGetUserById(const Rest::Request &request, Http::ResponseWriter response);
    void handleUpdateUser(const Rest::Request &request, Http::ResponseWriter response);
    void handleDeleteUser(const Rest::Request &request, Http::ResponseWriter response);

    bool isAuthorized(const string &token, const string &requiredRole);

    shared_ptr<Http::Endpoint> httpEndpoint;
    Rest::Router router;
    Database database;
};

#endif //CRUD_SERVER_H
