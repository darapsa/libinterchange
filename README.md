# Native (non-web) interface written in C for interacting with [Interchange](https://interchangecommerce.org) servers

# Building

## Getting and preparing for configuration

```sh
$ git clone git://darapsa.org/libicclient.git
$ cd libicclient
$ libtoolize
$ autoreconf --install
```

## Optionally setting environment values

```sh
$ export ANDROID_NDK_ROOT=$ANDROID_SDK_ROOT/ndk/21.3.6528147
$ export TOOLCHAIN=$ANDROID_NDK_ROOT/toolchains/llvm/prebuilt/linux-x86_64
```

and then

```sh
$ export TARGET=aarch64-linux-android
```

or

```sh
$ export TARGET=armv7a-linux-androideabi
```

or

```sh
$ export TARGET=i686-linux-android
```

or

```sh
$ export TARGET=x86_64-linux-android
```

and then

```sh
$ export API=21
$ export CC=$TOOLCHAIN/bin/$TARGET$API-clang
```

and only for Android 32-bit ARM, reset TARGET

```sh
$ export TARGET=arm-linux-androideabi
```

and then

```sh
$ export AR=$TOOLCHAIN/bin/$TARGET-ar
$ export AS=$TOOLCHAIN/bin/$TARGET-as
$ export LD=$TOOLCHAIN/bin/$TARGET-ld
$ export RANLIB=$TOOLCHAIN/bin/$TARGET-ranlib
$ export STRIP=$TOOLCHAIN/bin/$TARGET-strip
$ export PREFIX=$TOOLCHAIN/sysroot/usr
```

If debugging for Android:
```sh
$ export CPPFLAGS="$CPPFLAGS -DDEBUG -DANDROID"
$ export CFLAGS="$CFLAGS -g"
```

If, for example, on FreeBSD and cross-compiling for arm64 Android relying on Linux binary compatibility:
```sh
$ setenv LDFLAGS "$LDFLAGS -L$PREFIX/lib/$TARGET/$API"
```

## Configuring for various target hosts

```sh
$ ./configure
```

or

```sh
$ ./configure --host=$TARGET --prefix=$PREFIX --libdir=$PREFIX/lib/$TARGET/$API --disable-static
```

or so on.

## Compiling, linking, and installing

```sh
$ make # -jN (with N an integer number of parallel tasks you allow your computer to run for compiling this)
$ sudo make install
```
