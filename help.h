#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include<termios.h>
#include<cstring>
#include <sys/dir.h>
#include<vector>
#include <dirent.h>
#include <pwd.h>
#include<grp.h>
#include<iostream>
using namespace std;
 
#define MAX 1000
 
class Stack
{
    int top;
public:
    string a[MAX];   
    Stack()  { top = -1; }
    bool push(string x);
    string pop();
    bool isEmpty();
};
 
bool Stack::push(string x)
{
        a[++top] = x;
        return true;
    
}
 
string Stack::pop()
{
        string x = a[top--];
        return x;
}
 
bool Stack::isEmpty()
{
    return (top < 0);
}
void enter(string & dirname, vector<direct *> & entries,int x, int y){
	 direct ** darray;
	 entries.clear();
	 struct stat fileStat;
    int entryCount=scandir(dirname.c_str(), &darray, 0, alphasort);
    for(int k=0; k < entryCount; k++) {
    entries.push_back(darray[k]); }
    printf("\x1b[2J\x1b[1;1H");  
    for(unsigned k=x-1; k < entries.size() && k < y; k++) {
  	  	char *c;
  	  	string newpath = dirname+"/"+entries[k]->d_name;
  	  		stat(newpath.c_str(),&fileStat);  
  	  		 printf("%d %-25s",k+1,entries[k]->d_name);
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-"); 
    printf("\t");
    struct passwd *pw=getpwuid(fileStat.st_uid);
    printf("%-10s ",pw->pw_name);
    struct group *gp=getgrgid(fileStat.st_gid);
    printf("%-10s ",gp->gr_name);
    printf("%-5d",fileStat.st_size);
    //printf("\t");
        c=ctime(&fileStat.st_mtime);
    for(int i=4;i<=15;i++)
      printf("%c",c[i]);
  printf("\n");
  	  }
    //printf("\033[1;1H");
    //printf("%-40s%-10s\t\t%-30s %-10s \t%s\n\n","Name","Permissions","owner and group name","file size","last modified");
}
void createf(vector<string> task);
void perform(vector<string> task){
	if(task[0]=="createf"){
		createf(task);
	}
}
void createf(vector<string> task){
	int len=task.size();
	string file=task[len-1];
	for(int i=1;i<len-1;i++){
		 fopen(task[i].c_str(), "w");
	}
}

