#include <iostream>
#include <bits/stdc++.h>

struct Graph {
public:
    virtual void Add(int left_graph_val, int right_graph_val) = 0;
};

class GraphList : public Graph {
	enum Colors {
		WHITE,
	    GRAY,
	    BLACK,
	};

	std::vector<std::vector<int>> graph;
	size_t begin = 0;

	bool Dfs(int elem_ind, std::vector<bool>& is_visited, std::vector<Colors>& colors, std::vector<int>& res) {	
		bool key = false;
		colors[elem_ind] = GRAY;
		res.push_back(elem_ind + 1);
		for (int i = 0; i < graph[elem_ind].size(); ++i) {
			if (colors[graph[elem_ind][i]] == GRAY) {
				key = true;
				res.push_back(graph[elem_ind][i] + 1);
				return key;
			}
			if (colors[graph[elem_ind][i]] == WHITE) {
				key = Dfs(graph[elem_ind][i], is_visited, colors, res);
			}
			if (key) {
				return key;
			}
		}
		colors[elem_ind] = BLACK;
		res.pop_back();
		return key;
	}

	bool IsCycle(std::vector<int>& res) {
		bool key = false;
		int n = graph.size();
		std::vector<bool> is_visited(graph.size(), false);
		std::vector<Colors> colors(graph.size(), WHITE);
		for(int i = 0; i < n; ++i) {
			key = Dfs(i, is_visited, colors, res);
			if (key) {
				break;
			}
		}
		return key;
	}

public:

	GraphList(size_t input_size) {
		graph.resize(input_size);
	}

	void Add(int left_val, int right_val) {
		graph[left_val].push_back(right_val);
	}

	void IsMonochromeColoring() {
		std::vector<int> res;
		if (IsCycle(res)) {
			std::cout << "NO" << std::endl;
			return;
		}
		std::cout << "YES" << std::endl;
	}

	void Print() {
		for(int i = 0; i < graph.size(); ++i) {
			for(int j  = 0; j < graph[i].size(); ++j) {
				printf("%d %d\n", i, graph[i][j]);
			}
		}
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n = 0;

	std::cin >> n;
	char* colors = (char*)calloc(n, sizeof(char));

	GraphList graph(n);

	for(int i = 0; i < n - 1; ++i) {
		std::cin >> colors;
		for(int j = 0; j < n - 1 - i; ++j) {
			if (colors[j] == 'R') {
				graph.Add(i, i + j + 1);
			} else if (colors[j] == 'B') {
				graph.Add(i + j + 1, i);
			}
		}
	}

	graph.IsMonochromeColoring();
	return 0;
}