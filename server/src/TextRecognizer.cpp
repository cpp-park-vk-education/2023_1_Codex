#include "TextRecognizer.hpp"

#include <ocr.hpp>

namespace Handlers {

TextRecognizer::TextRecognizer(bool useCLf, std::shared_ptr<std::string const> docRoot)
    : DocRoot(std::move(docRoot)), UseClf(useCLf) {}

std::string TextRecognizer::RecognizeText(const std::string &imagePath) {
    return PaddleOCR::ocr(*DocRoot, imagePath, true, UseClf);
}

}  // namespace Handlers
