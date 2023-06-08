#pragma once

#include <stdlib.h>

#include <algorithm>
#include <chrono>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <ostream>
#include <vector>

#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"

namespace PaddleOCR {

struct OCRPredictResult {
    std::vector<std::vector<int>> box;
    std::string text;
    float score = -1.0;
    float cls_score;
    int cls_label = -1;
};

class Utility {
   public:
    static std::vector<std::string> ReadDict(const std::string &path);

    template <class ForwardIterator>
    inline static size_t argmax(ForwardIterator first, ForwardIterator last) {
        return std::distance(first, std::max_element(first, last));
    }

    static std::vector<int> argsort(const std::vector<float> &array);

    static bool PathExists(const std::string &path);
};

}  // namespace PaddleOCR