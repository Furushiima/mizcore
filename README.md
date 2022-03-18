# mizcore

Mizar Core Library

## Environment

- OS
  - Linux (Tested on Ubuntu 20.04 LTS)
- Compiler
  - GCC (Tested on GCC 9.3.0)

## Build

```bash
sudo apt install build-essential cmake flex bison clang-tidy clang-format
git clone https://github.com/mimosa-project/mizcore.git --recursive
cd mizcore
mkdir build
cd build
cmake ..
make
```

## Test

```bash
cd build
ctest
```

## Development

### Installation

All developers are supposed to inspect the source code with clang-tidy and clang-format before committing.

```bash
sudo apt install clang-tidy clang-format
```

It is also recommended that VSCode users install the following extensions for on-the-fly inspection.

- [Clang-Format](https://marketplace.visualstudio.com/items?itemName=xaver.clang-format)
- [Clang-Tidy](https://marketplace.visualstudio.com/items?itemName=notskm.clang-tidy)

## TODO

- Create error report function and output log.
- Create token replace function for TokenTable.
- Create arity table function.
- Collect arity information during tokenizer processing.
- Resolve reference relationships between variables.
- Replace token type from SYMBOL to VARIABLE in partial mode.
- Resolve reference relationships between labels.
- Make a cross compile environment.
- Error handling.
- Python binding (in another project).
- JavaScript binding (in another project).
- Support GitHub Actions.
