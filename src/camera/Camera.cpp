#include "camera/Camera.hpp"
#include <iostream>

/*
class Camera {

public:
  bool open();
  cv::Mat getFrame();

private:
  cv::VideoCapture camera;
};
*/

bool Camera::open() {
  int index_camera = 0;

  camera.open(index_camera);

  if (!camera.isOpened()) {
    std::cerr << "erro ao abrir camera" << std::endl;
    return false;
  }
  return true;
}

cv::Mat Camera::getFrame() {

  cv::Mat frame;

  if (camera.isOpened()) {
    camera >> frame;
  } else {
    std::cerr << "erro ao tentar ler frame" << std::endl;
  }

  return frame;
}