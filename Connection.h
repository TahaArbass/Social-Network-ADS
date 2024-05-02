#ifndef CONNECTION_H
#define CONNECTION_H

#include <iostream>
#include <string>

using namespace std;

class UserProfile;

class Connection {
private:
  UserProfile *source;
  UserProfile *destination;
  int weight;

public:
  // Constructors
  Connection(UserProfile *source, UserProfile *destination, int weight);

  Connection(UserProfile *source, UserProfile *destination);
  

  // Getters
  UserProfile *getSource() const;

  UserProfile *getDestination() const;

  int getWeight() const;

  // Setters
  void setSource(UserProfile *source);

  void setDestination(UserProfile *destination);

  void setWeight(int weight);

  void setConnection(UserProfile *source, UserProfile *destination, int weight);

  // Display info
  string displayInfo() const;
};

#endif
