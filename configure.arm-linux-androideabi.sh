export NDK=/opt/android-ndk-r19c
export TOOLCHAIN=$NDK/toolchains/llvm/prebuilt/linux-x86_64
export TARGET=armv7a-linux-androideabi
export API=21
export CC=$TOOLCHAIN/bin/$TARGET$API-clang
export TARGET=arm-linux-androideabi
export AR=$TOOLCHAIN/bin/$TARGET-ar
export AS=$TOOLCHAIN/bin/$TARGET-as
export LD=$TOOLCHAIN/bin/$TARGET-ld
export RANLIB=$TOOLCHAIN/bin/$TARGET-ranlib
export STRIP=$TOOLCHAIN/bin/$TARGET-strip
export PREFIX=$TOOLCHAIN/sysroot/usr
export CPPFLAGS="$CPPFLAGS -DDEBUG -DANDROID"
export CFLAGS="$CFLAGS -g"
export LDFLAGS="$LDFLAGS -L$PREFIX/lib/$TARGET/$API"
./configure --host=$TARGET --prefix=$PREFIX --libdir=$PREFIX/lib/$TARGET/$API --disable-static
