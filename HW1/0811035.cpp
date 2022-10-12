#define debug

#include<stdio.h>
#include<cstdlib>
typedef unsigned char uint8_t;
typedef unsigned int  uint32_t;

template <typename T>
struct polynomial{
    uint32_t order;
    T* coeffecient;
};

template <typename T> int read_polynomial(char* file_name, T dividend, T divisor);
template <typename T> int long_division(T dividend, T divisor, T quotient);
template <typename T> int write_polynomial(char* file_name, T dividend, T divisor, T quotient);

int main(int agrv, char* argc[])
{
    char* input_file = argc[1];
    char* output_file = argc[2];

    polynomial<int> dividend;
    polynomial<int> divisor;
    polynomial<int> quotient;

    read_polynomial(input_file, &dividend, &divisor);
    long_division(&dividend, &divisor, &quotient);
    write_polynomial(output_file, &dividend, &divisor, &quotient);
    
    free(dividend.coeffecient);
    free(divisor.coeffecient);
    free(quotient.coeffecient);
    
    return 0;
}

template <typename T>
int read_polynomial(char* file_name, T dividend, T divisor)
{
    uint32_t i;

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
    dividend->coeffecient = (int*) malloc((dividend->order+1)*sizeof(int));
    divisor ->coeffecient = (int*) malloc((divisor ->order+1)*sizeof(int));

    input_file = fopen(file_name, "r");
    for(i = dividend->order; i > 0; i--)
    {
        fscanf(input_file, "%d", &(dividend->coeffecient[i]));

#ifdef debug
        printf("%d ", dividend->coeffecient[i]);
#endif
    }
    fscanf(input_file, "%d", &(dividend->coeffecient[0]));
#ifdef debug
    printf("%d ", dividend->coeffecient[0]);
    printf("\n");
#endif
    for(i = divisor->order; i > 0; i--)
    {
        fscanf(input_file, "%d", &(divisor->coeffecient[i]));
#ifdef debug
        printf("%d ", divisor->coeffecient[i]);
#endif
    }
	fscanf(input_file, "%d", &(divisor->coeffecient[0]));
#ifdef debug
    printf("%d ", divisor->coeffecient[0]);
    printf("\n");
#endif
    fclose(input_file);

    return 0;
}

template <typename T>
int long_division(T dividend, T divisor, T quotient)
{
    uint32_t i, j;
    quotient->order = dividend->order - divisor->order;
#ifdef debug
    printf("quotient order: %032d\n", quotient->order);
#endif
    quotient->coeffecient = (int*) malloc((quotient->order+1)*sizeof(int));
    
    for(i = 0; i < quotient->order; i++)
    {
        int times;
		times = dividend->coeffecient[dividend->order - i] / 
            divisor->coeffecient[divisor->order];
        for(j = 1; j < divisor->order; j++)
        {
            dividend->coeffecient[dividend->order - i - j] -= 
                times * divisor->coeffecient[divisor->order - j];
        }
        dividend->coeffecient[dividend->order - i - j] -= 
            times * divisor->coeffecient[divisor->order - j];
        quotient->coeffecient[quotient->order - i] = times;
#ifdef debug
        printf("%d ", quotient->coeffecient[quotient->order - i]);
#endif
    }
    int times;
	times = dividend->coeffecient[dividend->order - i] / 
        divisor->coeffecient[divisor->order];
    for(j = 1; j < divisor->order; j++)
    {
        dividend->coeffecient[dividend->order - i - j] -= 
            times * divisor->coeffecient[divisor->order - j];
    }
    dividend->coeffecient[dividend->order - i - j] -= 
        times * divisor->coeffecient[divisor->order - j];
    quotient->coeffecient[quotient->order - i] = times;
#ifdef debug
    printf("%d ", quotient->coeffecient[quotient->order - i]);
    printf("\n");
#endif
    return 0;
}

template <typename T>
int write_polynomial(char* file_name, T dividend, T divisor, T quotient)
{
    uint32_t i;
    FILE* output_file;
    output_file = fopen(file_name, "w");
    
    // Write quotient
#ifdef debug
    printf("quotient order: %032d\n", quotient->order);
#endif
    for(i = quotient->order; i> 0; i--)
    {
        fprintf(output_file, "%d ", quotient->coeffecient[i]);
#ifdef debug
        printf("%d ", quotient->coeffecient[i]);
#endif
    }
	fprintf(output_file, "%d ", quotient->coeffecient[0]);
#ifdef debug
    printf("%d ", quotient->coeffecient[0]);
#endif
    fprintf(output_file, "\n");
#ifdef debug
    printf("\n");
#endif

    // Write remainder
#ifdef debug
    printf("remainder order: %032d\n", divisor->order-1);
#endif
    for(i = divisor->order-1; i > 0; i--)
    {
        fprintf(output_file, "%d ", dividend->coeffecient[i]);
#ifdef debug
        printf("%d ", dividend->coeffecient[i]);
#endif
    }
    fprintf(output_file, "%d ", dividend->coeffecient[i]);
#ifdef debug
    printf("%d ", dividend->coeffecient[i]);
    printf("\n");
#endif

    fclose(output_file);

    return 0;
}
