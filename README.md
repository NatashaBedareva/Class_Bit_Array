# Bulding Class BitArray
 To run not with tests
 
```
 cmake -S . -B build -DENABLE_TEST=OFF --fresh
 cmake --build build
 ./build/Debug/Bit_Array.exe
```

 To run with tests
 
```
 cmake -S. -B build -DBUILD_MOCK=OFF -DENABLE_TEST=ON --fresh
 cmake --build build
 cd build/test/
 ctest
 ./Debug/test_main_app
```
 
