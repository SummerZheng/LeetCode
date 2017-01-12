#include<iostream>
#include<vector>
#include<queue>

using namespace std;

template <typename T>
void print(const std::vector<T>& vec) {
  for (int i=0; i != vec.size(); ++i) {
    std::cout<<vec[i]<<" ";
  }
  std::cout<<std::endl;
}

template <typename T>
void print(const std::vector<vector<T> >& mat) {
  for (int i=0; i != mat.size(); ++i) {
    print(mat[i]);
  }
  std::cout<<std::endl;
}

template <typename T, size_t nRow, size_t nCol>
std::vector<vector<T> > initializeMat(const T (&arr) [nRow][nCol]) {
  vector<vector<T> > mat(nRow, vector<T>(nCol));
  for (int r = 0; r != nRow; ++r) {
    for (int c = 0; c != nCol; ++c) {
      mat[r][c] = arr[r][c];
    }
  }
  return mat;
}

// struct matrix{
//   matrix():mat(vector<vector<bool> >()), nRow(0), nCol(0){}
//   matrix(const vector<vector<char> > &grid):mat(vector<vector<bool> >(grid.size(), vector<bool>(grid[0].size(), false))), nRow(grid.size()), nCol(grid[0].size()){}
//   bool validPos(int i, int j) {return true;}
//   private:
//   vector<vector<bool> > mat;
//   int nRow;
//   int nCol;
// };

template<size_t n>
vector<vector<char> > convert_strvec_to_charmat(const string (&str_vec)[n]){
  const int NROW = n;
  const int NCOL = str_vec[0].size();
  vector<vector<char> > mat(NROW, vector<char>(NCOL));
  for (int r = 0; r != NROW; ++r) {
    for (int c = 0; c != NCOL; ++c) {
      mat[r][c] = str_vec[r][c];
    }
  }
  return mat;
}

inline void append_if_unvisited_land(const vector<vector<char> >& mat, vector<vector<bool> >& visited, int r, int c, queue<pair<int, int> >& Q) {
  if (mat[r][c] == '1' && visited[r][c] == false) {
    visited[r][c] = true;
    Q.push(make_pair(r, c));
  }
}

void BFS(vector<vector<char> >& mat, vector<vector<bool> >& visited, int r_init, int c_init) {
  const int row = visited.size();
  const int col = visited[0].size();
  int r, c;
  queue<pair<int, int> > BFSqueue;
  BFSqueue.push(make_pair(r_init, c_init));
  while(!BFSqueue.empty()) {
    pair<int, int> cur = BFSqueue.front();
    BFSqueue.pop();
    r = cur.first - 1, c = cur.second;
    if (r >= 0)
      append_if_unvisited_land(mat, visited, r, c, BFSqueue);
    r = cur.first + 1, c = cur.second;
    if (r < row)
      append_if_unvisited_land(mat, visited, r, c, BFSqueue);
    r = cur.first, c = cur.second + 1;
    if (c < col)
      append_if_unvisited_land(mat, visited, r, c, BFSqueue);
    r = cur.first, c = cur.second - 1;
    if (c >= 0)
      append_if_unvisited_land(mat, visited, r, c, BFSqueue);
  }
}

inline void append_if_unvisited_land(vector<vector<char> >& mat, int r, int c, queue<pair<int, int> >& Q) {
  if (mat[r][c] == '1') {
    mat[r][c] = '0';
    Q.push(make_pair(r, c));
  }
}

void BFS(vector<vector<char> >& mat, int r_init, int c_init) {
  const int row = mat.size();
  const int col = mat[0].size();
  int r, c;
  queue<pair<int, int> > BFSqueue;
  BFSqueue.push(make_pair(r_init, c_init));
  while(!BFSqueue.empty()) {
    pair<int, int> cur = BFSqueue.front();
    BFSqueue.pop();
    r = cur.first - 1, c = cur.second;
    if (r >= 0)
      append_if_unvisited_land(mat, r, c, BFSqueue);
    r = cur.first + 1, c = cur.second;
    if (r < row)
      append_if_unvisited_land(mat, r, c, BFSqueue);
    r = cur.first, c = cur.second + 1;
    if (c < col)
      append_if_unvisited_land(mat, r, c, BFSqueue);
    r = cur.first, c = cur.second - 1;
    if (c >= 0)
      append_if_unvisited_land(mat, r, c, BFSqueue);
  }
}

int numIslands(vector<vector<char> >& grid) {
  if (grid.size() == 0 || grid[0].size() == 0) return 0;
  int nRow = grid.size();
  int nCol = grid[0].size();
  int nIslands = 0;
  for (int r = 0; r != nRow; ++r) {
    for (int c = 0; c != nCol; ++c) {
      if (grid[r][c] == '1') {
        grid[r][c] = '0';
        ++nIslands;
        BFS(grid, r, c);
      }
    }
  }
  return nIslands;
}

int main() {
  // char a[][5] = {
  //   {'1', '1', '1', '1', '0'}, 
  //   {'1', '1', '0', '1', '0'},
  //   {'1', '1', '0', '0', '0'},
  //   {'0', '0', '0', '0', '0'},
  // };
  // char a[][5] = {
  //   {'1', '1', '0', '0', '0'}, 
  //   {'1', '1', '0', '0', '0'}, 
  //   {'0', '0', '1', '0', '0'},
  //   {'0', '0', '0', '1', '1'},
  // };
  // vector<vector<char> > mat(initializeMat(a));
  string str_vec[] = {"11111011111111101011","01111111111110111110","10111001101111111111","11110111111111111111","10011111111111111111",
                      "10111111011101110111","01111111111101101111","11111111111101111011","11111111110111111111","11111111111111111111",
                      "01111111011111111111","11111111111111111111","11111111111111111111","11111011111110111111","10111110111011110111",
                      "11111111111101111110","11111111111110111100","11111111111111111111","11111111111111111111","11111111111111111111"};
  vector<vector<char> > mat  = convert_strvec_to_charmat(str_vec);
  print(mat);
  cout<<numIslands(mat)<<endl;
  return 0;
}
