#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define Up(x,y) (x+1)/y
#define TwoPower(n) (1<<n)
#define even(n) !(n&1)
#define IsOn(n,i) ((n >> i) & 1)
#define Flib(n,i) (n&(~(1<<i)))
#define endl '\n'
#define MAZEN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

const int N = 8;     // number of nodes.

vector<vector<int>>AdjList = {          // take it from input.
    {1,2,3},        // 0
    {4,2,0},        // 1
    {0,1,8},        // 2
    {0,5,6},        // 3
    {7,1},          // 4 
    {3,8},          // 5
    {3},            // 6
    {4,8},          // 7
    {2,7,5}         // 8    
};

// Get vector<int> lengths of shortest paths from s to each node in graph
vector<int> BFS_ShortestPaths (int s){      
    vector<int>shortestPahts(N,0);
    queue<pair<int,int>> queue;
    map<int,bool>vis;
    queue.push({s,0});
    vis[s] = true;

    while (!queue.empty())
    {
        int node = queue.front().first;     
        int depth = queue.front().second;
        queue.pop();
        shortestPahts[node] = depth;
        
        for(int ch : AdjList[node]){
            if(!vis[ch]){
                queue.push({ch,depth+1});
                vis[ch] = true;
            }
        }
    }
    return shortestPahts;
}

vector<int> BFSPath (int s,int d){
    vector<int>parent(N);
    queue<int> queue;
    map<int,bool>vis;

    queue.push(s);
    vis[s] = true;
    parent[s] = -1;     // has no parent

    bool reach = false;

    while(!queue.empty() && !reach)
    {
        int node = queue.front();       queue.pop();
        for(int ch : AdjList[node]){
            if(!vis[ch]){
                vis[ch] = true;
                parent[ch] = node;

                if(ch == d){        // founded
                    reach = true;
                    break;
                }

                queue.push(ch);
            }
        }
    }
    
    if(!reach) 
        return vector<int>();        // return empty vector
    
    int current = d;
    vector<int>path;
    path.push_back(d);
    while (parent[current] != -1)
    {
        path.push_back(parent[current]);
        current = parent[current];
    }

    reverse(path.begin(),path.end());
    return path;
}

bool isBipartite(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int>colors(n,-1);
    queue<int>q;

    for(int i=0;i<n;++i){
        if(colors[i] != -1) continue;
        colors[i] = 0;
        q.push(i);
        while (!q.empty())
        {
            int node = q.front();   q.pop();
            for(int child : graph[node]){
                if (colors[child] == -1){
                    q.push(child);
                    colors[child] = !colors[node];
                }
                else if(colors[child] == colors[node]){
                    return false;
                }
            }
        }
    }

    return true;
}

/*  Doc
    Bfs Applications

    [1] Traversing.
    [2] Shortest Path.
    [3] if there is a path between node A to node B.
            =>  1 to 1
            => 1 to many    from A to [C , D , E]
            => many to many  from [A , B , C] to [M , N , Z]        => add source nodes intially into queue. 
    [4] determine Bipartite graph. 
    
    [5] Edge splite trick

    we know bfs determine shortest path if and only if graph is unwaighted graph(or with equal costs).
    
    so if the given graph is waighted graph but max cost is 5(or any small number)

    path A =(3)> D

    we can simplify to 3 edges with cost 1      ...

    A   =(1)>   B   =(1)>   C   =(1)>   D 

 */

int main(){

    
    
    auto paths = BFS_ShortestPaths(0);

    for(int i = 0;i <= N;++i){
        cout<<"Shortest Path From [0] => ["<<i<<"] Is = "<<paths[i]<<'\n';
    }

    cout<<"\n --------------------------------------------------------------------- \n";


    auto path = BFSPath(0,7);
    for(auto n : path) cout<<n<<" -> ";


    cout<<"\n --------------------------------------------------------------------- \n";



}