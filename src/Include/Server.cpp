
#include "../Header/Server.h"

Server::Server(Address addr) {
    httpEndpoint = std::make_shared<Http::Endpoint>(addr);
}

void Server::setupRoutes() {
    using namespace Rest;
    Routes::Post(router, "/users", Routes::bind(&Server::handleCreateUser, this));
    Routes::Get(router, "/users", Routes::bind(&Server::handleGetUsers, this));
}

void Server::start() {
    setupRoutes();
    httpEndpoint->init(Http::Endpoint::options().threads(1));
    httpEndpoint->setHandler(router.handler());
    httpEndpoint->serve();
}

void Server::handleCreateUser(const Rest::Request &request, Http::ResponseWriter response) {
    auto body = json::parse(request.body());
    database.CreateUser(body["name"], body["age"]);
    response.send(Http::Code::Created, "User created");
}

void Server::handleGetUsers(const Rest::Request &, Http::ResponseWriter response) {
    auto res = database.GetUsers();
    json j;
    for (auto row : res) {
        j.push_back({{"id", row["id"].as<int>()}, {"name", row["name"].as<std::string>()}, {"age", row["age"].as<int>()}});
    }
    response.send(Http::Code::Ok, j.dump());
}