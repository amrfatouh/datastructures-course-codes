#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;

typedef vector<int> vi;

class Graph {
  int numVertices;
  int maxVertices;
  vi vertices;
  vector<vi> edges;
  vector<bool> marked;

public:
  Graph(int maxv) {
    numVertices = 0;
    maxVertices = maxv;
    vertices = vi(maxv, -1);
    edges = vector<vi>(maxv, vi(maxv, -1));
    marked = vector<bool>(maxv, false);
  }
  ~Graph() {}

  void print() {
    //printing header row
    cout << "ver\t";
    for (int i=0; i<maxVertices; i++)
      cout << vertices[i] << "\t";
    cout << endl;
    //printing matrix
    for (int i = 0; i < maxVertices; i++) {
      //printing vertex value
      cout << vertices[i] << ":\t";
      //printing edges where the vertex is invloved
      for (int j = 0; j < maxVertices; j++)
        cout << edges[i][j] << "\t";
      cout << endl;
    }
  }

  void addVertex(int vertex) {
    for (int i = 0; i < numVertices + 1; i++) {
      edges[i][numVertices] = 0;
      edges[numVertices][i] = 0;
    }
    vertices[numVertices] = vertex;
    numVertices++;
  }

  int getIndex(int vertex) {
    if (find(vertices.begin(), vertices.end(), vertex) != vertices.end())
      return find(vertices.begin(), vertices.end(), vertex) - vertices.begin();
    return -1;
  }

  int getWeight(int from, int to) {
    int row = getIndex(from);
    int col = getIndex(to);
    return edges[row][col];
  }

  void addEdge(int from, int to, int weight) {
    int row = getIndex(from);
    int col = getIndex(to);
    edges[row][col] = weight;
  }

  void dfs(int start, int target) {
    bool found = false;
    marked = vector<bool>(maxVertices, false);
    stack<int> s;
    vi path;
    int sIndex = getIndex(start);
    s.push(vertices[sIndex]);
    marked[sIndex] = true;
    do {
      int x = s.top();
      s.pop();
      path.push_back(x);
      if (x == target) {
        found = true;
      }
      else {
        int index = getIndex(x);
        for (int i = 0; i < numVertices; i++) {
          if (edges[index][i] != 0 && !marked[i]) {
            s.push(vertices[i]);
            marked[i] = true;
          }
        }
      }
    } while (!s.empty() && !found);

    if (found)
      cout << "path found" << endl;
    else
      cout << "path not found" << endl;
    cout << "path taken: ";
    for (int i = 0; i < path.size(); i++) {
      cout << path[i] << " ";
    }
    cout << endl;

  }

  void bfs(int start, int target) {
    bool found = false;
    marked = vector<bool>(maxVertices, false);
    queue<int> q;
    vi path;
    int sIndex = getIndex(start);
    q.push(vertices[sIndex]);
    marked[sIndex] = true;
    do {
      int x = q.front();
      q.pop();
      path.push_back(x);
      if (x == target) {
        found = true;
      }
      else {
        int index = getIndex(x);
        for (int i = 0; i < numVertices; i++) {
          if (edges[index][i] != 0 && !marked[i]) {
            q.push(vertices[i]);
            marked[i] = true;
          }
        }
      }
    } while (!q.empty() && !found);

    if (found)
      cout << "path found" << endl;
    else
      cout << "path not found" << endl;
    cout << "path taken: ";
    for (int i = 0; i < path.size(); i++) {
      cout << path[i] << " ";
    }
    cout << endl;
  }
};

void testAddVertex() {
  Graph g(5);
  g.addVertex(1);
  g.addVertex(2);
  g.addVertex(3);
  g.print();
}

void testAddEdge() {
  Graph g(5);
  g.addVertex(1);
  g.addVertex(2);
  g.addVertex(3);
  g.addEdge(1, 2, 100);
  g.addEdge(1, 3, 200);
  g.addEdge(2, 1, 300);
  g.print();
}

void testGetWeight() {
  Graph g(5);
  g.addVertex(1);
  g.addVertex(2);
  g.addEdge(1, 2, 100);
  g.print();
  cout << "weight from 1 to 2: " << g.getWeight(1, 2) << endl;
}

void testDFS() {
  //doctor's example
  //graph slides - slide 30

  /*
  mapping states names to numbers:
  1- Austin
  2- Dallas
  3- Denver
  4- Chicago
  5- Washington
  6- Atlanta
  7- Houston
  */

  Graph g(7);
  //adding numbers(or states)
  g.addVertex(1);
  g.addVertex(2);
  g.addVertex(3);
  g.addVertex(4);
  g.addVertex(5);
  g.addVertex(6);
  g.addVertex(7);

  //connecting states
  g.addEdge(1, 2, 100);
  g.addEdge(1, 7, 100);
  g.addEdge(2, 1, 100);
  g.addEdge(2, 3, 100);
  g.addEdge(2, 4, 100);
  g.addEdge(3, 4, 100);
  g.addEdge(3, 6, 100);
  g.addEdge(4, 6, 100);
  g.addEdge(5, 2, 100);
  g.addEdge(5, 6, 100);
  g.addEdge(6, 5, 100);
  g.addEdge(6, 7, 100);
  g.addEdge(7, 6, 100);

  g.print();

  cout << "dfs path should be: 1,7,6,5" << endl;
  g.dfs(1, 5);
}

void testBFS() {
  //doctor's example
  //graph slides - slide 38

  /*
  mapping states names to numbers:
  1- Austin
  2- Dallas
  3- Denver
  4- Chicago
  5- Washington
  6- Atlanta
  7- Houston
  */

  Graph g(7);
  //adding numbers(or states)
  g.addVertex(1);
  g.addVertex(2);
  g.addVertex(3);
  g.addVertex(4);
  g.addVertex(5);
  g.addVertex(6);
  g.addVertex(7);

  //connecting states
  g.addEdge(1, 2, 100);
  g.addEdge(1, 7, 100);
  g.addEdge(2, 1, 100);
  g.addEdge(2, 3, 100);
  g.addEdge(2, 4, 100);
  g.addEdge(3, 4, 100);
  g.addEdge(3, 6, 100);
  g.addEdge(4, 6, 100);
  g.addEdge(5, 2, 100);
  g.addEdge(5, 6, 100);
  g.addEdge(6, 5, 100);
  g.addEdge(6, 7, 100);
  g.addEdge(7, 6, 100);

  g.print();

  cout << "bfs path from 1 to 5 should be: 1,2,7,3,4,6,5" << endl;
  g.bfs(1, 5);
}

int main() {

  testBFS();

  return 0;
}
