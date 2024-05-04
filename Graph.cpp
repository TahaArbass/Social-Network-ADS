#include "Graph.h"
#include "Connection.h"
#include "UserProfile.h"
#include <algorithm>
#include <fstream>
#include <limits>
#include <unordered_map>
#include <unordered_set>

// Default constructor
Graph::Graph() {}

// Destructor to clean up dynamically allocated memory
Graph::~Graph() {
  // Clear the adjacency list
  clearGraph();

  // Delete user profiles
  for (auto &user : users) {
    delete user.second;
  }
  users.clear();
}

// Function to add a user to the graph
bool Graph::addUser(UserProfile *user) {
  if (user == nullptr) {
    return false;
  }

  string username = user->getUserName();
  if (users.find(username) == users.end()) {
    users[username] = user;
    return true;
  }
  return false;
}

// Function to add an edge/connection between user1 and user2
bool Graph::addConnection(Connection *connection) {
  // Check if the connection is valid
  if (connection != nullptr) {
    string user1 = connection->getSource()->getUserName();
    string user2 = connection->getDestination()->getUserName();
    // Check if the users are already connected
    if (!isConnected(user1, user2)) {
      // Add the connection to the adjacency list (undirected graph)
      adj[user1].push_back(connection);
      adj[user2].push_back(
          new Connection(users[user2], users[user1], connection->getWeight()));
      return true;
    }
  }

  return false;
}
// Function to delete all connections of a user
void Graph::deleteConnectionsOfUser(const string &username) {
  if (adj.find(username) != adj.end()) {
    for (auto connection : adj[username]) {
      string dest = connection->getDestination()->getUserName();
      adj[dest].remove(connection);
      delete connection;
    }
    adj[username].clear();

    // Remove any connections pointing to the user
    for (auto &entry : adj) {
      entry.second.remove_if([username](Connection *connection) {
        return connection->getDestination()->getUserName() == username;
      });
    }
  }
}

// Function to remove a user from the graph
bool Graph::removeUser(const string &username) {
  if (users.find(username) != users.end()) {
    // Delete all connections of the user
    deleteConnectionsOfUser(username);
    // Delete the user profile
    delete users[username];
    users.erase(username);
    return true;
  }
  return false;
}

// Function to remove an edge/connection between user1 and user2
bool Graph::removeConnection(const string &src, const string &dest) {
  // Check if the source user and destination exist in the graph
  if (adj.find(src) != adj.end()) {
    // Iterate through the connections of the source user
    for (auto connection : adj[src]) {
      // Check if the destination user is connected to the source user
      if (connection->getDestination()->getUserName() == dest) {
        // Remove the connection from the adjacency list
        adj[src].remove(connection);
        // adj[dest].remove(connection);
        delete connection;
        for (auto connection2 : adj[dest]) {
          if (connection2->getDestination()->getUserName() == src) {
            adj[dest].remove(connection2);
            delete connection2;
            return true;
          }
        }
      }
    }
  }
  return false;
}

bool Graph::isUserNameTaken(const string &userName) {
  if (users.find(userName) != users.end()) {
    return true;
  }
  return false;
}

void Graph::displayUserInfo(const string &userName) {
  // Check if the user exists in the graph
  if (users.find(userName) != users.end()) {
    // Retrieve the user profile
    UserProfile *user = users[userName];

    // Display user information using the UserProfile function
    cout << user->displayUserInfo() << endl;
  } else {
    cout << "User '" << userName << "' not found." << endl;
  }
}

// Function to search for a user in the graph
UserProfile *Graph::searchUser(const string &username) {
  if (users.find(username) != users.end()) {
    return users[username];
  }
  return nullptr;
}

// Function to print the adjacency list representation of the graph
void Graph::printGraph() {
  if (adj.empty()) {
    cout << "Graph is empty" << endl;
    return;
  }

  for (const auto &entry : adj) {
    cout << "Connections of user " << entry.first << "\n";
    cout << "Connected with: ";
    for (auto connection : entry.second) {
      cout << connection->getDestination()->getUserName() << ", ";
    }
    cout << endl;
  }
}

