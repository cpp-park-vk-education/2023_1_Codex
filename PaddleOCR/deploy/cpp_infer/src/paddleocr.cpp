#include <paddleocr.h>

namespace PaddleOCR {

PPOCR::PPOCR(bool useClf, const std::string &docRoot) {
    if (useClf) {
        this->classifier_ = new Classifier(docRoot);
    }
    this->recognizer_ = new CRNNRecognizer(docRoot);
}

std::vector<std::vector<OCRPredictResult>> PPOCR::ocr(std::vector<cv::Mat> img_list, bool rec, bool cls) {
    std::vector<std::vector<OCRPredictResult>> ocr_results;

    std::vector<OCRPredictResult> ocr_result(1);

    if (cls && this->classifier_ != nullptr) {
        this->cls(img_list, ocr_result);
        for (int i = 0; i < img_list.size(); i++) {
            if (ocr_result[i].cls_label % 2 == 1 && ocr_result[i].cls_score > this->classifier_->cls_thresh) {
                cv::rotate(img_list[i], img_list[i], 1);
            }
        }
    }
    if (rec) {
        this->rec(img_list, ocr_result);
    }

    std::vector<OCRPredictResult> ocr_result_tmp;
    ocr_result_tmp.push_back(ocr_result[0]);
    ocr_results.push_back(ocr_result_tmp);

    return ocr_results;
}

void PPOCR::rec(std::vector<cv::Mat> img_list, std::vector<OCRPredictResult> &ocr_results) {
    std::vector<std::string> rec_texts(img_list.size(), "");
    std::vector<float> rec_text_scores(img_list.size(), 0);
    this->recognizer_->Run(img_list, rec_texts, rec_text_scores);
    // output rec results
    for (int i = 0; i < rec_texts.size(); i++) {
        ocr_results[i].text = rec_texts[i];
        ocr_results[i].score = rec_text_scores[i];
    }
}

void PPOCR::cls(std::vector<cv::Mat> img_list, std::vector<OCRPredictResult> &ocr_results) {
    std::vector<int> cls_labels(img_list.size(), 0);
    std::vector<float> cls_scores(img_list.size(), 0);
    this->classifier_->Run(img_list, cls_labels, cls_scores);
    // output cls results
    for (int i = 0; i < cls_labels.size(); i++) {
        ocr_results[i].cls_label = cls_labels[i];
        ocr_results[i].cls_score = cls_scores[i];
    }
}

PPOCR::~PPOCR() {
    if (this->classifier_ != nullptr) {
        delete this->classifier_;
    }
    if (this->recognizer_ != nullptr) {
        delete this->recognizer_;
    }
};

}  // namespace PaddleOCR
