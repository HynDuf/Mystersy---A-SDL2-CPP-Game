#pragma once
#include <math.h>
// 2D point data types
// Specifically for colliders of objects

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator < (P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator == (P p) const { return tie(x,y) == tie(p.x,p.y); }
	P operator + (P p) const { return P(x+p.x, y+p.y); }
	P operator - (P p) const { return P(x-p.x, y-p.y); }
	P operator * (T d) const { return P(x*d, y*d); }
	P operator / (T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a - *this).cross(b - *this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this / dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }
};

/**
 * @return true iff p lies on the seg segment from s to e.
 */
template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

/**
 * @return whether 2 segments intersect
 */
template<class P>
bool SegInterSeg(P a, P b, P c, P d) {
	auto oa = c.cross(d, a), ob = c.cross(d, b),
	     oc = a.cross(b, c), od = a.cross(b, d);
	// Checks if intersection is single non-endpoint point.
	if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
		return true;
	if (onSegment(c, d, a)) return true;
	if (onSegment(c, d, b)) return true;
	if (onSegment(a, b, c)) return true;
	if (onSegment(a, b, d)) return true;
	return false;
}

/**
 * Rectangle has bottom left corner 's' and top right corner 'e'.
 * @return Point 'p' is inside the rectangle or not 
 */
template<class P>
bool IsInsideRectangle(P s, P e, P p)
{
    return s.x <= p.x && p.x <= e.x && s.y <= p.y && p.y <= e.y;
}

/**
 * @return Does segment (seg_s, seg_e) intersect with rectangle (rect_s, rect_e)?
 */
template<class P>
bool SegInterRectangle(P rect_s, P rect_e, P seg_s, P seg_e)
{
    if (IsInsideRectangle(seg_s, rect_s, rect_e) || IsInsideRectangle(seg_e, rect_s, rect_e))
        return true;

    if (SegInterSeg(seg_s, seg_e, rect_s, P(rect_s.x, rect_e.y))
    ||  SegInterSeg(seg_s, seg_e, rect_s, P(rect_e.x, rect_s.y))
    ||  SegInterSeg(seg_s, seg_e, P(rect_e.x, rect_s.y), rect_e)
    ||  SegInterSeg(seg_s, seg_e, P(rect_s.x, rect_e.y), rect_e))
        return true;
    return false;
}

