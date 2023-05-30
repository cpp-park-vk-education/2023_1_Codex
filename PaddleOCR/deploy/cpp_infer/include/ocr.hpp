#pragma once

#include <string>

namespace PaddleOCR {

std::string ocr(const std::string& doc_root, const std::string& image_path, bool rec = true, bool clf = true);

}  // namespace PaddleOCR