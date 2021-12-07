#include <iostream>
#include <vector>
#include <queue>

struct Neighbor {
    int vertex;
    int flow;
    size_t back;
};

class IGraph {
public:
    virtual void AddEdge(int from_vertex, int to_vertex, int max_flow_v) = 0;
    virtual void DecreaseFlowOfBackEdge(Neighbor& edge, int value) = 0;
    virtual std::vector<Neighbor>& Neighbors(int vertex) = 0;
    virtual size_t GetNumberOfVertexes() const = 0;
    const int distance_poison_ = -1;
    const int parent_poison_ = -1;
    const int inf_ = 100000;
};

class Graph final : public IGraph {
    std::vector<std::vector<Neighbor>> graph_;

public:
    explicit Graph(int n) {
        graph_.resize(n);
    }
    void AddEdge(int from, int to, int capacity) final {
        graph_[from].push_back({to, capacity, graph_[to].size()});
        graph_[to].push_back({from, 0, graph_[from].size() - 1});
    }
    void DecreaseFlowOfBackEdge(Neighbor& edge, int value) final {
        graph_[edge.vertex][edge.back].flow += value;
    }
    size_t GetNumberOfVertexes() const final {
        return graph_.size();
    }

    std::vector<Neighbor>& Neighbors(int vertex) final {
        return graph_[vertex];
    }
};

bool Bfs(IGraph& graph, int from, int to, std::vector<int>& dist);
int Dfs(IGraph& graph, int from_vertex, int to_vertex, int flow, std::vector<int>& dist);

// Dinic
int MaxFlow(IGraph& graph, int from_vertex, int to_vertex);

int main() {
    int num_of_vertex = 0;
    int num_of_edge = 0;
    std::cin >> num_of_vertex >> num_of_edge;
    Graph graph(num_of_vertex);
    int from_vertex = 0;
    int to_vertex = 0;
    int max_flow = 0;
    for (int i = 0; i < num_of_edge; ++i) {
        std::cin >> from_vertex >> to_vertex >> max_flow;
        graph.AddEdge(from_vertex - 1, to_vertex - 1, max_flow);
    }
    std::cout << MaxFlow(graph, 0, num_of_vertex - 1) << std::endl;
    return 0;
}

// Dinic
int MaxFlow(IGraph& graph, int from_vertex, int to_vertex) {
    int flow = 0;
    std::vector<int> dist(graph.GetNumberOfVertexes(), graph.distance_poison_);
    while (Bfs(graph, from_vertex, to_vertex, dist)) {
        while (int pushed = Dfs(graph, from_vertex, to_vertex, graph.inf_, dist)) {
            flow += pushed;
        }
        dist.assign(dist.size(), graph.distance_poison_);
    }
    return flow;
}

int Dfs(IGraph& graph, int from_vertex, int to_vertex, int flow, std::vector<int>& dist) {
    if (from_vertex == to_vertex) {
        return flow;
    }
    int res = 0;
    for (auto& edge : graph.Neighbors(from_vertex)) {
        if (dist[edge.vertex] == dist[from_vertex] + 1 && edge.flow > 0) {
            int min_result = Dfs(graph, edge.vertex, to_vertex, std::min(flow, edge.flow), dist);
            if (min_result > 0) {
                graph.DecreaseFlowOfBackEdge(edge, min_result);
                edge.flow -= min_result;
                res = min_result;
                break;
            }
        }
    }
    return res;
}

bool Bfs(IGraph& graph, int from, int to, std::vector<int>& dist) {
    std::queue<int> queue;
    dist[from] = 0;
    queue.push(from);
    while (!queue.empty() && dist[to] == -1) {
        int v = queue.front();
        queue.pop();
        for (auto& neighbor : graph.Neighbors(v)) {
            int next_vertex = neighbor.vertex;
            if (dist[next_vertex] == graph.distance_poison_ && neighbor.flow > 0) {
                queue.push(next_vertex);
                dist[next_vertex] = dist[v] + 1;
            }
        }
    }
    return dist[to] != graph.distance_poison_;
}