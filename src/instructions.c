#include "instructions.h"
#include "registers.h"
/**
 * Sign extended an integer from its n-th bit
 * @param uint32 in
 * @param int n
 * @returns in sign extended from its n-th bit
 */
int sext(__uint32_t in, int n)
{
    // MEJORAR SEXT
    switch (n)
    {
    case 12:
        if (in >> 11 == 1)
            return in | 0xFFFFF000;
        break;
    case 13:
        if (in >> 12 == 1)
            return in | 0xFFFFE000;
        break;
    case 20:
        if (in >> 19 == 1)
            return in | 0xFFF00000;
        break;
    default:
        break;
    }
    return in;
}
void extract_instruction(__uint32_t instruction, InstructionData *instruction_data)
{
    __uint8_t opcode = instruction & 0b1111111;
    __uint8_t f3 = (instruction >> 12) & 0b111;
    __uint8_t f7 = (instruction >> 25) & 0b1111111;

    InstructionEntry entry = instruction_lookup(opcode, f3, f7);
    instruction_data->valid = entry.valid;
    instruction_data->instruction = entry.instruction;
    instruction_data->type = entry.instruction_type;
    instruction_data->string = entry.instruction_name;
}

void extract_r_instruction_data(__uint32_t instruction, InstructionData *instruction_data)
{
    RInstructionData *data = &instruction_data->data.r_instruction_data;

    data->rs1 = (instruction >> 15) & RegisterMASK;
    data->rs2 = (instruction >> 20) & RegisterMASK;
    data->rd = (instruction >> 7) & RegisterMASK;
}

void extract_i_instruction_data(__uint32_t instruction, InstructionData *instruction_data)
{
    IInstructionData *data = &instruction_data->data.i_instruction_data;
    data->rs1 = (instruction >> 15) & RegisterMASK;
    data->imm = sext((instruction >> 20) & 0xFFF, 12);
    data->rd = (instruction >> 7) & RegisterMASK;
}
void extract_ishift_instruction_data(__uint32_t instruction, InstructionData *instruction_data)
{
    IShiftInstructionData *data = &instruction_data->data.ishift_instruction_data;
    data->rs1 = (instruction >> 15) & RegisterMASK;
    data->imm = (instruction >> 20) & RegisterMASK;
    data->rd = (instruction >> 7) & RegisterMASK;
}

void extract_s_instruction_data(__uint32_t instruction, InstructionData *instruction_data)
{
    SInstructionData *data = &instruction_data->data.s_instruction_data;
    __uint32_t imm_temp = 0;
    imm_temp |= (((instruction >> 25) & 0x7F) << 5);
    imm_temp |= (instruction >> 7) & 0x1F;

    data->imm = sext(imm_temp, 12);
    data->rs1 = (instruction >> 15) & RegisterMASK;
    data->rs2 = (instruction >> 20) & RegisterMASK;
}
void extract_b_instruction_data(__uint32_t instruction, InstructionData *instruction_data)
{
    BInstructionData *data = &instruction_data->data.b_instruction_data;
    __uint32_t imm_temp = 0;
    imm_temp |= ((instruction >> 7) & 1) << 11;
    imm_temp |= (instruction >> 31) << 12;
    imm_temp |= (((instruction >> 25) & 0x3F) << 5);
    imm_temp |= ((instruction >> 8) & 0xF) << 1;

    data->imm = sext(imm_temp, 13);
    data->rs1 = (instruction >> 15) & RegisterMASK;
    data->rs2 = (instruction >> 20) & RegisterMASK;
}
void extract_u_instruction_data(__uint32_t instruction, InstructionData *instruction_data)
{
    UInstructionData *data = &instruction_data->data.u_instruction_data;

    data->imm = sext(instruction >> 12, 20);
    data->rd = (instruction >> 7) & RegisterMASK;
}
void extract_j_instruction_data(__uint32_t instruction, InstructionData *instruction_data)
{
    UInstructionData *data = &instruction_data->data.u_instruction_data;

    data->imm = sext(instruction >> 12, 20);
    data->rd = (instruction >> 7) & RegisterMASK;
}

void extract_instruction_data(__uint32_t instruction, InstructionData *instruction_data)
{
    extract_instruction(instruction, instruction_data);
    if (!instruction_data->valid)
        return;
    switch (instruction_data->type)
    {
    case R:
        extract_r_instruction_data(instruction, instruction_data);
        break;
    case IShift:
        extract_ishift_instruction_data(instruction, instruction_data);
        break;
    case I:
        extract_i_instruction_data(instruction, instruction_data);
        break;
    case S:
        extract_s_instruction_data(instruction, instruction_data);
        break;
    case B:
        extract_b_instruction_data(instruction, instruction_data);
        break;
    case U:
        extract_u_instruction_data(instruction, instruction_data);
        break;
    case J:
        // extract_j_instruction_data(instruction, instruction_data);
        break;
    default:
        break;
    }
}

void print_instruction(InstructionData *instruction_data)
{

    switch (instruction_data->type)
    {
    case R:
        printf("%s %s, %s, %s\n", instruction_data->string, get_register_name(instruction_data->data.r_instruction_data.rd), get_register_name(instruction_data->data.r_instruction_data.rs1), get_register_name(instruction_data->data.r_instruction_data.rs2));
        break;
    case IShift:
        printf("%s %s, %s, %d\n", instruction_data->string, get_register_name(instruction_data->data.ishift_instruction_data.rd), get_register_name(instruction_data->data.ishift_instruction_data.rs1), instruction_data->data.ishift_instruction_data.imm);
        break;
    case I:
        printf("%s %s, %s, %d\n", instruction_data->string, get_register_name(instruction_data->data.i_instruction_data.rd), get_register_name(instruction_data->data.i_instruction_data.rs1), instruction_data->data.i_instruction_data.imm);
        break;
    case S:
        printf("%s %s, %d(%s)\n", instruction_data->string, get_register_name(instruction_data->data.s_instruction_data.rs2), instruction_data->data.s_instruction_data.imm, get_register_name(instruction_data->data.s_instruction_data.rs1));
        break;
    case B:
        printf("%s %s, %s, %d\n", instruction_data->string, get_register_name(instruction_data->data.b_instruction_data.rs1), get_register_name(instruction_data->data.b_instruction_data.rs2), instruction_data->data.b_instruction_data.imm);
        break;
    case U:
        printf("%s %s, 0x%x\n", instruction_data->string, get_register_name(instruction_data->data.u_instruction_data.rd), instruction_data->data.u_instruction_data.imm);
        break;
    default:
        break;
    }
}
