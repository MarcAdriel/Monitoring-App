
#ifndef CRUD_USER_H
#define CRUD_USER_H

#include <string>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class User
{
public:
    User();
    ~User();
    User( int id, const string &firstname, const string &lastname,
          const string &email, const string &password, const string &role );

    string ToJson() const;
    static User FromJson(const string &jsonString);

    int GetId() const;
    string GetFirstname() const;
    string GetLastname() const;
    string GetEmail() const;
    string GetPassword() const;
    string GetRole() const;

    void SetId( int id );
    void SetFirstname( const string &firstname );
    void SetLastname( const string &lastname );
    void SetEmail( const string &email );
    void SetPassword( const string &password );
    void SetRole( const string &role );

private:
    int m_id;
    string m_firstname;
    string m_lastname;
    string m_email;
    string m_password;
    string m_role;
};

#endif //CRUD_USER_H
