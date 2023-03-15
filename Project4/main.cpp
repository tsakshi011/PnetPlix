#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Recommender.h"
#include <iostream>
#include <string>
using namespace std;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

const string USER_DATAFILE  = "/Users/sakshi/Desktop/Project4/users.txt";
const string MOVIE_DATAFILE = "/Users/sakshi/Desktop/Project4/movies.txt";

void findMatches(const Recommender& r, const MovieDatabase& md, const string& user_email, int num_recommendations)
{
    vector<MovieAndRank> recommendations = r.recommend_movies(user_email, 10);
    if(recommendations.empty())
    {
        cout << "We found no movies to recommend ;(.\n";
    }else{
        for(int i = 0; i < recommendations.size(); i++)
        {
            const MovieAndRank& mr = recommendations[i];
            Movie* m = md.get_movie_from_id(mr.movie_id);
            cout << i << ". " << m->get_title() << "(" << m->get_release_year() << ")\n Rating: " << m->get_rating() << "\n Compatibility Score: " << mr.compatibility_score << "\n";
        }
    }
}

int main()
{
    UserDatabase udb;
    if (!udb.load(USER_DATAFILE)) //returns true failed to load
    {
        cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
        return 1;
    }
    MovieDatabase mdb;
    if (!mdb.load(MOVIE_DATAFILE)) //returns true failed to load
    {
        cout << "Failed to load user data file " << MOVIE_DATAFILE << "!" << endl;
        return 1;
    }
    
    Recommender recommend(udb, mdb);
    User* u = udb.get_user_from_email("climberkip@gmail.com");
    vector<string> movies = u->get_watch_history();
    findMatches(recommend, mdb, "climberkip@gmail.com", 5);
    //recommend.recommend_movies("climberkip@gmail.com", 3);
    
    /*for (;;)
    {
        cout << "Enter user email address (or quit): ";
        string email;
        getline(cin, email);
        if (email == "quit")
            return 0;
        User* u = udb.get_user_from_email(email);
        if (u == nullptr)
            cout << "No user in the database has that email address." << endl;
        else
            cout << "Found " << u->get_full_name() << endl;
    }
    
    for (;;)
    {
        cout << "Enter movie (or quit): ";
        string movie;
        getline(cin, movie);
        if (movie == "quit")
            return 0;
        Movie *m = mdb.get_movie_from_id(movie);
        if (m == nullptr)
            cout << "No movie in the database has that ID." << endl;
        else
            cout << "FOUND " << m->get_title() << endl;
            //cout << "Found " << m << endl;
    }*/
    
    //cerr << "HERE" << endl;
    /*Recommender recommend(udb, mdb);
    User* u = udb.get_user_from_email("AbFow2483@charter.net");
    cerr << u->get_full_name() << endl;
    vector<string> movies = u->get_watch_history();
    recommend.recommend_movies("AbFow2483@charter.net", 3);*/
    
    /*Recommender recommend(udb, mdb);
    User* u = udb.get_user_from_email("HezekF0394@aol.com");
    cerr << u->get_full_name() << endl;
    vector<string> movies = u->get_watch_history();
    recommend.recommend_movies("HezekF0394@aol.com", 3);*/
    //cerr << "HERE" << endl;
    //findMatches(recommend, mdb, "AbFow2483@charter.net");
    
    
    /*Recommender recommend(udb, mdb);
    User* u = udb.get_user_from_email("climberkip@gmail.com");
    vector<string> movies = u->get_watch_history();
    recommend.recommend_movies("climberkip@gmail.com", 3);*/
    
    
}




/*int main()
{
    TreeMultimap<std::string, int> tmm;
    tmm.insert("carey",5);
    tmm.insert("carey",6);
    tmm.insert("carey",7);
    //tmm.insert("carey",8);
    //tmm.insert("carey",9);
    //tmm.insert("carey",10);
    tmm.insert("david",25);
    tmm.insert("david",425);
    tmm.insert("amy", 22);
    TreeMultimap<std::string, int>::Iterator it = tmm.find("amy");
    while(it.is_valid())
    {
        std::cout << it.get_value() << endl;
        it.advance();
    }
    
    it = tmm.find("laura");
    if(!it.is_valid())
    {
        std::cout << "laura is not in the multimap" << std::endl;
    }
}*/
