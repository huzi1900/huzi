#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int main (int argc,char *argv[])
{ 
  if(argc==1){
     printf("please input a directory\n");
     exit(EXIT_FAILURE);
  }
  DIR *dp;
  if((dp=opendir(argv[1]))==NULL) {
    printf("can't open:%s\n",argv[1]);
    exit(EXIT_FAILURE);
  }
  struct dirent *entry;
  while((entry=readdir(dp))!=NULL){
       if(*(entry->d_name)=='.'){
           continue;
           }
       char path[30]="";
        strcat(path,argv[1]);
        strcat(path,entry->d_name);
       struct stat buf;
       if (stat(path,&buf)!=0){
            printf("can't get status.\n");
            continue;
            }
       char str[11];
       strcpy(str,"----------");
       if(buf.st_mode & S_IFDIR)   str[0]='d';
       if(buf.st_mode & S_IFCHR)   str[0]='c';
       if(buf.st_mode & S_IFBLK)   str[0]='b';
      
       if(buf.st_mode & S_IRUSR)   str[1]='r';
       if(buf.st_mode & S_IWUSR)   str[2]='w';
       if(buf.st_mode & S_IXUSR)   str[3]='x';

       if(buf.st_mode & S_IRGRP)   str[4]='r';
       if(buf.st_mode & S_IWGRP)   str[5]='w';
       if(buf.st_mode & S_IXGRP)   str[6]='x';

       if(buf.st_mode & S_IROTH)   str[7]='r';
       if(buf.st_mode & S_IWOTH)   str[8]='w';
       if(buf.st_mode & S_IXOTH)   str[9]='x';
       
       str[10]='\0';
       printf("%-12s",str);
       printf("%-4d",(int)buf.st_nlink);
       struct passwd *password;
        password=getpwuid(buf.st_uid);
        struct group *gr;
        gr=getgrgid(buf.st_gid);
       printf("%-8s",password->pw_name);
       printf("%-8s",gr->gr_name);
       printf("%-8ld",(long)buf.st_size);
        printf("%-16s",(entry->d_name));
       printf("%s\n",ctime(&buf.st_mtim));
      
     }
 closedir(dp);
 exit(EXIT_SUCCESS);
}

