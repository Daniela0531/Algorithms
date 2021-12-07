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

struct Cell {
    int x;
    int y;
    Cell();
    Cell(int other_x, int other_y);
    Cell operator+(Cell other);
    Cell operator()(int other_x, int other_y);
};

class Grid {
    int grid_width = 0;
public:
    Grid(int width);
    Cell MakeCell(int other_x, int other_y);
    int MakeVertexFromCoord(int cell_x, int cell_y);
    int GetVertexFromCell(Cell cell);
    bool BelongsToGrid(Cell cell);
};

class Moves {
    std::vector<Cell> knites_moves = {{-2, 1}, {-2, -1}, {-1, 2}, {-1, -2}, {1, 2}, {1, -2}, {2, 1}, {2, -1}};
public:
    std::vector<Cell> KnitesMoves() {
        return knites_moves;
    }
};

void BuildGraph(Graph& graph, int grid_width);


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int grid_width = 0;

    std::cin >> grid_width;

    int start_cell_x, start_cell_y;
    int finish_cell_x, finish_cell_y;
    
    std::cin >> start_cell_x >> start_cell_y >> finish_cell_x >> finish_cell_y;
    
    int number_of_vertexes = grid_width * grid_width;
    GraphList graph(number_of_vertexes);

    BuildGraph(graph, grid_width);

    Grid grid(grid_width);
    
    int start_vertex = grid.MakeVertexFromCoord(start_cell_x - 1, start_cell_y - 1);
    int finish_vertex = grid.MakeVertexFromCoord(finish_cell_x - 1, finish_cell_y - 1);
    
    std::vector<int> res = Path(graph, start_vertex, finish_vertex);
    
    std::cout << (int)res.size() - 1 << std::endl;
    for(auto elem : res) {
        std::cout << elem % grid_width + 1 << " " << elem / grid_width + 1 << std::endl;
    }
    return 0;
}

void BuildGraph(Graph& graph, int grid_width) {
    Grid grid(grid_width);
    Moves moves;
    for(int x = 0; x < grid_width; ++x) {
        for(int y = 0; y < grid_width; ++y) {
            Cell cell = grid.MakeCell(x, y);
            for(auto move : moves.KnitesMoves()) {
                if (grid.BelongsToGrid(cell + move)) {
                    int vertex = grid.GetVertexFromCell(cell);
                    Cell new_cell = cell + move;
                    int vertex_neighbor = grid.GetVertexFromCell(cell + move);
                    graph.AddEdge(vertex, vertex_neighbor);
                }
            }
        }
    }
}

// Cell ////////////////////////////////////////////
Cell::Cell(int other_x, int other_y) {
    x = other_x;
    y = other_y;
}
Cell Cell::operator+(Cell other) {
    Cell cell(x + other.x, y + other.y);
    return cell;
}
Cell Cell::operator()(int other_x, int other_y) {
    x = other_x;
    y = other_y;
    return *this;
}


// Grid ////////////////////////////////////////////
Grid::Grid(int width) {
    grid_width = width;
}
Cell Grid::MakeCell(int other_x, int other_y) {
    Cell cell(other_x, other_y);
    return cell;
}
int Grid::MakeVertexFromCoord(int cell_x, int cell_y) {
    return cell_y * grid_width + cell_x;
}
int Grid::GetVertexFromCell(Cell cell) {
    return cell.y * grid_width + cell.x;
}
bool Grid::BelongsToGrid(Cell cell) {
    return cell.x >= 0 && cell.y >= 0 && cell.x < grid_width && cell.y < grid_width;
}

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
