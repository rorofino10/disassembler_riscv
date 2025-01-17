#include <stdio.h>
#include <stdlib.h>
#include "instructions.h"
#include "qol.h"

void set_in_out(FILE **ifp, FILE **ofp, int argc, char **argv)
{
    const char *prog_name = argv[0];

    *ifp = stdin;
    *ofp = stdout;

    switch (argc)
    {
    case 1:
        break;

    case 3:
        if ((*ofp = fopen(argv[2], "w")) == NULL)
        {
            fprintf(stderr, "%s: can't open file %s\n", prog_name, argv[2]);
            exit(EXIT_FAILURE);
        };
    case 2:
        if ((*ifp = fopen(argv[1], "r")) == NULL)
        {
            fprintf(stderr, "%s: can't open file %s\n", prog_name, argv[1]);
            exit(EXIT_FAILURE);
        };
        break;
    default:
        fprintf(stderr, "%s: invalid amount of arguments\n", prog_name);
        exit(EXIT_FAILURE);
        break;
    }
}

int main(int argc, char **argv)
{
    __uint32_t buffer;
    int status;
    const char *prog_name = argv[0];

    FILE *ifp, *ofp;

    set_in_out(&ifp, &ofp, argc, argv);
    while ((status = fscanf(ifp, "%x", &buffer)) == 1)
    {

        InstructionData instruction_data;
        extract_instruction_data(buffer, &instruction_data);
        print_instruction(ofp, &instruction_data);
    }
    if (status == 0)
    {
        fprintf(stderr, "%s: invalid formatting found.\n", prog_name);
    }
    fclose(ifp);
    fclose(ofp);
    return 0;
}
