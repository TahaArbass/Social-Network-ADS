/******************************************************************************
 * Fares Najjar & Taha arbas
 * ADS project (Spring 2024)
 * Instructor : Dr.charbel Obied
    Implementation of main.cpp:
    displayMenu: Function to display the menu options.
    addUserToGraph: Function to add a user to the graph.
    deleteUserFromGraph: Function to delete a user from the graph.
    addConnectionBetweenUsers: Function to add a connection between two users in the graph.
    deleteConnectionBetweenUsers: Function to delete a connection between two users in the graph.
    deleteAllConnectionsOfUser: Function to delete all connections of a user in the graph.
    isUserConnectedToAnother: Function to check if a user is connected directly to another user.
    bfsTraversal: Function to perform Breadth First Search (BFS) traversal on the graph.
    dfsTraversal: Function to perform Depth First Search (DFS) traversal on the graph.
    shortestPathBetweenUsers: Function to find the shortest path between two users in the graph.
    getAndDisplayConnectionsOfUser: Function to get and display all connections of a user in the graph.
    clearGraphWithConfirmation: Function to clear the graph with user confirmation.
    clearUsersWithConfirmation: Function to clear all users from the graph with user confirmation.
    readUsersFromFile: Function to read users from a file and add them to the graph.
    readConnectionsFromFile: Function to read connections from a file and add them to the graph.
    main: The main function that drives the execution of the program.
    ******************************************************************************/

#include "Connection.h"
#include "Graph.h"
#include "UserProfile.h"
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <type_traits>

/******************************************************************************
 * Function: displayMenu
 *
 * Purpose: Display the menu options for the user to choose from.
 *
 * Preconditions: None.
 *
 * Postconditions: None.
 *****************************************************************************/
void displayMenu();

/******************************************************************************
 * Function: addUserToGraph
 *
 * Purpose: Add a user to the graph.
 *
 * Preconditions:
 *    - 'graph' is a valid Graph object.
 *
 * Postconditions: The user is added to the graph.
 *****************************************************************************/
void addUserToGraph(Graph &graph);

/******************************************************************************
 * Function: deleteUserFromGraph
 *
 * Purpose: Delete a user from the graph.
 *
 * Preconditions:
 *    - 'graph' is a valid Graph object.
 *
 * Postconditions: The specified user is removed from the graph.
 *****************************************************************************/
void deleteUserFromGraph(Graph &graph);

/******************************************************************************
 * Function: addConnectionBetweenUsers
 *
 * Purpose: Add a connection between two users in the graph.
 *
 * Preconditions:
 *    - 'graph' is a valid Graph object.
 *
 * Postconditions: A connection is added between the specified users in the graph.
 *****************************************************************************/
void addConnectionBetweenUsers(Graph &graph);

/******************************************************************************
 * Function: deleteConnectionBetweenUsers
 *
 * Purpose: Delete a connection between two users in the graph.
 *
 * Preconditions:
 *    - 'graph' is a valid Graph object.
 *
 * Postconditions: If a connection exists between the specified users, it is deleted from the graph.
 *****************************************************************************/
void deleteConnectionBetweenUsers(Graph &graph);

/******************************************************************************
 * Function: deleteAllConnectionsOfUser
 *
 * Purpose: Delete all connections of a user in the graph.
 *
 * Preconditions:
 *    - 'graph' is a valid Graph object.
 *
 * Postconditions: All connections associated with the specified user are removed from the graph.
 *****************************************************************************/
void deleteAllConnectionsOfUser(Graph &graph);

/******************************************************************************
 * Function: isUserConnectedToAnother
 *
 * Purpose: Check if a user is directly connected to another user in the graph.
 *
 * Preconditions:
 *    - 'graph' is a valid Graph object.
 *
 * Postconditions: None.
 *****************************************************************************/
void isUserConnectedToAnother(Graph &graph);

/******************************************************************************
 * Function: bfsTraversal
 *
 * Purpose: Perform Breadth First Search (BFS) traversal on the graph starting from a specified user.
 *
 * Preconditions:
 *    - 'graph' is a valid Graph object.
 *
 * Postconditions: None.
 *****************************************************************************/
void bfsTraversal(Graph &graph);

