#pragma once

#include <preprocess_op.h>
#include <utility.h>

#include "paddle_api.h"
#include "paddle_inference_api.h"

namespace PaddleOCR {

class Classifier {
   public:
    explicit Classifier(const std::string &model_dir) {
        LoadModel(model_dir);
    }

    double cls_thresh = 0.9;

    // Load Paddle inference model
    void LoadModel(const std::string &model_dir);

    void Run(std::vector<cv::Mat> img_list, std::vector<int> &cls_labels, std::vector<float> &cls_scores);

   private:
    std::shared_ptr<paddle_infer::Predictor> predictor_;

    bool use_gpu_ = false;
    int gpu_id_ = 0;
    int gpu_mem_ = 4000;
    int cpu_math_library_num_threads_ = 4;
    bool use_mkldnn_ = false;

    std::vector<float> mean_ = {0.5f, 0.5f, 0.5f};
    std::vector<float> scale_ = {1 / 0.5f, 1 / 0.5f, 1 / 0.5f};
    bool is_scale_ = true;
    bool use_tensorrt_ = false;
    std::string precision_ = "fp32";
    int cls_batch_num_ = 1;
    // pre-process
    ClsResizeImg resize_op_;
    Normalize normalize_op_;
    PermuteBatch permute_op_;

};  // class Classifier

}  // namespace PaddleOCR