// Function to check if a user is connected to another user
bool Graph::isConnected(const string &src, const string &dest) {
  // Check if the source user exists in the graph
  if (adj.find(src) != adj.end()) {
    // Iterate through the connections of the source user
    for (auto connection : adj[src]) {
      // Check if the destination user is connected to the source user
      if (connection->getDestination()->getUserName() == dest) {
        return true;
      }
    }
  }
  return false;
}

// Function to empty the graph
void Graph::clearGraph() {
  // Clear the adjacency list
  for (auto &pair : adj) {
    pair.second.clear();
  }
  adj.clear();
}

// Function to remove all users
void Graph::clearUsers() {
  // Clear the adjacency list
  clearGraph();

  // Clear the users map
  for (auto &user : users) {
    delete user.second;
  }
  users.clear();
}

// Function to get the number of users in the graph
int Graph::getNumOfUsers() { return users.size(); }

// Function to get the number of connections in the graph
int Graph::getNumOfConnections() {
  int count = 0;
  for (const auto &entry : adj) {
    count += entry.second.size();
  }
  // Since each connection is counted twice in an undirected graph
  // we divide the total count by 2 to get the actual number of connections
  return count / 2;
}

// Function to perform Breadth First Search traversal
vector<string> Graph::bfsTraversal(const string &startUserName) {
  vector<string> traversalResult;

  if (users.find(startUserName) == users.end()) {
    cout << "User " << startUserName << " does not exist in the graph." << endl;
    return traversalResult;
  }

  unordered_set<string> visited;
  queue<string> userQueue;

  visited.insert(startUserName);
  userQueue.push(startUserName);
  while (!userQueue.empty()) {
    string currentUser = userQueue.front();
    userQueue.pop();

    traversalResult.push_back(currentUser);

    if (adj.find(currentUser) != adj.end()) {
      for (auto connection : adj[currentUser]) {
        string neighborUserName = connection->getDestination()->getUserName();
        if (visited.find(neighborUserName) == visited.end()) {
          visited.insert(neighborUserName);
          userQueue.push(neighborUserName);
        }
      }
    }
  }

  return traversalResult;
}

// A star algorithm to find the shortest path between two users
vector<UserProfile *> Graph::astar(const string &startUserName,
                                   const string &goalUserName) {
  // Heuristic function: estimate of the distance from a node to the goal
  auto heuristic = [](UserProfile *current, UserProfile *goal) {
    // Example heuristic: Manhattan distance between user IDs
    int dx = abs(current->getUserId() - goal->getUserId());
    return dx;
  };

  // Priority queue for open set
  priority_queue<pair<int, UserProfile *>, vector<pair<int, UserProfile *>>,
                 greater<pair<int, UserProfile *>>>
      openSet;

  // Closed set to store visited nodes
  unordered_set<UserProfile *> closedSet;

  // Map to track parent nodes for reconstructing the path
  unordered_map<UserProfile *, UserProfile *> cameFrom;

  // Map to store g-score (cost from start to current)
  unordered_map<UserProfile *, int> gScore;

  // Initialize g-score for start node
  gScore[users[startUserName]] = 0;

  // Add start node to open set with estimated total cost (f-score)
  openSet.emplace(heuristic(users[startUserName], users[goalUserName]),
                  users[startUserName]);

  while (!openSet.empty()) {
    // Get the node with the lowest f-score from the open set
    auto current = openSet.top().second;
    openSet.pop();

    // If the current node is the goal, reconstruct and return the path
    if (current->getUserName() == goalUserName) {
      vector<UserProfile *> path;
      while (current) {
        path.push_back(current);
        current = cameFrom[current];
      }
      reverse(path.begin(), path.end());
      return path;
    }

    // Add current node to the closed set
    closedSet.insert(current);

    // Iterate through the neighbors of the current node
    for (auto connection : adj[current->getUserName()]) {
      auto neighbor = connection->getDestination();

      // If neighbor is in the closed set, skip it
      if (closedSet.find(neighbor) != closedSet.end())
        continue;

      // Calculate tentative g-score for the neighbor
      int tentativeGScore = gScore[current] + connection->getWeight();

      // If neighbor is not in the open set or new g-score is lower
      if (gScore.find(neighbor) == gScore.end() ||
          tentativeGScore < gScore[neighbor]) {
        // Update cameFrom and g-score for the neighbor
        cameFrom[neighbor] = current;
        gScore[neighbor] = tentativeGScore;

        // Add neighbor to the open set with estimated total cost (f-score)
        int fscore = tentativeGScore + heuristic(neighbor, users[goalUserName]);
        openSet.emplace(fscore, neighbor);
      }
    }
  }

  // If no path found, return an empty vector
  return {};
}

