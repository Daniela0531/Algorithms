#include <bits/stdc++.h>

struct Neighbor {
    int vertex;
    int edge_capacity;
    bool operator==(const Neighbor &other) const {
        return (edge_capacity == other.edge_capacity);
    }
    bool operator<(const Neighbor &other) const {
        return edge_capacity < other.edge_capacity;
    }
    bool operator>=(const Neighbor &other) const {
        return !(*this < other);
    }
    bool operator>(const Neighbor &other) const {
        return (*this >= other) && !(*this == other);
    }
    bool operator<=(const Neighbor &other) const {
        return !(other < *this);
    }
};

const int kDistancePoison = -1;
const int kParentPoison = -1;

class IGraph {
public:
    virtual void AddEdge(int left_graph_val, int right_graph_val, int edge = 1) = 0;
    virtual std::vector<Neighbor> Neighbors(int vertex) const = 0;
    virtual size_t GetNumberOfVertixes() const = 0;
    virtual size_t GetNumberOfEdges() const = 0;
};

class GraphList final : public IGraph {
    std::vector<std::vector<Neighbor>> graph_;
    size_t number_of_vertexes_ = 0;
    size_t number_of_edges_ = 0;

public:
    explicit GraphList(size_t input_size) {
        graph_.resize(input_size);
        number_of_vertexes_ = input_size;
    }

    void AddEdge(int from_vertex, int to_vertex, int edge_cost = 1) final {
        graph_[from_vertex].push_back({to_vertex, edge_cost});
        ++number_of_edges_;
    }

    std::vector<Neighbor> Neighbors(int vertex) const final {
        return graph_[vertex];
    }

    size_t GetNumberOfVertixes() const final {
        return number_of_vertexes_;
    }

    size_t GetNumberOfEdges() const final {
        return number_of_edges_;
    }
};

std::vector<Neighbor> SpanningTree(IGraph &graph) {
    std::priority_queue<Neighbor, std::vector<Neighbor>, std::greater<>> queue;
    queue.push({0, 0});

    std::vector<bool> is_visited(graph.GetNumberOfVertixes(), false);

    std::vector<Neighbor> graph_tree;
    while (!queue.empty()) {
        Neighbor cur_vertex = queue.top();
        queue.pop();
        int vertex = cur_vertex.vertex;
        if (!is_visited[vertex]) {
            is_visited[vertex] = true;
            graph_tree.push_back(cur_vertex);
            for (auto &neighbor : graph.Neighbors(vertex)) {
                if (!is_visited[neighbor.vertex]) {
                    queue.push(neighbor);
                }
            }
        }
    }
    return graph_tree;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int vertex_number = 0;
    int edge_number = 0;
    std::cin >> vertex_number >> edge_number;

    GraphList graph(vertex_number);

    int vertex_1 = 0;
    int vertex_2 = 0;
    int edge_capacity = 0;
    for (int i = 0; i < edge_number; ++i) {
        std::cin >> vertex_1 >> vertex_2 >> edge_capacity;
        graph.AddEdge(--vertex_1, --vertex_2, edge_capacity);
        graph.AddEdge(vertex_2, vertex_1, edge_capacity);
    }
    int res_sum = 0;
    std::vector<Neighbor> tree_from_graph = SpanningTree(graph);
    for (auto leaf : tree_from_graph) {
        res_sum += leaf.edge_capacity;
    }
    std::cout << res_sum << std::endl;
    return 0;
}
