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

// возвращать std::vector<Neighbors> мне кажется, что не имеет смысла,
// если эта функция должна быть универсальной и работать и для задачи А тоже, например,
// то тогда лучше передавать по ссылке этот вектор, и если нужно,
// пользователь пусть делает NormalizePath сам
// + для задачи А вроде как всё-таки другой алгоритм требуется
int Path(Graph& graph, int from_vertex, int to_vertex, int max_cost_of_edge) {
    std::vector<int> distance(graph.GetNumberOfVertixes(), distance_poison);
    distance[from_vertex] = 0;

    int number_of_queues = max_cost_of_edge + 1;
    std::vector<std::queue<int>> vector_of_queues(number_of_queues);
    vector_of_queues[0].push(from_vertex);
    int ind_of_cur_queue = 0;
    int number_of_vertex_in_queues = 1;
    
    while(number_of_vertex_in_queues > 0) {
        while(vector_of_queues[ind_of_cur_queue].empty()) {
            ind_of_cur_queue = ++ind_of_cur_queue % number_of_queues;
        }
        int vertex = vector_of_queues[ind_of_cur_queue].front();
        for(auto& cur_neighbor : graph.Neighbors(vertex)) {
            if (distance[cur_neighbor.vertex] == distance_poison || distance[vertex] + cur_neighbor.edge_cost < distance[cur_neighbor.vertex]) {
                distance[cur_neighbor.vertex] = distance[vertex] + cur_neighbor.edge_cost;
                int ind_of_queue_for_cur_neighbor = distance[cur_neighbor.vertex] % number_of_queues;
                vector_of_queues[ind_of_queue_for_cur_neighbor].push(cur_neighbor.vertex);
                ++number_of_vertex_in_queues;
            }
        }
        vector_of_queues[ind_of_cur_queue].pop();
        --number_of_vertex_in_queues;
    }
    return distance[to_vertex];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int number_of_vertexes = 0;
    int number_of_edges = 0;

    std::cin >> number_of_vertexes >> number_of_edges;

    int start_vertex = 0;
    int finish_vertex = 0;

    std::cin >> start_vertex >> finish_vertex;

    GraphList graph(number_of_vertexes);

    int from_vertex = 0;
    int to_vertex = 0;
    int edge_cost = 0;
    for(int ind_of_cur_neighbor = 0; ind_of_cur_neighbor < number_of_edges; ++ind_of_cur_neighbor) {
        std::cin >> from_vertex >> to_vertex >> edge_cost;
        graph.AddEdge(from_vertex - 1, to_vertex - 1, edge_cost);
    }
    std::cout << Path(graph, start_vertex - 1, finish_vertex - 1, 10) << std::endl;
    return 0;
}
