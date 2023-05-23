#include "ArithmeticTask.hpp"

#include <memory>
#include <regex>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include "Calculations.hpp"
#include "Exceptions.hpp"
#include "TaskInfo.hpp"

static bool is_number(const std::string &str) {
    std::regex digit("^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)$");
    return !str.empty() && (std::regex_match(str, digit) || str == "pi");
}

static bool is_operator(const std::string &str) {
    return (operators_set.find(str) != operators_set.end());
}

static bool is_binary(const std::string &op) {
    return (op == "+" || op == "-" || op == "/" || op == "^" || op == "*");
}

static unsigned priority(const std::string &op) {
    if (op == "^") return 4;
    if (op == "/" || op == "*") return 3;
    if (op == "sin" || op == "asin" || op == "cos" || op == "acos" || op == "tg" || op == "atg" ||
        op == "ctg" || op == "actg" || op == "exp" || op == "abs" || op == "sqrt")
        return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

namespace Tasks {

ArithmeticTask::ArithmeticTask(std::string expression, TaskTypes taskType) {
    Expression = std::move(expression);
    TaskType = taskType;
}

std::string ArithmeticTask::Solve() {
    ParseData();
    double result = root->Calculate();
    return DoubleToString(result);
}

double ArithmeticTask::Solve_d() {
    ParseData();
    return root->Calculate();
}

std::vector<std::string> ArithmeticTask::get_lexems() {
    // std::cout << expression << std::endl;
    std::vector<std::string> lexems;
    std::stringstream ss(Expression);
    std::string lexem;
    while (ss >> lexem) {
        lexems.push_back(lexem);
    }
    return lexems;
}

void ArithmeticTask::analyze_operator(std::string op) {
    //Добавить возможность задать унарный минус (проверить не возникло ли новых проблем)
    if (is_binary(op)) {
        std::unique_ptr<ICalculatable> right = std::move(output.top());
        output.pop();

        std::unique_ptr<ICalculatable> left = std::move(output.top());
        output.pop();
        if (op == "+") {
            std::unique_ptr<ICalculatable> result = std::make_unique<Add>(std::move(left), std::move(right));
            output.push(std::move(result));
        } else if (op == "-") {
            std::unique_ptr<ICalculatable> result =
                std::make_unique<Subtraction>(std::move(left), std::move(right));
            output.push(std::move(result));
        } else if (op == "/") {
            std::unique_ptr<ICalculatable> result =
                std::make_unique<Division>(std::move(left), std::move(right));
            output.push(std::move(result));
        } else if (op == "*") {
            std::unique_ptr<ICalculatable> result =
                std::make_unique<Multiplication>(std::move(left), std::move(right));
            output.push(std::move(result));
        } else if (op == "^") {
            std::unique_ptr<ICalculatable> result =
                std::make_unique<Degree>(std::move(left), std::move(right));
            output.push(std::move(result));
        }

    } else {
        std::unique_ptr<ICalculatable> left = std::move(output.top());
        output.pop();
        if (op == "abs") {
            std::unique_ptr<ICalculatable> result = std::make_unique<Absolute>(std::move(left));
            output.push(std::move(result));
        } else if (op == "exp") {
            std::unique_ptr<ICalculatable> result = std::make_unique<Exponenta>(std::move(left));
            output.push(std::move(result));
        } else if (op == "sqrt") {
            std::unique_ptr<ICalculatable> result = std::make_unique<SquareRoot>(std::move(left));
            output.push(std::move(result));
        } else if (op == "sin") {
            std::unique_ptr<ICalculatable> result = std::make_unique<Sinus>(std::move(left));
            output.push(std::move(result));
        } else if (op == "asin") {
            std::unique_ptr<ICalculatable> result = std::make_unique<Arcsinus>(std::move(left));
            output.push(std::move(result));
        } else if (op == "cos") {
            std::unique_ptr<ICalculatable> result = std::make_unique<Cosine>(std::move(left));
            output.push(std::move(result));
        } else if (op == "acos") {
            std::unique_ptr<ICalculatable> result = std::make_unique<Arcosine>(std::move(left));
            output.push(std::move(result));
        } else if (op == "tg") {
            std::unique_ptr<ICalculatable> result = std::make_unique<Tangent>(std::move(left));
            output.push(std::move(result));
        } else if (op == "atg") {
            std::unique_ptr<ICalculatable> result = std::make_unique<Arctangent>(std::move(left));
            output.push(std::move(result));
        } else if (op == "ctg") {
            std::unique_ptr<ICalculatable> result = std::make_unique<Cotangent>(std::move(left));
            output.push(std::move(result));
        } else if (op == "actg") {
            std::unique_ptr<ICalculatable> result = std::make_unique<Arctangent>(std::move(left));
            output.push(std::move(result));
        }
    }
}

//вернет указатель на корень дерева выражений
void ArithmeticTask::ParseData() {
    // const std::vector<std::string>& lexems
    std::vector<std::string> lexems = get_lexems();

    std::unique_ptr<ICalculatable> number =
        std::make_unique<Number>(0);  //Если первый символ невведен, то как будто там ноль
    output.push(std::move(number));
    std::stack<std::string> operators;
    for (const auto &lexem : lexems) {
        if (is_number(lexem)) {
            // Если лексема является числом, то создаем объект Number
            double value;
            if (lexem == "pi") {
                value = pi;
            } else {
                value = std::stod(lexem);
            }
            std::unique_ptr<ICalculatable> number = std::make_unique<Number>(value);
            output.push(std::move(number));
        } else if (lexem == "(") {
            // Если лексема является открывающей скобкой, то помещаем ее в стек операторов
            operators.push("(");
        } else if (lexem == ")") {
            // Если лексема является закрывающей скобкой, то выполняем операции до тех пор,
            // пока не встретим открывающую скобку
            while (operators.top() != "(") {
                std::string op = operators.top();
                operators.pop();
                analyze_operator(op);
            }
            operators.pop();  // Удаляем открывающую скобку из стека операторов
        } else if (is_operator(lexem)) {
            // Если токен является оператором , то выполняем операции,
            // пока на вершине стека операторов находится оператор с большим
            // или равным приоритетом
            while (!operators.empty() && priority(operators.top()) >= priority(lexem)) {
                std::string op = operators.top();

                analyze_operator(op);
                operators.pop();
            }

            // Помещаем текущий оператор в стек операторов
            operators.push(lexem);
        } else {
            throw TaskInvalidData("Invalid lexem");
        }
    }
    // Выполняем оставшиеся операции
    while (!operators.empty()) {
        std::string op = operators.top();

        analyze_operator(op);
        operators.pop();
    }

    // (Возвращаем) вершину
    root = std::move(output.top());
}

}  // namespace Tasks