/******************************************************************************
 * Function: dfsTraversal
 *
 * Purpose: Perform Depth First Search (DFS) traversal on the graph starting from a specified user.
 *
 * Preconditions:
 *    - 'graph' is a valid Graph object.
 *
 * Postconditions: None.
 *****************************************************************************/
void dfsTraversal(Graph &graph);

/******************************************************************************
 * Function: shortestPathBetweenUsers
 *
 * Purpose: Find the shortest path between two users in the graph using a specified algorithm.
 *
 * Preconditions:
 *    - 'graph' is a valid Graph object.
 *
 * Postconditions: None.
 *****************************************************************************/
void shortestPathBetweenUsers(Graph &graph);

/******************************************************************************
 * Function: getAndDisplayConnectionsOfUser
 *
 * Purpose: Retrieve and display all connections of a specified user in the graph.
 *
 * Preconditions:
 *    - 'graph' is a valid Graph object.
 *
 * Postconditions: None.
 *****************************************************************************/
void getAndDisplayConnectionsOfUser(Graph &graph);

/******************************************************************************
 * Function: displayUserInfo
 *
 * Purpose: Display user information for a specified user in the graph.
 *
 * Preconditions:
 *    - 'graph' is a valid Graph object.
 *
 * Postconditions: None.
 *****************************************************************************/
void displayUserInfo(Graph &graph);

/******************************************************************************
 * Function: clearGraphWithConfirmation
 *
 * Purpose: Clear the graph with confirmation from the user.
 *
 * Preconditions:
 *    - 'graph' is a valid Graph object.
 *
 * Postconditions: The graph is cleared if confirmed by the user.
 *****************************************************************************/
void clearGraphWithConfirmation(Graph &graph);

/******************************************************************************
 * Function: clearUsersWithConfirmation
 *
 * Purpose: Clear all users from the graph with confirmation from the user.
 *
 * Preconditions:
 *    - 'graph' is a valid Graph object.
 *
 * Postconditions: All users are removed from the graph if confirmed by the user.
 *****************************************************************************/
void clearUsersWithConfirmation(Graph &graph);

/******************************************************************************
 * Function: readUsersFromFile
 *
 * Purpose: Read user data from a file and add users to the graph.
 *
 * Preconditions:
 *    - 'fileName' is the name of a valid file containing user data.
 *    - 'graph' is a valid Graph object.
 *
 * Postconditions: Users are added to the graph based on the data read from the file.
 *****************************************************************************/
void readUsersFromFile(const string &fileName, Graph &graph);

/******************************************************************************
 * Function: readConnectionsFromFile
 *
 * Purpose: Read connection data from a file and add connections to the graph.
 *
 * Preconditions:
 *    - 'folderName' is the name of the folder containing the connection file.
 *    - 'fileName' is the name of a valid file containing connection data.
 *    - 'graph' is a valid Graph object.
 *
 * Postconditions: Connections are added to the graph based on the data read from the file.
 *****************************************************************************/
void readConnectionsFromFile(const string &folderName, const string &fileName, Graph &graph);

int main()
{
  // Create a graph object
  Graph graph;
  // Read users from a file and add them to the graph
  readUsersFromFile("resources/users.txt", graph);

  // Read connections from a file and add them to the graph
  readConnectionsFromFile("resources", "connections.txt", graph);

  int choice;
  char choiceOfUser;
  string userName;
  do
  {
    displayMenu();
    cin >> choice;
    switch (choice)
    {
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
      clearGraphWithConfirmation(graph);

      break;
    case 16:
      clearUsersWithConfirmation(graph);
      break;

    case 17:
      // Display user info
      cout << "Enter a user name : ";
      cin >> userName;
      graph.displayUserInfo(userName);

      break;
    case 18:
      // Exit
      cout << "Exiting program..." << endl;
      break;
    default:
      cout << "Invalid choice. Please enter a valid option." << endl;
    }

  } while (choice != 18);

  return 0;
};

