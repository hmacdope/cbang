C! (a.k.a. C-Bang)
==================

[![Build Status](https://travis-ci.org/CauldronDevelopmentLLC/cbang.svg?branch=master)](https://travis-ci.org/CauldronDevelopmentLLC/cbang)

The C! or cbang library is a collection of C++ utility libraries
developed over the course of +15 years and several major C++
application development projects.  It should compile and run on
Windows, Linux and OSX using a modern C++ compiler.

Many of the facilities of C! are geared towards cross-platform
application development and providing basic services that most
applications need such as a configuration system, run-time build
information, logging facilities, threads, smart pointers, simple
embedded scripting, etc.

C!'s philosophy is to create clean, simple, readable, modular and
reusable code.  C! also encourages exception based error handling, and
light use of C++ templates and C preprocesor macros.

C! "leans" on the venerable boost library but also reimplements
several boost APIs which are considered by the author to be too
template heavy, less readable or overly complicated in boost.

The code was developed on an as needed basis and was never intended to
be any sort of grand unifying system for C++ application development.
However, I hope you find many parts of the library useful in your C++
development projects.

For licensing information please see the files LICENSE and COPYING.


# Features
  - Smart pointers, both thread safe and non, with downcasting capability.
  - Threading, mutexes, conditions & thread local storage
  - Soft exit & signal handling
  - Extensively configurable logging facilities.
  - Exception class with stack trace capability including line and file info.
  - Exception throwing and catching convenience macros.
  - HTTP and HTTPS client and server.
  - Socket client and server with asynchronous capability.
  - XMacro based enum implementation.
  - PyON Python Object Notation language for serializing and deserializing data.
  - Simple scripting language for configuration and text based command server.
  - Software build information system.
  - A system for compiling in a directory tree of resources.
  - Network packet automatic byte order and string packing functionality.
  - Temporary directories, directory traversal & file operations
  - C++ style number, to and from, string conversions.
  - iostream utilities.
  - Application configuration system.
  - XML facilities.
  - TAR file read and write.
  - Time and timing functions.
  - OpenSSL C++ interface.
  - IP address / hostname resolution, parsing and manipulation.
  - URL parsing.
  - Geometric primitives.
  - C++ wrapper for libevent.
  - Async MariaDB interface using libevent.
  - Human readable size & time formatting.
  - Many other utility classes.
  - Completely contained in it's own C++ namespace.
  - Consistent and clean code formating <= 80 column width.


# Prerequisites
## Required
  - A modern C++ compiler: GNU C++, Intel C++, MSVS
  - SCons      http://scons.org/
  - openssl    http://www.openssl.org/ (optional)

### Windows only
  - Winsock

### OS-X only
  - IOKit
  - CoreFoundation

### POSIX/Linux only
  - pthreads

## Optional
The following add optional features to C!.

  - V8         https://developers.google.com/v8/
  - mariadb    https://mariadb.org/
  - LevelDB    https://github.com/google/leveldb
  - Snappy     http://google.github.io/snappy/

## Debug mode
The following are required for debug builds.

  - libbfd    ftp://ftp.gnu.org/old-gnu/Manuals/bfd-2.9.1/html_mono/bfd.html
  - libiberty https://gcc.gnu.org/onlinedocs/libiberty/
  - libbfd (Posix only)

## Debian/Ubuntu install
On Debian based systems the prerequisites can be installed with the following
command line:

    sudo apt-get install -y scons build-essential libssl-dev binutils-dev \
      libiberty-dev libmariadb-dev-compat libleveldb-dev libsnappy-dev git

# Build

    cd cbang
    scons

There are a number of build options which can either be passed on the
command line to scons or place in a configuration file named
'options.py'.  These options are as follows:

  - debug                - Enable debugging
  - optimize             - Enable compiler optimizations
  - staticlib            - Build a static library
  - sharedlib            - Build a shared library
  - strict               - Enable strict checking
  - distcc               - Enable distcc distributed compile system
  - ccache               - Enable ccache caching compile system
  - backtrace_debugger   - Enable the printing backtraces

These options are enabled by setting them to 1.  For example:

    scons debug=1

## Build Warnings/Errors
If you get any build warnings, by default, the build will stop.  If you have
problems building, especially with warnings related to the boost library you
can ignore these warnings by building with `scons strict=0`.  This disables
strict checking.

# Testing the Build

You can testing C! by going to the *tests* directory in the root of the
cbang source tree, building the test programs and running the test harness:

    cd tests
    scons
    ./testHarness

# Troubleshooting

This section describes some common problems and their solutions.

## OpenSSL Library Too Old

If you get an error about the openssl library version being too old then you
either need to upgrade your package or build openssl from source like this:

    wget http://www.openssl.org/source/openssl-1.0.1f.tar.gz
    tar xzvf openssl-1.0.1f.tar.gz
    cd openssl-1.0.1f
    ./config
    make
    export OPENSSL_HOME=$PWD

Then build C!.
