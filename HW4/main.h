/*
*   function:
*       0: LEAF
*       1: AND
*       2: OR
*       3: NAND
*       4: NOR
*       5: XOR
*       6: XNOR
*/

class tree_node;

class tree_node
{
private:
    int children[10];
    int number_children;
    int function;
    int set_and_one();
    int set_or_one();
    int set_nand_one();
    int set_nor_one();
    int set_xor_one();
    int set_xnor_one();
    int set_and_zero();
    int set_or_zero();
    int set_nand_zero();
    int set_nor_zero();
    int set_xor_zero();
    int set_xnor_zero();
public:
    bool value;
    int neighber[10];
    int number_neighber;
    int index;
    tree_node()
    {
        number_children = 0;
        number_neighber = 0;
        function = 0;
    }
    int set_child(int parent);
    int set_neighber(int this_neighber);
    int set_function(int this_function);
    int get_value();
    int set_one();
    int set_zero();
    int print();
    int isleaf();
};