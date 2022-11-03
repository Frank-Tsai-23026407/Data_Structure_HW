#include <stdio.h>
#include "qm.h"
#include "stack.h"

int main()
{
    // declaration
    FILE *input_file, *output_file;
    implements imp, imp2, imp3;
    int size, temp, index;
    stack<implements> *remain;
    stack<implements>  output;
    stack<implements>  s_temp;
    stackIterater<implements> iterater;
    int flag, combination_times;

    // open file
    input_file = fopen("input.txt", "r");
    output_file = fopen("output.txt", "w");
    fscanf(input_file, "%d", &size);
    remain = new stack<implements>[size+1];

    printf("%d ", output.isEmpty());
    output.push(imp);
    printf("%d ", output.isEmpty());
    output.pop(imp);
    printf("%d ", output.isEmpty());

    // // read imlements
    // while(fscanf(input_file, "%*c%d", &temp) != EOF)
    // {
    //     imp.generate(size);
    //     imp.set_value(temp);
    //     remain[imp.num_one()].push(imp);
    // }

    // // Initial Grouping
    // fprintf(output_file, "Initial Grouping\n");
    // for(int i = 0; i <= size; i++)
    // {
    //     fprintf(output_file, "%d: ", i);
    //     remain[i].fprint(output_file);
    // }

    // Combination
    // flag = 1;
    // combination_times = 0;
    // while (flag)
    // {
    //     combination_times ++;
    //     flag = 0;  // no combination
    //     printf("Combination %d\n", combination_times);
    //     for(int i = 0; i < size - combination_times; i++)
    //     {
    //         printf("clear\n");
    //         s_temp.clear();
    //         s_temp.print();
    //         iterater.iterater(remain[i+1]);
    //         while (remain[i].pop(imp))
    //         {
    //             printf("pop\n");
    //             iterater.re();
    //             while(iterater.next(imp2))
    //             {
    //                 if(imp.similar(imp2, index))
    //                 {
    //                     imp3.generate_and_copy(imp);
    //                     imp3.set_element(index, '-');
    //                     s_temp.push(imp3);
    //                     flag = 1; // here is combination
    //                     imp2.implemented = true;
    //                 }
    //             }
    //             // check if element is implemented;
    //             if(imp.implemented)
    //             {
    //                 imp.~implements();
    //             }
    //             else
    //             {
    //                 output.push(imp);
    //             }
    //             s_temp.print();
    //             printf("\n");
    //             remain[i].inherient(s_temp);
    //         }
    //     }
    //     while (remain[size - combination_times].pop(imp))
    //     {
    //         // check if element is implemented;
    //         if(imp.implemented)
    //         {
    //             imp.~implements();
    //         }
    //         else
    //         {
    //             output.push(imp);
    //         }
    //     }
        // if(flag)
        // {
        //     // fprintf(output_file, "Combination %d\n", combination_times);
        //     printf("Combination %d\n", combination_times);
        //     for(int i = 0; i <= size; i++)
        //     {
        //         printf("%d: ", i);
        //         remain[i].print();
        //         // fprintf(output_file, "%d: ", i);
        //         // remain[i].fprint(output_file);
        //     }
        // }
    //}
    return 0;
}