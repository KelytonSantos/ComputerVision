#pragma once

#include <opencv2/opencv.hpp>

class Camera {

public:
  bool open();
  cv::Mat getFrame();

private:
  cv::VideoCapture camera;
};