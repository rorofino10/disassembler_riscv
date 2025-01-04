#include <stdio.h>
#include <stdlib.h>
#include "instructions.h"
#include "qol.h"

int main(int argc, char **argv)
{
    __uint32_t buffer;
    int status;
    const char *prog = argv[0];
    FILE *fp_in = stdin;
    FILE *fp_out = stdout;
    switch (argc)
    {
    case 1:
        break;

    case 3:
        if ((fp_out = fopen(argv[2], "w")) == NULL)
        {
            fprintf(stderr, "%s: can't open file %s\n", prog, argv[2]);
            exit(EXIT_FAILURE);
        };
    case 2:
        if ((fp_in = fopen(argv[1], "r")) == NULL)
        {
            fprintf(stderr, "%s: can't open file %s\n", prog, argv[1]);
            exit(EXIT_FAILURE);
        };
        break;
    default:
        fprintf(stderr, "%s: invalid amount of arguments\n", prog);
        exit(EXIT_FAILURE);
        break;
    }

    while ((status = fscanf(fp_in, "%x", &buffer)) == 1)
    {

        InstructionData instruction_data;
        extract_instruction_data(buffer, &instruction_data);
        print_instruction(fp_out, &instruction_data);
    }
    if (status == 0)
    {
        fprintf(stderr, "%s: invalid formatting found.\n", prog);
    }
    fclose(fp_in);
    fclose(fp_out);
    return 0;
}
