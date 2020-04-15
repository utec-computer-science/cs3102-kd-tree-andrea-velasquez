#include <iostream>
#include <vector>
#include <limits>
#include "utils.cpp"

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

  bool helperFind(KDNode<T,D>** &pointer, Coordinate<T> target){
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

  Coordinate<T>* closestCoord(Coordinate<T> *target, Coordinate<T> *c1, Coordinate<T> *c2){
    if (!c1 || !c2) return c1? c1 : c2; // if any coord is null, return the other one
    return euclideanDist(*target, *c1)<euclideanDist(*target, *c2)? c1 : c2;
  }

  Coordinate<T>* recursiveSearch(KDNode<T,D>* parent, Coordinate<T> *target, int dim){
    if (!parent) return nullptr;

    dim=++dim%D;
    
    // closest coord is itself
    if (*target == parent->coordinate) return target; 

    KDNode<T,D>* selected_side;
    KDNode<T,D>* other_side;

    if ((*target)[dim] >= parent->coordinate[dim]){
      selected_side = parent->right;
      other_side = parent->left;
    }
    else{
      selected_side = parent->left;
      other_side = parent->right;
    }

    // Search in selected subtree and compare with the parent
    Coordinate<T> *favorite = closestCoord(target, &parent->coordinate, recursiveSearch(selected_side, target, dim));

    // // If the selected side didn't have anything best, look on the other side
    if (*favorite == parent->coordinate){
      favorite = closestCoord(target, &parent->coordinate, recursiveSearch(other_side, target, dim));
    }

    return favorite;
  }

  public:
  void insert(Coordinate<T> target){
    KDNode<T,D>* new_node = new KDNode<T,D>(target);

    if (!root) {
      root = new_node;
      return;
    }
    
    KDNode<T,D>** pointer = &root;
    if (helperFind(pointer ,target)){
      std::cout << "Already in tree\n";
      return;
    }
    *pointer = new_node;
  }

  Coordinate<T> search(Coordinate<T> target){
    if (!root) throw "Can't search in empty tree";
    // Coordinate<T>* ptarget = &target;
    return *recursiveSearch(root, &target, -1);
  }

  bool isInTree(Coordinate<T> target){
    KDNode<T,D>** pointer = &root;
    return helperFind(pointer, target);
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

  std::cout << "Closer coordinate to (0,0): " << tree.search(Coordinate<int>({0, 0})) << std::endl;
  std::cout << "Is (2,7) in the tree?: " << tree.isInTree(Coordinate<int>({2, 7})) << std::endl;
  std::cout << "Is (7,13) in the tree?: " << tree.isInTree(Coordinate<int>({7, 13})) << std::endl;

}