#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
#include <vector>
#include <set>
#include <stack>

using namespace std;

template<typename T>
class Graph {
public:
    unordered_map<T, list<T> > adj;

    void addEdge(T u, T v, bool direction) {
        //direction = 0 - undirected
        //direction = 1 -> directed
        //create an edge from u to v
        adj[u].push_back(v);//u->[v]
        if (!direction) {
            //0->1
            //1->0
            adj[v].push_back(u);// v->[u]
        }
    }

    //1->[0,1,2]
    void printAdjList() {
        for (auto i: adj) {
            cout << i.first << "->";//index
            for (auto j: i.second) {
                cout << j << ", ";//lists
            }
            cout << endl;
        }
    }
};

//neighbours
vector<vector<int> > printAdjacency(int n, int m, vector<vector<int> > &edges) {
    vector<int> ans[n];
    //ans array will store all the adjacent nodes
    for (int i = 0; i < m; i++) {
        int u = edges[i][0];//u
        int v = edges[i][1];//v

        ans[u].push_back(v);//u->v
        ans[v].push_back(u);//v->u
    }

    vector<vector<int> > adj(n);
    for (int i = 0; i < n; i++) {
        adj[i].push_back(i);
        //neighbours
        for (int j = 0; j < ans[i].size(); j++) {
            adj[i].push_back(ans[i][j]);
        }
    }
    return adj;
}

//bfs
void prepareAdjList(unordered_map<int, set<int> > &adjList, vector<pair<int, int> > &edges) {
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].first;
        int v = edges[i].second;

        adjList[u].insert(v);
        adjList[v].insert(u);
    }
}

void bfs(unordered_map<int, set<int> > adjList, unordered_map<int, bool> visited, vector<int> ans, int node) {
    queue<int> q;
    q.push(node);
    visited[node] = true;

    while (!q.empty()) {
        int frontNode = q.front();
        q.pop();
        //store frontNode into ans
        ans.push_back(frontNode);
        //traverse all neighbours of frontend
        for (auto i: adjList[frontNode]) {
            if (!visited[i]) {//not visited
                q.push(i);
                visited[i] = 1;
            }
        }
    }
}

vector<int> bfsTraversal(int vertex, vector<pair<int, int> > &edges) {
    unordered_map<int, set<int> > adjList;
    vector<int> ans;
    unordered_map<int, bool> visited;

    prepareAdjList(adjList, edges);
    //traverse all components of a graph
    for (int i = 0; i < vertex; i++) {
        if (!visited[i]) {
            bfs(adjList, visited, ans, i);
        }
    }
}

//DFS; TC:SP: linear
void dfs(int node, unordered_map<int, bool> &visited, unordered_map<int, list<int> > &adj, vector<int> &component) {
    //ans store
    component.push_back(node);//0
    //mark visited
    visited[node] = true;// node, true
    //har connected ke liye recursive call
    for (auto i: adj[node]) {
        if (!visited[i]) {
            dfs(i, visited, adj, component);
        }
    }
}

vector<vector<int> > depthFirstSearch(int V, int E, vector<vector<int> > &edges) {
    unordered_map<int, list<int> > adj;// 1-> {}
    //prepare adjlist
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<vector<int> > ans;
    unordered_map<int, bool> visited;// 1, true
    //for all nodes call dfs if not visited
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {//not visited
            vector<int> component;
            dfs(i, visited, adj, component);
            ans.push_back(component);
        }
    }
    return ans;
}

//cycle detection in un-directed; node visited true, but not parent
bool isCyclicBFS(int src, unordered_map<int, bool> &visited, unordered_map<int, list<int> > &adj) {
    unordered_map<int, int> parent;
    parent[src] = -1;//1st node with no parent
    visited[src] = true;
    queue<int> q;
    q.push(src);

    while (!q.empty()) {
        int frontNode = q.front();
        q.pop();

        for (auto neighbour: adj[frontNode]) {
            if (visited[neighbour] == true && neighbour != parent[frontNode]) {
                return true;
            } else if (!visited[neighbour]) {
                q.push(neighbour);
                visited[neighbour] = true;
                parent[neighbour] = frontNode;
            }
        }
    }
    return false;
}

