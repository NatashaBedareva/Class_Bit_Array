include(FetchContent)

FetchContent_Declare(googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
        )

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(test_main_app test_main.cpp) # to run tests
target_link_libraries(test_main_app PRIVATE GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(test_main_app)

#cmake --build build
#cd build/test/
# ctest
#./Debug/test_main_app