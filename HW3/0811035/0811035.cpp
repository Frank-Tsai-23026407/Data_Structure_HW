#include <stdio.h>
#include "qm.h"
#include "stack.h"

int main(int argc, char* argv[])
{
    // declaration
    FILE *input_file, *output_file;
    implements imp, imp3;
    implements *p_imp, *p_imp2;
    int size, temp, index;
    stack<implements> *remain;
    stack<implements>  output;
    stack<implements>  s_temp;
    stackIterater<implements> iterater, iterater1;
    int flag, combination_times;

    // open file
    input_file = fopen(argv[1], "r");
    output_file = fopen(argv[2], "w");
    fscanf(input_file, "%d", &size);
    remain = new stack<implements> [size+1];

    // read imlements
    while(fscanf(input_file, "%*c%d", &temp) != EOF)
    {
        imp.generate(size);
        imp.set_value(temp);
        remain[imp.num_one()].push(imp);
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
    combination_times = 0;
    while (flag)
    {
        combination_times ++;
        flag = 0;  // no combination
        for(int i = 0; i <= size - combination_times; i++)
        {
            iterater.iterater(remain[i+1]);
            while (remain[i].pop(imp))
            {
                iterater.re();
                while(iterater.next(&p_imp))
                {
                    if(imp.similar(*p_imp, index))
                    {
                        imp3.generate_and_copy(imp);
                        imp3.set_element(index, '-');
                        int exist = 0;
                        iterater1.iterater(s_temp);
                        while(iterater1.next(&p_imp2)) if(*p_imp2==imp3) exist = 1;
                        if(! exist) s_temp.push(imp3);
                        flag = 1; // here is combination
                        imp .implemented = true;
                        p_imp->implemented = true;
                    }
                }
                // check if element is implemented;
                if(imp.implemented)
                {
                    imp.~implements();
                }
                else
                {
                    output.push(imp);
                }
            }
            remain[i].inherient(s_temp);
        }
        while (remain[size - combination_times + 1].pop(imp))
        {
            // check if element is implemented;
            if(imp.implemented)
            {
                imp.~implements();
            }
            else
            {
                output.push(imp);
            }
        }
        if(flag)
        {
            fprintf(output_file, "Combination %d\n", combination_times);
            for(int i = 0; i <= size; i++)
            {
                fprintf(output_file, "%d: ", i);
                remain[i].fprint(output_file);
            }
        }
    }
    fprintf(output_file, "Prime Implicants\n");
    output.fprint(output_file);

    imp .clear();
    imp3.clear();

    return 0;
}