#include "Movie.h"

#include <string>
#include <vector>
#include<iostream>
using namespace std;

Movie::Movie(const string& id, const string& title, const string& release_year,
             const vector<string>& directors, const vector<string>& actors,
             const vector<string>& genres, float rating)
{
    m_id = id;
    m_title = title;
    m_release_year = release_year;
    m_rating = rating;
    for(std::vector<std::string>::const_iterator it = directors.begin(); it != directors.end(); it++)
    {
        m_directors.push_back(*it);
    }
    for(std::vector<std::string>::const_iterator it = actors.begin(); it != actors.end(); it++)
    {
        m_actors.push_back(*it);
    }
    for(std::vector<std::string>::const_iterator it = genres.begin(); it != genres.end(); it++)
    {
        m_genres.push_back(*it);
    }
}

string Movie::get_id() const
{
    string temp_id = "";
    for(int i = 0; i < m_id.size(); i++)
    {
        temp_id += tolower(m_id.at(i));
    }
    return temp_id; 
}

string Movie::get_title() const
{
    return m_title;
}

string Movie::get_release_year() const
{
    return m_release_year;
}

float Movie::get_rating() const
{
    return m_rating;
}

vector<string> Movie::get_directors() const
{
    return m_directors;
}

vector<string> Movie::get_actors() const
{
    return m_actors;
}

vector<string> Movie::get_genres() const
{
    return m_genres;
}
