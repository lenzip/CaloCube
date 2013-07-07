#ifndef CaloCubePosition_h
#define CaloCubePosition_h

namespace CaloCube {

  class Position {

    public:

    Position():_x(0), _y(0), _z(0){}
    Position(int x, int y, int z):_x(x), _y(y), _z(z){}

    const int& getX() const { return _x; }
    const int& getY() const { return _y; }
    const int& getZ() const { return _z; }

    bool operator == (const Position& other) const {
      return _x == other.getX() &&
             _y == other.getY() &&
             _z == other.getZ() ;
    }

    private:
    int _x, _y, _z;

  };

}

#endif

