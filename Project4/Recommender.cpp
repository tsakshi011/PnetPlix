#include "Recommender.h"
#include "User.h"
#include "Movie.h"

#include <string>
#include <vector>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    // Replace this line with correct code.
    /*sort(answer.begin(), answer.end(), compareMovieAndRank);
    if(answer.size() > movie_count);
    
    bool Recommender::compareMovieAndRank(count Movie&Rank, const Moview&Rank m2)
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
    //udb = user_database;
    //mdb = movie_database;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    //unordered_set<MovieAndRank> m_movies;
    
    /*User* u = udb.get_user_from_email(user_email);
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
                std::cerr << (*j)->get_title() << std::endl;
                if(!m_movies.find((*j)->get_title()))
                {
                    addCompatabilityScore(30);
                }
            }
        }
    }
    */
    return vector<MovieAndRank>();  // Replace this line with correct code.
}
