#ifndef INSTRUCTIONS_TRIE_H
#define INSTRUCTIONS_TRIE_H

#include "instructions_definitions.h"
#include <stdio.h>
typedef struct
{
    Instructions instruction;
    InstructionType instruction_type;
    const char *instruction_name;
    int valid;
} InstructionEntry;

typedef struct
{
    __uint32_t key;
    InstructionEntry entry;
} CompactEntry;

extern const CompactEntry rv32i_base_instruction_set[];
const InstructionEntry instruction_lookup(__uint8_t opcode, __uint8_t f3, __uint8_t f7);
#endif // INSTRUCTIONS_TRIE_H
