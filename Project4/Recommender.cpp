#include "Recommender.h"
#include "User.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    // Replace this line with correct code.
    /*sort(answer.begin(), answer.end(), compareMovieAndRank);
    if(answer.size() > movie_count);*/
    udb = user_database;
    mdb = movie_database;
}

bool Recommender::compare(const MovieAndRank m1, const MovieAndRank m2)
{
    if(m1.compatability_score != m2.compatability_score)
    {
        return m1.compatibility_score < m2.compatibility_score;
    }
    Movie* movie1 = movies->get_movie_from_id(m1.movie_id);
    Movie* movie2 = movies->get_ovie_from_id(m2.movie_id);
    if(movie1->get_rating() != movie2->get_rating())
    {
        return movie1->get_rating() < movie2_get_rating();
    }
    return movie1->get_title() < movie2->get_title();
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
    
    User* u = udb.get_user_from_email(user_email);
    std::cerr << u->get_full_name() << std::endl;
    vector<string> history = u->get_watch_history();
    for(vector<string>::iterator it = history.begin(); it != history.end(); it++)
    {
        movie_history.insert(*it);
        //cerr << "ID " << *it << endl;
        vector<string> d = (mdb.get_movie_from_id(*it))->get_directors();
        for(vector<string>::const_iterator i = d.begin(); i != d.end(); i++)
        {
            //directors.emplace(*it, *i);
            directors.push_back(*i);
        }
        vector<string> g = mdb.get_movie_from_id(*it)->get_genres();
        for(vector<string>::const_iterator i = g.begin(); i != g.end(); i++)
        {
            genres.push_back(*i);
        }
        vector<string> a = mdb.get_movie_from_id(*it)->get_actors();
        for(vector<string>::const_iterator i = a.begin(); i != a.end(); i++)
        {
            actors.push_back(*i);
        }
    }
    
    for(auto it: directors)
    {
        //vector<Movie*> m1 = mdb.get_movies_with_director(it.second);
        vector<Movie*> m1 = mdb.get_movies_with_director(it);
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
        vector<Movie*> m2 = mdb.get_movies_with_genre(it);
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
        vector<Movie*> m3 = mdb.get_movies_with_actor(it);
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
    /*for(auto p: m_movies)
    {
        cerr << "Title " << p.first->get_title() << " " << p.second << endl;
    }*/
    for(auto p: m_movies)
    {
        MovieAndRank* temp = new MovieAndRank(p.first->get_id(), p.second);
        final_movies.push_back(*temp);
    }
    
    /*for(auto p: final_movies)
    {
        cerr << p << endl;
    }*/
    
    sort(final_movies.begin(), final_movies.end(), compare());
    
    return final_movies;  // Replace this line with correct code.
}


/*
 vector<std::string> history = u->get_watch_history();
 for(vector<std::string>::iterator it = history.begin(); it != history.end(); it++)
 {
     vector<std::string> director = mdb.get_movie_from_id(*it)->get_directors();
     for(vector<std::string>::iterator i = director.begin(); i != director.end(); i++)
     {
         vector<Movie*> m1 = mdb.get_movies_with_director(*i);
         for(vector<Movie*>::iterator j = m1.begin(); j != m1.end(); j++)
         {
             string id = (*j)->get_id();
             //int count = m_movies.count(id);
             if(count == 0)
             {
                 //m_movies.emplace(new MovieAndRank(id, 30));
             }else{
                 //(m_movies.find(id))->addCompatibilityScore(30);
             }
         }
     }
    
 }
}*/
