#include "camera/Camera.hpp"
#include "detection/FaceDetector.hpp"
#include <iostream>
// #include <stdexcept>

int main() {
  Camera camera;

  if (!camera.open()) {
    std::cerr << "Não foi possível iniciar o teste da câmera." << std::endl;
    return -1;
  }

  FaceDetector detector;

  while (true) {
    cv::Mat frame = camera.getFrame();

    if (frame.empty()) {
      std::cerr << "Erro: Frame vazio recebido!" << std::endl;
      break;
    }

    std::vector<cv::Rect> faces = detector.detect(frame);

    // 3. Desenha um retângulo ao redor de cada rosto detectado
    for (const auto &face : faces) {
      // cv::rectangle(imagem, retângulo, cor_BGR, espessura_da_linha)
      cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
    }

    cv::imshow("Teste de Webcam", frame);

    if (cv::waitKey(30) == 27) {
      std::cout << "Fechando o programa..." << std::endl;
      break;
    }
  }

  return 0;
}