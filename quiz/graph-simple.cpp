
#include <vector>
#include <iostream>
#include <set>
#include <queue>
#include <limits>
using namespace std;

struct TEdge {
    size_t From;
    size_t To;
    int Weight;
};

class TGraph {
private:
    vector<vector<TEdge> > AdjLists;
    vector<TEdge> Edges;

    void DfsImpl(size_t nodeInd, set<size_t>& unvisited) const {
        unvisited.erase(nodeInd);
        cout << nodeInd << " ";
        const vector<TEdge>& adj = AdjLists[nodeInd];
        for (size_t i = 0; i < adj.size(); ++i) {
            if (unvisited.count(adj[i].To)) {
                DfsImpl(adj[i].To, unvisited);
            }
        }
    }

    vector<int> InitDists(int src) const {
        vector<int> dists(Size(), numeric_limits<int>::max());
        dists[src] = 0;
        return dists;
    }

    void PrintDists(const vector<int>& dists) const {
        for (size_t i = 0; i < dists.size(); ++i) {
            cout << i << " => " << dists[i] << endl;
        }
    }

    void Relax(const TEdge& edge, vector<int>& dists) const {
        if (dists[edge.From] != numeric_limits<int>::max()) {
            if (dists[edge.To] > dists[edge.From] + edge.Weight) {
                dists[edge.To] = dists[edge.From] + edge.Weight;
            }
        }
    }

    bool HasNegativeCycles(const vector<int>& dists) const {
        for (size_t i = 0; i < Edges.size(); ++i) {
            if (dists[Edges[i].To] > dists[Edges[i].From] + Edges[i].Weight) {
                return true;
            }
        }
        return false;
    }

    size_t GetClosest(const vector<int>& dists, const vector<bool>& spanTree) const {
        size_t closestNode = 0;
        int minDist = numeric_limits<int>::max();
        for (size_t i = 0; i < dists.size(); ++i) {
            if (!spanTree[i] && minDist > dists[i]) {
                minDist = dists[i];
                closestNode = i;
            }
        }
        return closestNode;
    }

public:
    TGraph(size_t size)
        : AdjLists(size)
    {}

    void Insert(size_t from, size_t to, int weight) {
        TEdge edge = {from, to, weight};
        AdjLists[from].push_back(edge);
        Edges.push_back(edge);
    }

    void Bfs() const {
        set<size_t> unvisited;
        for (size_t i = 0; i < AdjLists.size(); ++i) {
            unvisited.insert(i);
        }
        queue<size_t> visitQueue;
        visitQueue.push(0);
        while (!unvisited.empty()) {
            size_t nodeInd;
            if (visitQueue.empty()) {
                nodeInd = *unvisited.begin();
            } else {
                nodeInd = visitQueue.front();
                visitQueue.pop();
            }
            cout << nodeInd << " ";
            const vector<TEdge>& adj = AdjLists[nodeInd];
            for (size_t i = 0; i < adj.size(); ++i) {
                if (unvisited.count(adj[i].To)) {
                    visitQueue.push(adj[i].To);
                    unvisited.erase(adj[i].To);
                }
            }
        }
    }

    void Dfs() const {
        set<size_t> unvisited;
        for (size_t i = 0; i < AdjLists.size(); ++i) {
            unvisited.insert(i);
        }
        while (!unvisited.empty()) {
            DfsImpl(*unvisited.begin(), unvisited);
        }
    }

    TGraph Copy() const {
        TGraph res(Size());
        res.AdjLists = AdjLists;
        return res;
    }

    size_t Size() const {
        return AdjLists.size();
    }

    // O(V*E)
    void BellmanFord(size_t src) const {
        vector<int> dists = InitDists(src);
        for (size_t i = 1; i <= Size() - 1; ++i) {
            for (size_t j = 0; j < Edges.size(); ++j) {
                Relax(Edges[j], dists);
            }
        }
        if (!HasNegativeCycles(dists)) {
            PrintDists(dists);
        }
    }

    // O(V^2)
    void Dijkstra(size_t src) const {
        vector<int> dists = InitDists(src);
        vector<bool> spanTree(Size(), false);

        for (size_t treeSize = 0; treeSize < Size(); ++treeSize) {
            size_t nodeInd = GetClosest(dists, spanTree);
            spanTree[nodeInd] = true;
            for (size_t i = 0; i < AdjLists[nodeInd].size(); ++i) {
                Relax(AdjLists[nodeInd][i], dists);
            }
        }
        PrintDists(dists);
    }
};

int main() {
    TGraph graph(5);
    graph.Insert(0, 1, 6);
    graph.Insert(0, 3, 7);
    graph.Insert(1, 2, 5);
    graph.Insert(1, 3, 8);
    graph.Insert(1, 4, -4);
    graph.Insert(2, 1, -2);
    graph.Insert(3, 2, -3);
    graph.Insert(3, 4, 9);
    graph.Insert(4, 2, 7);
    graph.Insert(4, 0, 2);

    cout << "DFS: ";
    graph.Dfs();
    cout << endl;

    cout << "BFS: ";
    graph.Bfs();
    cout << endl;

    TGraph copy = graph.Copy();

    cout << "copy DFS: ";
    copy.Dfs();
    cout << endl;

    cout << "copy BFS: ";
    copy.Bfs();
    cout << endl;

    int src = 0;
    cout << "Bellman Ford from src " << src << endl;
    graph.BellmanFord(src);

    TGraph nonNegGraph(5);
    nonNegGraph.Insert(0, 1, 10);
    nonNegGraph.Insert(0, 3, 5);
    nonNegGraph.Insert(1, 2, 1);
    nonNegGraph.Insert(1, 3, 2);
    nonNegGraph.Insert(2, 4, 4);
    nonNegGraph.Insert(3, 1, 3);
    nonNegGraph.Insert(3, 2, 9);
    nonNegGraph.Insert(3, 4, 2);
    nonNegGraph.Insert(4, 0, 7);
    nonNegGraph.Insert(4, 2, 6);

    cout << "non-neg BFS: ";
    nonNegGraph.Bfs();
    cout << endl;

    cout << "Dijkstra from src " << src << endl;
    nonNegGraph.Dijkstra(src);

    return 0;
}
