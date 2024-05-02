#include "Connection.h"
#include "Graph.h"
#include "UserProfile.h"
#include <iostream>
#include <random>
#include <type_traits>

void displayMenu();
void addUserToGraph(Graph &graph);
void deleteUserFromGraph(Graph &graph);
void addConnectionBetweenUsers(Graph &graph);
void deleteConnectionBetweenUsers(Graph &graph);
void deleteAllConnectionsOfUser(Graph &graph);
void isUserConnectedToAnother(Graph &graph);
void bfsTraversal(Graph &graph);
void dfsTraversal(Graph &graph);
void shortestPathBetweenUsers(Graph &graph);
void getAndDisplayConnectionsOfUser(Graph &graph);

int main() {
  Graph graph;

  int choice;
  char choiceOfUser;
  string userName;
  do {
    displayMenu();
    cin >> choice;
    switch (choice) {
      // Add user
    case 1:
      addUserToGraph(graph);
      break;

      // Delete user
    case 2:
      deleteUserFromGraph(graph);
      break;
    case 3:
      // Add connection between 2 users
      addConnectionBetweenUsers(graph);
      break;
    case 4:
      // Delete connection between 2 users
      deleteConnectionBetweenUsers(graph);
      break;
    case 5:
      deleteAllConnectionsOfUser(graph);
      // Implement delete all connections functionality
      break;
    case 6:
      // Get number of users
      cout << "\nThe number of Users : " << graph.getNumOfUsers() << endl;
      break;
    case 7:
      // Get number of connections
      cout << "\nThe number of connections : " << graph.getNumOfConnections()
           << endl;
      break;
    case 8:
      // Is a user connected directly to another?
      isUserConnectedToAnother(graph);
      break;
    case 9:
      // Breadth First Search (BFS) Traversal
      bfsTraversal(graph);
      break;
    case 10:
      // Depth First Search (DFS) Traversal
      dfsTraversal(graph);
      break;
    case 11:
      // Find shortest path between 2 users
      shortestPathBetweenUsers(graph);
      break;
    case 12:
      // Get all connections of a user
      getAndDisplayConnectionsOfUser(graph);
      break;
    case 13:
      // Display graph analysis
      cout << "Average Degree: " << graph.calculateAverageDegree() << endl;
      cout << "Diameter: " << graph.calculateDiameter() << endl;
      cout << "\nThe number of Users : " << graph.getNumOfUsers() << endl;
      cout << "\nThe number of connections : " << graph.getNumOfConnections()
           << endl;
      break;
    case 14:
      // Visualize graph
      graph.generateDOTFile("graph.dot");
      graph.renderGraph("graph.dot", "graph.png");
      break;
    case 15:
      // Clear graph
      graph.clearGraph();
      cout << "Graph cleared." << endl;
      break;
    case 16:
      // Exit
      cout << "Exiting program..." << endl;
      break;
    default:
      cout << "Invalid choice. Please enter a valid option." << endl;
    }

  } while (choice != 16);

  return 0;
};

void displayMenu() {
  cout << "Menu" << endl;
  cout << "1- Add user " << endl;
  cout << "2- Delete user " << endl;
  cout << "3- Add connection between 2 users " << endl;
  cout << "4- Delete connection between 2 users " << endl;
  cout << "5- Delete all connection of a user " << endl;
  cout << "6- Get number of users " << endl;
  cout << "7- Get number of connections " << endl;
  cout << "8- Is a user connected directly to another? " << endl;
  cout << "9- Breadth First Search (BFS) Traversal " << endl;
  cout << "10- Dephth First Search (DFS) Traversal " << endl;
  cout << "11- Find shortest path between users " << endl;
  cout << "12- Get all connections of a user " << endl;
  cout << "13- display graph analysis " << endl;
  cout << "14- Visualize graph " << endl;
  cout << "15- Clear graph " << endl;
  cout << "16- Exit" << endl;
  cout << "Enter a choice: ";
};

