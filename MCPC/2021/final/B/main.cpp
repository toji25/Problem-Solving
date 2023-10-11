//
// Created by user on 11/10/2023.
//

#include <iostream>
#include<vector>
#include<stack>

#define MOD 1'000'000'007
#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)


using namespace std;


void sccUtil(int u,
             vector<vector<int>> &graph,
             vector<int> &score,
             int &result,
             int &ways,
             vector<int> &disc,
             vector<int> &ancestor,
             vector<bool> &inStack,
             stack<int> &stack,
             int &time
             ) {

    disc[u] = time;
    ancestor[u] = time;
    time++;

    stack.push(u);
    inStack[u] = true;

    for (int v: graph[u]){
        if (disc[v] == -1) {
            sccUtil(v, graph, score, result, ways, disc, ancestor, inStack, stack, time);
            ancestor[u] = min(ancestor[u], ancestor[v]);
        } else if (inStack[v]) {
            ancestor[u] = min(ancestor[u],disc[v]);
        }
    }

    if (disc[u] != ancestor[u]) return;

    int sum = 0, most = INT32_MIN, zeros = 0;

    int w = -1;
    while (w != u) {
        w = stack.top();
        sum += max(score[w], 0);
        most = max(most, score[w]);
        zeros += (score[w] == 0);
        stack.pop();
        inStack[w] = false;
    }

    int two = 1;
    while (zeros--) two = (two << 1) % MOD;

    result += (sum > 0 ? sum : most);

    if (most == 0){
        ways = (ways * (two - 1)) % MOD;
    } else {
        ways = (ways * two) % MOD;
    }

}


void scc(vector<vector<int>> graph, vector<int> &score, int n, int &result, int &ways) {

    vector<int> disc(n, -1);
    vector<int> ancestor(n, -1);
    vector<bool> inStack(n, false);

    stack<int> stack;

    int time = 0;

    for (int i = 0; i < n; i++){
        if (disc[i] != -1) continue;
        sccUtil(i, graph, score, result, ways, disc, ancestor, inStack, stack, time);
    }

}


pair<int, int> solve(vector<vector<int>> &graph, vector<int> &score, int n) {

    int result = 0, ways = 1;

    scc(graph, score, n, result, ways);

    return {result, ways};

}



int main(){

    int t, n, m;

    cin >> t;

    while (t--) {
        cin >> n >> m;

        vector<vector<int>> graph(n, vector<int>());
        vector<int> score(n, 0);

        for (int i = 0; i < n; i++) {
            cin >> score[i];
        }

        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            graph[u - 1].push_back(v - 1);
        }

        pair<int, int> answer = solve(graph, score, n);

        cout << answer.first << " " << answer.second << endl;
    }

}