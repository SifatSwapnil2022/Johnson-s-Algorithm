#include <bits/stdc++.h>
using namespace std;

#define INF 9999

// Function to find the vertex with minimum distance
int minDistance(vector<int> dist, vector<bool> visited) {
  int minimum = INF, minVertex = 0;
  for (int vertex = 0; vertex < dist.size(); vertex++) {
    if (minimum > dist[vertex] && visited[vertex] == false) {
      minimum = dist[vertex];
      minVertex = vertex;
    }
  }
  return minVertex;
}

// Dijkstra Algorithm for Modified Graph
void Dijkstra(vector<vector<int>> graph, vector<vector<int>> modifiedGraph, int src) {
  int num_vertices = graph.size();
  vector<bool> sptSet(num_vertices, false);
  vector<int> dist(num_vertices, INF);

  dist[src] = 0;

  for (int count = 0; count < num_vertices; count++) {
    int curVertex = minDistance(dist, sptSet);
    sptSet[curVertex] = true;

    for (int vertex = 0; vertex < num_vertices; vertex++) {
      if (!sptSet[vertex] && dist[vertex] > (dist[curVertex] + modifiedGraph[curVertex][vertex]) && graph[curVertex][vertex] != 0) {
        dist[vertex] = dist[curVertex] + modifiedGraph[curVertex][vertex];
      }
    }
  }

  // Print the Shortest distance from the source
  for (int vertex = 0; vertex < num_vertices; vertex++) {
    cout << "Vertex " << vertex << ": " << dist[vertex] << endl;
  }
}

// Function to calculate shortest distances from source to all other vertices using Bellman-Ford algorithm
vector<int> BellmanFord(vector<vector<int>> edges, vector<vector<int>> graph, int num_vertices) {
  vector<int> dist(num_vertices + 1, INF); // Initialize with INF + 1 to handle overflow
  dist[num_vertices] = 0;

  for (int i = 0; i < num_vertices; i++) {
    // Add edge from added vertex to all others (similar to tuple approach)
    edges.push_back({num_vertices, i, 0});
  }

  for (int i = 1; i <= num_vertices; i++) { // Relax edges `num_vertices` times to detect negative cycles
    for (int j = 0; j < edges.size(); j++) {
      int src = edges[j][0];
      int des = edges[j][1];
      int weight = edges[j][2];
      if (dist[src] != INF && dist[src] + weight < dist[des]) {
        // If relaxation happens even after `num_vertices` iterations, there's a negative cycle
        if (i == num_vertices) {
          cout << "Negative edge cycle detected. Terminating..." << endl;
          exit(1); // Terminate execution upon negative cycle detection
        }
        dist[des] = dist[src] + weight;
      }
    }
  }

  // Don't return the value for the source added
  return vector<int>(dist.begin(), dist.begin() + num_vertices);
}

// Function to implement Johnson Algorithm
void JohnsonAlgorithm(vector<vector<int>> graph) {
  vector<vector<int>> edges;

  // Create a list of edges for Bellman-Ford Algorithm
  for (int i = 0; i < graph.size(); i++) {
    for (int j = 0; j < graph[i].size(); j++) {
      if (graph[i][j] != 0) {
        edges.push_back({i, j, graph[i][j]});
      }
    }
  }

  // Weights used to modify the original weights
  vector<int> modifyWeights = BellmanFord(edges, graph, graph.size());

  vector<vector<int>> modifiedGraph(graph.size(), vector<int>(graph.size(), 0));
for (int i = 0; i < graph.size(); i++) {
    for (int j = 0; j < graph[i].size(); j++) {
      if (graph[i][j] != 0) {
        modifiedGraph[i][j] = graph[i][j] + modifyWeights[i] - modifyWeights[j];
      }
    }
  }

  cout << "Modified Graph: \n";
   for (int i = 0; i < modifiedGraph.size(); i++) {
    for (int j = 0; j < modifiedGraph[i].size(); j++) {
      cout << modifiedGraph[i][j] << " ";
    }
    cout << endl;
  }

  // Run Dijkstra for every vertex as source one by one
  for (int src = 0; src < graph.size(); src++) {
    cout << "\nShortest Distance with vertex " << src << " as the source:\n";
    Dijkstra(graph, modifiedGraph, src);
  }
}

// Driver Code
int main() {
        cout<<"\t\t\t\t-----  Welcome to the Johnson Algorithm  -----                   ";

  int num_vertices, num_edges;
  cout << "\n\n\n\nEnter the number of vertices: ";
  cin >> num_vertices;
  cout << "Enter the number of edges: ";
  cin >> num_edges;

  vector<vector<int>> graph(num_vertices, vector<int>(num_vertices, 0));
 cout << "Enter the edges (source  destination  weight) one by one:\n";

  for (int i = 0; i < num_edges; i++) {
    int src, des, weight;
    cin >> src >> des >> weight;
    graph[src][des] = weight;
  }

  JohnsonAlgorithm(graph);
  return 0;
}
