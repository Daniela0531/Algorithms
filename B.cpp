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

enum PARTS {
    LEFT,
    RIGHT,
    NOT_CHOSEN,
};


bool CurrentConnectivityComponentCanBeSeparated(const Graph& graph, int start_vertex, std::vector<PARTS>& chosen_part_for_vertex) {
    std::queue<int> queue_of_vertexes;
    queue_of_vertexes.push(start_vertex);
    chosen_part_for_vertex[start_vertex] = LEFT;
    while(queue_of_vertexes.size()) {
        start_vertex = queue_of_vertexes.front();
        for(auto cur_neighbor : graph.Neighbors(start_vertex)) {
            if (chosen_part_for_vertex[cur_neighbor.vertex] == NOT_CHOSEN) {
                chosen_part_for_vertex[cur_neighbor.vertex] = (chosen_part_for_vertex[start_vertex] == LEFT) ? RIGHT : LEFT;
                queue_of_vertexes.push(cur_neighbor.vertex);
            }
            if (chosen_part_for_vertex[cur_neighbor.vertex] == chosen_part_for_vertex[start_vertex]) {
                return false;
            }
        }
        queue_of_vertexes.pop();
    }
    return true;
}

bool GraphCanBeSeparated(const Graph& graph) {
    std::vector<PARTS> chosen_part_for_vertex(graph.GetNumberOfVertixes(), NOT_CHOSEN);
    for(int i = 0; i < graph.GetNumberOfVertixes(); ++i) {
        if (chosen_part_for_vertex[i] == NOT_CHOSEN) {
            if (!CurrentConnectivityComponentCanBeSeparated(graph, i, chosen_part_for_vertex)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int vertex_number = 0;
    int edge_number = 0;

    std::cin >> vertex_number >> edge_number;

    GraphList graph(vertex_number);
    
    int vertex_1 = 0;
    int vertex_2 = 0;
    
    for (int i = 0; i < edge_number; i++) {
        std::cin >> vertex_1 >> vertex_2;
        graph.AddEdge(--vertex_1, --vertex_2);
        graph.AddEdge(vertex_2, vertex_1);
    }

    if (GraphCanBeSeparated(graph)) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
    return 0;
}
