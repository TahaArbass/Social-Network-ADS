int main()
{
    // Create user profiles
    UserProfile *user1 = new UserProfile("user1", "John", "Doe", "john@example.com");
    UserProfile *user2 = new UserProfile("user2", "Jane", "Smith", "jane@example.com");

    // Create connection between user profiles
    Connection connection(user1, user2, 5);

    // Display connection info
    std::cout << "Connection Info:\n";
    std::cout << connection.displayInfo();

    Graph graph;
    if (graph.addConnection(&connection))
    {
        std::cout << "Connection added successfully\n";
    }
    if (graph.isConnected("user1", "user2"))
    {
        std::cout << "Users are connected\n";
    }
    else
    {
        std::cout << "Users are not connected\n";
    }
    graph.bfsTraversal(user1->getUserName());

    // graph.clearGraph();
    // graph.printGraph();

    return 0;