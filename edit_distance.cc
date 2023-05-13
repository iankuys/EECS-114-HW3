#include <iostream>
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


int main(int argc, char* argv[])
{
  return 0;
}
