#include <bits/stdc++.h>
#include <sstream>

std::vector<int> dijkstra(std::vector<std::vector<std::pair<int, int>>> &adj, int v, int src);
void printShortest(std::vector<int> dist, int v);

int main(int argc, char **argv) {
    std::vector<std::vector<std::pair<int, int>>> adj;
    int v;

    if (argc == 2) {
        const char *path = argv[1];
        std::ifstream file(path);
        std::string line;

        if (!file) {
            std::cerr << "Error opening file\n";
            return 1;
        }

        int i = 0;
        while (std::getline(file, line)) {
            if (i == 0) {
                v = std::stoi(line);
                adj.resize(v);
                ++i;
                continue;
            }
            std::stringstream ss(line);
            int nums[3], num, idx = 0;
            while (ss >> num)
                nums[idx++] = num;
            adj[nums[0]].push_back({nums[1], nums[2]});
            ++i;
        }

        file.close();
    } else {
        std::cerr << "Usage: <binary> <fila-path>\nFirst line of the file should be the number of vertices and other lines should be \"vertex destination cost\".\n";
        return 1;
    }

    std::vector<int> dist = dijkstra(adj, v, 0);
    printShortest(dist, v);

    return 0;
}

std::vector<int> dijkstra(std::vector<std::vector<std::pair<int, int>>> &adj, int v, int src) {
    std::vector<int> distances(v, INT_MAX);
    distances[src] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int d = pq.top().first, u = pq.top().second;
        pq.pop();

        if (d > distances[u]) continue;

        for (auto &edge : adj[u]) {
            int v = edge.first, w = edge.second;

            if (distances[u] + w < distances[v]) {
                distances[v] = distances[u] + w;
                pq.push({distances[v], v});
            }
        }
    }

    return distances;
}

void printShortest(std::vector<int> dist, int v) {
    std::cout << "Vertex\tDistance from source\n";
    for (int i = 0; i < v; ++i)
        std::cout << i << '\t' << dist[i] << '\n';
}

