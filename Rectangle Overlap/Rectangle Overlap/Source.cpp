#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
class point {
public:
	point() : x(0), y(0) {};
	point(double x1, double y1) : x(x1), y(y1) {};
	double x;
	double y;
	point operator+(point p) {
		return point(x + p.x, y + p.y);
	}
	point operator-(point p) {
		return point(x - p.x, y - p.y);
	}
	point center(point p1, point p2) {
		return point((p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0);
	}
	double ComputeAngle(point p1, point p2) {
		return atan2((p1.y - p2.y) , (p1.x - p2.x));
	}
};
class vehicle : public point{
public:
	vehicle(vector<point>& rec) {
		fr = rec[0];
		fl = rec[1];
		rr = rec[2];
		rl = rec[3];
		c = center(fr, rl);
		fc = center(fr, fl);
		length = sqrt((fr.y - rr.y) * (fr.y - rr.y) + (fr.x - rr.x) * (fr.x - rr.x));
		width = sqrt((fr.y - fl.y) * (fr.y - fl.y) + (fr.x - fl.x) * (fr.x - fl.x));
		angle = ComputeAngle(fl, rr);
	}
	vehicle(point fr_,double angle_, double length_, double width_) :fr(fr_), angle(angle_), length(length_), width(width_) {
		fl.x = fr.x - width * sin(angle);
		fl.y = fr.y + width * cos(angle);
		rr.x = fr.x - length * cos(angle);
		rr.y = fr.y - length * sin(angle);
		rl.x = rr.x - width * sin(angle);
		rl.y = rr.y + width * cos(angle);
		c = center(fr, rl);
		fc = center(fr, fl);
	};
	point fr,fl,rr,rl,c,fc; // front_right, front_left, rear_right, rear_left, center, front_center
	double length, width;
	double angle;	 // angle = 0 when moving along with the positive direction of x axis
};
double dot(point o, point a, point b) {
	return ((a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y));
}
double cross(point o, point a, point b) {
	return ((a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x));
}
bool IsEdgeIntersect(point rec1_p1, point rec1_p2, point rec2_p1, point rec2_p2) {

	double c1 = cross(rec2_p1, rec1_p1, rec1_p2);
	double c2 = cross(rec2_p2, rec1_p1, rec1_p2);
	double c3 = cross(rec1_p1, rec2_p1, rec2_p2);
	double c4 = cross(rec1_p2, rec2_p1, rec2_p2);
	cout << "rec1_p1 : " << rec1_p1.x << "," << rec1_p1.y << endl;
	cout << "rec1_p2 : " << rec1_p2.x << "," << rec1_p2.y << endl;
	cout << "rec2_p1 : " << rec2_p1.x << "," << rec2_p1.y << endl;
	cout << "rec2_p2 : " << rec2_p2.x << "," << rec2_p2.y << endl;
	cout << "-----------------" << endl;
	if (c1 * c2 < 0 && c3 * c4 < 0) return true;

	if (c1 == 0) return (dot(rec2_p1, rec1_p1, rec1_p2) <= 0);
	if (c2 == 0) return (dot(rec2_p2, rec1_p1, rec1_p2) <= 0);
	if (c3 == 0) return (dot(rec1_p1, rec2_p1, rec2_p2) <= 0);
	if (c4 == 0) return (dot(rec1_p2, rec2_p1, rec2_p2) <= 0);

	return false;
}
bool CheckOverlap(vehicle car1, vehicle car2) {

	vector<point> p1,p2;
	p1 = { car1.fr,car1.fl,car1.rr,car1.rl };
	p2 = { car2.fr,car2.fl,car2.rr,car2.rl };

	//Check if the edges of rec1 and rec2 are intersect

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (IsEdgeIntersect(p1[i], p1[(i+1)%4], p2[j], p2[(j + 1) % 4])) return true;
		}
	}
	return false;
}
int main() {
	vector<point> p = { {4,0},{4,2},{0,0},{0,2} };
	vehicle car1(p);
	p = { {4,1},{4,3},{0,1},{0,3} };
	vehicle car2(p);
	vehicle car3(point(1,1), 0, 4, 3);
	cout << CheckOverlap(car1, car3) << endl;
	cout << car3.fr.x << "," << car3.fl.x << "," << car3.rr.x << "," << car3.rl.x << endl;
	cout << car3.fr.y << "," << car3.fl.y << "," << car3.rr.y << "," << car3.rl.y << endl;
	system("pause");
	return 0;
}