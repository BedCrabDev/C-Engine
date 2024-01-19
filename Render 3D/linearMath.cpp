#include "linearMath.h"

object3D::object3D(std::vector<Point3D> points, std::vector<Vertecy3D> vertecys) : pointV(std::move(points)), vertecyV(std::move(vertecys)) {
}

Point projectPoint(const Point3D& point3D, const cameraObject& camera, int width, int height) {
    //I lost the original function
}

perspectiveObject3D object3D::renderPerspective(cameraObject camera, int windowWidth, int windowHeight) {
    perspectiveObject3D po;
    std::vector<Point> points(pointV.size());
    std::vector<Vertecy> vertecys(vertecyV.size());
    for (size_t i = 0; i < pointV.size(); ++i) {
        points[i] = projectPoint(pointV[i], camera, windowWidth, windowHeight);
    }
    for (size_t i = 0; i < vertecyV.size(); ++i) {
        vertecys[i].A = projectPoint(vertecyV[i].A, camera, windowWidth, windowHeight);
        vertecys[i].B = projectPoint(vertecyV[i].B, camera, windowWidth, windowHeight);
    }
    po.points = points;
    po.vertecys = vertecys;

    return po;
}