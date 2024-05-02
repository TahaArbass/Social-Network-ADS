#include "Connection.h"
#include "Graph.h"
#include "UserProfile.h"
#include <cassert>
#include <cstdlib> // Include the <cstdlib> header for the rand() function
#include <iostream>


using namespace std;

void testGraphFunctions() {
  // Create user profiles
  UserProfile *users[15];
  for (int i = 0; i < 15; ++i) {
    string userName = "User" + to_string(i + 1);
    string firstName = "First" + to_string(i + 1);
    string lastName = "Last" + to_string(i + 1);
    string email = userName + "@example.com";
    users[i] = new UserProfile(userName, firstName, lastName, email);
  }

  // Create connections
  Connection *connections[28];
  int numOfConnections = 28;
  connections[0] = new Connection(users[0], users[1], 1);
  connections[1] = new Connection(users[0], users[2], 4);
  connections[2] = new Connection(users[1], users[2], 2);
  connections[3] = new Connection(users[1], users[3], 5);
  connections[4] = new Connection(users[2], users[3], 1);
  connections[5] = new Connection(users[2], users[4], 2);
  connections[12] = new Connection(users[6], users[7], 3);
  connections[13] = new Connection(users[6], users[8], 1);
  connections[14] = new Connection(users[7], users[8], 2);
  connections[15] = new Connection(users[7], users[9], 3);
  connections[6] = new Connection(users[3], users[4], 3);
  connections[7] = new Connection(users[3], users[5], 1);
  connections[16] = new Connection(users[8], users[9], 1);
  connections[17] = new Connection(users[8], users[10], 2);
  connections[24] = new Connection(users[1], users[5], 1);
  connections[25] = new Connection(users[2], users[5], 4);
  connections[18] = new Connection(users[9], users[10], 3);
  connections[19] = new Connection(users[9], users[11], 1);
  connections[20] = new Connection(users[10], users[11], 2);
  connections[21] = new Connection(users[11], users[12], 3);
  connections[8] = new Connection(users[4], users[5], 2);
  connections[9] = new Connection(users[4], users[6], 3);
  connections[10] = new Connection(users[5], users[6], 1);
  connections[11] = new Connection(users[5], users[7], 2);
  connections[22] = new Connection(users[0], users[4], 2);
  connections[23] = new Connection(users[1], users[4], 3);

  connections[26] = new Connection(users[2], users[6], 2);
  connections[27] = new Connection(users[3], users[6], 3);

  // Create graph
  Graph graph;

  // Test add users
  for (int i = 0; i < 15; ++i) {
    assert(graph.addUser(users[i]));
  }

  // Test add connections
  for (int i = 0; i < numOfConnections; ++i) {
    if (!graph.addConnection(connections[i])) {
      cout << "Failed to add connection: "
           << connections[i]->getSource()->getUserName() << " -- "
           << connections[i]->getDestination()->getUserName() << endl;
    }
  }

  // Generate DOT file
  graph.generateDOTFile("graph.dot");
  graph.renderGraph("graph.dot", "graph.png");

  // check if user 3 is connected to 2 and 1 and vice versa
  assert(graph.isConnected("User3", "User2"));
  assert(graph.isConnected("User3", "User1"));
  assert(graph.isConnected("User2", "User3"));
  assert(graph.isConnected("User1", "User3"));

  // Test BFS traversal
  cout << "BFS Traversal: ";
  vector<string> bfsTraversal = graph.bfsTraversal("User3");
  for (const auto &user : bfsTraversal) {
    cout << user << " ";
  }
  cout << endl;

  // Test DFS traversal
  cout << "DFS Traversal: ";
  vector<string> dfsTraversal = graph.dfsTraversal("User3");
  for (const auto &user : dfsTraversal) {
    cout << user << " ";
  }
  cout << endl;

  // Test calculate average degree
  cout << "Average Degree: " << graph.calculateAverageDegree() << endl;

  // Test calculate diameter
  cout << "Diameter: " << graph.calculateDiameter() << endl;

  // Test A* algorithm
  cout << "A* Shortest Path from User14 to User13: ";
  vector<UserProfile *> astarPath = graph.astar("User14", "User13");
  for (const auto &user : astarPath) {
    cout << user->getUserName() << " ";
  }
  cout << endl;

  // Test Bellman-Ford algorithm
  cout << "Bellman-Ford Shortest Path from User14 to User13: ";
  vector<string> bellmanFordPath =
      graph.shortestPathUsingBellmandFord("User14", "User13");
  for (const auto &user : bellmanFordPath) {
    cout << user << " ";
  }
  cout << endl;

  // Test Dijkstra's algorithm
  cout << "Dijkstra Shortest Path from User14 to User13: ";
  vector<UserProfile *> dijkstraPath = graph.dijkstra("User14", "User13");
  for (const auto &user : dijkstraPath) {
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
