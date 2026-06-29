#pragma once
#include <opencv2/core/types.hpp>
#include <opencv2/dnn.hpp>

class FaceDetector {

public:
  FaceDetector();
  std::vector<cv::Rect> detect(const cv::Mat &);

private:
  cv::dnn::Net net;
};