from random import randint
accepted_inputs = [
"003100b3",
"403100b3",
"003110b3",
"003120b3",
"003130b3",
"003140b3",
"003150b3",
"403150b3",
"003160b3",
"003170b3",
"ff010113",
"01012113",
"01013113",
"01014113",
"01016113",
"00531393",
"01f35f93",
"4014d413",
]
types = ["R","I", "U", "S", "B", "J"]
INPUTS_LEN = 1_000_000

with open("/home/nynmiz/allaboutc/disassembler_riscv/test/million_inputs.txt", "w") as file:
    for _ in range(INPUTS_LEN):
        type = types[randint(0, len(types)-1)]
        instruction = 0
        if type == "R":
            f3 = randint(0, 7)
            f7 = 0
            rs1 = randint(0,31)
            rs2 = randint(0,31)
            rd = randint(0,31)
            if f3 == 0 or f3 == 5:
                f7 = randint(0,1)
            instruction = 0b0110011 | rd << 7 | f3 << 12 | rs1 << 15| rs2 << 20 | f7 << 30
        elif type == "U":
            # imm = randint(0,2**20-1)
            imm = randint(-(2**20),2**20-1)
            rd = randint(0,31)
            opcode = [0b0110111,0b0010111]
            instruction = opcode[randint(0,len(opcode)-1)] | rd << 7 | imm << 20
        elif type == "I":
            opcodes = [0b0010011]
            opcode = opcodes[randint(0,len(opcodes)-1)]
            f3 = randint(0, 7)
            rs1 = randint(0,31)
            rd = randint(0,31)
            # shamt = randint(0,2**11-1)
            shamt = randint(-(2**11),2**11-1)
            if f3 == 0b001 or f3 ==0b101:
                shamt =randint(0,0x1F)
            instruction = opcode | rd << 7 | f3 << 12 | rs1 << 15 |shamt << 20
        elif type == "B":
            # imm = randint(0, 2**12-1)
            imm = randint(-(2**12), 2**12-1)
            rs1 = randint(0,31)
            rs2 = randint(0,31)
            f3_l = [0b000,0b001,0b100,0b101,0b110,0b111]
            f3 = f3_l[randint(0,len(f3_l)-1)]
            instruction = 0b1100011 | f3 << 12 | rs1 << 15 | rs2 << 20 | ((imm >> 1) & 0xF) << 8 | ((imm >> 5) & 0x2F) << 25 | ((imm >> 12) & 1) << 31 | ((imm >> 11) & 1) << 7
        elif type == "S":
            # imm = randint(0, 2**11-1)
            imm = randint(-(2**11), 2**11-1)
            rs1 = randint(0,31)
            rs2 = randint(0,31)
            f3 = randint(0,2)
            instruction = 0b0100011 | f3 << 12 | rs1 << 15 | rs2 << 20 | ((imm >> 5) & 0x3F) << 25 | ((imm >> 1) & 0x1F) << 7 
        elif type == "J":
            rd = randint(0,31)
            # imm = randint(0, 2**20-1)
            imm = randint(-(2**20), 2**20-1)
            instruction = 0b1101111 | rd << 7 | imm << 12
        instr_str = hex(instruction)
        # if (instr_str)[0] == '-':
            # instr_str = instr_str[1::]
        file.write(instr_str+"\n")
