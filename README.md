## Build Locally with CMAKE

### Installing CMAKE
On Mac use homebrew (or follow instructions [here](https://cmake.org/install/) if you don't use homebrew)
```shell script
brew install cmake
```

On Windows use the instructions on [cmake.org](https://cmake.org/install/)

On linux use a package installer

### Project build

In project dir 
```shell script
mkdir temp
cd temp
cmake ..
make
```

### Testing

Confirm build with unit test from within `temp` build directory
```shell script
./test/unitTest
```

Confirm CLI app from withinit `temp` dir. In the below example 23 is the seed and 6 is the number of random insertions
```shell script
./cpp-maps-app/cpp_maps_app 23 6
```

you should get a printout like follows:
```shell script
seed = 23
loop_count = 6
setting value 48 at index 3
values:  16 16 16 48 16 16 16 16 16
run count: 3

setting value 48 at index 6
values:  16 16 16 48 16 16 48 16 16
run count: 5

setting value 48 at index 8
values:  16 16 16 48 16 16 48 16 48
run count: 6

setting value 48 at index 6
values:  16 16 16 48 16 16 48 16 48
run count: 6

setting value 48 at index 8
values:  16 16 16 48 16 16 48 16 48
run count: 6

setting value 48 at index 7
values:  16 16 16 48 16 16 48 48 48
run count: 4
```

## Build with Docker
```shell script
docker build -t run-maps .
```

Run the unit tests:
```shell script
 docker run -it --entrypoint /bin/bash run-maps:t -c "./test/unitTest"
```

Confirm the docker image works:
```shell script
docker run -it run-maps:t 1999 6
```

results in:
```shell script
seed = 1999
loop_count = 6
setting value 48 at index 4
values:  16 16 16 16 48 16 16 16 16
run count: 3

setting value 48 at index 0
values:  48 16 16 16 48 16 16 16 16
run count: 4

setting value 48 at index 6
values:  48 16 16 16 48 16 48 16 16
run count: 6

setting value 48 at index 2
values:  48 16 48 16 48 16 48 16 16
run count: 8

setting value 48 at index 0
values:  48 16 48 16 48 16 48 16 16
run count: 8

setting value 48 at index 5
values:  48 16 48 16 48 48 48 16 16
run count: 6
```