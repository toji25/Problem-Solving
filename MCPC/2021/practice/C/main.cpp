#include <iostream>
#include <bits/stdc++.h>

#define MOD 1'000'000'007

using namespace std;

typedef  vector<vector<bool>> vvb;
typedef  vector<vector<int>> vvi;

typedef vector<bool> vb;
typedef vector<int> vi;

// This function calculates the number of paths in a matrix avoiding kittens and considering buttons.
int solve(int n, int m, int k, int l, vvb &kittens, vvb &buttons) {
    // Create two-dimensional arrays to store the number of paths to each cell in the matrix.
    vvi raw(n, vi(m, 0)); // this stores the number of possible paths from cell (0, 0) to cell (i, j) (buttons_pressed >= 0)
    vvi dp(n, vi(m, 0)); // this stores the number of valid paths from cell (0, 0) to cell (i, j) (buttons_pressed >= 1)

    // the number of paths from (0, 0) to (0, 0) is 1
    raw[0][0] = 1;

    // Loop over the matrix, starting from the top-left corner.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            // If the cell contains a kitten, the number of paths to that cell is 0.
            if (kittens[i][j]) {
                raw[i][j] = 0;
                continue;
            }

            // Otherwise, the number of paths to the cell is the sum of the number of paths to the cell from the top
            // and the number of paths to the cell from the left.
            if (i != 0) raw[i][j] = (raw[i][j] + raw[i - 1][j]) % MOD;
            if (j != 0) raw[i][j] = (raw[i][j] + raw[i][j - 1]) % MOD;

            // If the cell contains a button, then all paths leading to this cell are valid paths
            // Also check if no buttons are in the field (then are paths are valid)
            if (buttons[i][j] || (l == 0)) {
                dp[i][j] = raw[i][j];
                continue;
            }

            // If the cell does not contain a button, then the number of valid paths to the cell 
            // is the sum of the number of valid paths to the cell from the top
            // and the number of valid paths to the cell from the left.
            if (i != 0) dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
            if (j != 0) dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
            
        }
    }

    // Return the number of valid paths to the bottom-right corner of the matrix.
    return dp[n - 1][m - 1];
}

int main() {
    int t, n, m, k, l, i, j;

    cin >> t;
    while (t--) {
        cin >> n >> m >> k >> l;
        vvb kittens(n, vb(m, false));
        vvb buttons(n, vb(m, false));

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
