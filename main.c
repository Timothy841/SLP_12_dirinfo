#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

int main(int argc, char *argv[]){
  DIR *d = 0;
  struct dirent *dent;
  struct stat file;
  int size = 0;
  char s[100];
  if (argc>1){
  	d = opendir(argv[1]);
  }
  else{
  	errno = 2;
  }
  while (d == 0){
  	printf("No such directory or no input. Try again\n");
  	read(STDIN_FILENO, &s, sizeof(s)-1);
  	sscanf(s,"%s\n",s);
  	d = opendir(s);
  }
  while (1){
    dent = readdir(d);
    if (dent==0){
      break;
    }
    stat(dent->d_name, &file);
    size += file.st_size;
  }
  printf("total size: %d\n\n", size);
  rewinddir(d);
  printf("Directories:\n");
  while (1){
    dent = readdir(d);
    if (dent==0){
      break;
    }
    stat(dent->d_name, &file);
    if (S_ISDIR(file.st_mode)){
      printf("permission:%o\t size:%ld\t name:%s\t %s", file.st_mode, file.st_size, dent->d_name, ctime(&(file.st_atime)));
    }
  }
  rewinddir(d);
  printf("\nFiles:\n");
  while (1){
    dent = readdir(d);
    if (dent==0){
      break;
    }
    stat(dent->d_name, &file);
    if (S_ISREG(file.st_mode)){
      printf("permission:%o\t size:%ld\t name:%s\t %s", file.st_mode, file.st_size, dent->d_name, ctime(&(file.st_atime)));
    }
  }
  closedir(d);
  return 0;
}
