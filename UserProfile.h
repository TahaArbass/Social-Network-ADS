#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <iostream>
#include <string>

using namespace std;

class UserProfile {
public:
  UserProfile(const string &userName, const string &firstName,
              const string &lastName, const string &email);
  int getUserId() const;
  string getUserName() const;
  string getFirstName() const;
  string getLastName() const;
  string getEmail() const;
  void setUserName(const string &userName);
  void setFirstName(const string &firstName);
  void setLastName(const string &lastName);
  void setEmail(const string &email);
  void setUser(const string& username, const string &firstName, const string &lastName,
               const string &email);
  string displayUserInfo() const;

private:
  static int userIdCounter;
  int userId;
  string userName;
  string firstName;
  string lastName;
  string email;
};

#endif