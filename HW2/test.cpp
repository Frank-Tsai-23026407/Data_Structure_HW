/* fgets example */
#include <stdio.h>

int main()
{
   FILE * pFile;
   char mystring [100];

   pFile = fopen ("input.txt" , "r");
   if (pFile == NULL) perror ("Error opening file");
   else {
     if ( fgets (mystring , 100 , pFile) != NULL )
       printf("%s", mystring);
     fclose (pFile);
   }
   return 0;
}