// Djikstra's algorithm to find the shortest path between two users
vector<UserProfile *> Graph::dijkstra(const string &startUserName,
                                      const string &endUserName) {
  // Priority queue to store vertices according to their distances
  priority_queue<pair<int, string>, vector<pair<int, string>>,
                 greater<pair<int, string>>>
      pq;

  // Map to store distances from the source vertex
  unordered_map<string, int> distance;

  // Initialize distances to infinity
  for (const auto &entry : users) {
    distance[entry.first] = numeric_limits<int>::max();
  }

  // Mark the distance of the source vertex as 0
  distance[startUserName] = 0;

  // Push the source vertex into the priority queue
  pq.push({0, startUserName});

  // Map to store parent vertices
  unordered_map<string, string> parent;

  // Perform Dijkstra's algorithm
  while (!pq.empty()) {
    string u = pq.top().second;
    pq.pop();

    for (const auto &connection : adj[u]) {
      string v = connection->getDestination()->getUserName();
      int weight = connection->getWeight();

      // Relaxation step
      if (distance[u] + weight < distance[v]) {
        distance[v] = distance[u] + weight;
        pq.push({distance[v], v});
        parent[v] = u;
      }
    }
  }

  // Reconstruct the shortest path if it exists
  vector<UserProfile *> shortestPath;
  if (distance[endUserName] != numeric_limits<int>::max()) {
    string currentVertex = endUserName;
    while (currentVertex != startUserName) {
      shortestPath.push_back(users[currentVertex]);
      currentVertex = parent[currentVertex];
    }

    shortestPath.push_back(users[startUserName]);

    reverse(shortestPath.begin(), shortestPath.end());
  }

  return shortestPath;
}

unordered_map<string, pair<int, string>>
Graph::bellmanFordShortestPath(const string &startNode) {
  // Initialize distance map with infinite distance for all nodes
  unordered_map<string, pair<int, string>> distance;
  for (auto &entry : users) {
    distance[entry.first] = {numeric_limits<int>::max(), ""};
  }
  distance[startNode] = {0, startNode};

  // Relax all edges repeatedly
  for (int i = 0; i < users.size() - 1; ++i) {
    for (const auto &entry : adj) {
      string u = entry.first;
      for (auto connection : entry.second) {
        string v = (connection->getSource()->getUserName() == u)
                       ? connection->getDestination()->getUserName()
                       : connection->getSource()->getUserName();
        int weight = connection->getWeight();
        if (distance[u].first != numeric_limits<int>::max() &&
            distance[u].first + weight < distance[v].first) {
          distance[v] = {distance[u].first + weight, u};
        }
      }
    }
  }

  // Check for negative weight cycles
  for (const auto &entry : adj) {
    string u = entry.first;
    for (auto connection : entry.second) {
      string v = (connection->getSource()->getUserName() == u)
                     ? connection->getDestination()->getUserName()
                     : connection->getSource()->getUserName();
      int weight = connection->getWeight();
      if (distance[u].first != numeric_limits<int>::max() &&
          distance[u].first + weight < distance[v].first) {
        cout << "Graph contains negative weight cycle" << endl;
        return {};
      }
    }
  }

  return distance;
}