bool isCyclicDFS(int node, int parent, unordered_map<int, bool> &visited,
                 unordered_map<int, list<int> > &adj) {
    visited[node] = true;//visited = true

    for (auto neighbour: adj[node]) {
        if (!visited[neighbour]) {//not visited
            bool cycleDetected = isCyclicDFS(neighbour, node, visited, adj);
            if (cycleDetected) {
                return true;
            }
        } else if (neighbour != parent) {
            //cycle present
            return true;
        }
    }
    return false;
}

string cycleDetection(vector<vector<int> > &edges, int n, int m) {
    //create adj list
    unordered_map<int, list<int> > adj;
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

//    to handle disconnect components
    unordered_map<int, bool> visited;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
//            bool ans = isCyclicBFS(i, visited, adj);
//          parent -1
            bool ans = isCyclicDFS(i, -1, visited, adj);
            if (ans == 1) { return "Yes"; }
        }
    }
    return "No";
}

//cycle detection in directed graph; TC:O(nodes+edges), SP: linear
bool isDirCycleDFS(int node, unordered_map<int, bool> &visited, unordered_map<int, bool> &dfsVisited,
                   unordered_map<int, list<int> > &adj) {
    visited[node] = true;
    dfsVisited[node] = true;//func visited

    for (auto neighbour: adj[node]) {
        if (!visited[neighbour]) {
            bool cycleDetected = isDirCycleDFS(neighbour, visited, dfsVisited, adj);
            if (cycleDetected) {
                return true;
            }
        } else if (dfsVisited[neighbour]) {
            //cycle
            return true;
        }
    }
    dfsVisited[node] = false;//backtrack
    return false;
}

int detectCycleInDirectedGraph(int n, vector<pair<int, int> > &edges) {
//    create adj list
    unordered_map<int, list<int> > adj;
    unordered_map<int, bool> visited;
    unordered_map<int, bool> dfsVisited;
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].first;
        int v = edges[i].second;

        adj[u].push_back(v);
    }
    //call for dfs for all components
    for (int i = 1; i < n; i++) {
        if (!visited[i]) {
            bool cycleDetected = isDirCycleDFS(i, visited, dfsVisited, adj);
            if (cycleDetected) {
                return true;
            }
        }
    }
    return false;
}

//topological sort, DAG; TC: O(n+e), SP: linear
void topoSortDFS(int node, vector<int> &visited, stack<int> &s, unordered_map<int, list<int> > &adj) {
    visited[node] = true;

    for (auto neighbour: adj[node]) {
        if (!visited[neighbour]) {
            topoSortDFS(neighbour, visited, s, adj);
        }
    }
    //visited = true
    s.push(node);//LIFO
}

vector<int> topologicalSort(vector<vector<int> > &edges, int v, int e) {
    //v=no. of vertex
    unordered_map<int, list<int> > adj;
    vector<int> visited(v);
    stack<int> s;
    vector<int> ans;

    //create list
    for (int i = 0; i < e; i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        adj[u].push_back(v);
    }
    //call dfs topological sort for all comps
    for (int i = 0; i < v; i++) {
        if (!visited[i]) {
            topoSortDFS(i, visited, s, adj);
        }
    }
    while (!s.empty()) {
        ans.push_back(s.top());
        s.pop();
    }
    return ans;
}

