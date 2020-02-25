# Native (non-web) interface written in C for interacting with [Interchange](https://interchangecommerce.org) servers

# Building

## Getting and preparing for configuration

```sh
$ git clone git://darapsa.org/libicclient.git
$ cd libicclient
$ autoreconf --install
```

## Optionally setting environment values

If, for example, on FreeBSD and using a previously set up arm64 Android standalone toolchain:
```sh
$ setenv CFLAGS "-target aarch64-linux-android --sysroot=/usr/local/aarch64-linux-android/sysroot -I/usr/local/aarch64-linux-android/lib64/clang/7.0.2/include -L/usr/local/aarch64-linux-android/lib/gcc/aarch64-linux-android/4.9.x"
```

If debugging for Android:
```sh
$ export CFLAGS="${CFLAGS} -g -DDEBUG -DANDROID"
$ export LDFLAGS="${LDFLAGS} -llog"
```

and if for android_armv7:

```sh
$ export CFLAGS="${CFLAGS} -fPIC"
```

## Configuring for various target hosts

```sh
$ ./configure
```

or

```sh
$ CC=/usr/local/aarch64-linux-android/bin/aarch64-linux-android-clang ./configure --host=aarch64-linux-android
```

or

```sh
$ CC=/usr/local/arm-linux-androideabi/bin/arm-linux-androideabi-clang ./configure --host=arm-linux-androideabi
```

or so on.

## Compiling and linking

```sh
$ make # -jN (with N an integer number of parallel tasks you allow your computer to run for compiling this)
```
