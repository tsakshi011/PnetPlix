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
    //MovieAndRank* m = new MovieAndRank("hello", 1);
    vector<MovieAndRank> final_movies;
    unordered_map<Movie*, int> m_movies;
    //unordered_map<string, string> directors; //mapping from movie it to director
    vector<string> directors;
    vector<string> genres;
    vector<string> actors;
    unordered_set<string> movie_history;
    
    const User* u = udb->get_user_from_email(user_email);
    std::cerr << u->get_full_name() << std::endl;
    vector<string> history = u->get_watch_history();
    for(vector<string>::iterator it = history.begin(); it != history.end(); it++)
    {
        movie_history.insert(*it);
        //cerr << "ID " << *it << endl;
        vector<string> d = (mdb->get_movie_from_id(*it))->get_directors();
        for(vector<string>::const_iterator i = d.begin(); i != d.end(); i++)
        {
            //directors.emplace(*it, *i);
            directors.push_back(*i);
        }
        vector<string> g = mdb->get_movie_from_id(*it)->get_genres();
        for(vector<string>::const_iterator i = g.begin(); i != g.end(); i++)
        {
            genres.push_back(*i);
        }
        vector<string> a = mdb->get_movie_from_id(*it)->get_actors();
        for(vector<string>::const_iterator i = a.begin(); i != a.end(); i++)
        {
            actors.push_back(*i);
        }
    }
    
    for(auto it: directors)
    {
        //vector<Movie*> m1 = mdb.get_movies_with_director(it.second);
        vector<Movie*> m1 = mdb->get_movies_with_director(it);
        for(auto j: m1)
        {
            //cerr << j->get_title() << endl;
            if(movie_history.find(j->get_id()) == movie_history.end()){
                auto key = m_movies.find(j);
                if(key == m_movies.end())
                {
                    m_movies.emplace(j,20);
                }else{
                    key->second += 20;
                }
            }
        }
    }
    
    for(auto it: genres){
        //vector<Movie*> m2 = mdb.get_movies_with_genre(it.second);
        vector<Movie*> m2 = mdb->get_movies_with_genre(it);
        for(auto j: m2)
        {
            if(movie_history.find(j->get_id()) == movie_history.end()){
                auto key = m_movies.find(j);
                if(key == m_movies.end())
                {
                    m_movies.emplace(j,1);
                }else{
                    key->second += 1;
                }
            }
        }
    }
    
    for(auto it: actors){
        //vector<Movie*> m3 = mdb.get_movies_with_actor(it.second);
        vector<Movie*> m3 = mdb->get_movies_with_actor(it);
        for(auto j: m3)
        {
            if(movie_history.find(j->get_id()) == movie_history.end()){
                auto key = m_movies.find(j);
                if(key == m_movies.end())
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
    
    sort(final_movies.begin(), final_movies.end(), [this](const MovieAndRank& m1, const MovieAndRank& m2){
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
                return temp1->get_title() > temp2->get_title();
        });
    
    return final_movies;  // Replace this line with correct code.
}
