#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<stack>
#include<unordered_set>

using namespace std;

template <typename T>
void print(const std::vector<T>& vec) {
  for (int i=0; i != vec.size(); ++i) {
    std::cout<<vec[i]<<" ";
  }
  std::cout<<std::endl;
}

enum status{unvisited, in_stack, visited};
class Directed_Graph {
  public:
    Directed_Graph(int _v = 0):V(_v),adj(vector<unordered_set<int> >(_v)){}
    void construct_DG(vector<pair<int, int> >& vec) {
      for (int i = 0; i != vec.size(); ++i) {
        adj[vec[i].second].insert(vec[i].first);
      }
    }
    void print_Graph() {
      for (int i = 0; i != V; ++i) {
        cout<<i<<": ";
        for (auto iter = adj[i].begin(); iter != adj[i].end(); ++iter) {
          cout<<*iter<<", ";
        }
        cout<<endl;
      }
    }
    bool topological_sort(vector<int>& sorted_G) {
      stack<int> DFSstack;
      vector<status> status_vec(V, unvisited);
      bool DAG = true;
      for (int i = 0; i != V; ++i) {
        if (status_vec[i] == unvisited) {
          vector<int> sorted_CC; //Connected_Component
          DAG = topological_sort_util(sorted_CC, DFSstack, status_vec, i);
          if (!DAG) {
            return false;
          } else {
            sorted_G.insert(sorted_G.end(), sorted_CC.begin(), sorted_CC.end());
          }
        }
      }
      reverse(sorted_G.begin(), sorted_G.end());
      return true;
    }
  private:
    bool topological_sort_util(vector<int>& sorted_CC, stack<int>& DFSstack, vector<status>& status_vec, int s) {
      DFSstack.push(s);
      status_vec[s] = in_stack;
      while ( !DFSstack.empty() ) {
        int topNode = DFSstack.top();
        bool is_sink = true;
        for (unordered_set<int>::iterator iter = adj[topNode].begin(); iter != adj[topNode].end(); ++iter) {
          if (status_vec[*iter] == in_stack) {
            return false;
          } else if (status_vec[*iter] == unvisited) {
            DFSstack.push(*iter);
            status_vec[*iter] = in_stack;
            is_sink = false;
            break; // This is SUPER IMPORTANT!!! Otherwise, DFS mix with BFS
          } //(status_vec[*iter] == visited) do nothing
        }
        if (is_sink) {
          DFSstack.pop();
          status_vec[topNode] = visited;
          sorted_CC.push_back(topNode);
        }
      }
      return true;
    }
    vector<unordered_set<int> > adj; 
    int V;
};
bool canFinish(int numCourses, vector<pair<int, int> >& prerequisites) {
  if (numCourses == 0) return false;
  Directed_Graph courses(numCourses);
  courses.construct_DG(prerequisites);
  vector<int> sorted_courses;
  bool flag = courses.topological_sort(sorted_courses);
  if (!flag) sorted_courses.clear();
  return flag;
}

int main() {
  int V_input = 1000;
  ifstream infile("P207_P210_Course_Schedule_test_case_2.txt");
  string item;
  int vTail, vHead;
  vector<pair<int, int> > my_pair;

  while(infile.good()){
    getline(infile, item);
    if (item != "") {
    unsigned pos = item.find(',');
    vTail = stoi(item.substr(0, pos));
    vHead = stoi(item.substr(pos+1, item.length()-pos));
    my_pair.push_back(make_pair(vTail, vHead));    
    //cout<<item<<" -> "<<vHead<<", "<<vTail<<endl;
    }
  }
  
  // my_pair.push_back(make_pair(0, 1));
  // my_pair.push_back(make_pair(3, 1));
  // my_pair.push_back(make_pair(1, 3));
  // my_pair.push_back(make_pair(3, 2));
  cout<<canFinish(V_input, my_pair)<<endl;
  return 0;
}
