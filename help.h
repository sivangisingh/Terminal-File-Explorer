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
  	  		string fuc=entries[k]->d_name;
  	  		if(fuc.length()>19){
  	  			fuc=fuc.substr(0,18);
  	  			fuc=fuc+"..";
  	  		}
  	  		if(entries[k]->d_type==DT_DIR){
  	  		 printf("%d \033[1;34m %-24s\033[0m",k+1,fuc.c_str());
  	  		}else{
  	  			printf("%d %-24s",k+1,fuc.c_str());
  	  		}
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
    if(fileStat.st_size>10000)
    	fileStat.st_size=fileStat.st_size%10000;
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
void perform(vector<string> task,vector<direct *> & entries){
	if(task[0]=="create_file"){
		createf(task);
	}else if(task[0]=="create_dir"){
		string don=task[2]+"/"+task[1];
		printf("\033[2K");
		mkdir(don.c_str(),NULL);
		printf("\033[5;31m Diretory created\033[0m");
	}else if(task[0]=="goto"){
		enter(task[1],entries,1,20);
	}else if(task[0]=="delete_file"){
		remove(task[1].c_str());
		printf("\033[2K");
		printf("\033[5;31m File deleted\033[0m");
	}
	task.clear();
}
void createf(vector<string> task){
	int len=task.size();
	string file=task[len-1];
	string f;
	chdir(file.c_str());
	for(int i=1;i<len-1;i++){
		f=file+"/"+task[i];
		 fopen(f.c_str(), "w");
	}
	chdir("..");
	printf("\033[25;1H");
			printf("\033[2K");
			//cout<<f;
			printf("\033[5;31m File(s) created\033[0m");
}

