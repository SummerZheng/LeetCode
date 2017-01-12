#include<iostream>
#include<vector>
#include<string>
#include"print.h"

using namespace std;

inline bool test_config(int i, int j, vector<vector<bool> >& trail) {
  if (i >= 0 && j >= 0 && i < trail.size() && j < trail[0].size() && !trail[i][j]) {
    return true;
  } else {
    return false;
  }
}

bool DFS(vector<vector<char> >& board, int i, int j, string& word, int ix, vector<vector<bool> >& trail) {
  if (board[i][j] != word[ix]) return false;
  if (word[ix+1] == '\0') return true;
  trail[i][j] = true;
  ++ix;
  if (test_config(i-1, j, trail) && DFS(board, i-1, j, word, ix, trail)) return true;
  if (test_config(i+1, j, trail) && DFS(board, i+1, j, word, ix, trail)) return true;
  if (test_config(i, j-1, trail) && DFS(board, i, j-1, word, ix, trail)) return true;
  if (test_config(i, j+1, trail) && DFS(board, i, j+1, word, ix, trail)) return true;
  trail[i][j] = false;
  return false;
}

bool exist(vector<vector<char> >& board, string word) {
  if (word.size() == 0) return true;
  vector<vector<bool> > trail(board.size(), vector<bool>(board[0].size(), false));
  for (int i = 0; i != board.size(); ++i) {
    for (int j = 0; j != board[0].size(); ++j) {
      if (DFS(board, i, j, word, 0, trail)) return true;
    }
  }
  return false;
}

int main() {
  string str_vec[] = {"ABCE", "SFES", "ADEE"};
  int R = sizeof(str_vec)/sizeof(str_vec[0]);
  int C = str_vec[0].size();
  vector<vector<char> > board(R, vector<char>(C));
  for (int r = 0; r != R; ++r) {
    for (int c = 0; c != C; ++c) {
      board[r][c] = str_vec[r][c];
    }
  }
  string word = "ABCESEEEFS";
  cout<<exist(board, word)<<endl;
  return 0;
}
