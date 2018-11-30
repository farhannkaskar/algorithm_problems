
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Edge {
public:
  const int from;
  const int to;
  const int cost;

  Edge(const int from_, const int to_, const int cost_)
    : from(from_),
      to(to_),
      cost(cost_) {}
};

class Graph {
public:
  const int V;
  vector<vector<Edge> > allEdges;

  Graph(const int V_)
   : V(V_) {
     allEdges.resize(V);
   }

   void addEdge(const Edge& edge) {
     const bool isEdgeValid = edge.from >= 0 && edge.from < V &&
                              edge.to >= 0 && edge.to < V &&
                              edge.cost >= 0;
     if (!isEdgeValid) return;

     allEdges[edge.from].push_back(edge);
   }

   int GetMinDistanceVertex(const vector<int>& distance, const vector<bool>& visited) {
    if (distance.empty() || visited.empty() || distance.size() != visited.size()) return INT_MAX;

    int minDistance = INT_MAX;
    int minDistanceVertex = -1;

    for(int index = 0; index < distance.size(); ++index) {
      if (!visited[index]) {
        if (distance[index] < minDistance) {
          minDistance = distance[index];
          minDistanceVertex = index;
        }
      }
    }

    return minDistanceVertex;
   }

   void findShortestPath(const int source, vector<int>* distanceToAllNodePtr, vector<int>* backtracePtr) {
     const bool isInputValid = source >= 0 && source < V && distanceToAllNodePtr != NULL;

     if (!isInputValid) return;

     vector<int> distance(V, INT_MAX);
     vector<bool> visited(V, false);
     backtracePtr->resize(V);

     distance[source] = 0;
     findShortestPathUtil(source, distance, visited, *backtracePtr);
     distanceToAllNodePtr->swap(distance);
   }

   void findShortestPathUtil(const int source, vector<int>& distance, vector<bool>& visited, vector<int>& backtrace) {
      const bool isInputValid = source >= 0 && source < V && !distance.empty() && !visited.empty() && distance.size() == visited.size();
      if (!isInputValid) return;

       visited[source] = true;
       const vector<Edge>& connectedEdges = allEdges[source];

       if (connectedEdges.empty()) return;

       for (const Edge& edge : connectedEdges) {
         const int adjacentVertex = edge.to;
         const int cost = distance[source] + edge.cost;
         if (cost < distance[adjacentVertex]) {
           distance[adjacentVertex] = cost;
           backtrace[adjacentVertex] = source;
         }
       }

       const int vertexWithMinDistanceToSource = GetMinDistanceVertex(distance, visited);
       findShortestPathUtil(vertexWithMinDistanceToSource, distance, visited, backtrace);
   }
};

int main(int argc, char** argv) {
  Graph graph(6);
  graph.addEdge(Edge(0, 1, 5));
  graph.addEdge(Edge(0, 2, 2));
  graph.addEdge(Edge(2, 1, 8));
  graph.addEdge(Edge(2, 4, 7));
  graph.addEdge(Edge(1, 3, 4));
  graph.addEdge(Edge(1, 4, 2));
  graph.addEdge(Edge(3, 4, 6));
  graph.addEdge(Edge(3, 5, 3));
  graph.addEdge(Edge(4, 5, 1));

  vector<int> distance;
  vector<int> backtrace;
  graph.findShortestPath(0, &distance, &backtrace);

  for(int index = 0; index < 6; ++index) {
    cout << index << " - " << distance[index] << " - " << backtrace[index] << endl;
  }
}

//
// TIME COMPLEXITY OF ABOVE CODE: V^2 + E
// TIME COMPLEXITY OF ABOVE CODE: 2V = O(V)
//
// EXPLANATION:
// ============
// We are using BFS to traverse over all the vertices. Time complexity of BFS = V + E. (V or E which ever is higher. For more info: https://www.quora.com/What-is-the-time-complexity-of-Breadth-First-Search-Traversal-of-a-graph)
// Now above Dijkstra's implementation uses BFS but to figure out the next minumun distance node we are traversing over all graph nodes.
// This makes the time complexity of above code as V^2 + E
// V^2 component can be dropped to "V logV" by using binary heap Tree.
//
// Either we can create our own binary heap because we have to decrease the key's value every time or we can put the min value node again in the existing
// standard minHeap (ex: STL) this  way
//   - The new min is always on the top of minHeap even though its duplicate
//   - Even if we pop() the duplicate node we will never update the distance because min has already taken care of it.
//
// If we use minHeap then this will drop to log V
//
