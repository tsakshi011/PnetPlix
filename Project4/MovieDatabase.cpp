#include "MovieDatabase.h"
#include "Movie.h"
#include <string>
#include <cctype>
#include <vector>
#include <fstream>
using namespace std;

MovieDatabase::MovieDatabase()
{
    m_loaded = false;// Replace this line with correct code.
}

MovieDatabase::~MovieDatabase()
{
    vector<Movie*>::iterator it = delete_reference.begin();
    while(it != delete_reference.end())
    {
        delete *it;
        it = delete_reference.erase(it);
    }
}

bool MovieDatabase::load(const string& filename)
{
    if(m_loaded){
        return false;
    }
    string line = "";
    int line_number = 1;
    string movie_id = "";
    string movie_name = "";
    string movie_release_year = "";
    vector<string> movie_directors;
    vector<string> movie_actors;
    vector<string> movie_genres;
    float movie_rating = 0;
    int movie_count = 0;
    fstream file;
            
    file.open(filename);
    if(file.is_open()){
        while(getline(file, line, '\n'))
        {
            if(line == "")
            {
                if(movie_id != "" && movie_name != "" && movie_release_year != ""){
                    Movie* m_movie = new Movie(movie_id, movie_name, movie_release_year, movie_directors, movie_actors, movie_genres, movie_rating);
                    string temp_id = "";
                    for(int i = 0; i < movie_id.size(); i++)
                    {
                        temp_id += tolower(movie_id.at(i));
                    }
                    tmm_ids.insert(temp_id, m_movie);
                    
                    for(vector<string>::iterator it = movie_directors.begin(); it != movie_directors.end(); it++)
                    {
                        string temp_director = "";
                        for(int i = 0; i < (*it).size(); i++)
                        {
                            temp_director += tolower((*it).at(i));
                        }
                        tmm_directors.insert(temp_director, m_movie);
                    }
                    for(vector<string>::iterator it = movie_actors.begin(); it != movie_actors.end(); it++)
                    {
                        string temp_actor = "";
                        for(int i = 0; i < (*it).size(); i++)
                        {
                            temp_actor += tolower((*it).at(i));
                        }
                        tmm_actors.insert(temp_actor, m_movie);
                    }
                    for(vector<string>::iterator it = movie_genres.begin(); it != movie_genres.end(); it++)
                    {
                        string temp_genre = "";
                        for(int i = 0; i < (*it).size(); i++)
                        {
                            temp_genre += tolower((*it).at(i));
                        }
                        tmm_genres.insert(temp_genre, m_movie);
                    }
                    getline(file, line, '\n');
                    //cerr << m_movie->get_title() << endl;
                    delete_reference.push_back(m_movie);
                }
                line_number = 1;
                movie_id = "";
                movie_name = "";
                movie_release_year = "";
                movie_rating = 0;
                movie_directors.clear();
                movie_actors.clear();
                movie_genres.clear();
                movie_count++;
            }
            if(line_number == 1)
            {
                movie_id = line;
            }else if(line_number == 2)
            {
                movie_name = line;
            }else if(line_number == 3)
            {
                movie_release_year = line;
            }else if(line_number == 4)
            {
                string director = "";
                for(int i = 0; i < line.size(); i++)
                {
                    if(line[i] == ',')
                    {
                        movie_directors.push_back(director);
                        director = "";
                    }else{
                        director += line[i];
                    }
                }
                movie_directors.push_back(director);
            }else if(line_number == 5)
            {
                //cerr << "actor " << line << endl;
                string actor = "";
                for(int i = 0; i < line.size(); i++)
                {
                    if(line[i] == ',')
                    {
                        movie_actors.push_back(actor);
                        actor = "";
                    }else{
                        actor += line[i];
                    }
                }
                movie_actors.push_back(actor);
            }else if(line_number == 6)
            {
                //cerr << "genre " << line << endl;
                string genre = "";
                for(int i = 0; i < line.size(); i++)
                {
                    if(line[i] == ',')
                    {
                        movie_genres.push_back(genre);
                        genre = "";
                    }else{
                        genre += line[i];
                    }
                }
                movie_genres.push_back(genre);
            }else if(line_number == 7)
            {
                //cerr << "rating " << line << endl;
                movie_rating = stof(line);
            }
            
            line_number++;
        }
    }else{
        return false;
    }
    
    if(movie_id != "" && movie_name != "" && movie_release_year != "")
    {
        Movie* m_movie = new Movie(movie_id, movie_name, movie_release_year, movie_directors, movie_actors, movie_genres, movie_rating);
        string temp_id = "";
        for(int i = 0; i < movie_id.size(); i++)
        {
            temp_id += tolower(movie_id.at(i));
        }
        tmm_ids.insert(temp_id, m_movie);
        for(vector<string>::iterator it = movie_directors.begin(); it != movie_directors.end(); it++)
        {
            string temp_director = "";
            for(int i = 0; i < (*it).size(); i++)
            {
                temp_director += tolower((*it).at(i));
            }
            tmm_directors.insert(temp_director, m_movie);
        }
        for(vector<string>::iterator it = movie_actors.begin(); it != movie_actors.end(); it++)
        {
            string temp_actor = "";
            for(int i = 0; i < (*it).size(); i++)
            {
                temp_actor += tolower((*it).at(i));
            }
            tmm_actors.insert(temp_actor, m_movie);
        }
        for(vector<string>::iterator it = movie_genres.begin(); it != movie_genres.end(); it++)
        {
            string temp_genre = "";
            for(int i = 0; i < (*it).size(); i++)
            {
                temp_genre += tolower((*it).at(i));
            }
            tmm_genres.insert(temp_genre, m_movie);
        }
        delete_reference.push_back(m_movie);
    }
    file.close();
    m_loaded = true;
    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    string temp_id = "";
    for(int i = 0; i < id.size(); i++)
    {
        temp_id += tolower(id.at(i));
    }
    
    TreeMultimap<std::string, Movie*>::Iterator it = tmm_ids.find(temp_id);
    if(it.is_valid()){
        return it.get_value();
    }
    return nullptr;
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    string temp_director = "";
    for(int i = 0; i < director.size(); i++)
    {
        temp_director += tolower(director.at(i));
    }
    
    TreeMultimap<std::string, Movie*>::Iterator it = tmm_directors.find(temp_director); //finds where directors associated with movies are and inserts them into vector
    vector<Movie*> movies_with_director;
    while(it.is_valid()){
        movies_with_director.push_back(it.get_value());
        it.advance();
    }
    return movies_with_director;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    string temp_actor = "";
    for(int i = 0; i < actor.size(); i++)
    {
        temp_actor += tolower(actor.at(i));
    }
    
    TreeMultimap<std::string, Movie*>::Iterator it = tmm_actors.find(temp_actor); //finds where actors associated with movies are and inserts them into vector
    vector<Movie*> movies_with_actor;
    while(it.is_valid()){
        movies_with_actor.push_back(it.get_value());
        it.advance();
    }
    return movies_with_actor;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    string temp_genre = "";
    for(int i = 0; i < genre.size(); i++)
    {
        temp_genre += tolower(genre.at(i));
    }
    
    TreeMultimap<std::string, Movie*>::Iterator it = tmm_genres.find(temp_genre); //finds where genres associated with movies are and inserts them into vector
    vector<Movie*> movies_with_genre;
    while(it.is_valid()){
        movies_with_genre.push_back(it.get_value());
        it.advance();
    }
    return movies_with_genre;
}
