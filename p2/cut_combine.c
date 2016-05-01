#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
long length_lseek();

int main()
{
int handle;
int handle1;
int wr1;
int wr2;
long i;
int off_set;
long length;
char c;
handle=open("file.dat",O_RDWR);
wr1=open("file.0",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
wr2=open("file.1",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
handle1=open("file.dat1",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
length=length_lseek();
length=length/2;
for(i=0;i<length;i++){
		read(handle,&c,1);
		write(wr1,&c,1);
}
lseek(handle,0,SEEK_CUR);
while(read(handle,&c,1) == 1)
      write(wr2,&c,1);
  while(read(wr1,&c,1)==1)
  	write(handle1,&c,1);
  lseek(handle1,0,SEEK_CUR);
  while(read(wr1,&c,1)==1)
  	write(handle1,&c,1);
exit(0);
}

long length_lseek()
{  long n;
   int fid;
	fid=open("file.dat",O_RDONLY);
	n=lseek(fid,0,SEEK_END);
	close(fid);
	return n;
}

