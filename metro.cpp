#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <set>
#include <algorithm>
#include <climits>
#include <string>
#include <limits>
namespace std
{
    template <>
    struct hash<std::pair<int, int>>
    {
        size_t operator()(const std::pair<int, int> &p) const
        {
            // Custom hash function for std::pair<int, int>
            return std::hash<int>()(p.first) ^ std::hash<int>()(p.second);
        }
    };
}

class Edge
{
    int E_id{};
    int Distance{};
    std::string color;

public:
    Edge() = default;
    Edge(int id, int distance, const std::string &edgeColor = "") : E_id{id}, Distance{distance}, color(edgeColor) {}

    const int get_id() const
    {
        return E_id;
    }

    const int &get_distance() const
    {
        return Distance;
    }
    const std::string &get_color() const
    {
        return color;
    }
    const void set_distance(int distance)
    {
        Distance = distance;
    }
    bool operator==(const int &value) const
    {
        return E_id == value;
    }
};

class Vertex
{
    int V_id{};
    std::string Name{};
    int distance{};
    int predecessor{};

public:
    Vertex() = default;
    std::list<Edge> edges;
    Vertex(int id, std::string name) : V_id{id}, Name{name} {}
    std::vector<std::string> linecolor;

    const int &get_predecessor() const
    {
        return predecessor;
    }

    const void set_predecessor(const int &path)
    {
        predecessor = path;
    }

    const int &get_distance() const
    {
        return distance;
    }

    const void set_distance(const int &num)
    {
        distance = num;
    }

    const int &get_id() const
    {
        return V_id;
    }

    const void set_name(const std::string &name)
    {
        Name = name;
    }

    const std::string &get_name() const
    {
        return Name;
    }

    void printEdgeList()
    {
        std::cout << " [ ";
        for (const auto n : edges)
        {
            std::cout << std::setw(6) << n.get_id() << std::setw(6) << n.get_distance() << std::setw(6) << " --> ";
        }
        std::cout << " ] \n"
                  << std::endl;
    }

    bool checkIfEdgeexist(const int &id)
    {
        for (auto &ed : edges)
        {
            if (ed.get_id() == id)
            {
                return true;
            }
        }
        return false;
    }

    const std::string getLineColor(int destination) const
    {
        for (const auto &edge : edges)
        {
            if (edge.get_id() == destination)
            {
                return edge.get_color();
            }
        }
        return "Unknown"; // Default color if not found
    }

    bool operator==(const int &value) const
    {
        return V_id == value;
    }

    bool operator>(const Vertex &rhs) const
    {
        return get_distance() > rhs.get_distance();
    }

    bool operator<(const Vertex &other) const
    {
        return get_distance() < other.get_distance();
    }
};

class Graph
{
public:
    Graph() = default;
    std::vector<Vertex> vertices;
    std::unordered_map<std::pair<int, int>, std::string> edgeColors; // Store edge colors using source-destination pair as the key
    std::unordered_map<std::pair<int, int>, int> edgeDistances;      // Store edge distances using source-destination pair as the key

    void insert(const Vertex &newvertex)
    {
        if (!checkIfvertexExist(newvertex.get_id()))
        {
            vertices.push_back(newvertex);
            std::cout << "Added succesfully" << std::endl;
        }
        else
        {
            std::cout << "Already exist in the graph " << std::endl;
        }
    }

    void addEdge(const int &source, const int &destination, const int &distance, const std::string &color = "")
    {
        auto sourceIt = std::find_if(vertices.begin(), vertices.end(), [&source](const Vertex &v)
                                     { return v.get_id() == source; });

        auto destIt = std::find_if(vertices.begin(), vertices.end(), [&destination](const Vertex &v)
                                   { return v.get_id() == destination; });

        if (sourceIt != vertices.end() && destIt != vertices.end())
        {
            Vertex &sourceVertex = *sourceIt;
            if (!sourceVertex.checkIfEdgeexist(destination))
            {
                Edge e(destination, distance, color);
                sourceVertex.edges.push_back(e);
                edgeColors[{source, destination}] = color;       // Store edge color
                edgeDistances[{source, destination}] = distance; // Store edge distance
                std::cout << "Added successfully" << std::endl;
            }
            else
            {
                std::cout << "Edge already exists" << std::endl;
            }
        }
        else
        {
            std::cout << "Either of the vertices does not exist" << std::endl;
        }
    }
    void UpdateEdge(const int &source, const int &destination, const int &distance)
    {
        if (checkIfvertexExist(source) && checkIfvertexExist(destination))
        {
            for (auto &sourceVertex : vertices)
            {
                if (sourceVertex.get_id() == source)
                {
                    for (auto &edge : sourceVertex.edges)
                    {
                        if (edge.get_id() == destination)
                        {
                            edge.set_distance(distance);
                            std::cout << "\nUpdated successfully\n"
                                      << std::endl;
                            return; // Exit the function once you've updated the edge
                        }
                    }
                    std::cout << "\nEdge does not exist between the source and destination\n"
                              << std::endl;
                    return; // Exit the function if the destination vertex was not found
                }
            }
        }
        else
        {
            std::cout << "Either of vertex not exist  " << std::endl;
        }
    }

