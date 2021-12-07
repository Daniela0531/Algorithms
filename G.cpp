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

    void NormalizePath(std::vector<std::vector<Coord>> parent, Coord to) {
        std::vector<Coord> res;
        Coord end = {-1, -1};
        for(Coord v = to; v != end; v = parent[v.x][v.y]) {
            res.push_back({v.x + 1, v.y + 1});
        }
        std::reverse(res.begin(), res.end());
        std::cout << res.size() - 1 << std::endl;

        for(auto& elem : res) {
            std::cout << elem.x << " " << elem.y << std::endl;
        }
    }

    void Bfs(int v_x, int v_y, std::vector<std::vector<bool>>& is_visited, bool& key) {
        std::queue<Coord> q;
        q.push({v_x, v_y});

        while(q.size()) {
            Coord v = q.front();
            if (is_visited[v.x][v.y]) {
                q.pop();
                continue;
            }
            is_visited[v.x][v.y] = true;
            if (graph[v.x][v.y] > graph[v.x - 1][v.y] || graph[v.x][v.y] > graph[v.x][v.y - 1] ||
                graph[v.x][v.y] > graph[v.x + 1][v.y] || graph[v.x][v.y] > graph[v.x][v.y + 1]) {
                key = false;
            }
            std::vector<int> x_dif = {-1, 0, 1, 0};
            std::vector<int> y_dif = {0, -1, 0, 1};
            for(int i = 0; i < 4; i++) {
                int x = v.x + x_dif[i];
                int y = v.y + y_dif[i];
                if ((x >= 1) && (y >= 1) && (x < graph.size() - 1) && (y < graph[0].size() - 1) &&
                    !is_visited[x][y] && (graph[x][y] == graph[v.x][v.y])) {
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
        graph.resize(input_size_n);
        for(int i = 0; i < input_size_n; ++i) {
            graph[i].resize(input_size_m);
            graph[i].assign(input_size_m, 10001);
        }
    }

    void Path() {
        int sum = 0;
        std::vector<std::vector<bool>> is_visited(graph.size());
        for(int i = 0; i < graph.size(); ++i) {
            is_visited[i].resize(graph[0].size());
            is_visited[i].assign(graph[0].size(), false);
        }
        bool key = true;
        for(int i = 1; i < graph.size() - 1; i++) {
            for(int j = 1; j < graph[0].size() - 1; j++) {
                if (!is_visited[i][j]) {
                    key = true;
                    Bfs(i, j, is_visited, key);
                    sum += key;
                }
            }
        }
        std::cout << sum << std::endl;
    }

    void Print() {
        for(int i = 0; i < graph.size(); ++i) {
            for(int j = 0; j < graph[i].size(); ++j) {
                printf("%d ", graph[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n = 0, m = 0;
    std::cin >> n >> m;
    GraphList graph(n + 2, m + 2);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            int val = 0;
            std::cin >> val;
            graph.Add(i, j, val);
        }
    }
    graph.Path();
    return 0;
}
