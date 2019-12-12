#ifndef POINT_HPP
#define POINT_HPP

#include <tuple>

using namespace std;

struct point {
    point() : x( 0 ), y( 0 ) {}
    point( int x, int y ) : x( x ), y( y ) {}

    int x;
    int y;
};

inline bool operator==( point const& l, point const& r ) { return l.x == r.x && l.y == r.y; }
inline bool operator!=( point const& l, point const& r ) { return !( l == r ); }
inline point operator+( point const& l, point const& r ) { return point( l.x+r.x, l.y+r.y ); }
inline point operator-( point const& l, point const& r ) { return point( l.x-r.x, l.y-r.y ); }
inline point& operator+=( point& p1, point p2 ) { return p1 = point( p1.x+p2.x, p1.y+p2.y ); }
inline point& operator-=( point& p1, point p2 ) { return p1 = point( p1.x-p2.x, p1.y-p2.y ); }
inline bool operator<( point const& l, point const& r ){ return tie( l.x, l.y ) < tie( r.x, r.y ); }

#endif