void displayMenu()
{
  cout << "\n==============================\n";
  cout << "             Menu             \n";
  cout << "==============================\n";
  cout << "1.  Add user\n";
  cout << "2.  Delete user\n";
  cout << "3.  Add connection between 2 users\n";
  cout << "4.  Delete connection between 2 users\n";
  cout << "5.  Delete all connections of a user\n";
  cout << "6.  Get number of users\n";
  cout << "7.  Get number of connections\n";
  cout << "8.  Is a user connected directly to another?\n";
  cout << "9.  Breadth First Search (BFS) Traversal\n";
  cout << "10. Depth First Search (DFS) Traversal\n";
  cout << "11. Find shortest path between users\n";
  cout << "12. Get all connections of a user\n";
  cout << "13. Display graph analysis\n";
  cout << "14. Visualize graph\n";
  cout << "15. Clear graph\n";
  cout << "16. Clear Users\n";
  cout << "17. Display User Info\n";
  cout << "18. Exit\n";
  cout << "==============================\n";
  cout << "Enter a choice: ";
}
void addUserToGraph(Graph &graph)
{
  string username, fname, lname, email;

  bool userNameApproved = false;
  do
  {
    cout << "Enter a user name: ";
    cin >> username;

    if (!graph.isUserNameTaken(username))
    {
      cout << "Enter first name: ";
      cin >> fname;
      cout << "Enter last name: ";
      cin >> lname;
      cout << "Enter email: ";
      cin >> email;

      // Create UserProfile object and add it to the graph
      UserProfile *user = new UserProfile(username, fname, lname, email);
      if (graph.addUser(user))
      {
        cout << "User added successfully." << endl;
        userNameApproved = true; // Set flag to exit loop
      }
      else
      {
        cout << "Failed to add user." << endl;
      }
    }
    else
    {
      cout << "The username '" << username
           << "' is already taken. Please try a different one." << endl;
    }
  } while (!userNameApproved);
};

void deleteUserFromGraph(Graph &graph)
{
  string userName;
  char choiceOfUser;

  cout << "Enter the username to proceed with deletion: ";
  cin >> userName;

  bool validChoice = false;
  do
  {
    cout << "Are you sure that you want to delete the user '" << userName
         << "'? Deleting will remove all the connections associated with the "
            "user. (Y/y for yes, N/n for no): ";
    cin >> choiceOfUser;

    if (choiceOfUser == 'Y' || choiceOfUser == 'y')
    {
      if (graph.removeUser(userName))
      {
        cout << "User '" << userName << "' deleted successfully." << endl;
      }
      else
      {
        cout << "User '" << userName << "' not found." << endl;
      }
      validChoice = true;
    }
    else if (choiceOfUser == 'N' || choiceOfUser == 'n')
    {
      cout << "Deletion cancelled." << endl;
      validChoice = true;
    }
    else
    {
      cout << "Invalid input. Please enter 'Y' or 'N'." << endl;
    }
  } while (!validChoice);
}

void addConnectionBetweenUsers(Graph &graph)
{
  string user1, user2;
  int weight;

  cout << "Enter the first user name: ";
  cin >> user1;
  if (!graph.searchUser(user1))
  {
    cout << "User not found. Please enter a valid user name next time." << endl;
    return;
  }
  cout << "Enter the second user name: ";
  cin >> user2;
  if (!graph.searchUser(user2))
  {
    cout << "User not found. Please enter a valid user name next time." << endl;
    return;
  }
  cout << "Enter the weight of the connection (when a negative weight is "
          "entered, it becomes 1): ";
  cin >> weight;

  // Create a Connection object
  UserProfile *userProfile1 = graph.searchUser(user1);
  UserProfile *userProfile2 = graph.searchUser(user2);
  Connection *connection = new Connection(userProfile1, userProfile2, weight);

  // Add the connection to the graph
  if (graph.addConnection(connection))
  {
    cout << "Connection added successfully." << endl;
  }
  else
  {
    cout << "Failed to add connection. One or both users not found or "
            "connection already exists."
         << endl;
    delete connection; // Clean up memory
  }
}

void deleteConnectionBetweenUsers(Graph &graph)
{
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
         choiceOfUser != 'n')
  {
    cout << "Invalid choice. Please enter Y/y for yes or N/n for no: ";
    cin >> choiceOfUser;
  }

  if (choiceOfUser == 'Y' || choiceOfUser == 'y')
  {
    if (graph.removeConnection(user1, user2))
    {
      cout << "Connection between " << user1 << " and " << user2
           << " deleted successfully." << endl;
    }
    else
    {
      cout << "Failed to delete connection. Connection between " << user1
           << " and " << user2 << " not found." << endl;
    }
  }
  else
  {
    cout << "Deletion cancelled." << endl;
  }
}

