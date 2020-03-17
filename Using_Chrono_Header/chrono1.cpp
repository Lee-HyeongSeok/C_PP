#include <iostream>
#include <ratio>
#include <chrono>
using namespace std;
using namespace std::chrono;

template <typename V, typename R>
ostream& operator<<(ostream& s, const chrono::duration<V, R>& d) {
	s << "[ " << d.count() << " of " << R::num << "/" << R::den << " ]";
	return s;
}

class Point {
private : 
	int xpos, ypos;
public : 
	Point(int x, int y)
		: xpos(x), ypos(y) {
		
	}
	Point& Add(const Point& ref) {
		xpos += ref.xpos;
		ypos += ref.ypos;
		return *this;
	}
	~Point() {

	}
	friend ostream& operator<<(ostream& os, const Point& ref);
};

ostream& operator<<(ostream& os, const Point& ref) {
	os << "[ " << ref.xpos << ", " << ref.ypos << " ]" << endl;
	return os;
}
int main() {
	Point pt1(3, 5);
	Point pt2(4, 7);
	
	pt1.Add(pt2);

	cout << pt1 << endl;
	
	return 0;
}