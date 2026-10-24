#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <set>

using namespace std;

class Graph {
private:
    int numVertices;
    vector<int> labels;
    vector<vector<int>> adjacencyMatrix;

    int getIndex(int label) {
        for (int i = 0; i < numVertices; i++) {
            if (labels[i] == label) {
                return i;
            }
        }
        return -1;
    }

public:
    Graph() {
        numVertices = 0;
    }

    bool loadFromFile(string fileName) {
        ifstream file(fileName);

        if (!file) {
            return false;
        }

        vector<pair<int, int>> edges;
        set<int> nodes;

        int source, destination;

        while (file >> source >> destination) {
            edges.push_back({ source, destination });
            nodes.insert(source);
            nodes.insert(destination);
        }

        labels.assign(nodes.begin(), nodes.end());
        numVertices = labels.size();

        adjacencyMatrix.assign(numVertices, vector<int>(numVertices, 0));

        for (int i = 0; i < edges.size(); i++) {
            int row = getIndex(edges[i].first);
            int col = getIndex(edges[i].second);

            adjacencyMatrix[row][col] = 1;
        }

        return true;
    }

    void displayGraphText() {
        cout << "\nText Graphics Display of Graph:\n\n";

        for (int i = 0; i < numVertices; i++) {
            cout << labels[i] << " -> ";

            bool hasNeighbor = false;

            for (int j = 0; j < numVertices; j++) {
                if (adjacencyMatrix[i][j] == 1) {
                    cout << labels[j] << " ";
                    hasNeighbor = true;
                }
            }

            if (!hasNeighbor) {
                cout << "No adjacent nodes";
            }

            cout << endl;
        }
    }

    void BFS(int startLabel) {
        int startIndex = getIndex(startLabel);

        if (startIndex == -1) {
            cout << "Starting node was not found.\n";
            return;
        }

        vector<bool> visited(numVertices, false);
        queue<int> q;

        visited[startIndex] = true;
        q.push(startIndex);

        cout << "\nBFS Traversal starting from node " << startLabel << ":\n";

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            cout << labels[current] << " ";

            for (int i = 0; i < numVertices; i++) {
                if (adjacencyMatrix[current][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }

        cout << endl;
    }

    void DFS(int startLabel) {
        int startIndex = getIndex(startLabel);

        if (startIndex == -1) {
            cout << "Starting node was not found.\n";
            return;
        }

        vector<bool> visited(numVertices, false);
        stack<int> s;

        s.push(startIndex);

        cout << "\nDFS Traversal starting from node " << startLabel << ":\n";

        while (!s.empty()) {
            int current = s.top();
            s.pop();

            if (!visited[current]) {
                visited[current] = true;
                cout << labels[current] << " ";

                for (int i = numVertices - 1; i >= 0; i--) {
                    if (adjacencyMatrix[current][i] == 1 && !visited[i]) {
                        s.push(i);
                    }
                }
            }
        }

        cout << endl;
    }
};

int main() {
    Graph graph;

    string fileName = "c:\\temp\\graph.txt";

    if (!graph.loadFromFile(fileName)) {
        cout << "Could not open c:\\temp\\graph.txt\n";
        cout << "Please make sure graph.txt is located inside C:\\temp\n";
        return 1;
    }

    int choice;

    do {
        cout << "\n==============================\n";
        cout << " Graph Functions Menu\n";
        cout << "==============================\n";
        cout << "1. Display Graph Graphically using Text Graphics\n";
        cout << "2. Traverse Graph using BFS\n";
        cout << "3. Traverse Graph using DFS\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            graph.displayGraphText();
        }
        else if (choice == 2) {
            int startNode;
            cout << "Enter starting node: ";
            cin >> startNode;

            graph.BFS(startNode);
        }
        else if (choice == 3) {
            int startNode;
            cout << "Enter starting node: ";
            cin >> startNode;

            graph.DFS(startNode);
        }
        else if (choice == 0) {
            cout << "Program ended.\n";
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}