void deleteAllConnectionsOfUser(Graph &graph)
{
  string userName;
  char choiceOfUser;

  cout << "Enter the user name to delete all connections: ";
  cin >> userName;

  cout << "Are you sure that you want to delete all connections of '"
       << userName << "'? (Y/y for yes, N/n for no): ";
  cin >> choiceOfUser;

  while (choiceOfUser != 'Y' && choiceOfUser != 'y' && choiceOfUser != 'N' &&
         choiceOfUser != 'n')
  {
    cout << "Invalid choice. Please enter Y/y for yes or N/n for no: ";
    cin >> choiceOfUser;
  }

  if (choiceOfUser == 'Y' || choiceOfUser == 'y')
  {
    graph.deleteConnectionsOfUser(userName);
    cout << "All connections of user '" << userName << "' deleted successfully."
         << endl;
  }
  else
  {
    cout << "Deletion cancelled." << endl;
  }
}

void isUserConnectedToAnother(Graph &graph)
{
  string user1, user2;
  cout << "Enter the first user name: ";
  cin >> user1;
  cout << "Enter the second user name: ";
  cin >> user2;
  if (graph.isConnected(user1, user2))
  {
    cout << "User " << user1 << " is connected to user " << user2 << endl;
  }
  else
  {
    cout << "User " << user1 << " is not connected to user " << user2 << endl;
  }
}

void bfsTraversal(Graph &graph)
{
  string startUserName;
  cout << "Enter the starting user name for BFS traversal: ";
  cin >> startUserName;

  vector<string> bfsTraversal = graph.bfsTraversal(startUserName);
  cout << "BFS Traversal: ";
  for (const auto &user : bfsTraversal)
  {
    cout << user << " ";
  }
  cout << endl;
}

void dfsTraversal(Graph &graph)
{
  string startUserName;
  cout << "Enter the starting user name for DFS traversal: ";
  cin >> startUserName;

  vector<string> dfsTraversal = graph.dfsTraversal(startUserName);
  cout << "DFS Traversal: ";
  for (const auto &user : dfsTraversal)
  {
    cout << user << " ";
  }
  cout << endl;
}

void shortestPathBetweenUsers(Graph &graph)
{
  int choice = 0;
  do
  {
    cout << "Find Shortest Path Using:\n"
         << "1. Djikstra.\n"
         << "2. Bellman Ford.\n"
         << "3. A* algorithm.\n"
         << "4. Return.\n"
         << "Enter your choice: ";
    cin >> choice;

    // Check if choice is to return to the menu
    if (choice == 4)
    {
      // Exit loop and return to the menu
      break;
    }

    string user1, user2;
    cout << "Enter the first user name: ";
    cin >> user1;

    // Check if user1 is valid
    if (!graph.searchUser(user1))
    {
      cout << "User not found. Please enter a valid user name." << endl;
      continue;
    }

    // If choice is not to return to the menu, ask for user2
    cout << "Enter the second user name: ";
    cin >> user2;

    // Check if user2 is valid
    if (!graph.searchUser(user2))
    {
      cout << "User not found. Please enter a valid user name." << endl;
      continue;
    }

    // Perform the selected shortest path algorithm based on choice
    switch (choice)
    {
    case 1:
    {
      vector<UserProfile *> dijkstraPath = graph.dijkstra(user1, user2);
      cout << "Dijkstra Shortest Path from " << user1 << " to " << user2
           << ": ";
      // If no path found
      if (dijkstraPath.empty())
      {
        cout << "No path found." << endl;
        break;
      }
      for (const auto &user : dijkstraPath)
      {
        cout << user->getUserName() << " ";
      }
      cout << endl;
      break;
    }
    case 2:
    {
      vector<string> bellmanFordPath =
          graph.shortestPathUsingBellmandFord(user1, user2);
      cout << "Bellman-Ford Shortest Path from " << user1 << " to " << user2
           << ": ";
      // If no path found
      if (bellmanFordPath.empty())
      {
        cout << "No path found." << endl;
        break;
      }
      for (const auto &user : bellmanFordPath)
      {
        cout << user << " ";
      }
      cout << endl;
      break;
    }
    case 3:
    {
      vector<UserProfile *> astarPath = graph.astar(user1, user2);
      cout << "A* Shortest Path from " << user1 << " to " << user2 << ": ";
      // If no path found
      if (astarPath.empty())
      {
        cout << "No path found." << endl;
        break;
      }
      for (const auto &user : astarPath)
      {
        cout << user->getUserName() << " ";
      }
      cout << endl;
      break;
    }
    default:
      cout << "Invalid choice. Please enter a valid option." << endl;
    }
  } while (true);
}

