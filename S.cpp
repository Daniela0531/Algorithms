#include <iostream>
#include <bits/stdc++.h>

class Graph {
public:
    virtual void Add(int left_graph_val, int right_graph_val, int edge) = 0;
};

class GraphList : public Graph {
    struct Vertex_and_edge {
        int v;
        int edge;
    };
    std::vector<std::vector<Vertex_and_edge>> graph;
    
    int time;
    std::vector<int> time_in;
    std::vector<int> time_up;
    std::vector<bool> is_visited;

    void Dfs(int v, int p, std::vector<int>& res) {
		is_visited[v] = true;
		time_in[v] = time;
        time_up[v] = time++;
        int key = 0;
		for(auto& to : graph[v]) {
            if (to.v == p) {
                if (!key) {
                    key = 1;
                    continue;
                }
            }
			if (!is_visited[to.v]) {
                Dfs(to.v, v, res);
                time_up[v] = std::min(time_up[v], time_up[to.v]);
                if (time_up[to.v] > time_in[v]) {
                    res.push_back(to.edge);
                }
			} else {
                time_up[v] = std::min(time_up[v], time_in[to.v]);
			}
		}
	}

public:

    GraphList(size_t input_size) {
        graph.resize(input_size);
    }

    void Add(int left_val, int right_val, int edge) {
        graph[left_val].push_back({right_val, edge});
        graph[right_val].push_back({left_val, edge});
    }

    void FindBridges() {
		time = 0;
        time_in.resize(graph.size());
        time_up.resize(graph.size());

        is_visited.resize(graph.size());
        is_visited.assign(graph.size(), false);

        std::vector<int> res;
		for(int i = 0; i < graph.size(); ++i) {
			if (!is_visited[i]) {
				Dfs(i, -1, res);
			}
		}
        std::cout << res.size() << std::endl;
        std::sort(res.begin(), res.end());
        for(auto& elem : res) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
	}

    void Print() {
        for(int i = 0; i < graph.size(); ++i) {
            for(int j  = 0; j < graph[i].size(); ++j) {
                printf("[%d][%d] = %d\n", i, j, graph[i][j].edge);
            }
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n = 0, m = 0;
    int left = 0, right = 0;

    std::cin >> n >> m;

    GraphList graph(n);

    for(int i = 1; i <= m; ++i) {
    	std::cin >> left >> right;
        graph.Add(left - 1, right - 1, i);
    }
    graph.FindBridges();
    return 0;
}