    void UpdateVertex(const int &id, const std::string &name)
    {
        auto it = std::find_if(vertices.begin(), vertices.end(), [id](const Vertex &vec)
                               { return vec.get_id() == id; });
        if (it != vertices.end())
        {
            it->set_name(name);
        }
    }

    void DeleteEdge(const int &source, const int &destination)
    {
        if (checkIfvertexExist(source) && checkIfvertexExist(destination))
        {
            for (auto &n : vertices)
            {
                if (n.get_id() == source)
                {
                    if (checkIfEdgeExist(source, destination))
                    {
                        // update
                        auto it = std::find(n.edges.begin(), n.edges.end(), destination);
                        if (it != n.edges.end())
                        {
                            n.edges.erase(it);
                            std::cout << "\nDeleted successfully\n"
                                      << std::endl;
                        }
                    }
                    else
                    {
                        std::cout << "\nEdge does not exist between the source and destination\n"
                                  << std::endl;
                    }
                    break;
                }
            }
        }
        else
        {
            std::cout << "Either of vertex not exist  " << std::endl;
        }
    }
    void DeleteVector(const int &id)
    {
        if (checkIfvertexExist(id))
        {
            auto it = std::remove_if(vertices.begin(), vertices.end(), [id](const Vertex &vert)
                                     { return vert.get_id() == id; });
            vertices.erase(it, vertices.end()); // Remove the vertex

            // Remove edges associated with the deleted vertex
            for (auto &vertex : vertices)
            {
                vertex.edges.remove_if([id](const Edge &edge)
                                       { return edge.get_id() == id; });
            }
            std::cout << "\nDeleted Vertex successfully\n"
                      << std::endl;
        }
    }

    void print()
    {
        std::cout << std::left << std::setw(12) << "ST_ID's" << std::setw(12) << "Stations_Name " << std::setw(12) << " Connected_Stations_ID_List (CONNECTED STATION TO THIS STATION AND RESPECTIVE DISTANCE IN BETWEEN) " << std::endl;
        for (auto &n : vertices)
        {
            std::cout << "----------------------------------------------------------------------" << std::endl;
            std::cout << std::left << std::setw(12) << n.get_id() << std::setw(12) << n.get_name() << std::setw(12) << " ---> ";
            n.printEdgeList();
        }
    }
    bool checkIfvertexExist(const int &id)
    {
        for (const auto &vec : vertices)
        {
            if (vec.get_id() == id)
                return true;
        }
        return false;
    }
    bool checkIfEdgeExist(const int &source, const int &destination)
    {

        for (const auto &vert : vertices)
        {
            if (vert.get_id() == source)
            {
                auto it = std::find(vert.edges.begin(), vert.edges.end(), destination);
                if (it != vert.edges.end())
                {
                    return true;
                }
            }
        }
        return false;
    }

