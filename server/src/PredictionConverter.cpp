#include "PredictionConverter.hpp"

#include "Exceptions.hpp"

namespace Handlers {

// method has been implemented by Artem
std::string PredictionConverter::ConvertRecognizerPrediction(const std::string &prediction,
                                                             ::Tasks::TaskTypes taskType) {
    if (taskType <= ::Tasks::TaskTypes::IntegTrapez) {
        throw ::Handlers::HandlerUnsupportedTask();
    }
    if (taskType <= ::Tasks::TaskTypes::CombPart) {
        throw ::Handlers::HandlerUnsupportedTask();
    }
    if (taskType <= ::Tasks::TaskTypes::EqPoly) {
        throw ::Handlers::HandlerUnsupportedTask();
    }
    if (taskType <= ::Tasks::TaskTypes::EqSLU) {
        throw ::Handlers::HandlerUnsupportedTask();
    }
    if (taskType == ::Tasks::TaskTypes::Arithmetic) {
        return ConvertArithmeticTask(prediction);
    }
    if (taskType <= ::Tasks::TaskTypes::DiffNum) {
        throw ::Handlers::HandlerUnsupportedTask();
    }
    if (taskType <= ::Tasks::TaskTypes::MatrixNorm) {
        throw ::Handlers::HandlerUnsupportedTask();
    }

    // NumberSystemTask

    if (taskType <= ::Tasks::TaskTypes::LogicalPCNF) {
        throw ::Handlers::HandlerUnsupportedTask();
    }
    if (taskType <= ::Tasks::TaskTypes::MatStatSeqQuantile) {
        return ConvertMatStatTask(prediction);
    } else {
        throw ::Handlers::HandlerUnsupportedTask();
    }
}

// method has been implemented by Artem
std::string PredictionConverter::ConvertMatStatTask(const std::string &prediction) {
    std::string result;
    for (auto ch : prediction) {
        if (ch == ',') {
            result += " ";
        } else if (ch == '/') {
            result += " / ";
        } else {
            result += ch;
        }
    }
    return result;
}

// method has been implemented by Masha
std::string PredictionConverter::ConvertArithmeticTask(const std::string &prediction) {
    std::string result;
    int i = 0;
    while (i < prediction.length()) {
        if (prediction[i] == '+' || prediction[i] == '-' || prediction[i] == '*' || prediction[i] == '/' ||
            prediction[i] == '^' || prediction[i] == ')' || prediction[i] == '(') {
            result += " ";
            result += prediction[i];
            result += " ";
        }

        else if (i + 3 < prediction.length() &&
                 (prediction.substr(i, 4) == "actg" || prediction.substr(i, 4) == "sqrt" ||
                  prediction.substr(i, 4) == "asin" || prediction.substr(i, 4) == "acos")) {
            result += " ";
            result += prediction.substr(i, 4);
            result += " ";
            i += 3;
        } else if (i + 2 < prediction.length() &&
                   (prediction.substr(i, 3) == "atg" || prediction.substr(i, 3) == "cos" ||
                    prediction.substr(i, 3) == "sin" || prediction.substr(i, 3) == "ctg" ||
                    prediction.substr(i, 3) == "exp" || prediction.substr(i, 3) == "abs")) {
            result += " ";
            result += prediction.substr(i, 3);
            result += " ";
            i += 2;
        }

        else if (i < prediction.length() &&
                 (prediction.substr(i, 2) == "ln" || prediction.substr(i, 2) == "lg" ||
                  prediction.substr(i, 2) == "tg")) {
            result += " ";
            result += prediction.substr(i, 2);
            result += " ";
            i += 1;
        }

        else {
            result += prediction[i];
        }
        i++;
    }

    return result;
}

}  // namespace Handlers
