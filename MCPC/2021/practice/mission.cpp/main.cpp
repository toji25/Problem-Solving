#include <iostream>
#include <bits/stdc++.h>

#define MOD 1'000'000'007

using namespace std;

typedef  vector<vector<bool>> vvb;
typedef  vector<vector<int>> vvi;


int solve(int n , int m ,int k, int l, vvb &kittens, vvb &buttons){
    vvi  dp(n, vector<int>(m, 0));
    vvi  raw(n, vector<int>(m, 0));

    raw[0][0] = 1;

    for( int i = 0; i < n ; i++){
        for( int j = 0; j < m ; j++){

            if(kittens[i][j]){
                raw[i][j] = 0;
                dp[i][j] = 0;
                continue;
            }

            if (i != 0) raw[i][j] = (raw[i][j] + raw[i-1][j]) % MOD;
            if (j != 0) raw[i][j] = (raw[i][j] + raw[i][j - 1]) % MOD;

            // if we encounter a button, then all paths leading to this cell are valid paths
            // also check if no buttons are in the field
            if(buttons[i][j] || (l == 0)){
                dp[i][j] = raw[i][j];
            } else {
                if (i != 0) dp[i][j] = (dp[i][j] + dp[i-1][j]) % MOD;
                if (j != 0) dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
            }
        }
    }
    return dp[n-1][m-1];
}
int main() {
    int t, n, m, k, l, i, j;

    cin >> t;
    while (t--) {
        cin >> n >> m >> k >> l;
        vvb kittens(n, vector<bool>(m, false));
        vvb buttons(n, vector<bool>(m, false));

        for (int _ = 0; _ < k; _++) {
            cin >> i >> j;
            kittens[i - 1][j - 1] = true;
        }

        for (int _ = 0; _ < l; _++) {
            cin >> i >> j;
            buttons[i - 1][j - 1] = true;
        }

        cout << solve(n, m, k, l, kittens, buttons);

    }
}


