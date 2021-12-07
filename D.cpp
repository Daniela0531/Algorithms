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

std::vector<int> NormalizePath(std::vector<int> parent, int finish_vertex);
std::vector<int> Path(const Graph& graph, int start_vertex, int finish_vertex);

int number_with_left_shift(int x);
int number_with_right_shift(int x);
int number_with_changed_first_digit(int x);
int number_with_changed_last_digit(int x);
bool NoZerosInNumber(int x);
void BuildGraph(Graph& graph, int start_number, int finish_number);




int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int max_amount_of_numbers = 10000;

    int start_number;
    int finish_number;
    
    std::cin >> start_number >> finish_number;
    
    int number_of_vertexes = max_amount_of_numbers;
    GraphList graph(number_of_vertexes);
    BuildGraph(graph, 1111, 9999);

    std::vector<int> res = Path(graph, start_number, finish_number);
    
    std::cout << (int)res.size() << std::endl;
    for(auto elem : res) {
        std::cout << elem << std::endl;
    }
    return 0;
}



void BuildGraph(Graph& graph, int min_number, int max_number) {
    for(int cur_number = min_number; cur_number <= max_number; ++cur_number) {
        if (NoZerosInNumber(cur_number)) {
            if (NoZerosInNumber(number_with_changed_first_digit(cur_number))) {
                graph.AddEdge(cur_number, number_with_changed_first_digit(cur_number));
            }
            if (NoZerosInNumber(number_with_changed_last_digit(cur_number))) {
                graph.AddEdge(cur_number, number_with_changed_last_digit(cur_number));
            }
            if (NoZerosInNumber(number_with_left_shift(cur_number))) {
                graph.AddEdge(cur_number, number_with_left_shift(cur_number));
            }
            if (NoZerosInNumber(number_with_right_shift(cur_number))) {
                graph.AddEdge(cur_number, number_with_right_shift(cur_number));
            }
        }
    }
}

bool NoZerosInNumber(int x) {
    return (x % 10) != 0 && ((x / 10) % 10) != 0 && ((x / 100) % 10) != 0 && (x / 1000) != 0;
}

int number_with_left_shift(int x) {
    return (x % 1000) * 10 + (x / 1000);
}
int number_with_right_shift(int x) {
    return (x % 10) * 1000 + (x / 10);
}
int number_with_changed_first_digit(int x) {
    if (x / 1000 < 9) {
        x += 1000; 
    }
    return x;
}
int number_with_changed_last_digit(int x) {
    if (x % 10 > 1) {
        x -= 1; 
    }
    return x;
}
// int ChangesInNumber::left_shift(int x) {
//     return (x % 1000) * 10 + (x / 1000);
// }

// int ChangesInNumber::right_shift(int x) {
//     return (x % 10) * 1000 + (x / 10);
// }

// int ChangesInNumber::change_first_digit(int x) {
//     if (x / 1000 < 9) {
//         x += 1000; 
//     }
//     return x;
// }

// int ChangesInNumber::change_last_digit(int x) {
//     if (x % 10 > 1) {
//         x -= 1; 
//     }
//     return x;
// }


// Path /////////////////////////////////////////////
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