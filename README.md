# Cross-platform library written in C for interacting with [Interchange](https://interchangecommerce.org) servers

# Building

```sh
$ git clone git://darapsa.org/libinterchange.git
$ cd libinterchange
$ autoreconf -is
$ mkdir build
$ cd build
$ ../configure # (or use the platform specific wrappers, and adjust as necessary)
$ make # -jN
$ make install
```
