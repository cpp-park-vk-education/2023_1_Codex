add_executable(server_test /
        src/testLogicalExpressionTask.cpp /
        src/testNumberSystemsTask.cpp /
        )

target_link_libraries(server_test gtest GTest::gtest_main)

add_test(server_test server_test)
