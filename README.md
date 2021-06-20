# Native (non-web) interface written in C for interacting with [Interchange](https://interchangecommerce.org) servers

# Building

```sh
$ git clone git://darapsa.org/libicclient.git
$ cd libicclient
$ autoreconf -is
$ mkdir build
$ cd build
$ ../configure # (or use the platform specific wrappers, and adjust as necessary)
$ make # -jN
$ make install
```
