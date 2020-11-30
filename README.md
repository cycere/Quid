QUID BY CYCERE DEVELOPERS.

https://cycere.org

What is Quid?
----------------

Quid is an experimental digital currency that enables instant payments to
anyone, anywhere in the world based on CRYPTONOTE. Quid uses peer-to-peer 
technology to operate and to confirm any type of transaction done on the network
with no central authority: managing transactions and issuing money are carried
out collectively by the network. Quid Core is the name of open source
software which enables the use of this currency.

For more information, as well as an immediately usable, binary version of Quid Core 
open-source software via Cryptonote original whitepaper
(https://cycere.org/download/whitepaper.pdf)


License
-------

Bitcoin Core is released under the terms of the MIT license 
https://opensource.org/licenses/MIT.

## DISCLAIMER ##

The following software is and will be on constant development and is not a
guaranteed efficiency rate as there is no warranty and or completely funcionality is 
and will not be guaranteed due to the conituity in development. for issues arrising ensure
you check is you have followed isntruction to the letter and have ensured you have the right
dependancies installed.

For contibution check our contribution.md file for details


## Building QUID

### On Linux & Unix

Dependencies: GCC 4.7.3 or later, CMake 2.8.6 or later, and Boost 1.55.

You may download them from:

* http://gcc.gnu.org/
* http://www.cmake.org/
* http://www.boost.org/
* Alternatively, it may be possible to install them using a package manager.

To build, change to a directory where this file is located, and run `make`. The resulting executables can be found in `build/release/src`.

**Advanced options:**

* Parallel build: run `make -j<number of threads>` instead of `make`.
* Debug build: run `make build-debug`.
* Test suite: run `make test-release` to run tests in addition to building. Running `make test-debug` will do the same to the debug version.
* Building with Clang: it may be possible to use Clang instead of GCC, but this may not work everywhere. To build, run `export CC=clang CXX=clang++` before running `make`.

### On Windows
Dependencies: MSVC 2013 or later, CMake 2.8.6 or later, and Boost 1.55. You may download them from:

* http://www.microsoft.com/
* http://www.cmake.org/
* http://www.boost.org/

To build, change to a directory where this file is located, and run theas commands: 
```
mkdir build
cd build
cmake -G "Visual Studio 12 Win64" ..
```

And then do Build.
Good luck!

**Copyright (c) 2011-2016 The Cryptonote developers**
**Copyright (c) 2017-2021 The Cycere developers**
