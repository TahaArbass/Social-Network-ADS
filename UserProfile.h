/******************************************************************************
 * Implementation of UserProfile class:
 *
 * UserProfile: Constructor with username, first name, last name, and email.
 * getUserId: Getter for the user ID.
 * getUserName: Getter for the username.
 * getFirstName: Getter for the first name.
 * getLastName: Getter for the last name.
 *  getEmail: Getter for the email.
 * setUserName: Setter for the username.
 * setFirstName: Setter for the first name.
 * setLastName: Setter for the last name.
 * setEmail: Setter for the email.
 * setUser: Setter for all user attributes.
 * displayUserInfo: Display user information.
 * */

#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <iostream>
#include <string>

using namespace std;

class UserProfile
{
public:
  /******** Function Members ********/

  /***** Constructors *****/
  UserProfile(const string &userName, const string &firstName,
              const string &lastName, const string &email);
  /*-------------------------------------------------------------------------
    Construct a UserProfile object with the given attributes.

    Preconditions: None.
    Postconditions: A UserProfile object is created with the specified attributes.
  -------------------------------------------------------------------------*/

  /***** Getters *****/
  int getUserId() const;
  /*-------------------------------------------------------------------------
    Retrieve the user ID.

    Preconditions: None.
    Postconditions: Returns the user ID as an integer.
  -------------------------------------------------------------------------*/

  string getUserName() const;
  /*-------------------------------------------------------------------------
    Retrieve the username.

    Preconditions: None.
    Postconditions: Returns the username as a string.
  -------------------------------------------------------------------------*/

  string getFirstName() const;
  /*-------------------------------------------------------------------------
    Retrieve the first name.

    Preconditions: None.
    Postconditions: Returns the first name as a string.
  -------------------------------------------------------------------------*/

  string getLastName() const;
  /*-------------------------------------------------------------------------
    Retrieve the last name.

    Preconditions: None.
    Postconditions: Returns the last name as a string.
  -------------------------------------------------------------------------*/

  string getEmail() const;
  /*-------------------------------------------------------------------------
    Retrieve the email.

    Preconditions: None.
    Postconditions: Returns the email as a string.
  -------------------------------------------------------------------------*/

  /***** Setters *****/
  void setUserName(const string &userName);
  /*-------------------------------------------------------------------------
    Set the username.

    Preconditions: 'userName' is a valid string.
    Postconditions: Updates the username to the specified value.
  -------------------------------------------------------------------------*/

  void setFirstName(const string &firstName);
  /*-------------------------------------------------------------------------
    Set the first name.

    Preconditions: 'firstName' is a valid string.
    Postconditions: Updates the first name to the specified value.
  -------------------------------------------------------------------------*/

  void setLastName(const string &lastName);
  /*-------------------------------------------------------------------------
    Set the last name.

    Preconditions: 'lastName' is a valid string.
    Postconditions: Updates the last name to the specified value.
  -------------------------------------------------------------------------*/

  void setEmail(const string &email);
  /*-------------------------------------------------------------------------
    Set the email.

    Preconditions: 'email' is a valid string.
    Postconditions: Updates the email to the specified value.
  -------------------------------------------------------------------------*/

  void setUser(const string &username, const string &firstName, const string &lastName,
               const string &email);
  /*-------------------------------------------------------------------------
    Set all user attributes.

    Preconditions: All parameters are valid strings.
    Postconditions: Updates all user attributes with the specified values.
  -------------------------------------------------------------------------*/

  /***** Display User Info *****/
  string displayUserInfo() const;
  /*-------------------------------------------------------------------------
    Display user information.

    Preconditions: None.
    Postconditions: Returns user information as a string.
  -------------------------------------------------------------------------*/

private:
  static int userIdCounter; // Counter for generating unique user IDs
  int userId;               // User ID
  string userName;          // Username
  string firstName;         // First name
  string lastName;          // Last name
  string email;             // Email
};

#endif // END OF THE HEADER FILE
