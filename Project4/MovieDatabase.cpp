#include "MovieDatabase.h"

#include <string>
#include <vector>
#include <fstream>
using namespace std;

MovieDatabase::MovieDatabase()
{
    m_loaded = false;// Replace this line with correct code.
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
                if(movie_id != "" && movie_name != ""){
                    Movie* m_movie = new Movie(movie_id, movie_name, movie_release_year, movie_directors, movie_actors, movie_genres, movie_rating);
                    tmm_ids.insert(movie_id, m_movie);
                    for(vector<string>::iterator it = movie_directors.begin(); it != movie_directors.end(); it++)
                    {
                        tmm_directors.insert(*it, m_movie);
                    }
                    for(vector<string>::iterator it = movie_actors.begin(); it != movie_actors.end(); it++)
                    {
                        tmm_actors.insert(*it, m_movie);
                    }
                    for(vector<string>::iterator it = movie_genres.begin(); it != movie_genres.end(); it++)
                    {
                        tmm_genres.insert(*it, m_movie);
                        //cerr << *it << endl;
                    }
                    //cerr << "END" << endl;
                    //cerr << "HERE" << endl;
                    getline(file, line, '\n');
                    //delete_reference.push_back(m_user);
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
                //cerr << line_number << endl;
            }
            if(line_number == 1)
            {
                //cerr << "id " << line << endl;
                movie_id = line;
            }else if(line_number == 2)
            {
                //cerr << "name " << line << endl;
                movie_name = line;
            }else if(line_number == 3)
            {
                //cerr << "release " << line << endl;
                movie_release_year = line;
            }else if(line_number == 4)
            {
                //cerr << "director " << line << endl;
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
            //cerr << "HERE " << movie_count << endl;
            /*if(movie_count > 31)
             {
             cerr << "HERE" << endl;
             return true;
             }*/
        }
    }else{
        return false;
    }
    
    if(line == " ")
    {
        cerr << "HERE " << line_number << endl;
        cerr << line << endl;
        Movie* m_movie = new Movie(movie_id, movie_name, movie_release_year, movie_directors, movie_actors, movie_genres, movie_rating);
        tmm_ids.insert(movie_id, m_movie);
        for(vector<string>::iterator it = movie_directors.begin(); it != movie_directors.end(); it++)
        {
            tmm_directors.insert(*it, m_movie);
        }
        for(vector<string>::iterator it = movie_actors.begin(); it != movie_actors.end(); it++)
        {
            tmm_actors.insert(*it, m_movie);
        }
        for(vector<string>::iterator it = movie_genres.begin(); it != movie_genres.end(); it++)
        {
            tmm_genres.insert(*it, m_movie);
        }
        //delete_reference.push_back(m_user);
    }
    file.close();
    m_loaded = true;
    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    TreeMultimap<std::string, Movie*>::Iterator it = tmm_ids.find(id);
    if(it.is_valid()){
        return it.get_value();
    }
    return nullptr;
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    TreeMultimap<std::string, Movie*>::Iterator it = tmm_directors.find(director);
    vector<Movie*> movies_with_director;
    while(it.is_valid()){
        movies_with_director.push_back(it.get_value());
        it.advance();
    }
    return movies_with_director;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    TreeMultimap<std::string, Movie*>::Iterator it = tmm_actors.find(actor);
    vector<Movie*> movies_with_actor;
    while(it.is_valid()){
        movies_with_actor.push_back(it.get_value());
        it.advance();
    }
    return movies_with_actor;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    TreeMultimap<std::string, Movie*>::Iterator it = tmm_genres.find(genre);
    vector<Movie*> movies_with_genre;
    while(it.is_valid()){
        movies_with_genre.push_back(it.get_value());
        it.advance();
    }
    return movies_with_genre;
}
