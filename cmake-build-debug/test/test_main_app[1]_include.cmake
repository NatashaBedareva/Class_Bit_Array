if(EXISTS "C:/Users/Bedareva/Documents/STADING_NGU/OOP/Bit_Array/cmake-build-debug/test/test_main_app[1]_tests.cmake")
  include("C:/Users/Bedareva/Documents/STADING_NGU/OOP/Bit_Array/cmake-build-debug/test/test_main_app[1]_tests.cmake")
else()
  add_test(test_main_app_NOT_BUILT test_main_app_NOT_BUILT)
endif()
