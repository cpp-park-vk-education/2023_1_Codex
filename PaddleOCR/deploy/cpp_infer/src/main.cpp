#include <iostream>
#include <ocr.hpp>

int main() {
    // your paths
    std::string image_path = "./arith_80.png";
    std::string model_path = "./models";

    std::cout << PaddleOCR::ocr(model_path, image_path, true, false) << std::endl;

    return 0;
}