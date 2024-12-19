#ifndef INSTRUCTIONS_DEFINITIONS_H
#define INSTRUCTIONS_DEFINITIONS_H

#define LogicalOPCode 0b0110011
#define LogicalImmediateOPCode 0b0010011
#define RegisterMASK 0b11111

typedef enum instructions
{
    MISSING_IMPLEMENTATION,
    ADD,
    SUB,
    SLL,
    SLT,
    SLTU,
    XOR,
    SRL,
    SRA,
    OR,
    AND,
    ADDI,
    SLTI,
    SLTIU,
    XORI,
    ORI,
    ANDI,
    SLLI,
    SRLI,
    SRAI,
} Instructions;
typedef enum InstructionType
{
    R,
    I,
    IShift,
    S,
    B,
    U,
    J,
} InstructionType;

typedef struct InstructionData
{
    Instructions instruction;
    InstructionType instruction_type;
    const char *instr_str;
    int valid;
    int a;
    int b;
    int c;
} InstructionData;

#endif // INSTRUCTIONS_DEFINITIONS_H
