## Overview

[Amirkabir University of Technology 1400-2: Advanced Programming Course](https://csdiy.wiki/%E7%BC%96%E7%A8%8B%E5%85%A5%E9%97%A8/cpp/AUT1400/)

## Homework Details

### HW1

`upper_triangular` bonus question: swap the adjacent rows if find $0$ on main diagonal

### HW2

Install OpenSSL (Required in CMakeLists)

For Server Class:

- `void show_wallets`: to avoid add `friend` in Server class, use pointer to get the private variable `clients`;
- `bool parse_trx`: static member function, references;



## Setup

1. **Install WSL**

2. **Install essentials**

    ```
    sudo apt install cmake make gcc g++ git
    ```

3. **Install google test** ([Google Test](https://github.com/google/googletest/blob/main/googletest/README.md))

	```
	git clone https://github.com/google/googletest.git -b v1.17.0
	cd googletest        # Main directory of the cloned repository.
	mkdir build          # Create a directory to hold the build output.
	cd build
	cmake ..             # Generate native build scripts for GoogleTest.
	make
	sudo make install
	```

4. **Install VS Code extensions**

	Install **WSL** extension
	
	Install **C/C++ Extension Pack** after connecting to WSL in VS Code


## Configuration and Test

1. Open WSL and clone AP1400-2 repository.

2. Configure CMake: choose GCC 13.2.1 x86_64-pc-linux-gnu. Or manually, `Ctrl+Shift+p`,  `>Cmake: Configure`  (might be redundant)

3. To test, turn to `main.cpp` and make `false` to run unit-tests.

4. In `unit_test.cpp`, cancel comment the part you want to test.

5. Run test

    ```
    mkdir build
    cd build
    cmake ..
    make
    ```

After successfully building,

```
./main
```

Expected example:

```
RUNNING TESTS ...
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from HW1Test
[ RUN      ] HW1Test.ZEROS
[       OK ] HW1Test.ZEROS (0 ms)
[----------] 1 test from HW1Test (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.
<<<SUCCESS>>>
```

## Others

WSL 网络镜像

create a `.wslconfig` file in `%USERPROFILE%`

Add the following lines:

```ini
[wsl2]
networkingMode=mirrored
```

restart WSL

```cmd
wsl --shutdown
```

Known Caveats, better ways?

