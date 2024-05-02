#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
#include <vector>
#include <unordered_set>

using namespace std;

// Forward declaration of Connection and UserProfile classes
class Connection;
class UserProfile;

class Graph
{

public:
    // Default Constructor
    Graph();
    // Destructor to clean up dynamically allocated memory
    ~Graph();
    // Function to add an edge/connection between user1 and user2
    bool addConnection(Connection *connection);
    // Function to remove an edge/connection between user1 and user2
    bool removeConnection(const string &src, const string &dest);

    bool isUserNameTaken(const string &userName);
    // Function to delete all connections of a user
    void deleteConnectionsOfUser(const string &username);
    vector<string> getConnectedUsers(const string &userName);

    UserProfile *searchUser(const string &username);

    bool addUser(UserProfile *user);
    // Function to remove a user from the graph
    bool removeUser(const string &username);

    int getNumOfUsers();
    // Function to get the number of connections in the graph
    int getNumOfConnections();

    // Function to check if a user is connected to another user
    bool isConnected(const string &src, const string &dest);

    // Function to empty the graph
    void clearGraph();

    // Function to print the adjacency list representation of the graph
    void printGraph();

    // Function to find the shortest path between two users using BFS
    vector<UserProfile *> shortestPath(const string &src, const string &dest);

    vector<string> dfsTraversal(const string &startUserName);
    vector<string> bfsTraversal(const string &startUserName);

    vector<UserProfile *> astar(const string &startUserName, const string &goalUserName);
    vector<UserProfile *> dijkstra(const string &startUserName, const string &endUserName);
    unordered_map<string, pair<int, string>> bellmanFordShortestPath(const string &startNode);
    vector<string> shortestPathUsingBellmandFord(const string &startNode, const string &endNode);

    void generateDOTFile(const string &fileName);
    void renderGraph(const string &dotFileName, const string &outputFileName);

private:
    unordered_map<string, UserProfile *> users;    // user profiles
    unordered_map<string, list<Connection *>> adj; // adjacency list
    void dfsUtil(const string &node, unordered_set<string> &visited, vector<string> &path);
};

#endif