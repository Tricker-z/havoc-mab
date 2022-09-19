# Running a Target Program

Here we illustrate how to execute HavocMAB for readelf (binutils-2.37) with [wllvm](https://github.com/travitch/whole-program-llvm).

## Environment

- Tested on Ubuntu 18.04/20.04
- LLVM 10.0-12.0

## Instrumentation

```shell
# download the source code
wget https://ftp.gnu.org/gnu/binutils/binutils-2.37.tar.gz

tar -xvf binutils-2.37.tar.gz

# extract the byte code with wllvm
$ CC=wllvm LLVM_COMPILER=clang ./configure --disable-shared
$ LLVM_COMPILER=clang make -j$(nproc)
$ cd binutils
$ extract-bc readelf

# compile the target program
$ AFL_CC=clang AFL_CXX=cl
ang++ fuzzer/afl-clang-fast readelf.bc -o readelf_afl
```

## Running HavocMAB

```shell
# start to fuzz
$ fuzzer/afl-fuzz -d -i $FUZZ_IN -o $FUZZ_OUT -- ./readelf_afl -a @@
```
