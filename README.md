<h1 align="center">
    RISC-V Disassembler
</h1>

<h4 align="center">
    Simple project for translating machine code into risc-v instructions
</h4>

## Features
- supports only RV32I Base Instruction Set for now. Extensible for more instructions.
- reads hexadecimals from stdin or another specified stream and outputs its corresponding RISC-V instruction.

## Installation
You can either download from releases or build it yourself doing the following:
```bash
git clone https://github.com/rorofino10/disassembler_riscv.git
make
```
And you will find the executable in dist/

## Usage
Run the executable, and optionally add input and output files as parameters
```bash
    disassembler
    0x12c84b3 // Input
    add s1, s9, s2 // Output
```
You can also specify the input and output streams:
```bash
    disassembler test/input.txt test/compiled.riscv
```
