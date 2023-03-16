#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <fstream>
using namespace std;

UserDatabase::UserDatabase()
{
    loaded = false; //database loaded or not
}

UserDatabase::~UserDatabase() //destructor deleting new allocated Users
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
                if(name != "" && email != "") //if data present then user is present and must be created
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
            if(line_number == 1) //each file patter 1 has the name, 2 has email, 3 has number of movies watched, and 4 after has each movie_id
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
                    string temp_movie = "";
                    for(int i = 0; i < line.size(); i++)
                    {
                        temp_movie += tolower(line.at(i));
                    }
                    movie_ids.push_back(temp_movie);
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
