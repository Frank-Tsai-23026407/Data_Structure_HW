#include <stdio.h>
#include <stdlib.h>

typedef struct CITY
{
    unsigned int index;
    char name[100];
    unsigned char visit;
} CITY;

typedef struct PATH
{
    unsigned int source_city_index;
    unsigned int destination_city_index;
    unsigned int distance;
} PATH;

int getcity(FILE* input_file, CITY* city_list, int city_number)
{
    int i;
    for(i = 0; i < city_number; i++)
    {
        city_list[i].index = i;
        fgets(city_list[i].name, 100, input_file);
    }
    return 0;
}

int getpath(FILE* input_file, PATH* path_list, int path_number)
{
    int i;
    path_list = (PATH*) malloc (path_number*sizeof(PATH));
    for(i = 0; i < path_number; i++)
    {
        fscanf(input_file, "%u %u %u", 
            &path_list[i].source_city_index, 
            &path_list[i].destination_city_index,
            &path_list[i].distance);
    }
    return 0;
}

int getdestiantion(CITY* city_list, unsigned int* destination_index)