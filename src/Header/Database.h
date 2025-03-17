
#ifndef CRUD_DATABASE_H
#define CRUD_DATABASE_H

#include <iostream>
#include <pqxx/pqxx>
#include <string>

#include "User.h"

using namespace std;
using namespace pqxx;

class Database
{
public:
    Database();
    ~Database();

    void CreateUser( const User &user );
    result GetUsers();
    result GetUserById( int id );
    void UpdateUser(int id, const string &firstname, const string &lastname, const string &email);
    void DeleteUser( int id );

    result GetUserByEmail( const string &email );

private:
    pqxx::connection *m_conn;
};

#endif //CRUD_DATABASE_H
