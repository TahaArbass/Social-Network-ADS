#include <iostream>
#include "Connection.h"
#include "UserProfile.h"
#include "Graph.h"
#include <random>

void addUserToGraph(Graph &graph);
void deleteUserFromGraph(Graph &graph);
void addConnectionBetweenUsers(Graph &graph);
void deleteConnectionBetweenUsers(Graph &graph);
void deleteAllConnectionsOfUser(Graph &graph);
int main()
{
    Graph graph;

    int choice;
    char choiceOfUser;
    string userName;
    do
    {
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
            cout << "\nThe number of Users : " << graph.getNumOfUsers()<<endl;
            break;
        case 7:
            // Get number of connections
            cout << "\nThe number of connections : " << graph.getNumOfConnections()<<endl;
            break;
        case 8:
            // Is a user connected directly to another?
            // Implement is connected functionality
            break;
        case 9:
            // Breadth First Search (BFS) Traversal
            // Implement BFS traversal functionality
            break;
        case 10:
            // Depth First Search (DFS) Traversal
            // Implement DFS traversal functionality
            break;
        case 11:
            // Find shortest path between 2 users
            // Implement shortest path functionality
            break;
        case 12:
            // Get all connections of a user
            // Implement get all connections functionality
            break;
        case 13:
            // Display graph analysis
            // Implement display graph analysis functionality
            break;
        case 14:
            // Visualize graph
            // Implement graph visualization functionality
            break;
        case 15:
            // Clear graph
            // Implement clear graph functionality
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
            cout << "The username '" << username << "' is already taken. Please try a different one." << endl;
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
        cout << "Are you sure that you want to delete the user '" << userName << "'? Deleting will remove all the connections associated with the user. (Y/y for yes, N/n for no): ";
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
    cout << "Enter the second user name: ";
    cin >> user2;
    cout << "Enter the weight of the connection: ";
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
        cout << "Failed to add connection. One or both users not found or connection already exists." << endl;
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

    cout << "Are you sure that you want to delete the connection between '" << user1 << "' and '" << user2 << "'? (Y/y for yes, N/n for no): ";
    cin >> choiceOfUser;

    while (choiceOfUser != 'Y' && choiceOfUser != 'y' && choiceOfUser != 'N' && choiceOfUser != 'n')
    {
        cout << "Invalid choice. Please enter Y/y for yes or N/n for no: ";
        cin >> choiceOfUser;
    }

    if (choiceOfUser == 'Y' || choiceOfUser == 'y')
    {
        if (graph.removeConnection(user1, user2))
        {
            cout << "Connection between " << user1 << " and " << user2 << " deleted successfully." << endl;
        }
        else
        {
            cout << "Failed to delete connection. Connection between " << user1 << " and " << user2 << " not found." << endl;
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

    cout << "Are you sure that you want to delete all connections of '" << userName << "'? (Y/y for yes, N/n for no): ";
    cin >> choiceOfUser;

    while (choiceOfUser != 'Y' && choiceOfUser != 'y' && choiceOfUser != 'N' && choiceOfUser != 'n')
    {
        cout << "Invalid choice. Please enter Y/y for yes or N/n for no: ";
        cin >> choiceOfUser;
    }

    if (choiceOfUser == 'Y' || choiceOfUser == 'y')
    {
        graph.deleteConnectionsOfUser(userName);
        cout << "All connections of user '" << userName << "' deleted successfully." << endl;
    }
    else
    {
        cout << "Deletion cancelled." << endl;
    }
}