void addUserToGraph(Graph &graph) {
  string username, fname, lname, email;

  bool userNameApproved = false;
  do {
    cout << "Enter a user name: ";
    cin >> username;

    if (!graph.isUserNameTaken(username)) {
      cout << "Enter first name: ";
      cin >> fname;
      cout << "Enter last name: ";
      cin >> lname;
      cout << "Enter email: ";
      cin >> email;

      // Create UserProfile object and add it to the graph
      UserProfile *user = new UserProfile(username, fname, lname, email);
      if (graph.addUser(user)) {
        cout << "User added successfully." << endl;
        userNameApproved = true; // Set flag to exit loop
      } else {
        cout << "Failed to add user." << endl;
      }
    } else {
      cout << "The username '" << username
           << "' is already taken. Please try a different one." << endl;
    }
  } while (!userNameApproved);
};

void deleteUserFromGraph(Graph &graph) {
  string userName;
  char choiceOfUser;

  cout << "Enter the username to proceed with deletion: ";
  cin >> userName;

  bool validChoice = false;
  do {
    cout << "Are you sure that you want to delete the user '" << userName
         << "'? Deleting will remove all the connections associated with the "
            "user. (Y/y for yes, N/n for no): ";
    cin >> choiceOfUser;

    if (choiceOfUser == 'Y' || choiceOfUser == 'y') {
      if (graph.removeUser(userName)) {
        cout << "User '" << userName << "' deleted successfully." << endl;
      } else {
        cout << "User '" << userName << "' not found." << endl;
      }
      validChoice = true;
    } else if (choiceOfUser == 'N' || choiceOfUser == 'n') {
      cout << "Deletion cancelled." << endl;
      validChoice = true;
    } else {
      cout << "Invalid input. Please enter 'Y' or 'N'." << endl;
    }
  } while (!validChoice);
}

void addConnectionBetweenUsers(Graph &graph) {
  string user1, user2;
  int weight;

  cout << "Enter the first user name: ";
  cin >> user1;
  cout << "Enter the second user name: ";
  cin >> user2;
  cout << "Enter the weight of the connection: ";
  cin >> weight;

  // Create a Connection object
  UserProfile *userProfile1 = graph.searchUser(user1);
  UserProfile *userProfile2 = graph.searchUser(user2);
  Connection *connection = new Connection(userProfile1, userProfile2, weight);

  // Add the connection to the graph
  if (graph.addConnection(connection)) {
    cout << "Connection added successfully." << endl;
  } else {
    cout << "Failed to add connection. One or both users not found or "
            "connection already exists."
         << endl;
    delete connection; // Clean up memory
  }
}

void deleteConnectionBetweenUsers(Graph &graph) {
  string user1, user2;
  char choiceOfUser;

  cout << "Enter the first user name: ";
  cin >> user1;
  cout << "Enter the second user name: ";
  cin >> user2;

  cout << "Are you sure that you want to delete the connection between '"
       << user1 << "' and '" << user2 << "'? (Y/y for yes, N/n for no): ";
  cin >> choiceOfUser;

  while (choiceOfUser != 'Y' && choiceOfUser != 'y' && choiceOfUser != 'N' &&
         choiceOfUser != 'n') {
    cout << "Invalid choice. Please enter Y/y for yes or N/n for no: ";
    cin >> choiceOfUser;
  }

  if (choiceOfUser == 'Y' || choiceOfUser == 'y') {
    if (graph.removeConnection(user1, user2)) {
      cout << "Connection between " << user1 << " and " << user2
           << " deleted successfully." << endl;
    } else {
      cout << "Failed to delete connection. Connection between " << user1
           << " and " << user2 << " not found." << endl;
    }
  } else {
    cout << "Deletion cancelled." << endl;
  }
}

