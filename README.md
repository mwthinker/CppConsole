CppConsole
======
A simple c++ class to handle input and output to the active console. Visual studio uses Win32 API, the other option is to use ncurses.

Open source
======
The project is under the MIT license (see LICENSE.txt).

Building
======
CMake must be installed, at least version 2.8. Make sure all dependencies and a native compiler are installed. The dependencies must also be recognized by CMAKE.

To download, build and run under debian based os:
```bash
sudo apt-get update
sudo apt-get install git cmake build-essential
sudo apt-get install libncurses5-dev
git clone git@github.com:mwthinker/CppConsole.git
cd CppConsole
mkdir build
cd build
cmake -D "ConsoleTest:=1" ..
make
./ConsoleTest
```

Dependencies
======
Under windows no external dependencies except Visual Studio is needed.

Installing dependencies in debian based os, 

```bash
sudo apt-get install libncurses5-dev
```

Open source
=====
The project is under the MIT license (see LICENSE).
