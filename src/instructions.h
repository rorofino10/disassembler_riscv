#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdio.h>
#include "instruction_lookup.h"

extern const char *instr_str[];

void print_instruction(InstructionData *instruction_data);

const char *get_instr_str(Instructions instruction);

void extract_instruction_data(__uint32_t instruction, InstructionData *instruction_data);
InstructionType extract_type(__uint8_t opcode);
#endif // INSTRUCTIONS_H
