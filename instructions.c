#include "instructions.h"
#include "registers.h"

int sext(__uint32_t in, int n)
{
    switch (n)
    {
    case 12:
        if (in >> 11 == 1)
            return in | 0xFFFFF000;
        return in;

    default:
        return in;
    }
}

const char *instr_str[] = {
    [MISSING_IMPLEMENTATION] = "missing",
    [SUB] = "sub",
    [ADD] = "add",
    [SLL] = "sll",
    [SLT] = "slt",
    [SLTU] = "sltu",
    [XOR] = "xor",
    [SRL] = "srl",
    [SRA] = "sra",
    [OR] = "or",
    [AND] = "and",
    [ADDI] = "addi",
    [SLTI] = "slti",
    [SLTIU] = "sltiu",
    [XORI] = "xori",
    [ORI] = "ori",
    [ANDI] = "andi",
    [SLLI] = "slli",
    [SRLI] = "srli",
    [SRAI] = "srai",
};
const char *get_instr_str(Instructions instruction)
{
    return instr_str[instruction];
}

void extract_i_instruction_data(__uint32_t instruction, InstructionData *instruction_data)
{
    instruction_data->a = (instruction >> 15) & RegisterMASK;
    instruction_data->b = sext((instruction >> 20) & 0xFFF, 12);
    instruction_data->c = (instruction >> 7) & RegisterMASK;
}
void extract_r_instruction_data(__uint32_t instruction, InstructionData *instruction_data)
{
    instruction_data->a = (instruction >> 15) & RegisterMASK;
    instruction_data->b = (instruction >> 20) & RegisterMASK;
    instruction_data->c = (instruction >> 7) & RegisterMASK;
}

void extract_instruction_data(__uint32_t instruction, InstructionTrie *trie, InstructionData *instruction_data)
{
    extract_instruction(instruction, trie, instruction_data);
    switch (instruction_data->instruction_type)
    {
    case R:
    case IShift:
        extract_r_instruction_data(instruction, instruction_data);
        break;
    case I:
        extract_i_instruction_data(instruction, instruction_data);
        break;
    default:
        break;
    }
}

void extract_instruction(__uint32_t instruction, InstructionTrie *trie, InstructionData *instruction_data)
{
    __uint8_t opcode = instruction & 0b1111111;

    struct OpcodeNode *opcode_node = trie->opcode_list[opcode];
    if (opcode_node->has_data)
    {
        instruction_data->instruction = opcode_node->instruction;
        instruction_data->instruction_type = opcode_node->type;
        return;
    }

    int f3 = (instruction >> 12) & 0b111;
    struct F3Node *f3node = opcode_node->f3node_list[f3];
    if (f3node->has_data)
    {
        instruction_data->instruction = f3node->instruction;
        instruction_data->instruction_type = f3node->type;
        return;
    }
    int f7 = (instruction >> 25) & 0b1111111;
    struct F7Node *f7node = f3node->f7node_list[f7];
    instruction_data->instruction = f7node->instruction;
    instruction_data->instruction_type = f7node->type;
}

void print_instruction(InstructionData *instruction_data)
{
    const char *instr_name = get_instr_str(instruction_data->instruction);
    switch (instruction_data->instruction_type)
    {
    case R:
        printf("%s %s, %s, %s\n", instr_name, get_register_name(instruction_data->c), get_register_name(instruction_data->a), get_register_name(instruction_data->b));
        break;
    case I:
    case IShift:
        printf("%s %s, %s, %d\n", instr_name, get_register_name(instruction_data->c), get_register_name(instruction_data->a), instruction_data->b);
    default:
        break;
    }
}
