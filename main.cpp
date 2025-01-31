#include <iostream>
#include <vector>
#include <climits>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

// (distance, vertex)
typedef pair<int, int> Node;

class Graph {
private:
    unordered_map<int, vector<pair<int, int>>> adjList;

public:
    void addEdge(int u, int v, int weight) {
        adjList[u].emplace_back(v, weight);
        adjList[v].emplace_back(u, weight);
    }

    void dijkstra(int start, int end) {
        unordered_map<int, int> distances;
        unordered_map<int, int> previous;
        priority_queue<Node, vector<Node>, greater<Node>> pq;

        // Initialize distances to infinity
        for (const auto& entry : adjList) {
            distances[entry.first] = INT_MAX;
        }
        distances[start] = 0;
        pq.emplace(0, start);

        while (!pq.empty()) {
            int currentDist = pq.top().first;
            int currentNode = pq.top().second;
            pq.pop();

            if (currentDist > distances[currentNode]) continue;

            for (const auto& neighbor : adjList[currentNode]) {
                int nextNode = neighbor.first;
                int weight = neighbor.second;
                int newDist = currentDist + weight;

                if (newDist < distances[nextNode]) {
                    distances[nextNode] = newDist;
                    previous[nextNode] = currentNode;
                    pq.emplace(newDist, nextNode);
                }
            }
        }

        if (distances[end] == INT_MAX) {
            cout << "No path exists from " << start << " to " << end << "\n";
            return;
        }

        // Output the shortest path and its cost
        cout << "Shortest path cost: " << distances[end] << "\n";
        cout << "Path: ";
        stack<int> path;
        for (int at = end; at != start; at = previous[at]) {
            path.push(at);
        }
        path.push(start);
        while (!path.empty()) {
            cout << path.top();
            path.pop();
            if (!path.empty()) cout << " -> ";
        }
        cout << "\n";
    }
};

int main() {
    Graph graph;

    int numEdges;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    cout << "Enter the edges in the format (startNode endNode weight):\n";
    for (int i = 0; i < numEdges; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;
        graph.addEdge(u, v, weight);
    }

    int start, end;
    cout << "Enter the starting node: ";
    cin >> start;
    cout << "Enter the ending node: ";
    cin >> end;

    graph.dijkstra(start, end);

    return 0;
}
