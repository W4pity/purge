#include <stdlib.h>
#include <stdio.h>

int main ()
{
  FILE* stream = fopen("config", "w");
 fputs("done", stream); 
printf("Stopped \n");  
  fclose(stream);
}

