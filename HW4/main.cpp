#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjacent;
    vector<int> colors;  // -1 for uncolored, 0 and 1 for two colors
    vector<int> matched;  // For maximum matching

    bool clr_Graph(int start);
    bool matchHelper(int v, int index, vector<bool>& visited);

public:
    Graph(int vertices) : V(vertices) {
        adjacent.resize(vertices);
        colors.resize(vertices, -1);
        matched.resize(vertices, -1);
    }

    void addEdge(int u, int v) {
        adjacent[u].push_back(v);
        adjacent[v].push_back(u);
    }

    bool isGraphBipartiate();
    int maxMatching();
    bool get_matching(int v, vector<bool>& visited);
};

bool Graph::clr_Graph(int start) {
    // If this vertex is already colored, nothing to do here.
    if (colors[start] != -1) {
        return true;
    }

    // Color the start vertex with color 0
    colors[start] = 0;

    // Prepare a queue for BFS
    queue<int> bfsQueue;
    bfsQueue.push(start);

    // Standard BFS loop
    while (!bfsQueue.empty()) {
        int current = bfsQueue.front();
        bfsQueue.pop();

        // Explore neighbors of the current vertex
        for (int i = 0; i < adjacent[current].size(); i++) {
            int neighbor = adjacent[current][i];
            // If the neighbor is uncolored, assign the opposite color
            if (colors[neighbor] == -1) {
                colors[neighbor] = 1 - colors[current];
                bfsQueue.push(neighbor);
            }
                // If there's a color conflict, the graph cannot be bipartite
            else if (colors[neighbor] == colors[current]) {
                return false;
            }
        }
    }
    return true;
}


bool Graph::matchHelper(int v, int index, vector<bool>& visited) {

    if (index == adjacent[v].size()) {
        return false;
    }

    int u = adjacent[v][index];


    if (colors[u] != colors[v] && !visited[u]) {
        visited[u] = true;


        if (matched[u] == -1 || get_matching(matched[u], visited)) {
            matched[u] = v;
            return true;
        }
    }

    return matchHelper(v, index + 1, visited);
}

bool Graph::get_matching(int v, vector<bool> &visited) {

    return matchHelper(v, 0, visited);
}

bool Graph::isGraphBipartiate() {
    // Try coloring each uncolored component
    for (int i = 0; i < V; i++) {
        if (colors[i] == -1) {
            if (!clr_Graph(i)) {
                return false;
            }
        }
    }
    return true;
}

int Graph::maxMatching() {
    int matchCount = 0;
    // Start from vertex 1 to ignore vertex 0
    for (int v = 1; v < V; v++) {
        if (colors[v] == 0) {  // Only try matching from one color set
            vector<bool> visited(V, false);
            if (get_matching(v, visited)) {
                matchCount++;
            }
        }
    }
    return matchCount;
}

int main() {
    string input;
    while (true) {
        cout << "Enter the graph name (e.g., 'graph1' or 'exit' to terminate): ";
        cin >> input;

        if (input == "exit") {
            break;
        }

        string filename = input + ".txt";
        ifstream file(filename);

        if (!file.is_open()) {
            continue;
        }

        int V, E;
        file >> V >> E;
        Graph g(V + 1);  // +1 for 1-based indexing

        for (int i = 0; i < E; i++) {
            int u, v;
            file >> u >> v;
            g.addEdge(u, v);
        }

        if (!g.isGraphBipartiate()) {
            cout << "The graph is not bipartite." << endl;
        }
        else {
            cout << "The graph is bipartite." << endl;
            cout << "Maximum matching size: " << g.maxMatching() << endl;
        }

        file.close();
    }

    return 0;
}