# 2023_1_Codex

## Распределение работы по проекту

### Чапаев Артем
#### Клиент-серверное взаимодействие:
- разобрался, как писать асинхронный сервер и синхронный клиент с помощью Boost::beast,
- реализовал все взаимодействие клиента и сервера, продумал формат запросов, ответов.  

В рамках этой части мной были написаны файлы:
- server/include/Exceptions.hpp;
- server/include/IHandler.hpp;
- server/include/IMatStatTask.hpp;
- server/include/ITask.hpp;
- server/include/ITaskSearcher.hpp;
- server/include/Listener.hpp, server/src/Listener.cpp;
- server/include/RequestHandler.hpp, server/src/RequestHandler.cpp;
- server/include/Server.hpp, server/src/Server.cpp;
- server/include/Session.hpp, server/src/Session.cpp;
- server/include/SessionManager.hpp, server/src/SessionManager.cpp;
- server/include/TaskHandler.hpp, server/src/TaskHandler.cpp;
- server/include/TaskInfo.hpp;
- server/include/TaskSearcher.hpp, server/src/TaskSearcher.cpp;
- server/src/main.cpp;
- client/include/Client.hpp, client/src/Client.cpp;
- client/include/Exceptions.hpp;
- client/include/TaskInfo.hpp.

#### Взаимодействие сервера с проектом PaddleOCR:
- разобрался с исходным кодом проекта PaddleOCR, установил все зависимости и собрал его,
- преобразовал проект в статическую библиотеку,
- разобрался как работать с моделями для PaddleOCR и обучил модель для проекта,
- продумал как использовать библиотеку PaddleOCR в проекте.  

В рамках этой части мной были написаны файлы:  
- server/include/PredictionConverter.hpp, server/src/PredictionConverter.cpp; (совместно с Машей)
- server/include/TextRecognizer.hpp, server/src/TextRecognizer.cpp.

#### Другие пункты работы
- реализация задач математической статистики: написал файлы server/include/MatStatSequenceTask.hpp и
server/src/MatStatSequenceTask.cpp,
- работа над взаимосвязью проекта: занимался merge'ами всех Pull Request'ов, собирал проект и устранял ошибки во время сборки,
- реализовал иерархический каркас проекта и проверял правильность выполнения тестов.  

#### Общий список моих файлов в алфавитном порядке:
- client/include/Client.hpp, client/src/Client.cpp;
- client/include/Exceptions.hpp;
- client/include/TaskInfo.hpp;

- server/include/Exceptions.hpp;
- server/include/IHandler.hpp;
- server/include/IMatStatTask.hpp;
- server/include/ITask.hpp;
- server/include/ITaskSearcher.hpp;
- server/include/Listener.hpp, server/src/Listener.cpp;
- server/src/main.cpp;
- server/include/MatStatSequenceTask.hpp, server/src/MatStatSequenceTask.cpp;
- server/include/PredictionConverter.hpp, server/src/PredictionConverter.cpp; (совместно с Машей)
- server/include/RequestHandler.hpp, server/src/RequestHandler.cpp;
- server/include/Server.hpp, server/src/Server.cpp;
- server/include/Session.hpp, server/src/Session.cpp;
- server/include/SessionManager.hpp, server/src/SessionManager.cpp;
- server/include/TaskHandler.hpp, server/src/TaskHandler.cpp;
- server/include/TaskInfo.hpp;
- server/include/TaskSearcher.hpp, server/src/TaskSearcher.cpp;
- server/include/TextRecognizer.hpp, server/src/TextRecognizer.cpp.


### Новичкова Мария
#### Реализация математических модулей
Мною были реализованы следующие типы задач: 
Арифметика (файлы ArithmeticTask.hpp, ArithmeticTask.cpp, Calculations.hpp )
Дифференцирование (файлы DifferentiationTask.hpp, DifferentiationTask.cpp)
Матричные задачи, а именно нахождение детерминанта, транспонирование, нахождение нормы, ранга матрицы и нахождение собственных векторов и значений матрицы (файлы MatrixTask.hpp, MatrixTask.cpp) 

Для всех реализованных задач были написаны тесты:
server/tests/src/testArithmeticTask.cpp
server/tests/src/testDifferentiationTask.cpp
server/tests/src/testMatrixTask.cpp

#### Взаимодействие сервера с проектом PaddleOCR
Для обучения нейросети составила основную часть датасета из математических выражений, написанных разными шрифтами как вручную, так и в текстовых редакторах.
Написала функцию для конвертации строки, полученной из нейросети, в корректный формат для передачи решающему модулю для задач арифметики. (файл server/src/PredictionConverter.cpp )

#### Другие задачи
Продумывала итоговый дизайн приложения, составляла макеты для интерфейса.

#### Общий список моих файлов:

- server/include/ArithmeticTask.hpp;
- server/src/ArithmeticTask.cpp;
- server/include/Calculations.hpp;

- server/include/DifferentiationTask.hpp;
- server/src/DifferentiationTask.cpp;

- server/include/MatrixTask.hpp;
- server/src/MatrixTask.cpp;

- server/src/PredictionConverter.cpp