#include "Connection.h"
#include "UserProfile.h"
#include <queue>
// Constructors
Connection::Connection(UserProfile *source, UserProfile *destination)
{
    Connection(source, destination, 1);
}

Connection::Connection(UserProfile *source, UserProfile *destination, int weight)
{
    setConnection(source, destination, weight);
}

// Getters
UserProfile *Connection::getSource() const
{
    return source;
}

UserProfile *Connection::getDestination() const
{
    return destination;
}

int Connection::getWeight() const
{
    return weight;
}

// Setters
void Connection::setSource(UserProfile *source)
{
    this->source = source;
}

void Connection::setDestination(UserProfile *destination)
{
    this->destination = destination;
}

void Connection::setWeight(int weight)
{
    if (weight > 0)
    {
        this->weight = weight;
    }
    else
    {
        this->weight = 1;
    }
}

void Connection::setConnection(UserProfile *source, UserProfile *destination, int weight)
{
    setSource(source);
    setDestination(destination);
    setWeight(weight);
}

// Display info
string Connection::displayInfo() const
{
    string info = "Source: " + source->getUserName() + "\n" + "Destination: " + destination->getUserName() + "\n" + "Weight: " + to_string(weight) + "\n";
    return info;
}
