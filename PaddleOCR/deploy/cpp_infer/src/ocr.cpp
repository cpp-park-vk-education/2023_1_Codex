#include <paddleocr.h>
#include <utility.h>

#include <memory>
#include <ocr.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <vector>

namespace PaddleOCR {

std::string ocr(const std::string &doc_Root, const std::string &image_path, bool rec, bool clf) {
    PPOCR ocr(clf, doc_Root);

    std::vector<cv::Mat> img_list;

    // read image
    cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
    img_list.push_back(img);

    // make ocr
    std::vector<std::vector<PaddleOCR::OCRPredictResult>> ocr_results = ocr.ocr(img_list, rec, clf);
    return ocr_results[0][0].text;
}

}  // namespace PaddleOCR