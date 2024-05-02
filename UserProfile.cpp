#include "UserProfile.h"

// Static member initialization, counter to generate unique user IDs
int UserProfile::userIdCounter = 0;

// Constructor
UserProfile::UserProfile(const string &userName, const string &firstName,
                         const string &lastName, const string &email) {
  userId = ++userIdCounter;
  setUser(userName, firstName, lastName, email);
}

// Setters
void UserProfile::setUserName(const string &userName) {
  this->userName = userName;
}

void UserProfile::setFirstName(const string &firstName) {
  this->firstName = firstName;
}

void UserProfile::setLastName(const string &lastName) {
  this->lastName = lastName;
}

void UserProfile::setEmail(const string &email) { this->email = email; }

void UserProfile::setUser(const string &username, const string &firstName,
                          const string &lastName, const string &email) {
  setUserName(username);
  setFirstName(firstName);
  setLastName(lastName);
  setEmail(email);
}

// Getters
int UserProfile::getUserId() const { return userId; }
string UserProfile::getUserName() const { return userName; }
string UserProfile::getFirstName() const { return firstName; }
string UserProfile::getLastName() const { return lastName; }
string UserProfile::getEmail() const { return email; }

// Display user information
string UserProfile::displayUserInfo() const {
  return "User ID: " + to_string(userId) + "\n"
  + "Username: " + userName + "\n"
  + "First Name: " + firstName + "\n"
  + "Last Name: " +  lastName + "\n"
  + "Email: " + email + "\n";
}
