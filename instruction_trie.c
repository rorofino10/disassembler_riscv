#include "instruction_trie.h"
#include <stdlib.h>
#include <string.h>

InstructionTrie *empty_trie()
{
    InstructionTrie *instruction_trie = malloc(sizeof(InstructionTrie));

    if (instruction_trie == NULL)
    {
        return NULL;
    }

    memset(instruction_trie->opcode_list, NULL, sizeof(instruction_trie->opcode_list));
    return instruction_trie;
}

InstructionTrie *rv32i_base_instruction_set()
{
    InstructionTrie *trie = empty_trie();
    add_instruction(LogicalOPCode, 0b000, 0b0000000, 2, R, ADD, trie);
    add_instruction(LogicalOPCode, 0b000, 0b0100000, 2, R, SUB, trie);
    add_instruction(LogicalOPCode, 0b001, 0b0000000, 2, R, SLL, trie);
    add_instruction(LogicalOPCode, 0b010, 0b0000000, 2, R, SLT, trie);
    add_instruction(LogicalOPCode, 0b011, 0b0000000, 2, R, SLTU, trie);
    add_instruction(LogicalOPCode, 0b100, 0b0000000, 2, R, XOR, trie);
    add_instruction(LogicalOPCode, 0b101, 0b0000000, 2, R, SRL, trie);
    add_instruction(LogicalOPCode, 0b101, 0b0100000, 2, R, SRA, trie);
    add_instruction(LogicalOPCode, 0b110, 0b0000000, 2, R, OR, trie);
    add_instruction(LogicalOPCode, 0b111, 0b0000000, 2, R, AND, trie);
    // // Logical Immediates
    add_instruction(LogicalImmediateOPCode, 0b000, 0b0000000, 1, I, ADDI, trie);
    add_instruction(LogicalImmediateOPCode, 0b010, 0b0000000, 1, I, SLTI, trie);
    add_instruction(LogicalImmediateOPCode, 0b011, 0b0000000, 1, I, SLTIU, trie);
    add_instruction(LogicalImmediateOPCode, 0b100, 0b0000000, 1, I, XORI, trie);
    add_instruction(LogicalImmediateOPCode, 0b110, 0b0000000, 1, I, ORI, trie);
    add_instruction(LogicalImmediateOPCode, 0b111, 0b0000000, 1, I, ANDI, trie);
    // Shifter with immeadiate
    add_instruction(LogicalImmediateOPCode, 0b001, 0b0000000, 2, IShift, SLLI, trie);
    add_instruction(LogicalImmediateOPCode, 0b101, 0b0000000, 2, IShift, SRLI, trie);
    add_instruction(LogicalImmediateOPCode, 0b101, 0b0100000, 2, IShift, SRAI, trie);

    return trie;
}

void add_instruction(__uint8_t opcode, __uint8_t f3, __uint8_t f7, int depth, InstructionType type, Instructions instruction, InstructionTrie *trie)
{
    struct OpcodeNode *node;
    if (trie->opcode_list[opcode] == NULL)
    {
        node = malloc(sizeof(struct OpcodeNode));
        trie->opcode_list[opcode] = node;
    }
    node = trie->opcode_list[opcode];
    if (depth == 0)
    {
        node->has_data = 1;
        node->instruction = instruction;
        node->type = type;
        return;
    }
    struct F3Node *f3node;
    if (node->f3node_list[f3] == NULL)
    {
        f3node = malloc(sizeof(struct F3Node));
        node->f3node_list[f3] = f3node;
    }
    f3node = node->f3node_list[f3];
    if (depth == 1)
    {
        node->has_data = 0;
        f3node->has_data = 1;
        f3node->instruction = instruction;
        f3node->type = type;
        return;
    }
    struct F7Node *f7node = malloc(sizeof(struct F7Node));
    f3node->f7node_list[f7] = f7node;
    f3node->has_data = 0;
    f7node->instruction = instruction;
    f7node->type = type;
    return;
}
