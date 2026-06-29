#include "detection/FaceDetector.hpp"

/*
#pragma once
#include <opencv2/core/types.hpp>
#include <opencv2/dnn/dnn.hpp>

class FaceDetector {

public:
  std::vector<cv::Rect> detect(cv::Mat &);

private:
  cv::dnn::Net net;
};
*/

FaceDetector::FaceDetector() {
  net = cv::dnn::readNetFromCaffe(
      "models/deploy.prototxt",
      "models/res10_300x300_ssd_iter_140000_fp16.caffemodel");

  if (net.empty()) {
    throw std::runtime_error("Falha ao carregar o modelo.");
  }
}

std::vector<cv::Rect> FaceDetector::detect(const cv::Mat &frame) {

  cv::Mat blob = cv::dnn::blobFromImage(frame, 1.0, cv::Size(300, 300),
                                        cv::Scalar(104.0, 177.0, 123.0), false,
                                        false, CV_32F);

  net.setInput(blob);
  cv::Mat output = net.forward(); // executa propagação direta, retorna matriz
  // quadrimensional contendo todas as detecções
  // encontradas(formato: [1, 1, N, 7])

  // Matriz de detecções terá tamanho Nx7.
  // cv::Mat de 4 dimensões pode ser tratada como 2D acessando a última parte

  cv::Mat detectionMat(output.size[2], output.size[3], CV_32F,
                       output.ptr<float>());

  std::vector<cv::Rect> faces;
  float confidenceThreshold =
      0.5; // Filtro para ignorar falsos positivos (50% de certeza)

  for (int i = 0; i < detectionMat.rows; i++) {
    float confidence = detectionMat.at<float>(i, 2);

    if (confidence > confidenceThreshold) {
      // Recupera as coordenadas normalizadas
      float xLeftBottom = detectionMat.at<float>(i, 3);
      float yLeftBottom = detectionMat.at<float>(i, 4);
      float xRightTop = detectionMat.at<float>(i, 5);
      float yRightTop = detectionMat.at<float>(i, 6);

      // Converte de volta para os pixels reais do frame original
      int x = static_cast<int>(xLeftBottom * frame.cols);
      int y = static_cast<int>(yLeftBottom * frame.rows);
      int width = static_cast<int>((xRightTop - xLeftBottom) * frame.cols);
      int height = static_cast<int>((yRightTop - yLeftBottom) * frame.rows);

      // Adiciona o retângulo mapeado ao vetor de faces
      faces.push_back(cv::Rect(x, y, width, height));
    }
  }

  return faces;
}