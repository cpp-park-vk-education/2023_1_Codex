add_executable(server_test /
        src/testTaskSearcher.cpp /
        src/testMatStatSequenceTask.cpp /
        src/testArithmeticTask.cpp /
        src/testDifferentiationTask.cpp /
        src/testMatrixTask.cpp /
        )

target_link_libraries(server_test gtest GTest::gtest_main)

add_test(server_test server_test)
