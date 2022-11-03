#include <stdio.h>
#include "qm.h"
#include "stack.h"

int main()
{
    // declaration
    FILE *input_file, *output_file;
    implements i;
    int size, temp;
    stack<implements> *remain;
    stack<implements>  output;
    int flag, combination_times;

    // open file
    input_file = fopen("input.txt", "r");
    output_file = fopen("output.txt", "w");
    fscanf(input_file, "%d", &size);
    remain = new stack<implements>[size+1];

    // read imlements
    while(fscanf(input_file, "%*c%d", &temp) != EOF)
    {
        i.generate(size);
        i.set_value(temp);
        remain[i.num_one()].push(i);
    }

    // Initial Grouping
    fprintf(output_file, "Initial Grouping\n");
    for(int i = 0; i <= size; i++)
    {
        fprintf(output_file, "%d: ", i);
        remain[i].fprint(output_file);
    }

    // Combination
    flag = 1;
    combination_times = 1;
    while (flag)
    {
        flag = 0;  // no combination
        for(int i = 0; i <= size; i++)
        {
            // iterater
        }
    }
    

    return 0;
}