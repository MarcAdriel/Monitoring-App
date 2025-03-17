
#ifndef CRUD_JWTUTIL_H
#define CRUD_JWTUTIL_H

#include <string>
#include <iostream>
#include <jwt-cpp/jwt.h>

using namespace std;

class JwtUtil
{
public:
    static string GenerateToken(const string &email, const string &role);
    static bool VerifyToken(const string &token, string &role, string &email);
    static string GetRoleFromToken(const string &token);
};

#endif //CRUD_JWTUTIL_H
