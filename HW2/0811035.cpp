#include <stdio.h>
#include "stack.cpp"

int getname(char* name, int capacity, FILE* file)
{
	int i;
	char c;
	for(i = 0; i < capacity; i++)
	{
		c = fgetc(file);
		if(c == EOF) {
			name[i] = '\0';
			return 0;
		}
		else if(c == '\n') {
			name[i] = '\0';
			return 0;
		}
		else if(c == 13) {
			name[i] = '\0';
		}
		else
			name[i] = c;
	}
	return 1;
}

int main(int argc, char* argv[])
{
	printf("===== input pash =====\n");
    // --------------------------------------
    // declaration
    // --------------------------------------
    FILE *input_file, *output_file;
    int city_num;
    int path_num;
    int i;
    int destination = -1;
    char destination_name[1000] = {0};
    CITY* city_list;
    STACK stack(1000);
    int status = 0;
    int this_index;
    int cost;

    // --------------------------------------
    // open file
    // --------------------------------------
    input_file = fopen(argv[1], "r");
    if(input_file == NULL) printf("Cannot open input file\n");
    output_file = fopen(argv[2], "w");
    if(input_file == NULL) printf("Cannot open output file\n");

    // --------------------------------------
    // read file
    // --------------------------------------
    fscanf(input_file, "%d\n", &city_num);
    printf("Number of city: %d\n", city_num);
    city_list = new CITY[city_num];
    for(i = 0; i < city_num; i++)
    {
        
        getname(city_list[i].name, 1000, input_file);
        city_list[i].index = i;
        city_list[i].num_direction = 0;
        printf("city %05d: %s\n", city_list[i].index, city_list[i].name);
    }

    fscanf(input_file, "%d\n", &path_num);
    printf("Number of path: %d\n", path_num);
    for(i = 0; i < path_num; i++)
    {
        int this_source, this_direction, this_cost;
        fscanf(input_file, "%d %d %d\n", &this_source, &this_direction, &this_cost);
        printf("source:%05d destination:%05d cost:%05d\n", this_source, this_direction, this_cost);
        city_list[this_source].direction[city_list[this_source].num_direction++] = this_direction;
        city_list[this_direction].source = this_source;
        city_list[this_direction].cost = this_cost;
    }

    getname(destination_name, 1000, input_file);
    printf("%s\n", destination_name);
    for(i = 0; i < city_num; i++)
    {
    	int j;
    	int same = 1;
        for(j = 0; j < 1000; j++)
        {
        	if(destination_name[j] != city_list[i].name[j])
        	{
        		same = 0;
        		break;
        	}
        	if(destination_name[j] == '\0')
        		break;
		}
        if(same) destination = i;
    }
    printf("destination name: %s\ndestination number: %d\n", destination_name, destination);
    fclose(input_file);

    // --------------------------------------
    // check struct
    // --------------------------------------
    for(i = 0; i < city_num; i++)
    {
    	printf("CITY INDEX:%04d SOURCE:%04d DES_NUM:%04d DES:", city_list[i].index, city_list[i].source, city_list[i].num_direction);
        for(int j=0; j < city_list[i].num_direction; j++)
        {
            printf("%d ",city_list[i].direction[j]);
        }
        printf("\n");
    }

    // --------------------------------------
    // operation
    // --------------------------------------
    printf("\n===== operation =====\n");
    stack.push(0);
    fprintf(output_file, "pop %d\n", 0);
    printf("push %d\n", 0);
    while(stack.top()!=destination)
    {
        if(stack.isEmpty())
        {
            fprintf(output_file, "-1\n");
            fclose(output_file);
            return -1;
        }
        this_index = stack.pop();
        printf("pop %d\n", this_index);
        fprintf(output_file, "pop %d\n", this_index);
        for(i = 0; i < city_list[this_index].num_direction; i++)
        {
            stack.push(city_list[this_index].direction[i]);
            fprintf(output_file, "push %d\n", city_list[this_index].direction[i]);
            printf("push %d\n", city_list[this_index].direction[i]);
        }
    }
    
    // --------------------------------------
    // count cost
    // --------------------------------------
    cost = 0;
    this_index = stack.top();
    while(this_index != 0)
    {
    	cost += city_list[this_index].cost;
    	this_index = city_list[this_index].source;
	}
	fprintf(output_file, "%d", cost);
    printf("cost %d\n", cost);
    
    fclose(output_file);

    return 0;
}
