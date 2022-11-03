#include <iostream>
#include <cstdlib>
#include <stdio.h>
using namespace std;

#ifndef MAX
#define MAX 10
#endif
#define NUM_MAX 100 

int seed = 456;

typedef struct polynomial{
    unsigned int order;
    int* coeffecient;
}polynomial;

int random_structure_gen(polynomial* poly);
int dividend_gen(polynomial* dividend, polynomial* divisor, polynomial* quotient, polynomial* remainder);

int main(int agrv, char* argc[])
{	
	srand(seed);
	unsigned int i;
	
	polynomial dividend;
    polynomial divisor;
    polynomial quotient;
    polynomial remainder;
    
    divisor.order = (unsigned int) rand() % MAX;
    quotient.order = MAX - divisor.order;
    dividend.order = MAX;
    if(divisor.order == 0) remainder.order = 0;
    else remainder.order = divisor.order - 1;
    
    random_structure_gen(&divisor);
    random_structure_gen(&quotient);
    random_structure_gen(&remainder);
    dividend.coeffecient = (int*) malloc((dividend.order+1)*sizeof(int));
    
    dividend_gen(&dividend, &divisor, &quotient, &remainder);
    
    FILE* input_file;
    input_file = fopen("input.txt", "w");
    for(i = dividend.order; i > 0; i--)
    	fprintf(input_file, "%u ", dividend.coeffecient[i]);
    fprintf(input_file, "%u\n", dividend.coeffecient[0]);
    for(i = divisor.order; i > 0; i--)
    	fprintf(input_file, "%u ", divisor.coeffecient[i]);
    fprintf(input_file, "%u\n", divisor.coeffecient[0]);
    fclose(input_file);
    
    FILE* output_file;
    output_file = fopen("golden.txt", "w");
    for(i = quotient.order; i > 0; i--)
    	fprintf(output_file, "%u ", quotient.coeffecient[i]);
    fprintf(output_file, "%u\n", quotient.coeffecient[0]);
    for(i = remainder.order; i > 0; i--)
    	fprintf(output_file, "%u ", remainder.coeffecient[i]);
    fprintf(output_file, "%u\n", remainder.coeffecient[0]);
    fclose(output_file);
	
	system(".\\0811035.exe input.txt out.txt");
	
	free(divisor.coeffecient);
	free(dividend.coeffecient);
	free(quotient.coeffecient);
	free(remainder.coeffecient);
	
	cout << "SUCCESS";
	return 0;
}

int random_structure_gen(polynomial* poly)
{
	unsigned int i;
	poly->coeffecient = (int*) malloc((poly->order+1)*sizeof(int));
	cout << "order: " << poly->order << "\n";
	for(i = poly->order; i > 0; i--)
	{
		poly->coeffecient[i] = rand() % NUM_MAX;
		cout << poly->coeffecient[i] << " ";
	}
	poly->coeffecient[0] = rand() % NUM_MAX;
	cout << poly->coeffecient[0] << "\n";
	
	return 0;
}

int dividend_gen(polynomial* dividend, polynomial* divisor, polynomial* quotient, polynomial* remainder)
{
	unsigned int i, j;
	for(i = dividend->order; i > 0; i--)
		dividend->coeffecient[i] = 0;
	dividend->coeffecient[0] = 0;
	
	for(i = divisor->order; i > 0; i--)
	{
		for(j = quotient->order; j > 0; j--)
		{
			dividend->coeffecient[i+j] += divisor->coeffecient[i] * quotient->coeffecient[j];
		}
		dividend->coeffecient[i] += divisor->coeffecient[i] * quotient->coeffecient[0];
		dividend->coeffecient[i-1] += remainder->coeffecient[i-1];
	}
	for(j = quotient->order; j > 0; j--)
	{
		dividend->coeffecient[j] += divisor->coeffecient[0] * quotient->coeffecient[j];
	}
	dividend->coeffecient[0] += divisor->coeffecient[0] * quotient->coeffecient[0];
	
	cout << "order: " << dividend->order << "\n";
	for(i = dividend->order; i > 0; i--)
	{
		cout << dividend->coeffecient[i] << " ";
	}
	cout << dividend->coeffecient[0] << "\n";
	
	return 0;
}
