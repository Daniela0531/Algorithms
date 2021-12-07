#include <bits/stdc++.h>

class DSU {
    std::vector<int> rank_;
    std::vector<int> parent_;
    std::vector<int> weights_;

public:
    void PrintParent();
    void PrintRank();
    explicit DSU(int n) {
        rank_.resize(n);
        parent_.resize(n);
    }
    void MakeSet(int v);
    int FindSet(int v);
    int Rank(int a) const;
    int Parent(int a) const;
    int& Rank(int a);
    int& Parent(int a);
};

struct Edge {
    int from_vertex;
    int to_vertex;
    int weight;
    bool operator<=(const Edge& b) const;
};

void UnionSets(DSU& dsu, int vertex_1, int vertex_2);
int Kraskal(DSU& dsu, std::vector<Edge> edges);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int num_of_vertex = 0;
    int num_of_edge = 0;

    std::cin >> num_of_vertex >> num_of_edge;
    DSU dsu(num_of_vertex + num_of_edge);

    for (int i = 0; i < num_of_vertex + num_of_edge; ++i) {
        dsu.MakeSet(i);
    }

    int from_vertex = 0;
    int to_vertex = 0;
    int weight = 0;

    std::vector<Edge> edges;
    for (int i = 0; i < num_of_edge; ++i) {
        std::cin >> from_vertex >> to_vertex >> weight;
        --from_vertex;
        --to_vertex;
        edges.push_back({from_vertex, to_vertex, weight});
    }

    int answer = Kraskal(dsu, edges);
    std::cout << answer << std::endl;
    return 0;
}

int Kraskal(DSU& dsu, std::vector<Edge> edges) {
    int answer = 0;
    for (auto edge : edges) {
        if (dsu.FindSet(edge.from_vertex) != dsu.FindSet(edge.to_vertex)) {
            UnionSets(dsu, edge.from_vertex, edge.to_vertex);
            answer += edge.weight;
        }
    }
    return answer;
}

void UnionSets(DSU& dsu, int vertex_1, int vertex_2) {
    int current_parent_1 = dsu.FindSet(vertex_1);
    int current_parent_2 = dsu.FindSet(vertex_2);
    if (dsu.Rank(vertex_1) > dsu.Rank(vertex_2)) {
        dsu.Parent(current_parent_1) = current_parent_2;
        dsu.Rank(current_parent_1) += dsu.Rank(current_parent_2);
    } else {
        dsu.Parent(current_parent_2) = current_parent_1;
        dsu.Rank(current_parent_2) += dsu.Rank(current_parent_1);
    }
}

bool Edge::operator<=(const Edge& b) const {
    if (weight <= b.weight) {
        return true;
    }
    if (from_vertex > b.from_vertex) {
        return false;
    }
    return (to_vertex <= b.to_vertex);
}

void DSU::MakeSet(int v) {
    parent_[v] = v;
    rank_[v] = 1;
}
int DSU::FindSet(int v) {
    if (v == parent_[v]) {
        return v;
    }
    return (parent_[v] = FindSet(parent_[v]));
}
int DSU::Rank(int a) const {
    return rank_[a];
}
int DSU::Parent(int a) const {
    return parent_[a];
}
int& DSU::Rank(int a) {
    return rank_[a];
}
int& DSU::Parent(int a) {
    return parent_[a];
}
void DSU::PrintParent() {
    for (size_t i = 0; i < parent_.size(); ++i) {
        std::cout << parent_[i] << " ";
    }
    std::cout << std::endl;
}
void DSU::PrintRank() {
    for (size_t i = 0; i < rank_.size(); ++i) {
        std::cout << rank_[i] << " ";
    }
    std::cout << std::endl;
}