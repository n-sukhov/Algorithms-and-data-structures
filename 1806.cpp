#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

const int INF = INT_MAX;

struct Edge {
    int to;
    int weight;
};

struct Node {
    int id;
    int distance;
    bool operator<(const Node& other) const {
        return distance > other.distance;
    }
};

vector<int> dijkstra(const vector<vector<Edge>>& graph, int start, int end, vector<int>& prev) {
    int n = graph.size();
    vector<int> dist(n, INF);
    priority_queue<Node> pq;

    dist[start] = 0;
    pq.push({start, 0});

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.id == end) {
            break;
        }

        if (current.distance > dist[current.id]) {
            continue;
        }

        for (const Edge& edge : graph[current.id]) {
            int new_dist = dist[current.id] + edge.weight;
            if (new_dist < dist[edge.to]) {
                dist[edge.to] = new_dist;
                prev[edge.to] = current.id;
                pq.push({edge.to, new_dist});
            }
        }
    }

    return dist;
}

int get_common_prefix(const string& a, const string& b) {
    int len = 0;
    while (len < 10 && a[len] == b[len]) {
        len++;
    }
    return len;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> time(10);
    for (int i = 0; i < 10; ++i) {
        cin >> time[i];
    }

    vector<string> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    unordered_map<string, int> num_to_id;
    for (int i = 0; i < n; ++i) {
        num_to_id[numbers[i]] = i;
    }

    vector<vector<Edge>> graph(n);

    for (int i = 0; i < n; ++i) {
        string num = numbers[i];
        // Generate all possible neighbors by changing one digit
        for (int pos = 0; pos < 10; ++pos) {
            for (char c = '0'; c <= '9'; ++c) {
                if (c == num[pos]) continue;
                string neighbor = num;
                neighbor[pos] = c;
                if (num_to_id.count(neighbor)) {
                    int j = num_to_id[neighbor];
                    int common_prefix = get_common_prefix(num, neighbor);
                    graph[i].push_back({j, time[common_prefix]});
                }
            }
        }
        // Generate all possible neighbors by swapping two digits
        for (int pos1 = 0; pos1 < 10; ++pos1) {
            for (int pos2 = pos1 + 1; pos2 < 10; ++pos2) {
                if (num[pos1] == num[pos2]) continue;
                string neighbor = num;
                swap(neighbor[pos1], neighbor[pos2]);
                if (num_to_id.count(neighbor)) {
                    int j = num_to_id[neighbor];
                    int common_prefix = get_common_prefix(num, neighbor);
                    graph[i].push_back({j, time[common_prefix]});
                }
            }
        }
    }

    int start = 0;
    int end = n - 1;
    vector<int> prev(n, -1);
    vector<int> dist = dijkstra(graph, start, end, prev);

    if (dist[end] == INF) {
        cout << -1 << endl;
        return 0;
    }

    cout << dist[end] << endl;

    vector<int> path;
    for (int at = end; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    cout << path.size() << endl;
    for (int i = 0; i < path.size(); ++i) {
        if (i > 0) cout << " ";
        cout << path[i] + 1;
    }
    cout << endl;

    return 0;
}