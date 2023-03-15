#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <fstream>
using namespace std;

UserDatabase::UserDatabase()
{
    loaded = false;// Replace this line with correct code.
}

UserDatabase::~UserDatabase()
{
    vector<User*>::iterator it = delete_reference.begin();
    while(it != delete_reference.end())
    {
        delete *it;
        it = delete_reference.erase(it);
    }
}

bool UserDatabase::load(const string& filename)
{
    if(loaded){
        return false;
    }
    string line = "";
    int line_number = 1;
    string name = "";
    string email = "";
    int num_movies = -1;
    vector<string> movie_ids;
    fstream file;
    file.open(filename);
    if(file.is_open()){
        while(getline(file, line, '\n'))
        {
            if(line == "")
            {
                if(name != "" && email != "")
                {
                    User* m_user = new User(name, email, movie_ids);
                    delete_reference.push_back(m_user);
                    tmm.insert(email,m_user);
                }
                line_number = 1;
                name = "";
                email = "";
                movie_ids.clear();
                continue;
            }
            if(line_number == 1)
            {
                name = line;
            }else if(line_number == 2)
            {
                email = line;
            }else if(line_number == 3)
            {
                num_movies = stoi(line);
            }else if(line_number > 3)
            {
                if(num_movies > 0)
                {
                    movie_ids.push_back(line);
                    num_movies --;
                }
            }
            line_number++;
        }
    }else{
        return false;
    }
    
    if(name != "" && email != "")
    {
        User* m_user = new User(name, email, movie_ids);
        delete_reference.push_back(m_user);
        tmm.insert(email, m_user);
    }
    file.close();
    loaded = true;
    return true;  
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    TreeMultimap<std::string, User*>::Iterator it = tmm.find(email);
    if(it.is_valid()){
        return it.get_value();
    }
    return nullptr;
}
