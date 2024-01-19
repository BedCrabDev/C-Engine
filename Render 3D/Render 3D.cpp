#include <iostream>
#include "Window.h"

using namespace std;

int main() {
    Window* pWindow = new Window(640, 480);
    cameraObject camera = { 0, 0, 100 };
    vector<Point3D> p = { {0, 0, 0}, {10, 0, 0}, {5, 0, 15}, {5, 10, 15} };
    vector<Vertecy3D> v = { {p[0], p[1]}, {p[1], p[2]}, {p[2], p[0]}, {p[1], p[3]}, {p[2], p[3]}, {p[0], p[3]} };
    object3D* obj = new object3D(p, v);
    perspectiveObject3D per = obj->renderPerspective(camera, 640, 480);
    for (int i = 0; i < per.vertecys.size(); ++i) {
        pWindow->DrawLine(per.vertecys[i].A, per.vertecys[i].B, RGB(255, 255, 255));
    }
    pWindow->writeBitmap();
    bool running = true;
    while (running) {
        running = pWindow->ProcessMessages();
        Sleep(10);
    }

    delete pWindow;
    return 0;
}