vector<string> Graph::shortestPathUsingBellmandFord(const string &startNode,
                                                    const string &endNode) {
  // Use Bellman-Ford to find shortest paths
  unordered_map<string, pair<int, string>> shortestPaths =
      bellmanFordShortestPath(startNode);

  // Reconstruct the shortest path
  vector<string> path;
  string current = endNode;
  while (current != startNode) {
    path.push_back(current);
    current = shortestPaths[current].second;
    if (current.empty()) {
      cout << "No path exists between " << startNode << " and " << endNode
           << endl;
      return {};
    }
  }
  path.push_back(startNode);
  reverse(path.begin(), path.end());

  return path;
}

vector<string> Graph::getConnectedUsers(const string &userName) {
  vector<string> connectedUsers;

  if (users.find(userName) != users.end()) {
    if (adj.find(userName) != adj.end()) {
      for (auto connection : adj[userName]) {
        string connectedUserName = connection->getDestination()->getUserName();
        connectedUsers.push_back(connectedUserName);
      }
    }
  }

  return connectedUsers;
}

void Graph::generateDOTFile(const string &fileName) {
  ofstream dotFile(fileName);
  if (!dotFile.is_open()) {
    cerr << "Error: Unable to open DOT file for writing\n";
    return;
  }

  // Write DOT file header
  dotFile << "graph G {\n";
  dotFile << "  graph [splines=true, overlap=false];\n";
  dotFile << "  node [style=filled, fillcolor=\"#f0f0f0\", shape=ellipse, "
             "fontcolor=black, fontsize=16];\n";
  dotFile << "  edge [fontcolor=\"black\", fontsize=12, color=\"#3366ff\", "
             "penwidth=3];\n";

  // Write node properties
  for (const auto &entry : users) {
    string userName = entry.first;
    dotFile << "  " << userName << ";\n";
  }

  // Write edge properties
  unordered_set<string> processedEdges;
  for (const auto &entry : adj) {
    const string &source = entry.first;
    for (const auto &connection : entry.second) {
      const string &destination = connection->getDestination()->getUserName();
      if (source < destination) {
        string edge = source + " -- " + destination;
        if (processedEdges.find(edge) == processedEdges.end()) {
          processedEdges.insert(edge);
          dotFile << "  " << edge << " [label=\"" << connection->getWeight()
                  << "\"];\n";
        }
      }
    }
  }

  // Write DOT file footer
  dotFile << "}\n";

  dotFile.close();
}

// Function to render the graph visualization using Graphviz
void Graph::renderGraph(const string &dotFileName,
                        const string &outputFileName) {
  // Invoke Graphviz to render the DOT file
  string command = "dot -Tpng " + dotFileName + " -o " + outputFileName;
  int result = system(command.c_str());
  if (result != 0) {
    cerr << "Error: Failed to render graph using Graphviz\n";
    return;
  }

  cout << "Graph visualization saved as " << outputFileName << endl;
  command = "start " + outputFileName;
  system(command.c_str());
}

// Function to perform Depth First Search traversal
vector<string> Graph::dfsTraversal(const string &startUserName) {
  // Vector to store the path of visited nodes
  vector<string> path;

  // Check if startUserName exists in the graph
  if (users.find(startUserName) == users.end()) {
    cout << "User " << startUserName << " does not exist in the graph." << endl;
    return path;
  }

  // Set to keep track of visited nodes
  unordered_set<string> visited;

  // Perform DFS traversal
  dfsUtil(startUserName, visited, path);

  return path;
}

// Utility function for DFS traversal
void Graph::dfsUtil(const string &node, unordered_set<string> &visited,
                    vector<string> &path) {
  // Mark the current node as visited
  visited.insert(node);
  path.push_back(node);

  // Traverse all adjacent nodes of the current node
  for (auto connection : adj[node]) {
    string neighbor = (connection->getSource()->getUserName() == node)
                          ? connection->getDestination()->getUserName()
                          : connection->getSource()->getUserName();
    if (visited.find(neighbor) == visited.end()) {
      dfsUtil(neighbor, visited, path);
    }
  }
}

