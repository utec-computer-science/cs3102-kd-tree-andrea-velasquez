#include <iostream>
#include <vector>
#include "coordinate.h"

template <typename T, int D>
class KDNode{
  typedef std::vector<T> coord_t;
public:
  KDNode<T,D>* left = nullptr;
  KDNode<T,D>* right = nullptr;
  Coordinate<T> coordinate;

  bool isLeaf(){
    return !left && !right;
  }

  KDNode(Coordinate<T> c): coordinate(c){}
  ~KDNode(){}
};


template <typename T, int D>
class KDTree{
  KDNode<T,D>* root = nullptr;

  bool find(KDNode<T,D>** &pointer, Coordinate<T> target){
    if (!root) { return false; }

    int dim=-1;
    while (*pointer){
      dim=++dim%D;

      if (target[dim] >= (*pointer)->coordinate[dim]){ // right
        if (target==(*pointer)->coordinate) return true;
        pointer = &(*pointer)->right;
      }
      else{ // left
        pointer = &(*pointer)->left;
      }
    }
    return false;
  }

  public:
  void insert(Coordinate<T> target){
    KDNode<T,D>* new_node = new KDNode<T,D>(target);

    if (!root) {
      root = new_node;
      return;
    }
    
    KDNode<T,D>** pointer = &root;
    if (find(pointer ,target)){
      std::cout << "Already in tree\n";
      return;
    }
    *pointer = new_node;
  }

  KDTree(){};
  ~KDTree(){};
};

int main(){

  std::vector<std::vector<int>> dots = {{3,6}, {2,7}, {17,15}, {6,12}, {13,15}, {9,1}, {10,19}};

  KDTree<int, 2> tree;
  for (auto &dot : dots){
    Coordinate<int> coord(dot);
    tree.insert(coord);
  }
}