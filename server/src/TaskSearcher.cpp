#include "TaskSearcher.hpp"

#include <boost/asio.hpp>
#include <fstream>

#include "ArithmeticTask.hpp"
#include "CombinatoricsTask.hpp"
#include "DifferentiationTask.hpp"
#include "EqSystemsTask.hpp"
#include "EquationsTask.hpp"
#include "Exceptions.hpp"
#include "IntegrationTask.hpp"
#include "MatStatSequenceTask.hpp"
#include "MatrixTask.hpp"
#include "PredictionConverter.hpp"
#include "TextRecognizer.hpp"

namespace Handlers {

namespace http = boost::beast::http;  // from <boost/beast/http.hpp>

TaskSearcher::TaskSearcher(std::shared_ptr<std::string const> docRoot) : DocRoot(std::move(docRoot)) {}

::Tasks::ITaskUPtr TaskSearcher::Run(http::request<http::dynamic_body> &request) {
    // write into ::Tasks::TaskInfo Task from request
    ::Tasks::TaskInfo info = DoTaskSearch(request);

    // Create ITaskUPtr using TaskInfo and return it
    if (info.TaskType <= ::Tasks::TaskTypes::IntegTrapez) {
        return std::make_unique<::Tasks::IntegrationTask>(info.TaskData, info.TaskType);
    }
    if (info.TaskType <= ::Tasks::TaskTypes::CombPart) {
        return std::make_unique<::Tasks::CombinatoricsTask>(info.TaskData, info.TaskType);
    }
    if (info.TaskType <= ::Tasks::TaskTypes::EqPoly) {
        return std::make_unique<::Tasks::EquationsTask>(info.TaskData, info.TaskType);
    }
    if (info.TaskType <= ::Tasks::TaskTypes::EqSLU) {
        return std::make_unique<::Tasks::EqSystemTask>(info.TaskData, info.TaskType);
    }
    if (info.TaskType == ::Tasks::TaskTypes::Arithmetic) {
        return std::make_unique<::Tasks::ArithmeticTask>(info.TaskData, info.TaskType);
    }
    if (info.TaskType <= ::Tasks::TaskTypes::DiffNum) {
        return std::make_unique<::Tasks::DifferentiationTask>(info.TaskData, info.TaskType);
    }
    if (info.TaskType <= ::Tasks::TaskTypes::MatrixNorm) {
        return std::make_unique<::Tasks::MatrixTask>(info.TaskData, info.TaskType);
    }
    // add NumberSystem

    if (info.TaskType <= ::Tasks::TaskTypes::LogicalPCNF) {
        throw ::Handlers::HandlerUnsupportedTask();
    }
    if (info.TaskType <= ::Tasks::TaskTypes::MatStatSeqQuantile) {
        return std::make_unique<::Tasks::MatStatSequenceTask>(info.TaskData, info.TaskType);
    } else {
        throw ::Handlers::HandlerInvalidRequest("taskType");
    }
}

::Tasks::TaskInfo TaskSearcher::DoTaskSearch(http::request<http::dynamic_body> &request) const {
    // If emptyData or wrong req -> exception
    if (request.method() != http::verb::post) {
        throw ::Handlers::HandlerInvalidRequest("method");
    }
    if (request.body().size() == 0) {
        throw ::Handlers::HandlerEmptyRequestBody();
    }

    ::Tasks::TaskTypes taskType = ::Tasks::TaskTypes::NotFound;
    try {
        std::string type = request.target().data();
        taskType = static_cast<::Tasks::TaskTypes>(std::stoi(type));
    } catch (...) {
        throw ::Handlers::HandlerInvalidRequest("taskType");
    }
    if (taskType == ::Tasks::TaskTypes::NotFound) {
        throw ::Handlers::HandlerInvalidRequest("taskType");
    }

    std::string taskData;
    // Using Content-Type define type of data and parse it

    unsigned contentLength = std::stoi(request.at(http::field::content_length));
    if (request.at(http::field::content_type) == "text/plain") {
        for (auto seq : request.body().data()) {
            taskData += std::string(boost::asio::buffer_cast<const char *>(seq));
        }
        // Clear from garbage
        if (taskData.size() > contentLength) {
            taskData = taskData.erase(contentLength, taskData.size() - contentLength);
        }

    } else if (request.at(http::field::content_type) == "image/png") {
        std::string path = "./temp.png";
        std::ofstream outImage(path, std::ios::binary);
        if (!outImage.is_open()) {
            throw HandlerInvalidFile("writing into file on the server");
        }

        unsigned nW = contentLength;
        for (auto seq : request.body().data()) {
            auto *cbuf = boost::asio::buffer_cast<const char *>(seq);

            // Clear from garbage
            unsigned bufSize;
            if (boost::asio::buffer_size(seq) > nW) {
                bufSize = boost::asio::buffer_size(seq) - nW;
            } else {
                bufSize = boost::asio::buffer_size(seq);
            }

            outImage.write(cbuf, bufSize);
            nW -= bufSize;
        }

        // now we don't use angle classifier
        TextRecognizer recognizer(false, DocRoot);
        std::string recognizerPrediction = recognizer.RecognizeText(path);
        taskData = PredictionConverter::ConvertRecognizerPrediction(recognizerPrediction, taskType);
    } else {
        throw ::Handlers::HandlerInvalidRequest("type of data");
    }

    return {taskData, taskType};
}

}  // namespace Handlers