// Function to calculate the average degree of the graph
double Graph::calculateAverageDegree() {
  if (adj.empty() || users.empty()) {
    return 0.0;
  }

  double totalDegree = 0.0;
  for (const auto &entry : adj) {
    totalDegree += entry.second.size();
  }

  return totalDegree / users.size();
}

// Function to calculate the diameter of the graph
int Graph::calculateDiameter() {
  if (users.empty()) {
    return -1;
  }

  int diameter = 0;
  const int INF = std::numeric_limits<int>::max(); // Declare INF constant

  // Iterate through each vertex and find the maximum shortest path
  for (const auto &entry : users) {
    const string &src = entry.first;
    vector<int> dist = shortestPath(src);

    // Find the maximum distance in the shortest paths
    for (int d : dist) {
      if (d != INF && d > diameter) {
        diameter = d;
      }
    }
  }

  return diameter;
}

// Function to calculate shortest paths from a source node
vector<int> Graph::shortestPath(const string &src) {
  const int INF = std::numeric_limits<int>::max(); // Declare INF constant
  unordered_map<string, int>
      distance;    // Map to store distances from the source node
  queue<string> q; // Queue for BFS traversal

  // Initialize distances
  for (const auto &entry : users) {
    distance[entry.first] = INF;
  }

  // Enqueue the source node
  q.push(src);
  distance[src] = 0;

  // Perform BFS
  while (!q.empty()) {
    string u = q.front();
    q.pop();
    // Iterate through all adjacent nodes of u
    for (auto connection : adj[u]) {
      string v = (connection->getSource()->getUserName() == u)
                     ? connection->getDestination()->getUserName()
                     : connection->getSource()->getUserName();
      // If v is not visited yet
      if (distance[v] == INF) {
        distance[v] = distance[u] + 1;
        q.push(v);
      }
    }
  }

  // Convert distances to vector
  vector<int> dist;
  for (const auto &entry : users) {
    dist.push_back(distance[entry.first]);
  }
  return dist;
}

// Function to write Connections to a file
void Graph::writeConnectionsToFile(const string &fileName) {
  // open the file in trunc mode to overwrite the existing data
  ofstream outFile(fileName, ios::trunc);
  if (outFile.is_open()) {
    // check if the graph is empty
    if (!adj.empty()) {
      for (const auto &pair : adj) {
        const string &user = pair.first;
        const list<Connection *> &connections = pair.second;
        for (const auto &connection : connections) {
          const string &sourceUser = user;
          const string &destinationUser =
              connection->getDestination()->getUserName();
          if (sourceUser < destinationUser) {
            outFile << sourceUser << " " << destinationUser << " "
                    << connection->getWeight() << "\n";
          }
        }
      }
      cout << "Connection data has been written to " << fileName
           << " successfully." << endl;
    } else {
      cout << "The graph is empty. No connection data to write." << endl;
    }
    outFile.close();
  } else {
    cerr << "Unable to open file: " << fileName << endl;
  }
}

// Function to write Users to a file
void Graph::writeUsersToFile(const string &fileName) {
  // open the file in trunc mode to overwrite the existing data
  ofstream outFile(fileName, ios::trunc);
  if (outFile.is_open()) {
    // check if the graph is empty
    if (!users.empty()) {
      for (auto const &pair : users) {
        const string &userName = pair.first;
        UserProfile *user = pair.second;
        outFile << user->getUserName() << " " << user->getFirstName() << " "
                << user->getLastName() << " " << user->getEmail() << "\n";
      }
      cout << "User data has been written to " << fileName << " successfully."
           << endl;
    } else {
      cout << "The graph is empty. No user data to write." << endl;
    }
    outFile.close();
  } else {
    cerr << "Unable to open file: " << fileName << endl;
  }
}
