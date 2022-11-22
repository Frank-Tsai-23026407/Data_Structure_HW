#include "main.h"
#include <stdio.h>

tree_node* tree;

int main(int argc, char* argv[])
{
    FILE* input_file;
    FILE* output_file;
    int number_vertex;
    int degree[10];
    int min_degree = 6;
    int leaf[10];
    int number_leaf = 0;
    int root;
    char this_function[5];
    int this_function_index;
    int temp1, temp2;
    int i;
    bool visited[10];
    bool visited_temp[10];

    // input
    input_file = fopen(argv[1], "r");
    output_file = fopen(argv[2], "w");
    fscanf(input_file, "%d\n", &number_vertex);
    tree = new tree_node [number_vertex];
    for(int i = 0; i < number_vertex; i++) tree[i].index = i;

    for(int i = 0; i < number_vertex - 1; i++)
    {
        fscanf(input_file, "(%d, %d)\n", &temp1, &temp2);
        tree[temp1].set_neighber(temp2);
        tree[temp2].set_neighber(temp1);
    }

    while(fscanf(input_file, "%d", &temp1) != EOF)
    {
        fscanf(input_file, ": %s\n", this_function);
        if     (this_function[0] == 'A') this_function_index = 1;
        else if(this_function[0] == 'O') this_function_index = 2;
        else if(this_function[0] == 'N')
        { 
            if  (this_function[1] == 'A') this_function_index = 3;
            else                          this_function_index = 4;
        }
        else if(this_function[0] == 'X' )
        { 
            if  (this_function[1] == 'O') this_function_index = 5;
            else                          this_function_index = 6;
        }
        tree[temp1].set_function(this_function_index);
    }

    // find degree of each node
    for(int i = 0; i < number_vertex; i++) 
    {
        if(tree[i].isleaf())
        {
            degree[i] = 6;
            leaf[number_leaf++] = i;
        }
        else 
        {
            // initial
            degree[i] = 1;
            for(int j = 0; j < number_vertex; j++)
            {
                if(j == i)
                    visited[j] = 1;
                else
                    visited[j] = 0;
            }
            // propergate
            while(1)
            {
                degree[i]++;
                for(int j = 0; j < number_vertex; j++)
                {
                    visited_temp[j] = visited[j];
                }
                for(int j = 0; j < number_vertex; j++)
                {
                    if(visited_temp[j])
                    {
                        for(int k = 0; k < tree[j].number_neighber; k++)
                        {
                            visited[tree[j].neighber[k]] = 1;
                        }
                    }
                }
                
                int flag = 1;
                for(int j = 0; j < number_vertex; j++)
                {
                    if(visited[j] == 0) flag = 0;
                }
                if(flag == 1) break;
            }
        }
        if(min_degree > degree[i]) min_degree = degree[i];
    }

    for(int i = 0; i < number_vertex; i++)
    {
        if(min_degree == degree[i])
        {
            fprintf(output_file, "root = %d\n", i);
            tree[i].set_child(-1);
            for(int j = 0; j < number_vertex; j++) tree[j].print();

            // set value
            if(tree[i].set_one())
            {
                fprintf(output_file, "UNSAT\n");
            }
            else
            {
                fprintf(output_file, "SAT\n");
                for(int j = 0; j < number_leaf; j++)
                {
                    fprintf(output_file, "%d: %d\n", leaf[j], tree[leaf[j]].value == 0 ? 0 : 1);
                }
            }
        }
    }
}

inline int tree_node::set_neighber(int this_neighber)
{
    neighber[number_neighber++] = this_neighber;
    return 0;
}

inline int tree_node::set_function(int this_function)
{
    function = this_function;
    return 0;
}

inline int tree_node::set_child(int parent)
{
    for(int i = 0; i < number_neighber; i++)
    {
        if(neighber[i] == parent) continue;
        children[number_children++] = neighber[i];
        tree[neighber[i]].set_child(index);
    }
    return 0;
}

inline int tree_node::print()
{
    printf("===============vertex %d================\n", index);
    printf("number of children: %d\n", number_children);
    printf("children: ");
    for(int i = 0; i < number_children; i++) printf("%d ", children[i]);
    printf("\n");
    printf("number of neighber: %d\n", number_neighber);
    printf("neighber: ");
    for(int i = 0; i < number_neighber; i++) printf("%d ", neighber[i]);
    printf("\n");
    printf("function: %d\n", function);
    return 0;
}