    void dijkstrabellman(const std::string &startStation, const std::string &endStation)
    {
        // Dijkstra's algorithm
        std::priority_queue<Vertex, std::vector<Vertex>, std::greater<Vertex>> pq;
        std::unordered_set<int> visited;
        int shortestDistance{};

        // Find the vertex corresponding to the start station name
        int startVertex = -1;
        for (const auto &vertex : vertices)
        {
            if (vertex.get_name() == startStation)
            {
                startVertex = vertex.get_id();
                break;
            }
        }

        if (startVertex == -1)
        {
            std::cout << "Start station not found.\n";
            return;
        }

        // Initialize single source
        for (auto &v : vertices)
        {
            if (v.get_id() == startVertex)
                v.set_distance(0);
            else
                v.set_distance(INT_MAX);
            v.set_predecessor(-1);
        }

        pq.push(vertices.at(startVertex - 1));

        while (!pq.empty())
        {
            Vertex current = pq.top();
            pq.pop();

            int u = current.get_id();

            if (visited.find(u) != visited.end())
                continue;

            visited.insert(u);

            for (const auto &edge : current.edges)
            {
                int v = edge.get_id();
                int weight = edge.get_distance();
                int newDistance = current.get_distance() + weight;

                // Relaxing
                if (newDistance < vertices.at(v - 1).get_distance())
                {
                    vertices.at(v - 1).set_distance(newDistance);
                    vertices.at(v - 1).set_predecessor(u);
                    pq.push(vertices.at(v - 1));
                }
            }
        }

        // Bellman-Ford algorithm to check for negative cycles
        for (const auto &current : vertices)
        {
            for (auto &edge : current.edges)
            {
                int v = edge.get_id();
                int w = edge.get_distance();

                if (current.get_distance() != INT_MAX && current.get_distance() + w < (vertices.at(v - 1).get_distance()))
                {
                    std::cout << "The graph contains negative cycles." << std::endl;
                    return;
                }
            }
        }

        // Printing the results if no negative cycles
        std::cout << "\n>>>> "
                  << "Route Finding Please Wait ....... "
                  << " >>>>" << std::endl;
        std::cout << "Shortest path from station " << startStation << " to station " << endStation << ":\n";

        // Find the vertex corresponding to the end station name
        int endVertex = -1;
        for (const auto &vertex : vertices)
        {
            if (vertex.get_name() == endStation)
            {
                endVertex = vertex.get_id();
                break;
            }
        }

        if (endVertex == -1)
        {
            std::cout << "End station not found.\n";
            return;
        }

        std::vector<std::string> pathStations;
        std::vector<std::string> pathColors;
        std::string currentLineColor;
        int currentVertex = endVertex; // Initialize with the endVertex

        while (currentVertex != startVertex)
        {
            int prevVertexId = vertices.at(currentVertex - 1).get_predecessor();
            std::string color = edgeColors[{currentVertex, prevVertexId}];
            int edgeDistance = edgeDistances[{currentVertex, prevVertexId}];
            shortestDistance += edgeDistance; // Add edge distance to the shortestDistance

            if (color != currentLineColor)
            {

                currentLineColor = color;
            }

            pathStations.push_back(vertices.at(currentVertex - 1).get_name());
            pathColors.push_back(color);
            currentVertex = prevVertexId;

            if (currentVertex == -1)
            {
                std::cout << "No path exists from station " << startStation << " to station " << endStation << ".\n";
                return;
            }
        }

        if (!pathStations.empty())
        {
            // Print the last segment of the path
            pathStations.push_back(startStation);
            std::reverse(pathStations.begin(), pathStations.end());
            std::reverse(pathColors.begin(), pathColors.end());
            printPathWithColor(pathStations, pathColors, shortestDistance);
            std::cout << std::endl;
            pathStations.clear();
            pathColors.clear();
        }
    }

     void printPathWithColor(const std::vector<std::string> &pathStations, const std::vector<std::string> &pathColors, const int &shortestDistance)
    {
        if (pathStations.empty() || pathColors.empty())
        {
            return; // No path or colors to print
        }
        std::string prevcolor{};
        std::string currentcolor;
        std::set<std::string>UniqueColors;
        int j{};

        for (int i = 0; i < pathStations.size(); i++)
        {
            if(i==0){std::cout << "----- " << pathColors[0] << " Line -----" << std::endl;}
            if (i < pathColors.size() && prevcolor != pathColors[j])
            {
                    prevcolor = pathColors[j];
                
                    UniqueColors.insert(pathColors[j]);
                if(i!= 0){
                    std::cout << "----- " << pathColors[j] << " Line -----" << std::endl;
                }
            }
            if (i != 0)
            {
                j++;
                std::cout << "↓" << std::endl;
            }
            std::cout << pathStations[i] << std::endl;
        }

        // Print distance and number of stations
        std::cout << " >>>>   Distance: " << shortestDistance << "  >>>>\n";
        std::cout << " >>>>   Stations: " << pathStations.size() << "  >>>>\n";
        std::cout << " >>>> Number of lines changing required : " << UniqueColors.size() +1 << " >>>>" << std::endl;
        for(auto &c : pathColors){
            std::cout << c << std::endl;
        }
        
    }
};

