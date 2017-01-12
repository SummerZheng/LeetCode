#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>

template <typename T>
using matrix = std::vector<std::vector<T> >;

template <typename T>
void print(const std::vector<T>& vec) {
  for (int i=0; i!=vec.size(); i++)
    std::cout<<vec[i]<<", ";
  std::cout<<std::endl;
}

template <typename T1, typename T2>
void print(const std::vector<std::pair<T1, T2> >& vec) {
  for (int i=0; i!=vec.size(); i++)
    std::cout<<"("<<vec[i].first<<", "<<vec[i].second<<"), ";
  std::cout<<std::endl;
}

template <typename T>
void print(const matrix<T>& mat) {
  for (int i=0; i!=mat.size(); i++)
    print(mat[i]);
}

template <typename T1, typename T2>
void print(const std::unordered_map<T1, T2>& map, char sep = '\n') {
  for (auto iter = map.begin(); iter != map.end(); ++iter) {
    std::cout<<"("<<iter->first<<", "<<iter->second<<")"<<sep;
  } 
  std::cout<<std::endl;
}
