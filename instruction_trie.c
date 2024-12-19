#include "instruction_trie.h"
#include <stdlib.h>
#include <stdio.h>

#define KEY(OPCODE, F3, F7) ((OPCODE << 24) | (F3 << 16) | (F7 << 8))
#define ENTRY(OPCODE, F3, F7, INSTRUCTION, STRING, TYPE)      \
    {                                                         \
        KEY(OPCODE, F3, F7), { INSTRUCTION, TYPE, STRING, 1 } \
    }
const CompactEntry rv32i_base_instruction_set[] = {
    ENTRY(0x00, 0x0, 0x00, MISSING_IMPLEMENTATION, "", I),
    ENTRY(0x13, 0x0, 0x00, ADDI, "addi", I),
    ENTRY(0x13, 0x1, 0x00, SLLI, "slli", IShift),
    ENTRY(0x13, 0x2, 0x00, SLTI, "slti", I),
    ENTRY(0x13, 0x3, 0x00, SLTIU, "sltiu", I),
    ENTRY(0x13, 0x4, 0x00, XORI, "xori", I),
    ENTRY(0x13, 0x5, 0x00, SRLI, "srli", IShift),
    ENTRY(0x13, 0x5, 0x20, SRAI, "srai", IShift),
    ENTRY(0x13, 0x6, 0x00, ORI, "ori", I),
    ENTRY(0x13, 0x7, 0x00, ANDI, "andi", I),
    ENTRY(0x33, 0x0, 0x00, ADD, "add", R),
    ENTRY(0x33, 0x0, 0x20, SUB, "sub", R),
    ENTRY(0x33, 0x1, 0x00, SLL, "sll", R),
    ENTRY(0x33, 0x2, 0x00, SLT, "slt", R),
    ENTRY(0x33, 0x3, 0x00, SLTU, "sltu", R),
    ENTRY(0x33, 0x4, 0x00, XOR, "xor", R),
    ENTRY(0x33, 0x5, 0x00, SRL, "srl", R),
    ENTRY(0x33, 0x5, 0x20, SRA, "sra", R),
    ENTRY(0x33, 0x6, 0x00, AND, "and", R),
    ENTRY(0x33, 0x7, 0x00, OR, "or", R),
};

const InstructionEntry instruction_lookup(__uint8_t opcode, __uint8_t f3, __uint8_t f7)
{
    __uint32_t key = KEY(opcode, f3, f7);
    __uint32_t ikey = KEY(opcode, f3, 0);
    __uint32_t key_to_use;
    const CompactEntry *array = rv32i_base_instruction_set;
    for (size_t i = 0; i < sizeof(rv32i_base_instruction_set) / sizeof(rv32i_base_instruction_set[0]); i++)
    {
        if (rv32i_base_instruction_set[i].entry.instruction_type == I)
            key_to_use = ikey;
        else
            key_to_use = key;
        if (rv32i_base_instruction_set[i].key == key_to_use)
        {
            return rv32i_base_instruction_set[i].entry;
        }
    }
    return (InstructionEntry){0};
};