int getIntegerInput(const std::string &prompt)
{
    int value;
    bool validInput = false;
    while (!validInput)
    {
        std::cout << prompt;
        if (!(std::cin >> value))
        {
            std::cin.clear();                                                   // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
            std::cout << "Invalid input. Please enter an integer.\n";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear trailing newline
            validInput = true;
        }
    }
    return value;
}

char getCharInput(const std::string &prompt)
{
    char input;
    bool validInput = false;
    while (!validInput)
    {
        std::cout << prompt;
        std::cin >> input;
        if (std::cin.fail() || std::cin.peek() != '\n' || (input < 'A' || (input > 'Z' && input < 'a') || input > 'z'))
        {
            std::cin.clear();                                                   // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
            std::cout << "Invalid input. Please enter a single alphabetical character.\n";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear trailing newline
            validInput = true;
        }
    }
    return input;
}

std::string getStringInput(const std::string &prompt)
{
    std::string input;
    while (true)
    {
        std::cout << prompt;
        std::getline(std::cin, input);

        // Check if the input is not empty and contains at least one non-space character
        if (!input.empty() && input.find_first_not_of(' ') != std::string::npos)
        {
            return input;
        }
        else
        {
            std::cout << "Invalid input. Please enter a non-empty string.\n";
        }
    }
}
int main()
{
    Graph g;

    // Add vertices and edges to the graph
    Vertex vertex1(1, "a");
    g.insert(vertex1);

    Vertex vertex2(2, "b");
    g.insert(vertex2);

    Vertex vertex3(3, "c");
    g.insert(vertex3);

    Vertex vertex4(4, "d");
    g.insert(vertex4);

    Vertex vertex5(5, "e");
    g.insert(vertex5);

    Vertex vertex6(6, "f");
    g.insert(vertex6);

    Vertex vertex7(7, "g");
    g.insert(vertex7);

    Vertex vertex8(8, "h");
    g.insert(vertex8);

    Vertex vertex9(9, "i");
    g.insert(vertex9);

    Vertex vertex10(10, "j");
    g.insert(vertex10);

    Vertex vertex11(11, "k");
    g.insert(vertex11);

    Vertex vertex12(12, "l");
    g.insert(vertex12);

    Vertex vertex13(13, "m");
    g.insert(vertex13);

    Vertex vertex14(14, "n");
    g.insert(vertex14);

    Vertex vertex15(15, "o");
    g.insert(vertex15);

    Vertex vertex16(16, "p");
    g.insert(vertex16);

    Vertex vertex17(17, "q");
    g.insert(vertex17);

    Vertex vertex18(18, "r");
    g.insert(vertex18);

    Vertex vertex19(19, "s");
    g.insert(vertex19);

    Vertex vertex20(20, "t");
    g.insert(vertex20);

    Vertex vertex21(21, "u");
    g.insert(vertex21);

    Vertex vertex22(22, "v");
    g.insert(vertex22);

    Vertex vertex23(23, "w");
    g.insert(vertex23);

    g.addEdge(4, 3, 3, "RED");
    g.addEdge(3, 4, 3, "RED");

    g.addEdge(3, 2, 4, "RED");
    g.addEdge(2, 3, 4, "RED");

    g.addEdge(2, 1, 3, "RED");
    g.addEdge(1, 2, 3, "RED");

    g.addEdge(1, 5, 2, "RED");
    g.addEdge(5, 1, 2, "RED");

    g.addEdge(5, 6, 1, "RED");
    g.addEdge(6, 5, 1, "RED");

    g.addEdge(6, 7, 3, "RED");
    g.addEdge(7, 6, 3, "RED");

    g.addEdge(7, 8, 4, "RED");
    g.addEdge(8, 7, 4, "RED");

    g.addEdge(14, 15, 4, "GREEN");
    g.addEdge(15, 14, 4, "GREEN");

    g.addEdge(16, 15, 3, "GREEN");
    g.addEdge(15, 16, 3, "GREEN");

    g.addEdge(17, 16, 3, "GREEN");
    g.addEdge(16, 17, 3, "GREEN");

    g.addEdge(18, 17, 2, "GREEN");
    g.addEdge(17, 18, 2, "GREEN");

    g.addEdge(18, 19, 5, "GREEN");
    g.addEdge(19, 18, 5, "GREEN");

    g.addEdge(20, 18, 1, "BLUE");
    g.addEdge(18, 20, 1, "BLUE");

    g.addEdge(18, 6, 1, "BLUE");
    g.addEdge(6, 18, 1, "BLUE");

    g.addEdge(6, 9, 1, "BLUE");
    g.addEdge(9, 6, 1, "BLUE");

    g.addEdge(9, 8, 4, "BLUE");
    g.addEdge(8, 9, 4, "BLUE");

    g.addEdge(23, 22, 4, "VOILET");
    g.addEdge(22, 23, 4, "VOILET");

    g.addEdge(22, 21, 3, "VOILET");
    g.addEdge(21, 22, 3, "VOILET");

    g.addEdge(21, 16, 2, "VOILET");
    g.addEdge(16, 21, 2, "VOILET");

    g.addEdge(16, 1, 1, "VOILET");
    g.addEdge(1, 16, 1, "VOILET");

    g.addEdge(1, 10, 2, "VOILET");
    g.addEdge(10, 1, 2, "VOILET");

    g.addEdge(10, 11, 2, "VOILET");
    g.addEdge(11, 10, 2, "VOILET");

    g.addEdge(11, 12, 4, "VOILET");
    g.addEdge(12, 11, 4, "VOILET");

    g.addEdge(12, 13, 5, "VOILET");
    g.addEdge(13, 12, 5, "VOILET");

    std::string s;
    char choice;

    while (choice != 'Q' && choice != 'q')
    {
        std::cout << "Enter A to add  vertex: " << std::endl;
        std::cout << "Enter E for adding edge " << std::endl;
        std::cout << "Enter U for Updating distance in edge " << std::endl;
        std::cout << "Enter S for Geting shorttest path from a source" << std::endl;
        std::cout << "Enter V for Updating Vertex " << std::endl;
        std::cout << "Enter D for deleting the edge " << std::endl;
        std::cout << "Enter X for deleting the Vertex " << std::endl;
        std::cout << "Enter P for printing " << std::endl;
        std::cout << "Enter Q to quit : " << std::endl;
        char choice = getCharInput("Please enter your choice : ");
        if (::toupper(choice) >= 'A' && ::toupper(choice) <= 'Z')
        {
            switch (::toupper(choice))
            {

            case 'A':
            {
                int id = getIntegerInput("Enter the id : ");
                std::string name = getStringInput("Enter the name of the Station : ");
                Vertex v(id, name);
                g.insert(v);
                break;
            }

            case 'E':
            {
                int source = getIntegerInput("Enter the source id : ");
                int destination = getIntegerInput("Enter the destination id :");
                int distance = getIntegerInput("Enter the weight of edge : ");
                std::string color = getStringInput("Enter teh color of the edge : ");
                g.addEdge(source, destination, distance, color);
                break;
            }
            case 'U':
            {
                int source = getIntegerInput("Enter the source id : ");
                int destination = getIntegerInput("Enter the destination id :");
                int distance = getIntegerInput("Enter the Updated weight of edge : ");
                g.UpdateEdge(source, destination, distance);
                break;
            }
            case 'V':
            {
                int Vector_id = getIntegerInput("Enter the source id : ");
                std::string name = getStringInput("Enter the Updated name : ");
                g.UpdateVertex(Vector_id, name);
                break;
            }
            case 'S':
            {
                std::string startName = getStringInput("Please enter the source station name: ");
                std::string destinationName = getStringInput("Please enter the destination station name: ");
                g.dijkstrabellman(startName, destinationName);
                break;
            }
            case 'D':
            {
                int source = getIntegerInput("Enter the source id : ");
                int destination = getIntegerInput("Enter the destination id :");
                g.DeleteEdge(source, destination);
                break;
            }
            case 'X':
            {
                int Vector_id = getIntegerInput("Enter the source id : ");
                g.DeleteVector(Vector_id);
                break;
            }
            case 'P':
            {
                std::cout << "Printing : ... \n"
                          << std::endl;
                g.print();
                break;
            }
            case 'Q':
            {
                std::cout << "THANKS FOR USING THIS PROGRAM\n";
                break;
            }
            default:
            {
                std::cout << "\nrenter the value\n"
                          << std::endl;
                break;
            }
            }
        }
        else
        {
            std::cout << "\nInvalid choice. Please enter a valid option.\n"
                      << std::endl;
        }
    }
    return 0;
}
