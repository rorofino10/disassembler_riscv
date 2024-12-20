#ifndef INSTRUCTIONS_DEFINITIONS_H
#define INSTRUCTIONS_DEFINITIONS_H

#define LogicalOPCode 0b0110011
#define LogicalImmediateOPCode 0b0010011
#define RegisterMASK 0b11111

typedef enum instructions
{
    MISSING_IMPLEMENTATION,
    LUI,
    AUIPC,
    JAL,
    JALR,
    BEQ,
    BNE,
    BLT,
    BGE,
    BLTU,
    BGEU,
    LB,
    LH,
    LW,
    LBU,
    LHU,
    SB,
    SH,
    SW,
    ADDI,
    SLTI,
    SLTIU,
    XORI,
    ORI,
    ANDI,
    SLLI,
    SRLI,
    SRAI,
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
    FENCE,
    ECALL,
    EBREAK,
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

typedef struct
{
    unsigned int rs1 : 5;
    unsigned int rs2 : 5;
    unsigned int rd : 5;
} RInstructionData;

typedef struct
{
    int imm;
    unsigned int rs1 : 5;
    unsigned int rd : 5;
} IInstructionData;
typedef struct
{
    unsigned int imm : 5;
    unsigned int rs1 : 5;
    unsigned int rd : 5;
} IShiftInstructionData;

typedef struct
{
    int imm;
    unsigned int rs1 : 5;
    unsigned int rs2 : 5;
} SInstructionData;

typedef struct
{
    int imm;
    unsigned int rs1 : 5;
    unsigned int rs2 : 5;
} BInstructionData;

typedef struct
{
    int imm;
    unsigned int rd : 5;
} UInstructionData;

typedef struct
{
    int imm;
    unsigned int rd : 5;
} JInstructionData;

typedef struct
{
    InstructionType type;
    const char *string;
    int valid;
    Instructions instruction;
    union
    {
        RInstructionData r_instruction_data;
        IInstructionData i_instruction_data;
        IShiftInstructionData ishift_instruction_data;
        SInstructionData s_instruction_data;
        BInstructionData b_instruction_data;
        UInstructionData u_instruction_data;
        JInstructionData j_instruction_data;
    } data;

} InstructionData;

#endif // INSTRUCTIONS_DEFINITIONS_H
