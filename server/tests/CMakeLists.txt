add_executable(server_test /
        src/testArithmeticTask.cpp /
        src/testCombinatoricsTask.cpp /
        src/testDifferentiationTask.cpp /
        src/testEqSystemsTask.cpp /
        src/testEquationsTask.cpp /
        src/testIntegrationsTask.cpp /
        src/testLogicalExpressionTask.cpp /
        src/testNumberSystemsTask.cpp /
        src/testTaskSearcher.cpp /
        src/testMatrixTask.cpp /
        src/testMatStatSequenceTask.cpp /
        )

target_link_libraries(server_test gtest GTest::gtest_main)

add_test(server_test server_test)
