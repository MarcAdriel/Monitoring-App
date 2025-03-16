
#include "../Header/Database.h"

Database::Database()
{
    try
    {
        m_conn = new pqxx::connection("dbname=crud_db user=postgres password=root host=db port=5432");


        if ( !m_conn -> is_open() )
        {
            throw runtime_error("Database connection failed");
        }
    }
    catch ( const exception &e )
    {
        cerr << "Database error: " << e.what() << endl;
    }
}

Database::~Database()
{
    if ( m_conn != nullptr )
    {
        delete m_conn;
    }
}

void Database::CreateUser(const string &name, int age)
{
    work txn( *m_conn );
    txn.exec(
            "INSERT INTO users (name, age) VALUES (" + txn.quote(name) + "," + txn.quote(age) + ")"
            );
    txn.commit();
}

result Database::GetUsers()
{
    work tnx( *m_conn );
    return tnx.exec(
            "SELECT * FROM users"
            );
}

result Database::GetUserById( int id )
{
    work txn( *m_conn );
    return txn.exec(
            "SELECT * FROM users WHERE id = " + txn.quote( id )
            );
}

void Database::UpdateUser( int id, const string &name, int age )
{
    work txn( *m_conn );
    txn.exec(
            "UPDATE users SET name = " + txn.quote(name) + ", age = " + txn.quote(age) + "WHERE id = " + txn.quote(id)
            );
    txn.commit();
}

void Database::DeleteUser( int id )
{
    work txn( *m_conn );
    txn.exec(
            "DELETE FROM users WHERE id = " + txn.quote(id)
            );
    txn.commit();
}