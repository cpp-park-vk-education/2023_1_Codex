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

#### Общий список моих тестов в алфавитном порядке:
- server/tests/src/testMatStatSequenceTask.cpp;
- server/tests/src/testTaskSearcher.cpp.

### Новичкова Мария
#### Реализация математических модулей
Мною были реализованы следующие типы задач: 
- Арифметика (файлы ArithmeticTask.hpp, ArithmeticTask.cpp, Calculations.hpp )
- Дифференцирование (файлы DifferentiationTask.hpp, DifferentiationTask.cpp)
- Матричные задачи, а именно нахождение детерминанта, транспонирование, нахождение нормы, ранга матрицы и нахождение собственных векторов и значений матрицы (файлы MatrixTask.hpp, MatrixTask.cpp)

#### Взаимодействие сервера с проектом PaddleOCR
- Для обучения нейросети составила основную часть датасета из математических выражений, написанных разными шрифтами как вручную, так и в текстовых редакторах.
- Написала функцию для конвертации строки, полученной из нейросети, в корректный формат для передачи решающему модулю для задач арифметики. (файл server/src/PredictionConverter.cpp )

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

#### Общий список моих тестов в алфавитном порядке:
- server/tests/src/testArithmeticTask.cpp;
- server/tests/src/testDifferentiationTask.cpp;
- server/tests/src/testMatrixTask.cpp.


### Ангелова Анастасия
#### Реализация математических модулей
Реализованы следующие типы задач: 
- Комбинаторика - сочетания, разбиения, размещения, перестановки (файлы CombinatoricsTask.hpp, CombinatoricsTask.cpp)
- Системы уравнений - решение методом Гаусса, методом Гаусса с выбором главного элемента, LU-разложение (файлы EqSystemsTask.hpp, EqSystemsTask.cpp)
- Различные типы уравнений - линейные, квадратные, полиномиальные (метод Ньютона) (файлы EquationsTask.hpp, EquationsTask.cpp)    
- Вычисление интегралов - реализован метод средних, метод Симпсона, метод трапеций (файлы IntegrationTask.hpp, IntegrationTask.cpp)

#### Взаимодействие сервера с проектом PaddleOCR
Помогала с написанием датасета

#### Общий список реализованных файлов:

- server/include/CombinatoricsTask.hpp;
- server/src/CombinatoricsTask.cpp;

- server/include/EqSystemsTask.hpp;
- server/src/EqSystemsTask.cpp;

- server/include/EquationsTask.hpp;
- server/src/EquationsTask.cpp;

- server/include/IntegrationsTask.hpp;
- server/src/IntegrationsTask.cpp;

#### Общий список моих тестов в алфавитном порядке:
- server/tests/src/testCombinatoricsTask.cpp;
- server/tests/src/testEqSystemsTask.cpp;
- server/tests/src/testEquationsTask.cpp;
- server/tests/src/testIntegrationsTask.cpp.

### Завадская Людмила
#### Интерфейс
Реализовала задачи, связанные с UI. Приложение состояло из нескольких окон:
- Главное окно с функционалом кнопок начала взаимодействия с приложением и кнопкой открытия правил использования (client/include/MainWindow.hpp, client/src/MainWindow.cpp)
- Окно выбора типа задачи (client/include/ProblemTypeWindow.hpp, client/src/ProblemTypeWindow.cpp)
  - Окно содержит список глобальных задач, по нажатию на 1 из которых появляется список соответствующих подзадач - которые мы непосредственно решаем
  - Каждая подзадача соответствует одному математическому модулю
- Окно вывода решения (client/include/SolutionWindow.hpp, client/src/SolutionWindow.cpp). Для разных задач был необходим ввод условий задачи в различном формате, поэтому практически все задачи имеют свой шаблон окна SolutionWindow. В зависимости от задачи в окно подгружается нужный набор виджетов для ввода данных. 
  - Нестандартные наборы виджетов ввода и их лейблов имеют: задачи с матрицами, интегралы, задачи комбинаторики, дифференцирования в точке, линейные и квадратные уравнения, полиномиальные уравнения, задачи решения Систем Линейных Алгебраических Уравнений
  - Для задач, связанных с матрицами и СЛАУ, был реализован отдельный класс отображения матрицы динамического размера MatrixInputForm (rows и cols задаются пользователем в интерефейсе, и размеры матрицы меняются)
  - Также реализован набор виджетов для "стандартного" ввода - ввода задачи вручную
  - Для задач арифметики также была создана возможность загрузки задачи на фото. Было настроено взаимодействие с клиентом для случая ввода таким способом. В том числе, для данного типа задач при вводе условия задачи картинкой предусмотрена возможность редактировать распознанный текст - он помещается также в поле мануального ввода, и пользователь может подредактировать неточности, которые могли произойти при распознавании 

#### Другие задачи
- Реализовала обработку введенных данных в поля ввода для каждого набора виджетов и отправку их на клиент. Затем получение решения и отображение его в окне
- Реализовала вспомогательный файл client/include/ProblemType.hpp с соответствием TaskType задачи и ее названием
- Написала скелеты классов задач перевода чисел из одной системы счисления в другую и решения логических выражений, также написала для них тесты. В итоговом проекте от данных типов задач решили отказаться.

#### Общий список моих файлов:

- client/include/MainWindow.hpp;
- client/include/UI_MainWindow.hpp;
- client/src/MainWindow.cpp;
- client/ui/MainWindow.ui;


- client/include/MatrixInputForm.hpp;
- client/src/MatrixInputForm.cpp;
- client/ui/MatrixInputForm.ui;


- client/include/ProblemTypeWindow.hpp;
- client/include/UI_ProblemTypeWindow.hpp;
- client/src/ProblemTypeWindow.cpp;
- client/ui/ProblemTypeWindow.ui;


- client/include/SolutionWindow.hpp;
- client/include/UI_SolutionWindow.hpp;
- client/src/SolutionWindow.cpp;
- client/ui/SolutionWindow.ui;


- client/include/UsageWindow.hpp;
- client/include/UI_UsageWindow.hpp;
- client/src/UsageWindow.cpp;
- client/ui/UsageWindow.ui;


- client/include/ProblemType.hpp.

#### Общий список моих тестов в алфавитном порядке:
- server/tests/src/testLogicalExpressionTask.cpp;
- server/tests/src/testNumberSystemsTask.cpp.
