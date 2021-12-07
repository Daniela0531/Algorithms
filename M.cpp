#include <iostream>
#include <bits/stdc++.h>

template <typename INPUT_T>
class Graph {
    enum Colors {
        WHITE,
        GRAY,
        BLACK,
    };
    struct Graph_elem {
        INPUT_T graph_elem_val;
        int graph_elem_ind;
        Colors color;
        Graph_elem() {}
        void operator()(INPUT_T ind) {
            graph_elem_ind = ind - 1;
            graph_elem_val = ind;
            color = WHITE;
        }
    };
    std::vector<std::vector<Graph_elem>> graph;
    size_t begin = 0;

    void FindConnectivityComponentsWithDfs(int ind, std::vector<bool>& roots, std::vector<INPUT_T>& each_root_vertices) {
        if (graph[ind][0].color == BLACK) {
            roots[ind] = false;
            return;
        }
        if (graph[ind][0].color == WHITE) {
            each_root_vertices.push_back(graph[ind][0].graph_elem_val);
        }
        graph[ind][0].color = GRAY;
        for(int i = 1; i < graph[ind].size(); ++i) {
            if (graph[ind][i].color == WHITE) {
                graph[ind][i].color = GRAY;
                FindConnectivityComponentsWithDfs(graph[ind][i].graph_elem_ind, roots, each_root_vertices);
                graph[ind][i].color = BLACK;
            }
        }
        graph[ind][0].color = BLACK;
    }

public:

    Graph(size_t input_size) {
        graph.resize(input_size);
        for(int i = 0; i < input_size; ++i) {
            Graph_elem elem;
            elem(i + 1);
            graph[i].push_back(elem);
        }
    }

    void Add(INPUT_T left_graph_val, INPUT_T right_graph_val) {
        Graph_elem left_graph_elem;
        left_graph_elem(left_graph_val);
        Graph_elem right_graph_elem;
        right_graph_elem(right_graph_val);
        graph[right_graph_elem.graph_elem_ind].push_back(left_graph_elem);
        graph[left_graph_elem.graph_elem_ind].push_back(right_graph_elem);
    }

    void ConnectivityComponents() {
        int n = graph.size();
        int sum = 0;
        std::vector<bool> res(n, {true});
        std::vector<std::vector<INPUT_T>> sub_graph(n);
        for(int i = 0; i < n; ++i) {
            FindConnectivityComponentsWithDfs(i, res, sub_graph[i]);
        }
        for(int i = 0; i < n; ++i) {
            sum += res[i];
        }
        std::cout << sum << std::endl;
        for(int i = 0; i < n; ++i) {
            if (sub_graph[i].size()) {
                std::cout << sub_graph[i].size() << std::endl;
                for(int j = 0; j < sub_graph[i].size(); ++j) {
                std::cout << sub_graph[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n = 0, m = 0;
    int couple_member = 0, other_couple_member = 0;
    int begin = 0;

    std::cin >> n >> m;

    Graph<int> graph(n);

    for(int i = 1; i <= m; ++i) {
        std::cin >> couple_member >> other_couple_member;
        graph.Add(couple_member, other_couple_member);
    }
    graph.ConnectivityComponents();
    return 0;
}