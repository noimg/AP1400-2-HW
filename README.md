## Overview

[Amirkabir University of Technology 1400-2: Advanced Programming Course](https://csdiy.wiki/%E7%BC%96%E7%A8%8B%E5%85%A5%E9%97%A8/cpp/AUT1400/)

referred to: https://github.com/Daniel741312/AUT-1400/
and with the help of AI

## Homework Details

### HW1

`upper_triangular` bonus question: swap the adjacent rows if find $0$ on main diagonal

### HW2

Install OpenSSL (Required in CMakeLists)

Server Class:

- `void show_wallets`: to avoid add `friend` in Server class, use pointer to get the private variable `clients`;
- `bool parse_trx`: static member function, references;

### HW3

BST Class:

- use a sentinel node as `root`, `root->value` is number of nodes, `root->left` is the actual tree
- use double pointer to implement `add`, `find`, other efficient ways?
- `BST::find_successor`: is actually find predecessor (from unit-test)
- not familiar with copy constructor, move constructor

### HW4

Unique_ptr

- not quite understand `make_unique`

Shared_ptr

- not quite understand `make_shared`
- define pointer `int* count`
- `*count++` is parsed as `*(count++)`, so we need `(*count)++`
- check if `count` is `nullptr` before dereference it

### HW5

Espresso Based:

- `brew()` done by AI
- not quite understand deep copy

### HW6

- not familiar with STL and file processing , almost AI assisted

### HW7

- `areSimilar` is kind of interesting

- skip `daemon_figure.py`, I don't like matplotlib

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

1. Clone AP1400-2 repository.

2. Configure CMake

    - If the repositories in ubuntu, vscode will automatically configure cmake, choose GCC 13.2.1 x86_64-pc-linux-gnu, or manually check: `Ctrl+Shift+p`,  `>Cmake: Configure` 

    - If the repositories in windows, open wsl shell, manually run

    	```
    	mkdir build
    	cmake ..
    	```

3. To test, turn to `main.cpp` and make `false` to run unit-tests.

4. In `unit_test.cpp`, cancel comment the part you want to test.

5. Run test

    ```
    mkdir build
    cd build
    cmake ..
    make
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

---

We can also put the repositories in windows system. In ubuntu, windows files are at like `/mnt/c`, `/mnt/d`

so we don't need vscode wsl extension?

but compiling cmake in windows is slower

I'm not quite understand this field of knowledge
