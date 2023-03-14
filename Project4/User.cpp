#include "User.h"

#include <string>
#include <vector>
using namespace std;

User::User(const string& full_name, const string& email,
           const vector<string>& watch_history)
{
    user_name = full_name;
    user_email = email;
    /*for(vector<string>::const_iterator it = watch_history.begin(); it != watch_history.end(); it++)
    {
        movie_history.push_back(*it);
    }*/
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
    return movie_history;
}

