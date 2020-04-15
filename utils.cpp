#include <cmath>
#include "coordinate.h"

template <typename T>
double euclideanDist(Coordinate<T> c1, Coordinate<T> c2){
  if (c1.getDimensions() != c2.getDimensions()) throw "Uncomparable coordinates";

  double sumDifSquares = 0; 
  for (int dim=0; dim<c1.getDimensions(); ++dim){
    sumDifSquares += pow(c1[dim]-c2[dim], 2);
  }
  return sqrt(sumDifSquares);
}