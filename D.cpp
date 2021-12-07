#include <bits/stdc++.h>

struct Edge {
    int from_vertex;
    int to_vertex;
    int weight;
    bool operator==(const Edge& other) const {
        return (weight == other.weight);
    }
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
    bool operator>=(const Edge& other) const {
        return !(*this < other);
    }
    bool operator>(const Edge& other) const {
        return (*this >= other) && !(*this == other);
    }
    bool operator<=(const Edge& other) const {
        return !(other < *this);
    }
};

class IGraph {
public:
    virtual void AddEdge(int from_vertex, int to_vertex, int edge = 1) = 0;
    virtual std::vector<Edge> Neighbors(int vertex) const = 0;
    virtual size_t GetNumberOfVertexes() const = 0;
    virtual size_t GetNumberOfEdges() const = 0;
    const int distance_poison_ = -1;
    const int parent_poison_ = -1;
    const int inf_ = 100000000;
};

class GraphList final : public IGraph {
    std::vector<std::vector<Edge>> graph_;
    size_t number_of_vertexes_ = 0;
    size_t number_of_edges_ = 0;

public:
    explicit GraphList(size_t input_size) {
        graph_.resize(input_size);
        number_of_vertexes_ = input_size;
    }

    void AddEdge(int from_vertex, int to_vertex, int edge_cost = 1) final {
        graph_[from_vertex].push_back({from_vertex, to_vertex, edge_cost});
        ++number_of_edges_;
    }

    std::vector<Edge> Neighbors(int vertex) const final {
        return graph_[vertex];
    }

    size_t GetNumberOfVertexes() const final {
        return number_of_vertexes_;
    }

    size_t GetNumberOfEdges() const final {
        return number_of_edges_;
    }
};

std::vector<Edge> SpanningTree(IGraph& graph) {
    std::vector<Edge> spanning_tree;
    std::vector<bool> is_visited(graph.GetNumberOfVertexes(), false);
    std::priority_queue<Edge, std::vector<Edge>, std::greater<>> queue_of_edges;

    queue_of_edges.push({0, 0, 0});

    while (!queue_of_edges.empty()) {
        Edge edge = queue_of_edges.top();
        int vertex = edge.to_vertex;
        queue_of_edges.pop();
        if (!is_visited[vertex]) {
            is_visited[vertex] = true;
            spanning_tree.push_back(edge);
            for (auto edge_from_vertex : graph.Neighbors(vertex)) {
                if (!is_visited[edge_from_vertex.to_vertex]) {
                    queue_of_edges.push(edge_from_vertex);
                }
            }
        }
    }
    return spanning_tree;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int vertex_number = 0;
    std::cin >> vertex_number;
    GraphList graph(vertex_number + 1);
    int weight = 0;
    for (int i = 0; i < vertex_number; ++i) {
        for (int j = 0; j < vertex_number; ++j) {
            std::cin >> weight;
            graph.AddEdge(i, j, weight);
        }
    }
    for (int i = 0; i < vertex_number; ++i) {
        std::cin >> weight;
        graph.AddEdge(vertex_number, i, weight);
        graph.AddEdge(i, vertex_number, weight);
    }
    int64_t spanning_tree_weight = 0;
    std::vector<Edge> spanning_tree;
    spanning_tree = SpanningTree(graph);
    for (auto tree_elem : spanning_tree) {
        spanning_tree_weight += tree_elem.weight;
    }
    std::cout << spanning_tree_weight << std::endl;
    return 0;
}
