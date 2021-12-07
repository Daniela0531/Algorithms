#include <bits/stdc++.h>

class Graph {
public:
    virtual void Add(int left_graph_val, int right_graph_val, int edge) = 0;
};

class GraphList : public Graph {
    struct Vector {
        int edge;
        int v;
    };
    std::vector<std::vector<Vector>> graph;

public:

    GraphList(size_t input_size) {
        graph.resize(input_size);
    }

    void Add(int x, int y, int edge) {
        Vector new_elem = {edge, y};
        graph[x].push_back(new_elem);
    }

    void Path(int from, int to, char k) {
        --from;
        --to;
        std::vector<std::queue<int64_t>> in_queue(k + 1);
        std::vector<int64_t> dist(graph.size(), -1);

        in_queue[0].push(from);
        dist[from] = 0;
        int queue_ind = 0;
        int number_of_vertex_in_queue = 1;
        while(number_of_vertex_in_queue > 0) {
            while(!in_queue[queue_ind].size()) {
                queue_ind = (queue_ind + 1) % (k + 1);
            }
            int v = in_queue[queue_ind].front();
            for(auto& elem : graph[v]) {
                if (dist[elem.v] == -1 || dist[v] + elem.edge < dist[elem.v]) {
                    dist[elem.v] = dist[v] + elem.edge;
                    in_queue[dist[elem.v] % (k + 1)].push(elem.v);
                    ++number_of_vertex_in_queue;
                }
            }
            in_queue[queue_ind].pop();
            --number_of_vertex_in_queue;
        }

        std::cout << dist[to] << std::endl;
    }

    void Print() {
        for(int i = 0; i < graph.size(); ++i) {
            for(int j = 0; j < graph[i].size(); ++j) {
                printf("%d %d = %d\n", i, graph[i][j].v, graph[i][j].edge);
            }
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n = 0;
    int m = 0;
    int left = 0;
    int right = 0;
    int edge = 0;
    int begin = 0;
    int end = 0;

    std::cin >> n >> m;

    GraphList graph(n);

    for(int i = 0; i < m; ++i) {
        std::cin >> left >> right;
        if (left != right) {
            graph.Add(left - 1, right - 1, 0);
            graph.Add(right - 1, left - 1, 1);
        }
    }
    // graph.Print();
    int64_t count = 0;
    std::cin >> count;
    for(int64_t i = 0; i < count; ++i) {
        std::cin >> begin >> end;
        graph.Path(begin, end, 2);
    }
    return 0;
}
