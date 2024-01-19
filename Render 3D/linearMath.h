#pragma once

#include <vector>
#include <cmath>
#include "gameEngine.h"

const double M_PI = 3.14159265358979323846264338327950288419716939937510;

struct Point {
	double x, y;
};

struct Point3D {
	double x, y, z;
};

struct Vertecy3D {
	Point3D A;
	Point3D B;
};

struct Vertecy {
	Point A;
	Point B;
};

struct perspectiveObject3D {
	std::vector<Point> points;
	std::vector<Vertecy> vertecys;
};

class object3D {
public:
	object3D(std::vector<Point3D> points, std::vector<Vertecy3D> vertecys);
	perspectiveObject3D renderPerspective(cameraObject camera, int windowWidth, int windowHeight);
private:
	std::vector<Point3D> pointV;
	std::vector<Vertecy3D> vertecyV;
};

Point projectPoint(const Point3D& point3D, const cameraObject& camera, int windowWidth, int windowHeight);
