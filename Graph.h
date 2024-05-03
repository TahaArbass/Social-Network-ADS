#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// Forward declaration of Connection and UserProfile classes
class Connection;
class UserProfile;

/******************************************************************************
 * Class: Graph
 *
 * Description: Represents a graph data structure to
 *                                   store users and connections between them.
 *
 * Member Variables:
 *    - users: An unordered map to store user profiles.
 *    - adj: An unordered map representing the adjacency list
 *                                          to store connections between users.
 *
 *****************************************************************************/
class Graph
{
public:
  /***** Constructors and Destructor *****/
  // Default Constructor
  Graph();
  /*-------------------------------------------------------------------------
    Constructs an empty graph.

    Preconditions: None.
    Postconditions: An empty graph object is created.
  -------------------------------------------------------------------------*/

  // Destructor to clean up dynamically allocated memory
  ~Graph();
  /*-------------------------------------------------------------------------
    Destroys the graph object and deallocates memory.

    Preconditions: None.
    Postconditions: All dynamically allocated memory is freed.
  -------------------------------------------------------------------------*/

  /***** Connection Management *****/
  // Function to add an edge/connection between user1 and user2
  bool addConnection(Connection *connection);
  /*-------------------------------------------------------------------------
    Adds a connection between two users in the graph.

    Preconditions:
      - 'connection' is a valid Connection object.

    Postconditions: The connection is added to the graph.
  -------------------------------------------------------------------------*/

  // Function to remove an edge/connection between user1 and user2
  bool removeConnection(const string &src, const string &dest);
  /*-------------------------------------------------------------------------
    Removes a connection between two users in the graph.

    Preconditions:
      - 'src' and 'dest' are valid usernames representing users in the graph.

    Postconditions: If the connection exists, it is removed from the graph.
  -------------------------------------------------------------------------*/

  /***** User Management *****/
  void displayUserInfo(const string &userName);
  /*-------------------------------------------------------------------------
    Display user information for the specified username.

    Preconditions:
      - 'userName' is a valid username in the graph.

    Postconditions:
      - If the user exists in the graph, their information is displayed.
      - Otherwise, an error message is displayed.
      */

  bool isUserNameTaken(const string &userName);
  /*-------------------------------------------------------------------------
    Check if a username is already taken.

    Preconditions:
      - 'userName' is a valid string representing a username.

    Postconditions:
      - Returns true if the username is already in use; otherwise, false.
      */

  void deleteConnectionsOfUser(const string &username);
  /*-------------------------------------------------------------------------
      Delete all connections of a user.

      Preconditions:
        - 'username' is a valid username in the graph.

      Postconditions:
        - All connections associated with the specified user are removed.
  */

  vector<string> getConnectedUsers(const string &userName);
  /*-------------------------------------------------------------------------
      Get a list of usernames connected to the specified user.

      Preconditions:
        - 'userName' is a valid username in the graph.

      Postconditions:
        -Returns a vector containing usernames connected to the specified user.
        */

  UserProfile *searchUser(const string &username);
  /*-------------------------------------------------------------------------
    Search for a user by username.

    Preconditions:
      - 'username' is a valid username.

    Postconditions:
   - Returns a pointer to the UserProfile object if found; otherwise, nullptr.
      */
  bool addUser(UserProfile *user);
  /*-------------------------------------------------------------------------
    Add a new user to the graph.

    Preconditions:
      - 'user' is a valid pointer to a UserProfile object.

    Postconditions:
      - If the user is successfully added, returns true; otherwise, false.
      */

  bool removeUser(const string &username);
  /*-------------------------------------------------------------------------
    Remove a user from the graph.

    Preconditions:
      - 'username' is a valid username in the graph.

    Postconditions:
      - If the user is successfully removed, returns true; otherwise, false.
      */

  /***** Graph Information *****/
  int getNumOfUsers();
  /*-------------------------------------------------------------------------
    Get the number of users in the graph.

    Preconditions: None.

    Postconditions: Returns the total number of users in the graph.
    */
  int getNumOfConnections();
  /*-------------------------------------------------------------------------
    Get the number of connections in the graph.

    Preconditions: None.

    Postconditions: Returns the total number of connections in the graph.
    */
  bool isConnected(const string &src, const string &dest);
  /*-------------------------------------------------------------------------
    Check if there is a connection between two users.

    Preconditions:
      - 'src' and 'dest' are valid usernames.

    Postconditions:
  - Returns true if there is a connection between the users; otherwise, false.
      */

