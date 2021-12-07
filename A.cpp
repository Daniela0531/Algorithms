#include <bits/stdc++.h>

class DSU {
    std::vector<int> rank_;
    std::vector<int> parent_;

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
    explicit DSU(int n) {
        rank_.resize(n);
        parent_.resize(n);
    }
    void MakeSet(int v) {
        parent_[v] = v;
        rank_[v] = 0;
    }
    int FindSet(int v) {
        if (v == parent_[v]) {
            return v;
        }
        return (parent_[v] = FindSet(parent_[v]));
    }
    int Rank(int a) const {
        return rank_[a];
    }
    int Parent(int a) const {
        return parent_[a];
    }
    int& Rank(int a) {
        return rank_[a];
    }
    int& Parent(int a) {
        return parent_[a];
    }
};

int UnionSets(DSU& dsu, int a, int b) {
    a = dsu.FindSet(a);
    b = dsu.FindSet(b);
    if (a != b) {
        if (dsu.Rank(a) < dsu.Rank(b)) {
            int tmp = a;
            a = b;
            b = tmp;
        }
        dsu.Parent(b) = a;
        if (dsu.Rank(a) == dsu.Rank(b)) {
            ++dsu.Rank(a);
        }
        return 1;
    }
    return 0;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int num_of_vertex = 0;
    int num_of_edge = 0;

    std::cin >> num_of_vertex >> num_of_edge;

    int vertex_1 = 0;
    int vertex_2 = 0;
    DSU dsu(num_of_vertex);
    for (int i = 0; i < num_of_vertex; ++i) {
        dsu.MakeSet(i);
    }
    int key = 0;
    int answer = 0;
    for (int i = 0; i < num_of_edge; ++i) {
        std::cin >> vertex_1 >> vertex_2;
        num_of_vertex -= UnionSets(dsu, vertex_1, vertex_2);
        if (!key) {
            ++answer;
        }
        if (num_of_vertex == 1) {
            key = 1;
        }
    }
    std::cout << answer << std::endl;
}