#ifndef _QM_H
#define _QM_H

#include <stdio.h>

// typedef enum{
//     one         = '1',
//     zero        = '0',
//     donotcare   = '-'
// }ELEMENT;
typedef char ELEMENT;

class implements
{
private: 
    bool builded;
    int length;
    ELEMENT* element;
    bool implemented;    
public:
    implements();
    ~implements();
    int generate(int size);
    int set_value(int value);
    int set_element(int index, ELEMENT value);
    bool operator==(implements& t);
    bool similar(implements &t, int &index);
    int print();
    int num_one();
    int fprint(FILE *file);
};

#endif