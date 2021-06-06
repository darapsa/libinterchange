# Native (non-web) interface written in C for interacting with [Interchange](https://interchangecommerce.org) servers

# Building

## Getting and preparing for configuration

```sh
$ git clone git://darapsa.org/libicclient.git
$ cd libicclient
$ autoreconf --install
```

## Configuring for various target hosts, compiling, linking, and installing

```sh
$ ./configure # (or use the platform specific wrappers, and adjust as necessary)
$ make # -jN (with N an integer number of parallel tasks you allow your computer to run for compiling this)
$ make install
```
