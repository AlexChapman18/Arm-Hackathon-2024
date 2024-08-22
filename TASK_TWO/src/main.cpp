#include <iostream>
#include <vector>

using namespace std;

class state_t {
  public: 
    vector<vector<int>> grid_; 
    int n_cols_=0;
    int n_rows_=0;
    void parse();
};

int main(int argc, char *argv[])
{
  state_t state;
  state.parse();
  return 0; // for breakpoint
}


void state_t::parse() {
  string line;
  int curr_int;
  int curr_row,curr_col;
  
  getline(cin,line);

  curr_row = 0;

  grid_.push_back(vector<int>());
  for (char& c: line) {
    curr_int = c - '0';
    grid_[curr_row].push_back(curr_int);
    n_cols_++;
  }

  while(getline(cin,line)) {
    curr_row++;
    grid_.push_back(vector<int>());

    for (char& c: line) {
      curr_int = c - '0';
      grid_[curr_row].push_back(curr_int);
    }
  }
}

