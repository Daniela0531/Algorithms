#include <bits/stdc++.h>
#include <iostream>
#include <vector>

template <class T>
class DSU {
    std::vector<int> rank_;
    std::vector<T> parent_;
    std::vector<int> weight_of_connectivity_components_;

public:
    void PrintParent() {
        for (size_t i = 0; i < parent_.size(); ++i) {
            std::cout << parent_[i] << " ";
        }
        std::cout << std::endl;
    }
    void PrintRank() {
        for (size_t i = 0; i < rank_.size(); ++i) {
            std::cout << rank_[i] << " ";
        }
        std::cout << std::endl;
    }
    int GetWeightOfConnectivityComponent(int v) {
        return weight_of_connectivity_components_[FindSet(v)];
    }
    explicit DSU(size_t n) {
        rank_.resize(n);
        parent_.resize(n);
        weight_of_connectivity_components_.resize(n);
    }
    // должна быть реализована в зависимости от типа
    int IndexForElem(T v) {
        return v;
    }
    void MakeSet(T v) {
        parent_[IndexForElem(v)] = v;
        rank_[IndexForElem(v)] = 0;
    }
    int FindSet(T v) {
        if (v == parent_[IndexForElem(v)]) {
            return v;
        }
        return (parent_[IndexForElem(v)] = FindSet(IndexForElem(parent_[v])));
    }
    void UnionSets(T x, T y, size_t weight) {
        x = FindSet(IndexForElem(x));
        y = FindSet(IndexForElem(y));
        if (x != y) {
            if (rank_[IndexForElem(x)] == rank_[IndexForElem(y)]) {
                parent_[IndexForElem(x)] = y;
                weight_of_connectivity_components_[IndexForElem(y)] +=
                    weight + weight_of_connectivity_components_[IndexForElem(x)];
                ++rank_[IndexForElem(y)];
            } else if (rank_[IndexForElem(x)] < rank_[IndexForElem(y)]) {
                parent_[IndexForElem(x)] = y;
                weight_of_connectivity_components_[IndexForElem(y)] +=
                    weight + weight_of_connectivity_components_[IndexForElem(x)];
            } else if (rank_[IndexForElem(y)] < rank_[IndexForElem(x)]) {
                parent_[IndexForElem(y)] = x;
                weight_of_connectivity_components_[IndexForElem(x)] +=
                    weight + weight_of_connectivity_components_[IndexForElem(y)];
            }
        } else {
            weight_of_connectivity_components_[IndexForElem(x)] += weight;
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t num_of_vertex = 0;
    int num_of_edge = 0;

    std::cin >> num_of_vertex >> num_of_edge;

    DSU<int> dsu(num_of_vertex);
    for (size_t i = 0; i < num_of_vertex; ++i) {
        dsu.MakeSet(i);
    }
    for (int i = 0; i < num_of_edge; ++i) {
        int command = 0;
        std::cin >> command;
        if (command == 1) {
            int vertex_1 = 0;
            int vertex_2 = 0;
            int weight = 0;
            std::cin >> vertex_1 >> vertex_2 >> weight;
            dsu.UnionSets(vertex_1 - 1, vertex_2 - 1, weight);
        } else if (command == 2) {
            int vertex = 0;
            std::cin >> vertex;
            std::cout << dsu.GetWeightOfConnectivityComponent(vertex - 1) << "\n";
        }
    }
}