#include "../Header/Server.h"

Server::Server(Address addr) {
    httpEndpoint = make_shared<Http::Endpoint>(addr);
}

void Server::setupRoutes() {
    using namespace Rest;
    Routes::Post(router, "/register", Routes::bind(&Server::handleRegister, this));
    Routes::Post(router, "/login", Routes::bind(&Server::handleLogin, this));
    Routes::Get(router, "/users", Routes::bind(&Server::handleGetUsers, this));
    Routes::Get(router, "/users/:id", Routes::bind(&Server::handleGetUserById, this));
    Routes::Put(router, "/users/:id", Routes::bind(&Server::handleUpdateUser, this));
    Routes::Delete(router, "/users/:id", Routes::bind(&Server::handleDeleteUser, this));
}

void Server::start() {
    setupRoutes();
    httpEndpoint->init(Http::Endpoint::options().threads(1));
    httpEndpoint->setHandler(router.handler());
    httpEndpoint->serve();
}

void Server::shutdown() {
    cout << "Stopping server gracefully..." << endl;
    httpEndpoint->shutdown();
}

void Server::handleRegister(const Rest::Request &request, Http::ResponseWriter response) {
    auto body = json::parse(request.body());

    if (!body.contains("firstname") || !body.contains("lastname") ||
        !body.contains("email") || !body.contains("password") || !body.contains("role")) {
        response.send(Http::Code::Bad_Request, "Missing required fields");
        return;
    }

    User newUser(0, body["firstname"], body["lastname"], body["email"], body["password"], body["role"]);

    // Save user to database
    database.CreateUser(newUser);
    response.send(Http::Code::Created, "User registered successfully");
}


void Server::handleLogin(const Rest::Request &request, Http::ResponseWriter response) {
    auto body = json::parse(request.body());
    string email = body["email"];
    string password = body["password"];

    auto res = database.GetUserByEmail(email);
    if (res.empty()) {
        response.send(Http::Code::Unauthorized, "Invalid credentials");
        return;
    }

    string storedPassword = res[0]["password"].as<string>();
    if (storedPassword != password) {
        response.send(Http::Code::Unauthorized, "Invalid credentials");
        return;
    }

    string token = JwtUtil::GenerateToken(email, res[0]["role"].as<string>());
    response.send(Http::Code::Ok, json({{"token", token}}).dump());
}

void Server::handleGetUsers(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    auto authHeader = request.headers().tryGetRaw("Authorization");
    std::string token = authHeader.has_value() ? authHeader->value() : "";

    if (token.empty()) {
        response.send(Http::Code::Unauthorized, "Missing Authorization token");
        return;
    }

    // Remove "Bearer " prefix if present
    if (token.find("Bearer ") == 0) {
        token = token.substr(7);
    }

    std::string role, email;
    if (!JwtUtil::VerifyToken(token, role, email)) {
        response.send(Http::Code::Unauthorized, "Invalid JWT signature");
        return;
    }

    // Check role permissions (Only admin can list users)
    if (role != "admin") {
        response.send(Http::Code::Forbidden, "Access denied: Admin role required");
        return;
    }

    // Fetch and return user list
    auto res = database.GetUsers();
    json j;
    for (auto row : res) {
        j.push_back({
                            {"id", row["id"].as<int>()},
                            {"firstname", row["firstname"].as<std::string>()},
                            {"lastname", row["lastname"].as<std::string>()},
                            {"email", row["email"].as<std::string>()},
                            {"role", row["role"].as<std::string>()}
                    });
    }
    response.send(Http::Code::Ok, j.dump());
}


void Server::handleGetUserById(const Rest::Request &request, Http::ResponseWriter response) {
    int id = stoi(request.param(":id").as<string>());
    auto res = database.GetUserById(id);
    if (res.empty()) {
        response.send(Http::Code::Not_Found, "User not found");
        return;
    }

    json j = {{"id", res[0]["id"].as<int>()}, {"firstname", res[0]["firstname"].as<string>()},
              {"lastname", res[0]["lastname"].as<string>()}, {"email", res[0]["email"].as<string>()}};
    response.send(Http::Code::Ok, j.dump());
}

void Server::handleUpdateUser(const Rest::Request &request, Http::ResponseWriter response) {
    int id = stoi(request.param(":id").as<string>());
    auto body = json::parse(request.body());

    database.UpdateUser(id, body["firstname"], body["lastname"], body["email"]);
    response.send(Http::Code::Ok, "User updated successfully");
}

void Server::handleDeleteUser(const Rest::Request &request, Http::ResponseWriter response) {
    int id = stoi(request.param(":id").as<string>());

    database.DeleteUser(id);
    response.send(Http::Code::Ok, "User deleted successfully");
}

bool Server::isAuthorized(const string &token, const string &requiredRole) {
    string role, email;

    // Verify the JWT token and extract role and email
    if (!JwtUtil::VerifyToken(token, role, email)) {
        return false;
    }

    if (role == "admin" || role == requiredRole) {
        return true;
    }

    return false;
}