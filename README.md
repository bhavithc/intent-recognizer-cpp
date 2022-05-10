# intent-recognizer-cpp
Intent recognizer command line tool, The input and output looks like this:

```
What is the weather like today? => Prints (Intent: Get Weather)
What is the weather like in Paris today? => Prints (Intent: Get Weather City)
Tell me an interesting fact. => Prints (Intent: Get Fact)
```

## Cmake build steps

### Configure cmake
```
cmake -H. -Bbuild
```

### Configure with debug flag enabled
```
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Debug
```

### Build
```
cmake --build build
```

### Executing unit test cases
```
cmake --build build --target test
```

### Installing
```
cmake --build build --target install
```

### clean
```
rm -rf build
```

## Dependecy libraries
```
sudo apt install qtbase5-dev
sudo apt-get install cmake
```