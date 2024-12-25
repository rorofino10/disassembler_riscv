#include <stdio.h>
#include <stdlib.h>
#include "instructions.h"
#include "qol.h"
int main(int argc, char **argv)
{
    __uint32_t buffer;
    int status;
    while ((status = scanf("%x", &buffer)) == 1)
    {

        InstructionData instruction_data;
        extract_instruction_data(buffer, &instruction_data);
        if (!instruction_data.valid)
        {
            SET_RED_COUT();
            printf("ERROR"); // Display ERROR in red
            SET_DEFAULT_COUT();
            printf("Invalid instruction found.\n");
            // exit(EXIT_FAILURE);
        }
        else
        {
            print_instruction(&instruction_data);
        }
    }
    if (status == 0)
    {
        SET_RED_COUT();
        printf("ERROR"); // Display ERROR in red
        SET_DEFAULT_COUT();
        printf("Invalid formatting\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}