void getAndDisplayConnectionsOfUser(Graph &graph)
{
  cout << "Enter the user name to get connections: ";
  string userName;
  cin >> userName;
  vector<string> connectedUsers = graph.getConnectedUsers(userName);
  cout << "Connections of user " << userName << ": ";
  for (const auto &user : connectedUsers)
  {
    cout << user << ", ";
  }
  cout << endl;
}

// option 15
void clearGraphWithConfirmation(Graph &graph)
{
  char choiceOfUser;

  do
  {
    cout << "Are you sure? (Y/y for yes, N/n for no) Clearing the graph will remove all connections: ";
    cin >> choiceOfUser;

    if (choiceOfUser == 'Y' || choiceOfUser == 'y')
    {
      graph.clearGraph();
      cout << "Graph cleared." << endl;
      return; // Exit the function after successful clearing
    }
    else if (choiceOfUser == 'N' || choiceOfUser == 'n')
    {
      cout << "Cancelled operation." << endl;
      return; // Exit the function if the user cancels the operation
    }
    else
    {
      cout << "Invalid input. Please enter Y/y or N/n." << endl;
      cin.clear();                                         // Clear any error flags
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the input buffer
    }
  } while (true); // Repeat until a valid choice is entered
}

// option 16
void clearUsersWithConfirmation(Graph &graph)
{
  char choiceOfUser;
  do
  {
    cout << "Are you sure? (Y/y for yes, N/n for no) This option will delete all the users from your graph: ";
    cin >> choiceOfUser;

    if (choiceOfUser == 'Y' || choiceOfUser == 'y')
    {
      graph.clearUsers();
      cout << "All users have been removed from the graph." << endl;
      return;
    }
    else if (choiceOfUser == 'N' || choiceOfUser == 'n')
    {
      cout << "Operation cancelled." << endl;
      return;
    }
    else
    {
      cout << "Invalid input. Please enter Y/y for yes or N/n for no." << endl;
      cin.clear();                                         // Clear any error flags
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the input buffer
    }
  } while (true);
}

// Read users from a file and add them to the graph
void readUsersFromFile(const string &fileName, Graph &graph)
{
  ifstream file(fileName);
  if (!file.is_open())
  {
    cerr << "Unable to open file: " << fileName << endl;
    return;
  }

  string line;
  while (getline(file, line))
  {
    stringstream ss(line);
    string userName, firstName, lastName, email;
    ss >> userName >> firstName >> lastName >> email;

    graph.addUser(new UserProfile(userName, firstName, lastName, email));
  }

  file.close();
}

// Read connections from a file and add them to the graph
void readConnectionsFromFile(const string &folderName, const string &fileName,
                             Graph &graph)
{
  string filePath = folderName + "/" + fileName;
  ifstream file(filePath);
  if (!file.is_open())
  {
    cerr << "Unable to open file: " << filePath << endl;
    return;
  }

  string line;
  while (getline(file, line))
  {
    stringstream ss(line);
    string sourceUserName, destUserName;
    int weight;
    ss >> sourceUserName >> destUserName >> weight;

    UserProfile *sourceUser = graph.searchUser(sourceUserName);
    UserProfile *destUser = graph.searchUser(destUserName);

    if (sourceUser && destUser)
    {
      Connection *connection = new Connection(sourceUser, destUser, weight);
      graph.addConnection(connection);
    }
  }

  file.close();
}