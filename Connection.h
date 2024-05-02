/******************************************************************************
     Implementation of Connection class:
    Connection: Constructor with source, destination, and weight.
    Connection: Constructor with source and destination (default weight = 0).
    getSource: Getter for the source UserProfile.
    getDestination: Getter for the destination UserProfile.
    getWeight: Getter for the weight of the connection.
    setSource: Setter for the source UserProfile.
    setDestination: Setter for the destination UserProfile.
    setWeight: Setter for the weight of the connection.
    setConnection: Setter for the source, destination, and weight.
    displayInfo: Display information about the connection.
 * ****************************************************************************
 * */

#ifndef CONNECTION_H
#define CONNECTION_H

#include <iostream>
#include <string>

using namespace std;

class UserProfile;

class Connection
{
private:
  UserProfile *source;      // Pointer to the source UserProfile
  UserProfile *destination; // Pointer to the destination UserProfile
  int weight;               // Weight of the connection

public:
  /******** Function Members ********/

  /***** Constructors *****/
  Connection(UserProfile *source, UserProfile *destination, int weight);
  /*-------------------------------------------------------------------------
    Construct a Connection object with the given source, destination, and weight.

    Preconditions:  'source' and 'destination' are valid pointers to UserProfile objects,
                     'weight' is an integer representing the weight of the connection.
    Postconditions: A Connection object is created with the specified source, destination, and weight.
  -------------------------------------------------------------------------*/

  Connection(UserProfile *source, UserProfile *destination);
  /*-------------------------------------------------------------------------
    Construct a Connection object with the given source and destination.
    Default weight is set to 0.

    Preconditions:  'source' and 'destination' are valid pointers to UserProfile objects.
    Postconditions: A Connection object is created with the specified source and destination,
                     and default weight of 0.
  -------------------------------------------------------------------------*/

  /***** Getters *****/
  UserProfile *getSource() const;
  /*-------------------------------------------------------------------------
    Retrieve the source UserProfile of the connection.

    Preconditions:  None.
    Postconditions: The source UserProfile is returned as a pointer.
  -------------------------------------------------------------------------*/

  UserProfile *getDestination() const;
  /*-------------------------------------------------------------------------
    Retrieve the destination UserProfile of the connection.

    Preconditions:  None.
    Postconditions: The destination UserProfile is returned as a pointer.
  -------------------------------------------------------------------------*/

  int getWeight() const;
  /*-------------------------------------------------------------------------
    Retrieve the weight of the connection.

    Preconditions:  None.
    Postconditions: The weight of the connection is returned as an integer.
  -------------------------------------------------------------------------*/

  /***** Setters *****/
  void setSource(UserProfile *source);
  /*-------------------------------------------------------------------------
    Set the source UserProfile of the connection.

    Preconditions:  The 'source' parameter is a valid pointer to a UserProfile object.
    Postconditions: The source UserProfile is updated to the specified value.
  -------------------------------------------------------------------------*/

  void setDestination(UserProfile *destination);
  /*-------------------------------------------------------------------------
    Set the destination UserProfile of the connection.

    Preconditions:  The 'destination' parameter is a valid pointer to a UserProfile object.
    Postconditions: The destination UserProfile is updated to the specified value.
  -------------------------------------------------------------------------*/

  void setWeight(int weight);
  /*-------------------------------------------------------------------------
    Set the weight of the connection.

    Preconditions:  The 'weight' parameter is an integer.
    Postconditions: The weight of the connection is updated to the specified value.
  -------------------------------------------------------------------------*/

  void setConnection(UserProfile *source, UserProfile *destination, int weight);
  /*-------------------------------------------------------------------------
    Set the source, destination, and weight of the connection.

    Preconditions:  'source' and 'destination' are valid pointers to UserProfile objects,
                     'weight' is an integer representing the weight of the connection.
    Postconditions: The source, destination, and weight of the connection are updated.
  -------------------------------------------------------------------------*/

  /***** Display Connection Info *****/
  string displayInfo() const;
  /*---------------------------------------------------------------------------
    Display information about the connection.

    Preconditions:  None.
    Postconditions: Information about the connection is returned as a string.
  ----------------------------------------------------------------------------*/
};

#endif // END OF THE HEADER FILE
