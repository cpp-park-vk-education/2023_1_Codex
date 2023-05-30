#pragma once

#include <memory>
#include <string>

namespace Handlers {

class TextRecognizer {
   public:
    TextRecognizer(bool useCLf, std::shared_ptr<std::string const> docRoot);

    std::string RecognizeText(const std::string &imagePath);

   private:
    std::shared_ptr<std::string const> DocRoot;
    bool UseClf;
};

}  // namespace Handlers
