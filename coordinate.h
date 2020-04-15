template <typename T>
class Coordinate{
  typedef std::vector<T> coord_t;

  public:
  coord_t coord = {};

  Coordinate(std::vector<T> c): coord(c){}
  int getDimensions(){ return coord.size(); }

  int &operator[](uint i){
    if (i>coord.size()) throw "Index out of bounds";
    return coord[i];
  }

  template <typename _T>
  friend std::ostream& operator<<(std::ostream & out, const Coordinate <_T> c) {
    out << "(";
    for (_T el: c.coord){
      out << el << ",";
    }
    out << "\b)";
    return out;
  }

  template <typename _T>
  friend bool operator== (const Coordinate<_T> &c1, const Coordinate<_T> &c2){
    return c1.coord == c2.coord;
  }
};