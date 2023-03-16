#include "Recommender.h"
#include "User.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    udb = &user_database;
    mdb = &movie_database;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    vector<MovieAndRank> final_movies;
    unordered_map<Movie*, int> m_movies;
    vector<string> directors; //unordered_map<string, string> directors; //mapping from movie it to director
    vector<string> genres;
    vector<string> actors;
    unordered_set<string> movie_history;
    
    const User* u = udb->get_user_from_email(user_email);
    vector<string> history = u->get_watch_history();
    for(vector<string>::iterator it = history.begin(); it != history.end(); it++)
    {
        string movie = "";
        for(int i = 0; i < (*it).size(); i++)
        {
            movie += tolower((*it).at(i));
        }
        movie_history.insert(movie);
        vector<string> d = (mdb->get_movie_from_id(movie))->get_directors();
        for(vector<string>::const_iterator i = d.begin(); i != d.end(); i++)
        {
            directors.push_back(*i);
        }
        vector<string> g = mdb->get_movie_from_id(movie)->get_genres();
        for(vector<string>::const_iterator i = g.begin(); i != g.end(); i++)
        {
            genres.push_back(*i);
        }
        vector<string> a = mdb->get_movie_from_id(movie)->get_actors();
        for(vector<string>::const_iterator i = a.begin(); i != a.end(); i++)
        {
            actors.push_back(*i);
        }
    } //go through watch history and gather all genres, directors, and actors related to every moving in watch history
    
    for(auto it: directors)
    {
        vector<Movie*> m1 = mdb->get_movies_with_director(it);
        for(auto j: m1) //for each director in movie history get the movie id
        {
            if(movie_history.find(j->get_id()) == movie_history.end()){
                auto key = m_movies.find(j);
                if(key == m_movies.end())
                {
                    m_movies.emplace(j,20); //if movie not present then add movie to set
                }else{
                    key->second += 20; //if movie present add 20 to existing score
                }
            }
        }
    }
    
    for(auto it: genres){
        vector<Movie*> m2 = mdb->get_movies_with_genre(it);
        for(auto j: m2)// for each genre in movie history get the movie id
        {
            if(movie_history.find(j->get_id()) == movie_history.end()){
                auto key = m_movies.find(j);
                if(key == m_movies.end()) //add to recommended movies
                {
                    m_movies.emplace(j,1);
                }else{
                    key->second += 1;
                }
            }
        }
    }
    
    for(auto it: actors){
        vector<Movie*> m3 = mdb->get_movies_with_actor(it);
        for(auto j: m3)//for each actor in movie history get the id
        {
            if(movie_history.find(j->get_id()) == movie_history.end()){
                auto key = m_movies.find(j);
                if(key == m_movies.end()) //add to recommended movies
                {
                    m_movies.emplace(j,30);
                }else{
                    key->second += 30;
                }
            }
        }
    }
    
    for(auto p: m_movies)
    {
        MovieAndRank* temp = new MovieAndRank(p.first->get_id(), p.second);
        final_movies.push_back(*temp);
    }
    
    sort(final_movies.begin(), final_movies.end(), [this](const MovieAndRank& m1, const MovieAndRank& m2){ //sort all the final movies based on compatability score then rating then title alphabetical
                if(m1.compatibility_score != m2.compatibility_score)
                {
                    return m1.compatibility_score > m2.compatibility_score;
                }
                Movie* temp1 = mdb->get_movie_from_id(m1.movie_id);
                Movie* temp2 = mdb->get_movie_from_id(m2.movie_id);
                if(temp1->get_rating() != temp2->get_rating())
                {
                    return temp1->get_rating() > temp2->get_rating();
                }
                return temp1->get_title() < temp2->get_title();
        });
    
    vector<MovieAndRank> recommended_movies;
    int count = 0;
    for(int i = 0; i < final_movies.size(); i++)
    {
        if(count < movie_count && final_movies[i].compatibility_score > 1){
            recommended_movies.push_back(final_movies[i]);
        } //as long as the final movies compatability score is greater than 1 and the count is less than the movie count then enter into final recommended movies vector to be returned
        count ++;
    }
    return recommended_movies;
}
