# Bulding Class BitArray
 To run not with tests
 
```
 cmake -S. -Bbuild -DBUILD_MOCK=OFF --fresh
 cmake --build build
 ./build/Debug/main.exe
```

 To run with tests
 
```
 cmake -S. -Bbuild -DBUILD_MOCK=OFF --fresh
 cmake --build build
 cd build/test/
 ctest
 ./Debug/test_main_app
```
 
