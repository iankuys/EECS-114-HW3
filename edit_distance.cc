#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void print_head()
{
  cout.setf(ios::left);
  cout << setw(16) << "Operation" 
       << setw(32) << "z" 
       << setw(8) << "Cost" 
       << setw(8) << "Total" << endl;

  for (int i=0; i<64; ++i) cout << "-";
  cout << endl;
}


int findMin(int a, int b, int c) {
    return min(a, min(b, c));
}


int computeEditDistance(const string& x, const string& y) {
    int m = x.length();
    int n = y.length();

    // Create a 2D matrix to store the edit distances
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    // Initialize the first row and first column
    for (int i = 0; i <= m; ++i) {
        dp[i][0] = i * 2;  // delete operation cost
    }
    for (int j = 0; j <= n; ++j) {
        dp[0][j] = j * 3;  // insert operation cost
    }

    // Compute the edit distance
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (x[i - 1] == y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];  // no operation required
            } else {
                int replaceCost = (i == dp.size() - 1) ? 0 : 4 + dp[i - 1][j - 1];  // replace operation cost
                int deleteCost = (i == dp.size() - 1) ? 0 : 2 + dp[i - 1][j];      // delete operation cost
                int insertCost = 3 + dp[i][j - 1];                                // insert operation cost
                dp[i][j] = findMin(replaceCost, deleteCost, insertCost);
            }
        }
    }

    return dp[m][n];  // minimum edit distance
}


int main()
{
    string x = "algorithm";
    string y = "analysis";

    int editDistance = computeEditDistance(x, y);

    cout << "Edit Distance: " << editDistance << endl;

    return 0;
}
