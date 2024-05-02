#include <iostream>
#include "Connection.h"
#include "UserProfile.h"
#include "Graph.h"
#include <random>

int main()
{
    const int numUsers = 40;       // Number of users
    const int numConnections = 100; // Number of connections

    // Create user profiles
    vector<UserProfile *> users;
    for (int i = 1; i <= numUsers; ++i)
    {
        string userName = "user" + to_string(i);
        string firstName = "First" + to_string(i);
        string lastName = "Last" + to_string(i);
        string email = userName + "@example.com";
        UserProfile *user = new UserProfile(userName, firstName, lastName, email);
        users.push_back(user);
    }

    // Create connections between user profiles
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> disUser(0, numUsers - 1);
    uniform_int_distribution<> disWeight(1, 10);

    vector<Connection> connections;
    for (int i = 0; i < numConnections; ++i)
    {
        int idx1 = disUser(gen);
        int idx2 = disUser(gen);
        while (idx2 == idx1) // Ensure the two users are different
        {
            idx2 = disUser(gen);
        }
        int weight = disWeight(gen); // Random weight between 1 and 10
        Connection connection(users[idx1], users[idx2], weight);
        connections.push_back(connection);
    }

    // Display connection info
    cout << "Connection Info:\n";
    for (const auto &connection : connections)
    {
        cout << connection.displayInfo();
    }

    Graph graph;

    // Add users to the graph
    for (auto user : users)
    {
        graph.addUser(user);
    }

    // Add connections to the graph
    for (auto &connection : connections)
    {
        graph.addConnection(&connection);
    }

    // Check if connections are successful
    string user1Name = "user1";
    string user6Name = "user" + to_string(numUsers);
    // string user6Name = "user" + to_string(numUsers);
    if (graph.isConnected(user1Name, user6Name))
    {
        cout << "Users " << user1Name << " and " << user6Name << " are connected\n";
    }
    else
    {
        cout << "Users " << user1Name << " and " << user6Name << " are not connected\n";
    }

    // Test A* algorithm to find the shortest path between user1 and user6
    vector<UserProfile *> shortestPath = graph.astar(user1Name, user6Name);

    // Display the shortest path
    cout << "A* Shortest Path from " << user1Name << " to " << user6Name << ":\n";
    for (UserProfile *user : shortestPath)
    {
        cout << user->getUserName() << " -> ";
    }
    cout << endl;

    // display the shortest path using digkistra
    vector<UserProfile *> shortestPathDijkistra = graph.dijkstra(user1Name, user6Name);
    cout << "Djikstra Shortest path from " << user1Name << "to " << user6Name << ":\n";

    for (UserProfile *user : shortestPathDijkistra)
    {
        cout << user->getUserName() << "->";
    }

    cout << endl;
    // Generate DOT file
    graph.generateDOTFile("graph.dot");

    // Render the graph using Graphviz
    graph.renderGraph("graph.dot", "graph.png");

    // Clean up memory
    for (auto user : users)
    {
        delete user;
    }

    return 0;
}
