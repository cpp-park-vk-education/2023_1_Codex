#pragma once

#include <ocr_cls.h>
#include <ocr_rec.h>

namespace PaddleOCR {

class PPOCR {
   public:
    PPOCR(bool useClf, const std::string &docRoot);
    ~PPOCR();

    std::vector<std::vector<OCRPredictResult>> ocr(std::vector<cv::Mat> img_list, bool rec = true,
                                                   bool cls = true);

   protected:
    void rec(std::vector<cv::Mat> img_list, std::vector<OCRPredictResult> &ocr_results);
    void cls(std::vector<cv::Mat> img_list, std::vector<OCRPredictResult> &ocr_results);

   private:
    Classifier *classifier_ = nullptr;
    CRNNRecognizer *recognizer_ = nullptr;
};

}  // namespace PaddleOCR
