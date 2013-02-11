
#include <iostream>
#include <vector>
#include <unordered_set>
#include <memory>
#include <list>
using namespace std;

class IUndirectedGraph;

class IAdjIterator {
public:
	virtual ~IAdjIterator() {}
	virtual bool End() const = 0;
	virtual void Next() = 0;
	virtual int operator*() const = 0;
};

class IUndirectedGraph {
public:
	virtual ~IUndirectedGraph() {}
	virtual void InsertEdge(int v1, int v2) = 0;
	virtual void DeleteEdge(int v1, int v2) = 0;
	virtual bool HasEdge(int v1, int v2) const = 0;
	virtual size_t EdgesCount() const = 0;
	virtual size_t VertCount() const = 0;
	virtual IAdjIterator* Iter(int v) const = 0;
};

// Implementation of undirected graph using vector of edges and hash-set of vertices
// memory and time requirements:
// memory: O(E+V)
// insertion of an edge: O(1)
// insertion of a vertex: O(1)
// search of an edge: O(E)
// deletion of an edge: O(E)
// deletion of a vertex: O(E)
// path search: O(E^2)
class TEdgesVectorUndirectedGraph: public IUndirectedGraph {
private:
	vector<pair<int, int> > Edges;
	unordered_set<int> Vertices;

public:
	class TAdjIterator: public IAdjIterator {
	private:
		const TEdgesVectorUndirectedGraph* Graph;
		int Vertex;
		size_t Ind;

	public:
		TAdjIterator(const TEdgesVectorUndirectedGraph* graph, int v)
			: Graph(graph)
			, Vertex(v)
			, Ind(0)
		{
			while(!End() && Graph->Edges[Ind].first != Vertex && Graph->Edges[Ind].second != Vertex) {
				++Ind;
			}
		}

		virtual bool End() const {
			return Ind == Graph->Edges.size();
		}

		virtual void Next() {
			do {
				++Ind;
			} while(!End() && Graph->Edges[Ind].first != Vertex && Graph->Edges[Ind].second != Vertex);
		}

		virtual int operator*() const {
			pair<int, int> edge = Graph->Edges[Ind];
			return edge.first == Vertex
				? edge.second
				: edge.first;
		}
	};

	virtual void InsertEdge(int v1, int v2) {
		pair<int, int> edge(::min(v1, v2), ::max(v1, v2));
		for (size_t i = 0; i < Edges.size(); ++i) {
			if (Edges[i] == edge) {
				return;
			}
		}
		Edges.push_back(edge);
		Vertices.insert(v1);
		Vertices.insert(v2);
	}

	virtual void DeleteEdge(int v1, int v2) {
		pair<int, int> edge(::min(v1, v2), ::max(v1, v2));
		for (vector<pair<int, int> >::iterator iter = Edges.begin(); iter != Edges.end(); ++iter) {
			if (*iter == edge) {
				Edges.erase(iter);
				return;
			}
		}
	}

	virtual bool HasEdge(int v1, int v2) const {
		pair<int, int> edge(::min(v1, v2), ::max(v1, v2));
		for (size_t i = 0; i < Edges.size(); ++i) {
			if (Edges[i] == edge) {
				return true;
			}
		}
		return false;
	}

	virtual size_t EdgesCount() const {
		return Edges.size();
	}

	virtual size_t VertCount() const {
		return Vertices.size();
	}

	virtual IAdjIterator* Iter(int v) const {
		return new TAdjIterator(this, v);
	}
};

// Implementation of undirected graph using adjancy matrix
// memory and time requirements:
// memory: O(V^2)
// insertion of an edge: O(1)
// insertion of a vertex: O(V)
// search of an edge: O(1)
// deletion of an edge: O(1)
// deletion of a vertex: O(V)
// path search: O(V^2)
class TMatrixUndirectedGraph: public IUndirectedGraph {
private:
	vector<vector<bool> > Matrix;
	size_t Count;

public:
	class TAdjIterator: public IAdjIterator {
	private:
		const TMatrixUndirectedGraph* Graph;
		int Vertex;
		size_t Ind;

	public:
		TAdjIterator(const TMatrixUndirectedGraph* graph, int v)
			: Graph(graph)
			, Vertex(v)
			, Ind(0)
		{
			while (Ind < Graph->Matrix.size() && !Graph->Matrix[v][Ind]) {
				++Ind;
			}
		}

		virtual bool End() const {
			return Ind == Graph->Matrix.size();
		}

		virtual void Next() {
			do {
				++Ind;
			} while (Ind < Graph->Matrix.size() && !Graph->Matrix[Vertex][Ind]);
		}

		virtual int operator*() const {
			return Ind;
		}
	};

	TMatrixUndirectedGraph()
		: Count(0)
	{}

	virtual void InsertEdge(int v1, int v2) {
		size_t m = ::max(v1, v2) + 1;
		if (m > Matrix.size()) {
			Matrix.resize(m);
			for (size_t i = 0; i < m; ++i) {
				Matrix[i].resize(m, false);
			}
		}
		Matrix[v1][v2] = true;
		Matrix[v2][v1] = true;
		++Count;
	}

	virtual void DeleteEdge(int v1, int v2) {
		Matrix[v1][v2] = false;
		Matrix[v2][v1] = false;
		--Count;
	}

	virtual bool HasEdge(int v1, int v2) const {
		return Matrix[v1][v2];
	}

	virtual size_t EdgesCount() const {
		return Count;
	}

	virtual size_t VertCount() const {
		return Matrix.size() - 1;
	}