//kahn's algorithm; bfs
vector<int> topologicalSortKahnAlgo(vector<vector<int> > &edges, int v, int e) {
    unordered_map<int, list<int> > adj;
    //create adj
    for (int i = 0; i < e; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u].push_back(v);
    }

    //find all in-degrees
    vector<int> indegree(v);
    for (auto i: adj) {//taking each index
        for (auto j: i.second) {//increasing indegree count
            indegree[j]++;//increasing for index []
        }
    }

    //0 indegree walo ko push kardo
    queue<int> q;
    for (int i = 0; i < v; i++) {
        if (indegree[i] == 0) {
            q.push(i);//pushing in queue in indegree = 0
        }
    }

    //do bfs
    vector<int> ans;
    while (!q.empty()) {
        int front = q.front();
        q.pop();

        //ans store
        ans.push_back(front);

        //neighbour indegree update
        for (auto neighbour: adj[front]) {
            indegree[neighbour]--;//decreasing indegree for index
            if (indegree[neighbour] == 0) {
                q.push(neighbour);//pushing if 0
            }
        }
    }
    return ans;
}

//using bfs; TC,SP: O(n+e)
int detectCycleInDirectedGraphBFS(int n, vector<pair<int, int> > &edges) {
    //using Kahn's Algo
    unordered_map<int, list<int> > adj;
    //create adj
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].first - 1;//0 se for me start karne ke liye
        int v = edges[i].second - 1;
        adj[u].push_back(v);
    }

    //find all in-degrees
    vector<int> indegree(n);
    for (auto i: adj) {//taking each index
        for (auto j: i.second) {//increasing indegree count
            indegree[j]++;//increasing for index []
        }
    }

    //0 indegree walo ko push kardo
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            q.push(i);//pushing in queue in indegree = 0
        }
    }

    //do bfs
    int count = 0;
    while (!q.empty()) {
        int front = q.front();
        q.pop();
        //inc count
        count++;

        //neighbour indegree update
        for (auto neighbour: adj[front]) {
            indegree[neighbour]--;//decreasing indegree for index
            if (indegree[neighbour] == 0) {
                q.push(neighbour);//pushing if 0
            }
        }
    }

    if (count == n) {//valid topological sort
        return false;//cycle is not present
    } else {//invalid topological sort
        return true;
    }
}

//shortest distance
vector<int> shortestPath(vector<pair<int, int> > edges, int n, int m, int s, int t) {
    //s=src node
    //create adj list
    unordered_map<int, list<int> > adj;
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].first;
        int v = edges[i].second;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    //do bfs
    unordered_map<int, bool> visited;
    unordered_map<int, int> parent;
    queue<int> q;
    q.push(s);
    parent[s] = -1; // root node parent = -1
    visited[s] = true;

    while (!q.empty()) {
        int front = q.front();
        q.pop();
        for (auto i: adj[front]) {//0->[1,2]; i = 1, 2
            if (!visited[i]) {//If not visited
                visited[i] = true;
                parent[i] = front;
                q.push(i);
            }
        }
    }
    //prepare the shortest path
    vector<int> ans;
    int currentNode = t;//curr node
    ans.push_back(t);

    while (currentNode != s) {//curr node != source node; last node
        currentNode = parent[currentNode];
        ans.push_back(currentNode);
    }
    reverse(ans.begin(), ans.end());//reversing
    return ans;
}

//shortest path is DAG; TS,SP: O(n+e)
void addEdge(unordered_map<int, list<pair<int, int> > > &adj, int u, int v, int weight) {
    pair<int, int> p = make_pair(v, weight);//vertices, weight
    adj[u].push_back(p);
}

void dfs(int node, unordered_map<int, bool> &visited, stack<int> &s, unordered_map<int, list<pair<int, int> > > &adj) {
    visited[node] = true;
    for (auto neighbour: adj[node]) {
        if (!visited[neighbour.first]) {
            dfs(neighbour.first, visited, s, adj);
        }
    }
    s.push(node);

}

void getShortestPath(int src, vector<int> &dist, stack<int> &s, unordered_map<int, list<pair<int, int> > > &adj) {
    dist[src] = 0;//root ka dist =0

    while (!s.empty()) {//stack se nikala aur check kiya
        int top = s.top();
        s.pop();
        if (dist[top] != INT_MAX) {//if infi
            for (auto i: adj[top]) {
                if (dist[top] + i.second < dist[i.first]) {
                    dist[i.first] = dist[top] + i.second;//dist update
                }
            }
        }
    }
}

