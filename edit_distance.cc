#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>
#include <stack>
#include <fstream>


using namespace std;

class Operation
{
public:
  string operation;
  int cost;
  int total;
  Operation(string op, int c, int ttl)
  {
    operation = op;
    cost = c;
    total = ttl;
  }
};

void print_head()
{
  cout.setf(ios::left);
  cout << setw(16) << "Operation"
       << setw(32) << "z"
       << setw(8) << "Cost"
       << setw(8) << "Total" << endl;

  for (int i = 0; i < 64; ++i)
    cout << "-";
  cout << endl;
}

// Utility function to find the minimum of three numbers
int min(int x, int y, int z)
{
  if (x <= y && x <= z)
    return x;
  if (y <= x && y <= z)
    return y;
  return z;
}

void printEditDistance(stack<Operation> op_stack, string word1, string word2)
{

  string temp = word1;
  string buffer = temp;

  string ast_pointer = "*";
  int ptr_counter = 0;

  buffer.insert(ptr_counter, ast_pointer);
  cout << setw(16) << "initial string"
       << setw(32) << buffer
       << setw(8) << 0
       << setw(8) << 0 << endl;

  while (!op_stack.empty())
  {
    Operation op = op_stack.top();
    op_stack.pop(); // get rid of the top element
    // temp.insert(ptr_counter, ast_pointer);

    if (op.operation.length() >= 11 && op.operation.substr(0, 10) == "replace by")
    {
      temp.replace(ptr_counter, 1, op.operation.substr(11, 1));
      buffer = temp;
      ptr_counter++;
      buffer.insert(ptr_counter, ast_pointer);
      cout << setw(16) << op.operation
           << setw(32) << buffer
           << setw(8) << op.cost
           << setw(8) << op.total << endl;
    }
    else if (op.operation.length() >= 7 && op.operation.substr(0, 6) == "insert")
    {
      temp.insert(ptr_counter, op.operation.substr(7, 1));
      buffer = temp;
      ptr_counter++;
      buffer.insert(ptr_counter, ast_pointer);
      cout << setw(16) << op.operation
           << setw(32) << buffer
           << setw(8) << op.cost
           << setw(8) << op.total << endl;
    }
    else if (op.operation.length() >= 6 && op.operation.substr(0, 6) == "delete")
    {
      temp = temp.substr(0, ptr_counter) + temp.substr(ptr_counter + 1, temp.length() - ptr_counter);
      buffer = temp;
      // ptr_counter++;
      buffer.insert(ptr_counter, ast_pointer);
      cout << setw(16) << op.operation
           << setw(32) << buffer
           << setw(8) << op.cost
           << setw(8) << op.total << endl;
    }
    else
    {
      buffer = temp;
      buffer.insert(ptr_counter, ast_pointer);
      cout << setw(16) << op.operation
           << setw(32) << buffer
           << setw(8) << op.cost
           << setw(8) << op.total << endl;
      ptr_counter++;
    }
  }
}

int editDistance(char *word1, char *word2, int m, int n)
{

  int dp[m + 1][n + 1];

  // Fill dp matrix from bottom up using bottom up recursion
  for (int i = 0; i <= m; i++)
  {
    for (int j = 0; j <= n; j++)
    {
      /**
       * If word1 is empty, the only option is to fill
       * the rest of the string with the remaining of word2
       * multiply by the cost of insertion which is 3
       */
      if (i == 0)
        dp[i][j] = j * 3;

      // If second string is empty, only option is to
      // remove all characters of second string
      else if (j == 0)
        dp[i][j] = i * 2;

      // If last characters are same, ignore last char
      // and recur for remaining string
      else if (word1[i - 1] == word2[j - 1])
        dp[i][j] = dp[i - 1][j - 1];

      // If the last character is different, consider
      // all possibilities and find the minimum
      else
        dp[i][j] = min(dp[i][j - 1] + 3,      // Insert with Insert Cost
                       dp[i - 1][j] + 2,      // Remove with Remove Cost
                       dp[i - 1][j - 1] + 4); // Replace with Replace Cost
    }
  }
  stack<Operation> operationStack;

  int i = m;
  int j = n;

  while (i > 0 && j > 0)
  {
    if (word1[i - 1] == word2[j - 1])
    {
      // Characters are the same, move to the next characters
      // right operation cost 0
      operationStack.push(Operation("right", 0, dp[i][j]));
      i--;
      j--;

      continue; // Skip the rest of the loop and continue to the next iteration
    }
    else if (dp[i][j] == dp[i - 1][j - 1] + 4)
    {
      // Replace operation, continue moving diagonally
      operationStack.push(Operation("replace by " + string(1, word2[j - 1]), 4, dp[i][j]));
      i--;
      j--;
    }
    else if (dp[i][j] == dp[i][j - 1] + 3)
    {
      // Insert operation, continue moving left
      operationStack.push(Operation("insert " + string(1, word2[j - 1]), 3, dp[i][j]));
      j--;
    }
    else if (dp[i][j] == dp[i - 1][j] + 2)
    {
      // Delete operation, continue moving up
      operationStack.push(Operation("delete", 2, dp[i][j]));
      i--;
    }
  }

  while (i > 0)
  {
    // if at first column continue moving up the dp table which will be a
    // delete operation
    operationStack.push(Operation("delete", 2, dp[i][0]));
    i--;
  }

  while (j > 0)
  {
    // if at first row continue moving left the dp table which will be a
    // insert operation
    operationStack.push(Operation("insert " + string(1, word2[j - 1]), 3, dp[0][j]));
    j--;
  }

  // Print the edit table
  print_head();
  printEditDistance(operationStack, word1, word2);

  return dp[m][n];
}

int main(int argc, char *argv[])
{
  char *word1 = "";
  char *word2 = "";

  if (argc == 3)
  {
    word1 = argv[1];
    assert(word1 != "");
    word2 = argv[2];
    assert(word2 != "");

    int result = editDistance(word1, word2, strlen(word1), strlen(word2));
    cout << "Result: " << result << endl;
  }
  else if (argc == 2)
  {
    word1 = argv[1];
    assert(word1 != "");

    ifstream inputFile(word1);  // Replace "example.txt" with the path to your text file

    if (inputFile.is_open()) {
        string numberStr;
        getline(inputFile, numberStr);
        int number1 = stoi(numberStr);  // Convert the string to an integer

        string passage1;
        string passage2;
        string line;

        getline(inputFile, line);
        passage1 = line;

        getline(inputFile, numberStr);
        int number2 = stoi(numberStr);  // Convert the string to an integer

        getline(inputFile, line);
        passage2 = line;

        char* passageChar1 = &passage1[0];  // Convert the passage to a char*
        char* passageChar2 = &passage2[0];  // Convert the passage to a char*

        inputFile.close();

        int result = editDistance(passageChar1, passageChar2, number1, number2);
        cout << "Result: " << result << endl; 

    } else {
        cout << "Unable to open the file." << endl;
    }
    
  }
  else
  {
    fprintf(stderr, "usage: %s <n>\n", argv[0]);
    fprintf(stderr, "Either 1 input text file name or 2 inputs of different strings\n");
    return -1;
  }

  return 0;
}
