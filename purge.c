#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <string.h>



void readFolder(char* folder)
{
  DIR *rep = opendir("./temp");
  if(rep != NULL)
  {
    struct dirent *lecture;
    while (lecture = readdir(rep))
    {
      char* name = lecture->d_name;
      char base[50] = "./temp/";
      char* nametemp = strcat(base, name);

      struct stat s;
      stat(nametemp, &s);
      struct tm *p;
      time_t fff = s.st_mtime;
      p = localtime(&fff); 

      time_t tfile = mktime(p);
      time_t now = time(NULL);
      if(name != ".." && name != "."&& difftime(now, fff) > 259200)
      {
	printf("modified: %uh %umin %usec le %u/%u/%u, ", p->tm_hour, p->tm_min, p->tm_sec, p->tm_mday, p->tm_mon, p->tm_year);
	printf(" deleted  %s ", /*remove(nametemp)*/ name);
	printf("diff %f \n", difftime(now, fff));

      }

    }
    closedir(rep);


  }

}


int main(int argc, char* argv)
{
    int next = 1;
    while(next)
    {
      FILE *stream = fopen("config", "r");
      if(stream == NULL)
      {
	printf("config file not found");
	return 0;
      }
      else
      {
	char c[6];
	fgets(c, 6, stream);
	if(*c !='s' )
	{
	  next = 0;
	  printf("Stop was order: '%s' ", c);
	  
	}
	
	
      }
        fclose(stream);
	printf("readFolder started\n");
	readFolder("./temp");
        sleep(2);
    }

  
  FILE *conf = fopen("config", "w");
  fputs("start", conf);
  fclose(conf);
  return 0;
}


