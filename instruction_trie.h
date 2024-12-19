#ifndef INSTRUCTIONS_TRIE_H
#define INSTRUCTIONS_TRIE_H

#include "instructions_definitions.h"
#include <stdio.h>
struct F7Node
{
    InstructionType type;
    Instructions instruction;
};

struct F3Node
{
    InstructionType type;
    Instructions instruction;
    int has_data;
    struct F7Node *f7node_list[128];
};

struct OpcodeNode
{
    InstructionType type;
    Instructions instruction;
    int has_data;
    struct F3Node *f3node_list[8];
};

typedef struct InstructionTrie
{
    struct OpcodeNode *opcode_list[128];
} InstructionTrie;

InstructionTrie *empty_trie();
InstructionTrie *rv32i_base_instruction_set();
void add_instruction(__uint8_t opcode, __uint8_t f3, __uint8_t f7, int depth, InstructionType type, Instructions instruction, InstructionTrie *trie);
void get_instruction(__uint8_t opcode, __uint8_t f3, __uint8_t f7, InstructionType *type, Instructions *instruction, InstructionTrie *trie);
#endif // INSTRUCTIONS_TRIE_H
