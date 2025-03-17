
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

void Database::CreateUser(const User &user)
{
    work txn(*m_conn);
    txn.exec_params("INSERT INTO users (firstname, lastname, email, password, role) VALUES ($1, $2, $3, $4, $5)",
                    user.GetFirstname(), user.GetLastname(), user.GetEmail(), user.GetPassword(), user.GetRole());
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

void Database::UpdateUser(int id, const string &firstname, const string &lastname, const string &email)
{
    try
    {
        work txn(*m_conn);
        txn.exec_params("UPDATE users SET firstname = $1, lastname = $2, email = $3 WHERE id = $4",
                        firstname, lastname, email, id);
        txn.commit();
    }
    catch (const exception &e)
    {
        cerr << "Error updating user: " << e.what() << endl;
    }
}

void Database::DeleteUser( int id )
{
    work txn( *m_conn );
    txn.exec(
            "DELETE FROM users WHERE id = " + txn.quote(id)
            );
    txn.commit();
}

result Database::GetUserByEmail(const std::string &email) {
    work txn(*m_conn);
    return txn.exec_params("SELECT * FROM users WHERE email = $1", email);
}
