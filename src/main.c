#include <stdio.h>
#include <stdlib.h>
#include "instructions.h"

int main(int argc, char **argv)
{
    __uint32_t buffer;

    while (scanf("%x", &buffer) != EOF)
    {
        InstructionData instruction_data;
        extract_instruction_data(buffer, &instruction_data);
        if (!instruction_data.valid)
        {
            printf("ERROR: invalid instruction found.\n");
            // exit(EXIT_FAILURE);
        }
        else
        {
            print_instruction(&instruction_data);
        }
    }

    return 0;
}
