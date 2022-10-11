// #define debug

#include<stdio.h>
#include<cstdlib>
typedef unsigned char uint8_t;
typedef unsigned int  uint32_t;

template <typename T>
struct polynomial{
    uint32_t order;
    T* coeffecient;
};

int read_polynomial(char* file_name, polynomial<float>* dividend, polynomial<float>* divisor);
int long_division(polynomial<float>* dividend, polynomial<float>* divisor, polynomial<float>* quotient);
int write_polynomial(char* file_name, polynomial<float>* dividend, polynomial<float>* divisor, polynomial<float>* quotient);

int main(int agrv, char* argc[])
{
    char* input_file = argc[1];
    char* output_file = argc[2];

    polynomial<float> dividend;
    polynomial<float> divisor;
    polynomial<float> quotient;

    read_polynomial(input_file, &dividend, &divisor);
    long_division(&dividend, &divisor, &quotient);
    write_polynomial(output_file, &dividend, &divisor, &quotient);
}

int read_polynomial(char* file_name, polynomial<float>* dividend, polynomial<float>* divisor)
{
    int i;

    dividend->order = 0;
    divisor->order  = 0;

    // Read order of polynomial
    FILE* input_file;
    input_file = fopen(file_name, "rb");
    char input_char;
    while(fscanf(input_file, "%c", &input_char)!=EOF)
    {
        if(input_char == ' ') dividend->order++;
        if(input_char == '\n') break;
    }
    while(fscanf(input_file, "%c", &input_char)!=EOF)
    {
        if(input_char == ' ') divisor->order++;
        if(input_char == '\n') break;
    }
    fclose(input_file);

#ifdef debug
    printf("dividend order: %032d\n", dividend->order);
    printf("divisor  order: %032d\n", divisor ->order);
#endif

    // Read coefficient of polynomial
    dividend->coeffecient = (float*) malloc((dividend->order+1)*sizeof(float));
    divisor ->coeffecient = (float*) malloc((divisor ->order+1)*sizeof(float));

    input_file = fopen(file_name, "r");
    for(i = dividend->order; i >= 0; i--)
    {
        fscanf(input_file, "%f", &(dividend->coeffecient[i]));

#ifdef debug
        printf("%f ", dividend->coeffecient[i]);
#endif
    }
#ifdef debug
    printf("\n");
#endif
    for(i = divisor->order; i >= 0; i--)
    {
        fscanf(input_file, "%f", &(divisor->coeffecient[i]));
#ifdef debug
        printf("%f ", divisor->coeffecient[i]);
#endif
    }
#ifdef debug
    printf("\n");
#endif
    fclose(input_file);

    return 0;
}

int long_division(polynomial<float>* dividend, polynomial<float>* divisor, polynomial<float>* quotient)
{
    int i, j;
    quotient->order = dividend->order - divisor->order;
#ifdef debug
    printf("quotient order: %032d\n", quotient->order);
#endif
    quotient->coeffecient = (float*) malloc((quotient->order+1)*sizeof(float));
    
    for(i = 0; i <= quotient->order; i++)
    {
        float times = dividend->coeffecient[dividend->order - i] / 
            divisor->coeffecient[divisor->order];
        for(j = 1; j <= divisor->order; j++)
        {
            dividend->coeffecient[dividend->order - i - j] -= 
                times * divisor->coeffecient[divisor->order - j];
        }
        quotient->coeffecient[quotient->order - i] = times;
#ifdef debug
        printf("%f ", quotient->coeffecient[quotient->order - i]);
#endif
    }
#ifdef debug
    printf("\n");
#endif
    return 0;
}

int write_polynomial(char* file_name, polynomial<float>* dividend, polynomial<float>* divisor, polynomial<float>* quotient)
{
    int i;
    FILE* output_file;
    output_file = fopen(file_name, "w");
    
    // Write quotient
#ifdef debug
    printf("quotient order: %032d\n", quotient->order);
#endif
    for(i = quotient->order; i>= 0; i--)
    {
        fprintf(output_file, "%f ", quotient->coeffecient[i]);
#ifdef debug
        printf("%f ", quotient->coeffecient[i]);
#endif
    }
    fprintf(output_file, "\n");
#ifdef debug
    printf("\n");
#endif

    // Write remainder
#ifdef debug
    printf("remainder order: %032d\n", divisor->order-1);
#endif
    for(i = divisor->order-1; i>= 0; i--)
    {
        fprintf(output_file, "%f ", dividend->coeffecient[i]);
#ifdef debug
        printf("%f ", dividend->coeffecient[i]);
#endif
    }
#ifdef debug
    printf("\n");
#endif

    fclose(output_file);

    return 0;
}