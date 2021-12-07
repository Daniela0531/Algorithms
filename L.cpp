#include <iostream>
#include <bits/stdc++.h>

template <typename INPUT_T>
class Graf {
	enum Colors {
		WHITE,
	    GRAY,
	    BLACK,
	    RED,
	};

	struct Graf_elem {
		INPUT_T graf_elem_val;
		int graf_elem_ind;
		Colors color;
		Graf_elem() {}
		void operator()(INPUT_T ind) {
			graf_elem_ind = ind - 1;
			graf_elem_val = ind;
			color = WHITE;
		}
	};

	std::vector<std::vector<Graf_elem>> graf;
	size_t begin = 0;

	void Dfs(int ind, std::vector<bool>& res) {
		if (graf[ind][0].color == BLACK || graf[ind][0].color == RED) {
			res[ind] = false;
			return;
		}
		graf[ind][0].color = GRAY;
		for (int i = 1; i < graf[ind].size(); ++i) {
			if (graf[ind][i].color == WHITE) {
				graf[ind][i].color = GRAY;
				Dfs(graf[ind][i].graf_elem_ind, res);
				graf[ind][i].color = BLACK;
			}
		}
		graf[ind][0].color = BLACK;
	}

	void Build() {
		int n = graf.size();
		for(int i = 0; i < n; ++i) {
			if (graf[i].size() == 0) {
				Graf_elem elem;
				elem(i + 1);
				graf[i].push_back(elem);
			}
		}
	}

public:

	Graf(size_t input_size) {
		graf.resize(input_size);
		for(int i = 0; i < input_size; ++i) {
			Graf_elem elem;
			elem(i + 1);
			graf[i].push_back(elem);
		}
	}

	void Add(INPUT_T left_graf_val, INPUT_T right_graf_val) {
		Graf_elem left_graf_elem;
		left_graf_elem(left_graf_val);
		Graf_elem right_graf_elem;
		right_graf_elem(right_graf_val);
		if (graf[left_graf_elem.graf_elem_ind].size() == 0) {
			graf[left_graf_elem.graf_elem_ind].push_back(left_graf_elem);
		}
		graf[left_graf_elem.graf_elem_ind].push_back(right_graf_elem);
	}

	void ConnectivityComponents() {
		int n = graf.size();
		int sum = 0;
		std::vector<bool> res(n, {true});
		for(int i = 0; i < n; ++i) {
			Dfs(i, res);
		}
		for(int i = 0; i < n; ++i) {
			sum += res[i];
		}
	    std::cout << sum << std::endl;
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n = 0;
	int money_box_with_key_from_other_money_box = 0;
	int other_money_box = 0;
	int begin = 0;

	std::cin >> n;

	Graf<int> graf(n);

	for(int i = 1; i <= n; ++i) {
		std::cin >> money_box_with_key_from_other_money_box;
		other_money_box = i;
		graf.Add(money_box_with_key_from_other_money_box, other_money_box);
	}
	graf.ConnectivityComponents();
	return 0;
}