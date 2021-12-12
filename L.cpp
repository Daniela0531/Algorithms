#include <iostream>
#include <vector>
#include <queue>

struct Edge {
    int from_vertex;
    int to_vertex;
    int weight;
};

class IGraph {
public:
    virtual void AddEdge(int from_vertex, int to_vertex, int edge = 1) = 0;
    virtual std::vector<Edge>& Neighbors(int vertex) = 0;
    virtual size_t GetNumberOfVertexes() const = 0;
    const int distance_poison_ = -1;
    const int parent_poison_ = -1;
    const int inf_ = 2009000999;
};

class Graph final : public IGraph {
    std::vector<std::vector<Edge>> graph_;

public:
    const int distance_poison_ = -1;
    const int parent_poison_ = -1;
    const int inf_ = 2009000999;

    explicit Graph(int n) {
        graph_.resize(n);
    }
    void AddEdge(int from_vertex, int to_vertex, int edge = 1) final {
        graph_[from_vertex].push_back({from_vertex, to_vertex, edge});
    }

    size_t GetNumberOfVertexes() const final {
        return graph_.size();
    }

    std::vector<Edge>& Neighbors(int vertex) final {
        return graph_[vertex];
    }
};

std::vector<size_t> Distances(IGraph& graph, int from_vertex) {
    std::vector<size_t> distance(graph.GetNumberOfVertexes(), graph.inf_);
    std::vector<int> parent(graph.GetNumberOfVertexes(), graph.parent_poison_);
    distance[from_vertex] = 0;
    std::priority_queue<std::pair<int, int>> queue;
    queue.push(std::make_pair(0, from_vertex));
    while (!queue.empty()) {
        int vertex = queue.top().second;
        int cur_distance = -queue.top().first;
        queue.pop();
        if (cur_distance > static_cast<int>(distance[vertex])) {
            continue;
        }
        for (auto edge : graph.Neighbors(vertex)) {
            int new_to_vertex = edge.to_vertex;
            int len = edge.weight;
            if (distance[vertex] + len < distance[new_to_vertex]) {
                distance[new_to_vertex] = distance[vertex] + len;
                parent[new_to_vertex] = vertex;
                queue.push(std::make_pair(-static_cast<int64_t>(distance[new_to_vertex]), new_to_vertex));
            }
        }
    }
    return distance;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int block_count = 0;
    std::cin >> block_count;
    for (int j = 0; j < block_count; ++j) {
        int vertex_number = 0;
        int edge_number = 0;
        std::cin >> vertex_number >> edge_number;
        Graph graph(vertex_number);

        for (int i = 0; i < edge_number; ++i) {
            int vertex_1 = 0;
            int vertex_2 = 0;
            int weight = 0;
            std::cin >> vertex_1 >> vertex_2 >> weight;
            graph.AddEdge(vertex_1, vertex_2, weight);
            graph.AddEdge(vertex_2, vertex_1, weight);
        }
        int from_vertex = 0;
        std::cin >> from_vertex;
        std::vector<size_t> res = Distances(graph, from_vertex);
        for (int i = 0; i < vertex_number; ++i) {
            std::cout << res[i] << "\n";
        }
    }
    return 0;
}
