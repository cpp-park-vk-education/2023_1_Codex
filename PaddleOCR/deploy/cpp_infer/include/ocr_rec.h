#pragma once

#include <ocr_cls.h>
#include <utility.h>

#include "paddle_api.h"
#include "paddle_inference_api.h"

namespace PaddleOCR {

class CRNNRecognizer {
   public:
    explicit CRNNRecognizer(const std::string &model_dir) {
        this->label_list_ = Utility::ReadDict("./PaddleOCR/deploy/en_dict.txt");
        this->label_list_.insert(this->label_list_.begin(), "}");
        this->label_list_.push_back(" ");

        LoadModel(model_dir);
    }

    // Load Paddle inference model
    void LoadModel(const std::string &model_dir);

    void Run(std::vector<cv::Mat> img_list, std::vector<std::string> &rec_texts,
             std::vector<float> &rec_text_scores);

   private:
    std::shared_ptr<paddle_infer::Predictor> predictor_;

    bool use_gpu_ = false;
    int gpu_id_ = 0;
    int gpu_mem_ = 4000;
    int cpu_math_library_num_threads_ = 4;
    bool use_mkldnn_ = false;

    std::vector<std::string> label_list_;

    std::vector<float> mean_ = {0.5f, 0.5f, 0.5f};
    std::vector<float> scale_ = {1 / 0.5f, 1 / 0.5f, 1 / 0.5f};
    bool is_scale_ = true;
    bool use_tensorrt_ = false;
    std::string precision_ = "fp32";
    int rec_batch_num_ = 6;
    int rec_img_h_ = 32;
    int rec_img_w_ = 320;
    std::vector<int> rec_image_shape_ = {3, rec_img_h_, rec_img_w_};
    // pre-process
    CrnnResizeImg resize_op_;
    Normalize normalize_op_;
    PermuteBatch permute_op_;

};  // class CrnnRecognizer

}  // namespace PaddleOCR
