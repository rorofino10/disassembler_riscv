#include <stdio.h>
#include <stdlib.h>
#include "instructions.h"
#include "qol.h"
int main(int argc, char **argv)
{
    __uint32_t buffer;
    int status;
    const char *prog = argv[0];
    while ((status = scanf("%x", &buffer)) == 1)
    {

        InstructionData instruction_data;
        extract_instruction_data(buffer, &instruction_data);
        if (!instruction_data.valid)
        {
            printf("unknown.\n");
        }
        else
        {
            print_instruction(&instruction_data);
        }
    }
    if (status == 0)
    {
        fprintf(stderr, "%s: invalid formatting found.\n", prog);
        exit(EXIT_FAILURE);
    }
    return 0;
}
