#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include "UserDatabase.h"
#include "MovieDatabase.h"
#include <string>
#include <vector>
#include <unordered_set>
#include <set>

class UserDatabase;
class MovieDatabase;

struct MovieAndRank
{
    MovieAndRank(const std::string& id, int score)
     : movie_id(id), compatibility_score(score)
    {}

    std::string movie_id;
    int compatibility_score;
    
    //void addCompatibilityScore(int score){compatibility_score += score;}
};

class Recommender
{
public:
    Recommender(const UserDatabase& user_database,
                const MovieDatabase& movie_database);
    std::vector<MovieAndRank> recommend_movies(const std::string& user_email,
                                               int movie_count) const;
    
private:
    const UserDatabase* udb;
    const MovieDatabase* mdb;
    
    //bool operator<(const MovieAndRank& m1, const MovieAndRank& m2);
};

#endif // RECOMMENDER_INCLUDED

