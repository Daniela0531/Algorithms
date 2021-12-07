#include <bits/stdc++.h>

const int distance_poison = -1;
const int parent_poison = -1;

struct Edge {
    int vertex;
    int edge_cost;
};

class Graph {
public:
    virtual void AddEdge(int from_vertex, int to_vertex, int edge = 1) = 0;
    virtual std::vector<Edge> Neighbors(int vertex) const = 0;
    virtual size_t GetNumberOfVertixes() const = 0;
    virtual size_t GetNumberOfEdges() const = 0;
};

class GraphList : public Graph {
    std::vector<std::vector<Edge>> graph_;
    size_t number_of_vertices = 0;
    size_t number_of_edges = 0;
public:

    GraphList(size_t input_size) {
        graph_.resize(input_size);
        number_of_vertices = input_size;
    }

    void AddEdge(int from_vertex, int to_vertex, int edge_cost = 1) {
        Edge edge = {.vertex = to_vertex, .edge_cost = edge_cost};
        graph_[from_vertex].push_back(edge);
        ++number_of_edges;
    }

    std::vector<Edge> Neighbors(int vertex) const {
        return graph_[vertex];
    }

    size_t GetNumberOfVertixes() const {
        return number_of_vertices;
    }

    size_t GetNumberOfEdges() const {
        return number_of_edges;
    }
};


std::vector<int> NormalizePath(std::vector<int> parent, int finish_vertex) {
    std::vector<int> res;

    for(int vertex = finish_vertex; vertex != -1; vertex = parent[vertex]) {
        res.push_back(vertex);
    }
    std::reverse(res.begin(), res.end());
    return res;
}

std::vector<int> Path(const Graph& graph, int start_vertex, int finish_vertex) {
    std::vector<int> distance(graph.GetNumberOfVertixes(), distance_poison);
    std::vector<int> parent(graph.GetNumberOfVertixes(), parent_poison);
    std::queue<int> queue_of_verteces;
    distance[start_vertex] = 0;
    queue_of_verteces.push(start_vertex);
    bool path_exists = false;
    while(queue_of_verteces.size()) {
        int vertex = queue_of_verteces.front();
        for(auto cur_neighbor : graph.Neighbors(vertex)) {
            if (distance[cur_neighbor.vertex] == distance_poison) {
                distance[cur_neighbor.vertex] = distance[vertex] + cur_neighbor.edge_cost;
                parent[cur_neighbor.vertex] = vertex;
                queue_of_verteces.push(cur_neighbor.vertex);
            }
            if (vertex == finish_vertex) {
                path_exists = true;
                break;
            }
        }
        queue_of_verteces.pop();
    }
    std::vector<int> path;
    if (path_exists) {
        path = NormalizePath(parent, finish_vertex);
    }
    return path;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int vertex_number = 0;
    int edge_number = 0;

    std::cin >> vertex_number >> edge_number;
    
    int start_vertex = 0;
    int finish_vertex = 0;
    
    std::cin >> start_vertex >> finish_vertex;

    GraphList graph(vertex_number);

    int vertex_1 = 0;
    int vertex_2 = 0;
    
    for(int i = 0; i < edge_number; ++i) {
        std::cin >> vertex_1 >> vertex_2;
        graph.AddEdge(vertex_1 - 1, vertex_2 - 1);
        graph.AddEdge(vertex_2 - 1, vertex_1 - 1);
    }

    std::vector<int> res;
    res = Path(graph, start_vertex - 1, finish_vertex - 1);
    std::cout << (int)res.size() - 1 << std::endl;
    for(auto& elem : res) {
        std::cout << elem + 1 << std::endl;
    }
    return 0;
}
