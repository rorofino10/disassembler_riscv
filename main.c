#include <stdio.h>
#include "instructions.h"
#include "instruction_trie.h"

int main(int argc, char **argv)
{
    __uint32_t buffer;
    InstructionTrie *trie = rv32i_base_instruction_set();

    while (scanf("%x", &buffer) != EOF)
    {
        InstructionData instruction_data;
        extract_instruction_data(buffer, trie, &instruction_data);
        print_instruction(&instruction_data);
    }

    return 0;
}
