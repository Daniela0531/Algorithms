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
    virtual std::vector<Edge>& Neighbors(int vertex) = 0;
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

    std::vector<Edge>& Neighbors(int vertex) {
        return graph_[vertex];
    }

    size_t GetNumberOfVertixes() const {
        return number_of_vertices;
    }

    size_t GetNumberOfEdges() const {
        return number_of_edges;
    }
};

enum Colors {
    WHITE,
    GRAY,
    BLACK,
};
bool Dfs(Graph& graph, int vertex, std::vector<Colors>& colors_of_vertexes, std::vector<int>& cycle);
bool IsCycle(Graph& graph, std::vector<int>& cycle);
void NormalizePath(std::vector<int>& bad_path);


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int number_of_vertexes = 0;
    int number_of_edges = 0;

    std::cin >> number_of_vertexes >> number_of_edges;

    GraphList graph(number_of_vertexes);

    int from_vertex = 0;
    int to_vertex = 0;
    for(int i = 0; i < number_of_edges; ++i) {
        std::cin >> from_vertex >> to_vertex;
        graph.AddEdge(from_vertex - 1, to_vertex - 1);
    }
    std::vector<int> cycle;
    if (IsCycle(graph, cycle)) {
        std::cout << "YES" << std::endl;
        for(auto& element : cycle) {
            std::cout << element + 1 << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
    return 0;
}



bool IsCycle(Graph& graph, std::vector<int>& cycle) {
    int number_of_vertexes = graph.GetNumberOfVertixes();
    std::vector<Colors> colors_of_vertexes(number_of_vertexes, WHITE);
    for(int vertex = 0; vertex < number_of_vertexes; ++vertex) {
        if (Dfs(graph, vertex, colors_of_vertexes, cycle)) {
            NormalizePath(cycle);
            return true;
        }
    }
    return false;
}

bool Dfs(Graph& graph, int vertex, std::vector<Colors>& colors_of_vertexes, std::vector<int>& path) {   
    colors_of_vertexes[vertex] = GRAY;
    path.push_back(vertex); // запоминаю все вершины, по которым иду
    for (auto& neighbor : graph.Neighbors(vertex)) {
        if (colors_of_vertexes[neighbor.vertex] == WHITE) {
            if (Dfs(graph, neighbor.vertex, colors_of_vertexes, path)) {
                return true;
            }
        } else if (colors_of_vertexes[neighbor.vertex] == GRAY) {
            path.push_back(neighbor.vertex);
            return true;
        }
    }
    colors_of_vertexes[vertex] = BLACK;
    path.pop_back(); // если дошли сюда, значит цикла не было, удаляем лишнее
    return false;
}

void NormalizePath(std::vector<int>& bad_path) {
    std::reverse(bad_path.begin(), bad_path.end());
    while(bad_path.front() != bad_path.back()) {
        bad_path.pop_back();
    }
    bad_path.pop_back();
    std::reverse(bad_path.begin(), bad_path.end());
}