inline int tree_node::isleaf()
{
    return function == 0;
}

inline int tree_node::set_one()
{
    switch (function)
    {
        case 0: value = 1; return 0;
        case 1: return set_and_one();
        case 2: return set_or_one();
        case 3: return set_nand_one();
        case 4: return set_nor_one();
        case 5: return set_xor_one();
        case 6: return set_xnor_one();
    }
    return 1;
}

inline int tree_node::set_zero()
{
    switch (function)
    {
        case 0: value = 0; return 0;
        case 1: return set_and_zero();
        case 2: return set_or_zero();
        case 3: return set_nand_zero();
        case 4: return set_nor_zero();
        case 5: return set_xor_zero();
        case 6: return set_xnor_zero();
    }
    return 1;
}

int tree_node::set_and_one()
{
    if(number_children == 1) return tree[children[0]].set_one();
    else
    {
        for(int i = 0; i < number_children; i++)
        {
            if(tree[children[i]].set_one()) return 1;
        }
        return 0;
    }
}

int tree_node::set_or_one()
{
    if(number_children == 1) return tree[children[0]].set_one();
    else
    {
        for(int i = 0; i < number_children; i++)
        {
            if(!tree[children[i]].set_one()) return 0;
        }
        return 1;
    }
}

int tree_node::set_nand_one()
{
    if(number_children == 1) return tree[children[0]].set_zero();
    else
    {
        for(int i = 0; i < number_children; i++)
        {
            if(!tree[children[i]].set_zero()) return 0;
        }
        return 1;
    }
}

int tree_node::set_nor_one()
{
    if(number_children == 1) return tree[children[0]].set_zero();
    else
    {
        for(int i = 0; i < number_children; i++)
        {
            if(tree[children[i]].set_zero()) return 1;
        }
        return 0;
    }
}

int tree_node::set_and_zero()
{
    if(number_children == 1) return tree[children[0]].set_zero();
    else
    {
        for(int i = 0; i < number_children; i++)
        {
            if(!tree[children[i]].set_zero()) return 0;
        }
        return 1;
    }
}

int tree_node::set_or_zero()
{
    if(number_children == 1) return tree[children[0]].set_zero();
    else
    {
        for(int i = 0; i < number_children; i++)
        {
            if(tree[children[i]].set_zero()) return 1;
        }
        return 0;
    }
}

int tree_node::set_nand_zero()
{
    if(number_children == 1) return tree[children[0]].set_one();
    else
    {
        for(int i = 0; i < number_children; i++)
        {
            if(tree[children[i]].set_one()) return 1;
        }
        return 0;
    }
}

int tree_node::set_nor_zero()
{
    if(number_children == 1) return tree[children[0]].set_one();
    else
    {
        for(int i = 0; i < number_children; i++)
        {
            // one of them is one
            if(!tree[children[i]].set_one()) return 0;
        }
        return 1;
    }
}

int tree_node::set_xor_one()
{
    if(number_children == 1) return 1;
    int temp[10] = {0};
    int acc = 0;
    for(int i = 0; i < number_children; i++)
    {
        if(tree[children[i]].set_zero())
        { 
            temp[i] = 1;
            acc += 1;
        }
    }
    if(acc % 2 == 1) return 0;
    for(int i = 0; i < number_children; i++)
    {
        if(temp[i] == 0)
        {
            if(!tree[children[i]].set_one()) return 0;
        }
    }
    return 1;
}

int tree_node::set_xor_zero()
{
    if(number_children == 1) return 0;
    int temp[10] = {0};
    int acc = 0;
    for(int i = 0; i < number_children; i++)
    {
        if(tree[children[i]].set_zero())
        { 
            temp[i] = 1;
            acc += 1;
        }
    }
    if(acc % 2 == 0) return 0;
    for(int i = 0; i < number_children; i++)
    {
        if(temp[i] == 0)
        {
            if(!tree[children[i]].set_one()) return 0;
        }
    }
    return 1;
}

int tree_node::set_xnor_one()
{
    return set_xor_zero();
}

int tree_node::set_xnor_zero()
{
    return set_xor_one();
}