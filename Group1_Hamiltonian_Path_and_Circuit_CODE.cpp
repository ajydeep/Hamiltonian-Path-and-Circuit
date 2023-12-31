#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class HamiltonianPathCircuit 
{
private:

    int vertices;
    vector<vector<int>> graph;
    bool isDirected;

public:

    HamiltonianPathCircuit(int v, bool directed) : vertices(v), graph(v, vector<int>(v, 0)), isDirected(directed) {}

    
    void addEdge(int u, int v)   // here we are adding edge
    {
        graph[u][v] = 1;
        if (!isDirected) 
        {
            graph[v][u] = 1;    // if the graph is not directed then 
        }
    }

    
    bool isSafe(int v, vector<int>& path, int pos) 
    {
        if (graph[path[pos - 1]][v] == 0)
            return false;

        if (find(path.begin(), path.end(), v) != path.end())
            return false;

        return true;
    }


    
    bool hamiltonianPathUtil(vector<int>& path, int pos)
     {
        if (pos == vertices) 
        {
            return true;
        }

        for (int v = 0; v < vertices; ++v) 
        {
            if (isSafe(v, path, pos))
            {
                path[pos] = v;

                if (hamiltonianPathUtil(path, pos + 1))
                    return true;

                path[pos] = -1; // Backtrack
            }
        }

        return false;
    }

    bool findHamiltonianPath()  // this function will find and print the hamiltonian path
    {
        vector<int> path(vertices, -1);
        path[0] = 0; 

        if (!hamiltonianPathUtil(path, 1)) 
        {
            cout << "Hamiltonian path does not exist." << endl;
            return false;
        }

        cout << "Hamiltonian path exists. Path: ";
        for (int vertex : path) 
        {
            cout << vertex << " ";
        }
        cout << endl;

        return true;
    }

    
    bool isHamiltonianCircuit() // function for hamiltonian circuit
    {
        vector<int> path(vertices, -1);

        for (int v = 0; v < vertices; ++v) 
        {
            path[0] = v;

            
            if (hamiltonianPathUtil(path, 1) && ((isDirected && graph[path[vertices - 1]][path[0]] == 1) || (!isDirected))) 
            {   // this function checks if a hamiltonian path exists and the last vertex is connected to the starting vertex, it's a circuit
                cout << "Hamiltonian circuit exists. Circuit: ";

                for (int vertex : path) 
                {
                    cout << vertex << " ";
                }

                cout << path[0] << endl;

                return true;
            }
        }

        cout << "Hamiltonian circuit does not exist." << endl;

        return false;
    }
};

int main() 
{
    int vertices, edges;
    bool isDirected;

    cout << "Enter the number of vertices in the graph: ";
    cin >> vertices;

    cout << "Is the graph directed? (0 for undirected, 1 for directed): ";
    cin >> isDirected;

    HamiltonianPathCircuit graph(vertices, isDirected);

    cout << "Enter the number of edges: ";
    cin >> edges;

    cout << "Enter the edges (format: u v):" << endl;

    for (int i = 0; i < edges; ++i) 
    {
        int u, v;
        cin >> u >> v;
        graph.addEdge(u, v);

    }

    int choice;
    do {
        cout << "\nMenu:\n1. Find Hamiltonian Path\n2. Find Hamiltonian Circuit\n3. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:

                graph.findHamiltonianPath();
                break;

            case 2:

                graph.isHamiltonianCircuit();
                break;

            case 3:

                cout << "Exiting the program.\n";
                break;

            default:
                cout << "Invalid choice. Please enter a valid option.\n";

        }

    } 

    while (choice != 3);

    return 0;
}
