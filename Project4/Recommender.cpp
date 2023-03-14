#include "Recommender.h"
#include "User.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <unordered_map>
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

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    //MovieAndRank m_movies;
    unordered_map<string, MovieAndRank*> m_movies;
    
    User* u = udb.get_user_from_email(user_email);
    std::cerr << u->get_full_name() << std::endl;
    int compatibility_score = 0;
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
                int count = m_movies.count(id);
                if(count == 0)
                {
                    m_movies.emplace(new MovieAndRank(id, 30));
                }else{
                    //(m_movies.find(id))->addCompatibilityScore(30);
                }
            }
        }
        /*vector<std::string> actor = mdb.get_movie_from_id(*it)->get_actors();
        for(vector<std::string>::iterator i = actor.begin(); i != actor.end(); i++)
        {
            vector<Movie*> m2 = mdb.get_movies_with_actor(*i);
            for(vector<Movie*>::iterator j = m2.begin(); j != m2.end(); j++)
            {
                std::cerr << (*j)->get_title() << std::endl;
                if(!m_movies.find((*j)->get_title()))
                {
                    addCompatibilityScore(20);
                }
            }
        }
        vector<std::string> genre = mdb.get_movie_from_id(*it)->get_genres();
        for(vector<std::string>::iterator i = genre.begin(); i != genre.end(); i++)
        {
            vector<Movie*> m3 = mdb.get_movies_with_genre(*i);
            for(vector<Movie*>::iterator j = m3.begin(); j != m3.end(); j++)
            {
                std::cerr << (*j)->get_title() << std::endl;
                if(!m_movies.find((*j)->get_title()))
                {
                    addCompatibilityScore(10);
                }
            }
        }*/
    }
    return vector<MovieAndRank>();  // Replace this line with correct code.
}


/*bool Recommender::compareMovieAndRank(count Movie&Rank, const Moview&Rank m2)
{
    if(m1.compaitiblity_score != m2.compatablity_score)
    {
        return m1.compatibility_score < m2.compatibility_score;
    }
    Moview* movie1 = movies->get_movie_from_id(m1.movie_id)
    Movie* movie2 = movies->get_ovie_from_id(m2.movie_id);
    if(movie1->get_rating() != movie2->get_rating())
    {
        return movie1->get_rating() < movie2_get_rating();
    }
    return movie1->get_title() < movie2->get_title();
}*/
