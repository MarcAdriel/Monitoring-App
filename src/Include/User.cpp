
#include "../Header/User.h"

User::User() : m_id(0), m_firstname(""), m_lastname(""),
m_email(""), m_password(""), m_role("user") {}

User::~User() {}

User::User(int id, const string &firstname, const string &lastname, const string &email,
           const string &password, const string &role) :
           m_id(id), m_firstname(firstname), m_lastname(lastname),
           m_email(email), m_password(password), m_role(role) {}

string User::ToJson() const
{
    json j;
    j["id"] = m_id;
    j["firstname"] = m_firstname;
    j["lastname"] = m_lastname;
    j["email"] = m_email;
    j["role"] = m_role;
    return j.dump();
}

User User::FromJson(const string &jsonString) {
    json j = json::parse(jsonString);
    return User(
            j.value("id", 0),
            j.value("firstname", ""),
            j.value("lastname", ""),
            j.value("email", ""),
            j.value("password", ""),
            j.value("role", "user")
    );
}

int User::GetId() const
{
    return m_id;
}

string User::GetFirstname() const
{
    return m_firstname;
}

string User::GetLastname() const
{
    return m_lastname;
}

string User::GetEmail() const
{
    return m_email;
}

string User::GetPassword() const
{
    return m_password;
}

string User::GetRole() const
{
    return m_role;
}

void User::SetId( int id )
{
    m_id = id;
}

void User::SetFirstname( const string &firstname )
{
    m_firstname = firstname;
}

void User::SetLastname( const string &lastname )
{
    m_lastname = lastname;
}

void User::SetEmail( const string &email )
{
    m_email = email;
}

void User::SetPassword( const string &password )
{
    m_password = password;
}

void User::SetRole( const string &role )
{
    m_role = role;
}



