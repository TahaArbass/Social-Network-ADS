#include <iostream>
#include <cassert>
#include <cstdlib> // Include the <cstdlib> header for the rand() function
#include "Graph.h"
#include "Connection.h"
#include "UserProfile.h"

using namespace std;

void testGraphFunctions() {
    // Create user profiles
    UserProfile* users[15];
    for (int i = 0; i < 15; ++i) {
        string userName = "User" + to_string(i + 1);
        string firstName = "First" + to_string(i + 1);
        string lastName = "Last" + to_string(i + 1);
        string email = userName + "@example.com";
        users[i] = new UserProfile(userName, firstName, lastName, email);
    }

    // Create connections
    int numOfConnections = 22; // Adjust the number of random connections here
    Connection* connections[numOfConnections];
    for (int i = 0; i < numOfConnections; ++i) {
        int sourceIndex = rand() % 15;
        int destinationIndex = rand() % 15;
        while (sourceIndex == destinationIndex) {
            destinationIndex = rand() % 15;
        }
        int weight = rand() % 10 + 1; // Random weight between 1 and 10
        connections[i] = new Connection(users[sourceIndex], users[destinationIndex], weight);
    }

    // Create graph
    Graph graph;

    // Test add users
    for (int i = 0; i < 15; ++i) {
        assert(graph.addUser(users[i]));
    }

    // Test add connections
    for (int i = 0; i < numOfConnections; ++i) {
        if (!graph.addConnection(connections[i])) {
            cout << "Failed to add connection: " << connections[i]->getSource()->getUserName() << " -- " << connections[i]->getDestination()->getUserName() << endl;
        }
    }

    // Generate DOT file
    graph.generateDOTFile("graph.dot");
    graph.renderGraph("graph.dot", "graph.png");

    // Test BFS traversal
    cout << "BFS Traversal: ";
    vector<string> bfsTraversal = graph.bfsTraversal("User3");
    for (const auto& user : bfsTraversal) {
        cout << user << " ";
    }
    cout << endl;

    // Test DFS traversal
    cout << "DFS Traversal: ";
    vector<string> dfsTraversal = graph.dfsTraversal("User3");
    for (const auto& user : dfsTraversal) {
        cout << user << " ";
    }
    cout << endl;

    // Test calculate average degree
    cout << "Average Degree: " << graph.calculateAverageDegree() << endl;

    // Test calculate diameter
    cout << "Diameter: " << graph.calculateDiameter() << endl;

    // Test A* algorithm
    cout << "A* Shortest Path from User1 to User8: ";
    vector<UserProfile*> astarPath = graph.astar("User1", "User8");
    for (const auto& user : astarPath) {
        cout << user->getUserName() << " ";
    }
    cout << endl;

    // Test Bellman-Ford algorithm
    cout << "Bellman-Ford Shortest Path from User1 to User8: ";
    vector<string> bellmanFordPath = graph.shortestPathUsingBellmandFord("User1", "User8");
    for (const auto& user : bellmanFordPath) {
        cout << user << " ";
    }
    cout << endl;

    // Test Dijkstra's algorithm
    cout << "Dijkstra Shortest Path from User1 to User8: ";
    vector<UserProfile*> dijkstraPath = graph.dijkstra("User1", "User8");
    for (const auto& user : dijkstraPath) {
        cout << user->getUserName() << " ";
    }
    cout << endl;

    // Clean up
    for (int i = 0; i < 15; ++i) {
        delete users[i];
    }
    for (int i = 0; i < numOfConnections; ++i) {
        delete connections[i];
    }
}

int main() {
    testGraphFunctions();
    cout << "All tests passed!" << endl;
    return 0;
}
