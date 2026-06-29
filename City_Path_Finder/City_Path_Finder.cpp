#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

const int INF = 1000000000;

int main() {
    int n, e;

    cout << "Enter number of cities: ";
    cin >> n;

    vector<string> city(n);

    cout << "Enter city names:\n";
    for (int i = 0; i < n; i++)
        cin >> city[i];

    vector<pair<int, int>> graph[20];

    cout << "Enter number of roads: ";
    cin >> e;

    cout << "Enter Source Destination Distance:\n";
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    int source, destination;

    cout << "Enter source city index: ";
    cin >> source;

    cout << "Enter destination city index: ";
    cin >> destination;

    vector<int> dist(n, INF);
    vector<int> parent(n, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {

        int u = pq.top().second;
        pq.pop();

        for (auto edge : graph[u]) {

            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {

                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[destination] == INF) {
        cout << "\nNo path exists.";
        return 0;
    }

    vector<int> path;

    for (int v = destination; v != -1; v = parent[v])
        path.push_back(v);

    cout << "\nShortest Route:\n";

    for (int i = path.size() - 1; i >= 0; i--) {
        cout << city[path[i]];
        if (i != 0)
            cout << " -> ";
    }

    cout << "\nTotal Distance = " << dist[destination];

    return 0;
}
