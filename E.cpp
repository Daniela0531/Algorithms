#include <bits/stdc++.h>

class Graph {
public:
    virtual void Add(int left_graph_val, int right_graph_val, int val) = 0;
};

class GraphList : public Graph {
    std::vector<std::vector<int>> graph;

    struct Coord {
        int x;
        int y;
        bool operator==(Coord& other) {
            return (x == other.x) && (y == other.y);
        }
        bool operator!=(Coord& other) {
            return !(*this == other);
        }
    };
    
    void Bfs(std::vector<std::vector<int>>& dist, std::vector<std::vector<bool>>& is_visited) {
        std::queue<Coord> q;
        for(int i = 0; i < graph.size(); ++i) {
            for(int j = 0; j < graph[0].size(); ++j) {
                if (graph[i][j]) {
                    q.push({i, j});
                    dist[i][j] = 0;
                }
            }
        }
        while(q.size()) {
            Coord parent = q.front();
            is_visited[parent.x][parent.y] = true;
            std::vector<int> x_dif = {-1, 0, 1, 0};
            std::vector<int> y_dif = {0, -1, 0, 1};
            for(int i = 0; i < 4; i++) {
                int x = parent.x + x_dif[i];
                int y = parent.y + y_dif[i];
                if ((x >= 0) && (x < graph.size()) && (y >= 0) && (y < graph[0].size()) && !is_visited[x][y]) {
                    dist[x][y] = std::min(dist[parent.x][parent.y] + 1, dist[x][y]);                    
                    q.push({x, y});
                }
            }
            q.pop();
        }
    }
public:
    void Add(int x, int y, int val) {
        graph[x][y] = val;
    }

    GraphList(size_t input_size_n, size_t input_size_m) {
        graph.resize(input_size_n, std::vector<int>(input_size_m));
    }

    void Path() {
        std::vector<std::vector<bool>> is_visited(graph.size(), std::vector<bool>(graph[0].size(), false));
        const int max_dist = std::max(graph.size(), graph[0].size());
        std::vector<std::vector<int>> dist(graph.size(), std::vector<int>(graph[0].size(), max_dist));

        Bfs(dist, is_visited);

        for(int i = 0; i < graph.size(); ++i) {
            for(int j = 0; j < graph[0].size(); ++j) {
                std::cout << dist[i][j] << " ";
            }
            std::cout << std::endl;
        }        
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n = 0;
    int m = 0;
    int edge = 0;

    std::cin >> n >> m;

    GraphList graph(n, m);

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            std::cin >> edge;
            graph.Add(i, j, edge);
        }
    }
    graph.Path();
    return 0;
}