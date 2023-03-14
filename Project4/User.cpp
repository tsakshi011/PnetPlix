#include "User.h"

#include <string>
#include <iostream>
#include <vector>
using namespace std;

User::User(const string& full_name, const string& email,
           const vector<string>& watch_history)
{
    user_name = full_name;
    user_email = email;
    movie_history = watch_history;
}

string User::get_full_name() const
{
    return user_name;
}

string User::get_email() const
{
    return user_email;
}

vector<string> User::get_watch_history() const
{
    //return vector<string>();
    //cerr << "HERE " << endl;
    //cerr << "SIZE " << movie_history.size() << endl;
    return movie_history;
}

