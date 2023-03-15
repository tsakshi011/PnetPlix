#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include "treemm.h"
#include "User.h"
#include <map>
#include <string>

class User;

class UserDatabase
{
  public:
    UserDatabase();
    ~UserDatabase();
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;

  private:
    bool loaded;
    std::vector<User*> delete_reference;
    TreeMultimap<std::string, User*> tmm;
};

#endif // USERDATABASE_INCLUDED
