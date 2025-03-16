
#ifndef CRUD_DATABASE_H
#define CRUD_DATABASE_H

#include <iostream>
#include <pqxx/pqxx>
#include <string>

using namespace std;
using namespace pqxx;

class Database
{
public:
    Database();
    ~Database();

    void CreateUser( const string &name, int age );
    result GetUsers();
    result GetUserById( int id );
    void UpdateUser( int id, const string &name, int age );
    void DeleteUser( int id );
private:
    pqxx::connection *m_conn;
};

#endif //CRUD_DATABASE_H
