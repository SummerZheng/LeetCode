#include<iostream>
#include<string>
#include<map>

using namespace std;

bool canConstruct(string ransomNote, string magazine) {
  map<char, int> mag_dict;
  map<char, int> rs_dict;
  for (int i = 0; i != magazine.size(); i++)
    mag_dict[magazine[i]]++;
  for (int i = 0; i != ransomNote.size(); i++)
    rs_dict[ransomNote[i]]++;
  for (map<char, int>::iterator iter = rs_dict.begin(); iter != rs_dict.end(); iter++) {
    map<char, int>::iterator map_iter = mag_dict.find(iter->first);
    if (map_iter == mag_dict.end() || map_iter->second < iter->second)
      return false;
  }
  return true;
}

int main() {
  bool flag = canConstruct("aa", "ab");
  cout<<flag<<endl;
  return 0;
}