void deleteAllConnectionsOfUser(Graph &graph) {
  string userName;
  char choiceOfUser;

  cout << "Enter the user name to delete all connections: ";
  cin >> userName;

  cout << "Are you sure that you want to delete all connections of '"
       << userName << "'? (Y/y for yes, N/n for no): ";
  cin >> choiceOfUser;

  while (choiceOfUser != 'Y' && choiceOfUser != 'y' && choiceOfUser != 'N' &&
         choiceOfUser != 'n') {
    cout << "Invalid choice. Please enter Y/y for yes or N/n for no: ";
    cin >> choiceOfUser;
  }

  if (choiceOfUser == 'Y' || choiceOfUser == 'y') {
    graph.deleteConnectionsOfUser(userName);
    cout << "All connections of user '" << userName << "' deleted successfully."
         << endl;
  } else {
    cout << "Deletion cancelled." << endl;
  }
}

void isUserConnectedToAnother(Graph &graph) {
  string user1, user2;
  cout << "Enter the first user name: ";
  cin >> user1;
  cout << "Enter the second user name: ";
  cin >> user2;
  if (graph.isConnected(user1, user2)) {
    cout << "User " << user1 << " is connected to user " << user2 << endl;
  } else {
    cout << "User " << user1 << " is not connected to user " << user2 << endl;
  }
}

void bfsTraversal(Graph &graph) {
  string startUserName;
  cout << "Enter the starting user name for BFS traversal: ";
  cin >> startUserName;

  vector<string> bfsTraversal = graph.bfsTraversal(startUserName);
  cout << "BFS Traversal: ";
  for (const auto &user : bfsTraversal) {
    cout << user << " ";
  }
  cout << endl;
}

void dfsTraversal(Graph &graph) {
  string startUserName;
  cout << "Enter the starting user name for DFS traversal: ";
  cin >> startUserName;

  vector<string> dfsTraversal = graph.dfsTraversal(startUserName);
  cout << "DFS Traversal: ";
  for (const auto &user : dfsTraversal) {
    cout << user << " ";
  }
  cout << endl;
}

void shortestPathBetweenUsers(Graph &graph) {
  int choice = 0;
  do {
    cout << "Find Shortest Path Using:\n"
         << "1. Djikstra.\n"
         << "2. Bellman Ford.\n"
         << "3. A* algorithm.\n"
         << "4. Return.\n"
         << "Enter your choice: ";
    cin >> choice;
    string user1, user2;
    cout << "Enter the first user name: ";
    cin >> user1;
    if (graph.searchUser(user1)) {
      cout << "Enter the second user name: ";
      cin >> user2;
      if (!(graph.searchUser(user2))) {
        cout << "User not found. Please enter a valid user name." << endl;
        continue;
      }
    } else {
      cout << "User not found. Please enter a valid user name." << endl;
      continue;
    }

    switch (choice) {
    case 1: {
      vector<UserProfile *> dijkstraPath = graph.dijkstra(user1, user2);
      cout << "Dijkstra Shortest Path from " << user1 << " to " << user2
           << ": ";
      for (const auto &user : dijkstraPath) {
        cout << user->getUserName() << " ";
      }
      cout << endl;
      break;
    }
    case 2: {
      vector<string> bellmanFordPath =
          graph.shortestPathUsingBellmandFord(user1, user2);
      cout << "Bellman-Ford Shortest Path from " << user1 << " to " << user2
           << ": ";
      for (const auto &user : bellmanFordPath) {
        cout << user << " ";
      }
      cout << endl;
      break;
    }
    case 3: {
      vector<UserProfile *> astarPath = graph.astar(user1, user2);
      cout << "A* Shortest Path from " << user1 << " to " << user2 << ": ";
      for (const auto &user : astarPath) {
        cout << user->getUserName() << " ";
      }
      cout << endl;
      break;
    }
    case 4:
      break;

    default:
      cout << "Invalid choice. Please enter a valid option." << endl;
    }
  } while (choice != 4);
}

void getAndDisplayConnectionsOfUser(Graph &graph) {
  cout << "Enter the user name to get connections: ";
  string userName;
  cin >> userName;
  vector<string> connectedUsers = graph.getConnectedUsers(userName);
  cout << "Connections of user " << userName << ": ";
  for (const auto &user : connectedUsers) {
    cout << user << ", ";
  }
  cout << endl;
}