  /***** Graph Operations *****/
  void clearGraph();
  /*-------------------------------------------------------------------------
    Clear the entire graph.

    Preconditions: None.

    Postconditions: Removes all users and connections from the graph.
    */
  void clearUsers();
  /*-------------------------------------------------------------------------
    Clear all users from the graph.

    Preconditions: None.

    Postconditions: Removes all users from the graph
                                       while keeping connections intact.
    */
  void printGraph();
  /*-------------------------------------------------------------------------
   Print the adjacency list representation of the graph.

   Preconditions: None.

   Postconditions: Prints the graph structure to the console.
   */
  vector<string> dfsTraversal(const string &startUserName);
  /*-------------------------------------------------------------------------
  Perform Depth First Search (DFS) traversal starting from the specified user.

    Preconditions:
      - 'startUserName' is a valid username in the graph.

  Postconditions: Returns a vector containing the usernames visited during DFS.
*/
  vector<string> bfsTraversal(const string &startUserName);
  /*-------------------------------------------------------------------------
Perform Breadth First Search (BFS) traversal starting from the specified user.

    Preconditions:
      - 'startUserName' is a valid username in the graph.

Postconditions: Returns a vector containing the usernames visited during BFS.
    */
  vector<UserProfile *> astar(const string &startUserName,
                              const string &goalUserName);
  /*-------------------------------------------------------------------------
    Find the shortest path between two users using A* algorithm.

    Preconditions:
      - 'startUserName' and 'goalUserName' are valid usernames in the graph.

    Postconditions: Returns a vector containing
     the UserProfile pointers representing the shortest path between the users.
    */
  vector<UserProfile *> dijkstra(const string &startUserName,
                                 const string &endUserName);
  /*-------------------------------------------------------------------------
    Find the shortest path between two users using Dijkstra's algorithm.

    Preconditions:
      - 'startUserName' and 'endUserName' are valid usernames in the graph.

    Postconditions: Returns a vector containing the UserProfile
               pointers representing the shortest path between the users.
    */
  unordered_map<string, pair<int, string>>
  bellmanFordShortestPath(const string &startNode);
  /*-------------------------------------------------------------------------
    Find the shortest path from a source node
                              to all other nodes using Bellman-Ford algorithm.

    Preconditions:
      - 'startNode' is a valid username in the graph.

    Postconditions: Returns an unordered map containing the shortest distances and
    predecessors for each node.
    */
  vector<string> shortestPathUsingBellmandFord(const string &startNode,
                                               const string &endNode);
  /*-------------------------------------------------------------------------
    Find the shortest path between two nodes using Bellman-Ford algorithm.

    Preconditions:
      - 'startNode' and 'endNode' are valid usernames in the graph.

    Postconditions: Returns a vector containing the usernames representing the
    shortest path between the nodes.
    */
  void generateDOTFile(const string &fileName);
  /*-------------------------------------------------------------------------
    Generate a DOT file representation of the graph.

    Preconditions:
      - 'fileName' is a valid filename for the DOT file.

    Postconditions: Generates a DOT file representing the graph structure.
    */
  void renderGraph(const string &dotFileName, const string &outputFileName);
  /*-------------------------------------------------------------------------
     Render the graph visualization from a DOT file.

    Preconditions:
      - 'dotFileName' is a valid filename for the DOT file.
      - 'outputFileName' is a valid filename for the output image.

    Postconditions: Renders the graph visualization to an image file
  */
  double calculateAverageDegree();
  /*-------------------------------------------------------------------------
    Calculate the average degree of the graph.

    Preconditions: None.

    Postconditions: Returns the average degree of the graph.
    */
  int calculateDiameter();
  /*-------------------------------------------------------------------------
    Calculate the diameter of the graph.

    Preconditions: None.

    Postconditions: Returns the diameter of the graph.
  -------------------------------------------------------------------------*/

private:
  /***** Private Functions *****/
  void dfsUtil(const string &node, unordered_set<string> &visited,
               vector<string> &path);
  /*-------------------------------------------------------------------------
    Utility function for Depth First Search (DFS) traversal.

    Parameters:
      - 'node': The current node being visited.
      - 'visited': Set containing visited nodes.
      - 'path': Vector representing the path traversed during DFS.

    Preconditions:
      - 'node' is a valid username in the graph.
      - 'visited' is a valid unordered_set.
      - 'path' is a valid vector.

    Postconditions:
      - The 'visited' set is updated to include the current node.
      - The 'path' vector is updated with the current node.
      */
  vector<int> shortestPath(const string &src);
  /*-------------------------------------------------------------------------
    Find the shortest path from a source node to
                       all other nodes using Dijkstra's algorithm.

    Parameters:
      - 'src': The source node from which to find the shortest paths.

    Preconditions:
      - 'src' is a valid username in the graph.

    Postconditions:
      - Returns a vector containing the shortest distances
                       from the source node to all other nodes.
  -------------------------------------------------------------------------*/

  /***** Member Variables *****/
  unordered_map<string, UserProfile *> users;    // user profiles
  unordered_map<string, list<Connection *>> adj; // adjacency list
};

#endif