void shortestPathDAG() {
    unordered_map<int, list<pair<int, int> > > adj;

    for (auto i: adj) {
        cout << i.first << " ->";
        for (auto j: i.second) {
            cout << "(" << j.first << "," << j.second << "), ";
        }
        cout << endl;
    }
    //topological sort
    unordered_map<int, bool> visited;
    stack<int> s;
    int n = 6;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, visited, s, adj);
        }
    }
    int src = 1;
    vector<int> dist(n);//distance array
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;//for all value=infinity
    }
    getShortestPath(src, dist, s, adj);
    for (int i = 0; i < dist.size(); i++) {
        cout << dist[i] << " ";
    }
    cout << endl;
}

//Dijkstra's Algorithm
vector<int> dijkstra(vector<vector<int> > &vec, int vertices, int edges, int source) {
    unordered_map<int, list<pair<int, int> > > adj;
    for (int i = 0; i < edges; i++) {
        int u = vec[i][0]; //
        int v = vec[i][1];
        int w = vec[i][2]; // weight

        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }

    //create distance array with infinite value initially
    vector<int> dist(vertices);
    for (int i = 0; i < vertices; i++) {
        dist[i] = INT_MAX;//setting all to infinity
    }

    //creation of set
    set<pair<int, int> > st;//node Dist, node; st.top will give smallest
    //initialise distance and set with source node
    dist[source] = 0;
    st.insert(make_pair(0, source));//0dist, node

    while (!st.empty()) {
        //fetch top record
        auto top = *(st.begin());//top rec from set

        int nodeDist = top.first;//dist
        int topNode = top.second;//node

        //remove top rec
        st.erase(st.begin());

        //traverse on neighbours
        for (auto neighbour: adj[topNode]) {
            // d+node < dist(before)
            if (nodeDist + neighbour.second < dist[neighbour.first]) {
                auto record = st.find(make_pair(dist[neighbour.first], neighbour.first));

                //if rec found then erase it
                if (record != st.end()) {
                    st.erase(record);
                }
                //distance update
                dist[neighbour.first] = nodeDist + neighbour.second;
                //record push in set
                st.insert(make_pair(dist[neighbour.first], neighbour.first));
            }
        }
    }
    return dist;
}

vector<pair<pair<int, int>, int> > calculatePrimsMST(int n, int m, vector<pair<pair<int, int>, int> > &g) {
    //adj
    unordered_map<int, list<pair<int, int> > > adj;
    for (int i = 0; i < g.size(); i++) {
        int u = g[i].first.first;
        int v = g[i].first.second;
        int w = g[i].second;

        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }

    vector<int> key(n + 1);//1 node = 1 index
    vector<bool> mst(n + 1);
    vector<int> parent(n + 1);
    //initialising them
    for (int i = 0; i <= n; i++) {
        key[i] = INT_MAX;//infi
        parent[i] = -1;
        mst[i] = false;
    }
    //algo
    key[1] = 0;//parent
    parent[1] = -1;//root node has no parent

    for (int i = 1; i < n; i++) {
        int mini = INT_MAX;
        int u;
        //find the min wali node
        for (int v = 1; j <= n; v++) {
            if (mst[v] == false && key[v] < mini) {
                u = v;
                mini = key[v];
            }
        }
        //mark min node as true
        mst[u] = true;
        //check adjacent nodes
        for (auto it: adj[u]) {
            int v = it.first;
            int w = it.second;
            if (mst[v] == false && w < key[v]) {
                parent[v] = u;
                key[v] = w;
            }
        }
    }
    vector<pair<pair<int, int>, int> > result;



}

//Disjoint set
//Kruskal's Algorithm

int main() {
    int n;
    cout << "enter number of nodes" << endl;
    cin >> n;
    int m;
    cout << "enter the no. of edges" << endl;
    cin >> m;

    Graph<int> g;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        //undirected graph
        g.addEdge(u, v, false);
    }
    //print graph
    g.printAdjList();
    return 0;
}