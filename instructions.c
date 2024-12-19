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

void extract_instruction_data(__uint32_t instruction, InstructionData *instruction_data)
{
    extract_instruction(instruction, instruction_data);
    if (!instruction_data->valid)
        return;
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

void extract_instruction(__uint32_t instruction, InstructionData *instruction_data)
{
    __uint8_t opcode = instruction & 0b1111111;
    __uint8_t f3 = (instruction >> 12) & 0b111;
    __uint8_t f7 = (instruction >> 25) & 0b1111111;

    InstructionEntry entry = instruction_lookup(opcode, f3, f7);
    instruction_data->valid = entry.valid;
    instruction_data->instruction = entry.instruction;
    instruction_data->instruction_type = entry.instruction_type;
    instruction_data->instr_str = entry.instruction_name;
}

void print_instruction(InstructionData *instruction_data)
{

    switch (instruction_data->instruction_type)
    {
    case R:
        printf("%s %s, %s, %s\n", instruction_data->instr_str, get_register_name(instruction_data->c), get_register_name(instruction_data->a), get_register_name(instruction_data->b));
        break;
    case I:
    case IShift:
        printf("%s %s, %s, %d\n", instruction_data->instr_str, get_register_name(instruction_data->c), get_register_name(instruction_data->a), instruction_data->b);
    default:
        break;
    }
}