	virtual IAdjIterator* Iter(int v) const {
		return new TAdjIterator(this, v);
	}

};

// Implementation of undirected graph using adjancy matrix
// memory and time requirements:
// memory: O(V+E)
// insertion of an edge: O(1)
// insertion of a vertex: O(1)
// search of an edge: O(V)
// deletion of an edge: O(V)
// deletion of a vertex: O(E)
// path search: O(V+E)
class TAdjListUndirectedGraph: public IUndirectedGraph {
private:
	vector<list<int> > Vertices;
	size_t Count;

public:
	class TAdjIterator: public IAdjIterator {
		private:
			const TAdjListUndirectedGraph* Graph;
			int Vertex;
			list<int>::const_iterator Iter;

		public:
			TAdjIterator(const TAdjListUndirectedGraph* graph, int v)
				: Graph(graph)
				, Vertex(v)
				, Iter(Graph->Vertices[v].begin())
			{}

			virtual bool End() const {
				return Iter == Graph->Vertices[Vertex].end();
			}

			virtual void Next() {
				++Iter;
			}

			virtual int operator*() const {
				return *Iter;
			}
		};

	TAdjListUndirectedGraph()
		: Count(0)
	{}

	virtual void InsertEdge(int v1, int v2) {
		size_t m = ::max(v1, v2) + 1;
		if (m > Vertices.size()) {
			Vertices.resize(m);
		}
		Vertices[v1].push_back(v2);
		Vertices[v2].push_back(v1);
		++Count;
	}

	virtual void DeleteEdge(int v1, int v2) {
		Vertices[v1].remove(v2);
		Vertices[v2].remove(v1);
		--Count;
	}

	virtual bool HasEdge(int v1, int v2) const {
		const list<int>& adj = Vertices[v1];
		for (list<int>::const_iterator iter = adj.begin(); iter != adj.end(); ++iter) {
			if (*iter == v2) {
				return true;
			}
		}
		return false;
	}

	virtual size_t EdgesCount() const {
		return Count;
	}

	virtual size_t VertCount() const {
		return Vertices.size() - 1;
	}

	virtual IAdjIterator* Iter(int v) const {
		return new TAdjIterator(this, v);
	}
};

// find simple path between two vertices
// usage of Depth-First Search
class TSimplePathFinder {
private:
	const IUndirectedGraph& Graph;
	vector<bool> Visited;

public:
	TSimplePathFinder(const IUndirectedGraph& graph)
		: Graph(graph)
		, Visited(graph.VertCount(), false)
	{}

	bool Exists(int first, int second) {
		if (first == second) {
			return true;
		}
		Visited[first] = true;
		auto_ptr<IAdjIterator> iter(Graph.Iter(first));
		for (; !iter->End(); iter->Next()) {
			int vert = **iter;
			if (!Visited[vert]) {
				if (Exists(vert, second)) {
					return true;
				}
			}
		}
		return false;
	}

	void Clear() {
		Visited.assign(Visited.size(), false);
	}
};

// coloring graph into two colors
// usage of Depth-First Search
class TTwoColorer {
private:
	const IUndirectedGraph& Graph;
	bool IsBipartite;
	vector<int> ColorMap;

	bool DepthFirstSearch(int v, int color) {
		ColorMap[v] = (color + 1) % 2;
		auto_ptr<IAdjIterator> iter(Graph.Iter(v));
		for (; !iter->End(); iter->Next()) {
			int adj = **iter;
			if (ColorMap[adj] == -1) {
				if (!DepthFirstSearch(adj, ColorMap[v])) {
					return false;
				}
			} else if (ColorMap[adj] != color) {
				return false;
			}
		}
		return true;
	}

public:
	TTwoColorer(const IUndirectedGraph& graph)
		: Graph(graph)
		, IsBipartite(true)
		, ColorMap(graph.VertCount(), -1)
	{
		for (int i = 0; i < (int)ColorMap.size(); ++i) {
			if (ColorMap[i] == -1) {
				if (!DepthFirstSearch(i, 0)) {
					IsBipartite = false;
					return;
				}
			}
		}
	}

	bool GetIsBipartite() const {
		return IsBipartite;
	}

	const vector<int>& GetColorMap() const {
		return ColorMap;
	}
};

int main() {
	//unique_ptr<IUndirectedGraph> graph(new TEdgesVectorUndirectedGraph);
	//unique_ptr<IUndirectedGraph> graph(new TMatrixUndirectedGraph);
	unique_ptr<IUndirectedGraph> graph(new TAdjListUndirectedGraph);

	graph->InsertEdge(1,2);
	graph->InsertEdge(2,5);
	graph->InsertEdge(2,4);
	graph->InsertEdge(3,7);
	graph->InsertEdge(7,1);
	graph->InsertEdge(4,1);
	graph->InsertEdge(6,8);
	cout << "E = " << graph->EdgesCount() << endl;
	cout << "V = " << graph->VertCount() << endl;

	TSimplePathFinder finder(*graph);
	cout << "5->7: " << finder.Exists(5, 7) << endl;
	// true

	finder.Clear();
	cout << "3->8: " << finder.Exists(3, 8) << endl;
	// false

	TTwoColorer colorer1(*graph);
	cout << "is bipartite: " << colorer1.GetIsBipartite() << endl;
	// false

	graph->DeleteEdge(1, 4);
	TTwoColorer colorer2(*graph);
	cout << "is bipartite: " << colorer2.GetIsBipartite() << endl;
	// true

	return 0;
}
