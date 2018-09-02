#include <sys/types.h>
#include "help.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include<termios.h>
#include<string>
#include<vector>
#include <dirent.h>
#include <pwd.h>
#define GetCurrentDir getcwd
#include<grp.h>
using namespace std;
string buff = ".";
string command="";
static struct termios initial_settings, new_settings;
void canon(vector<direct *> entries);
void init_keyboard();
void close_keyboard();
std::string GetCurrentWorkingDir( void ) {
  char home[FILENAME_MAX];
  GetCurrentDir( home, FILENAME_MAX );
  std::string current_working_dir(home);
  return current_working_dir;
}
int main()
{
	
	printf("\x1b[2J\x1b[1;1H");
 	   int n=0;
 	   std::vector<std::string> v;
 	   vector<direct *> entries;
 	   struct Stack s1,s2;
	enter(buff,entries,1,20);
	n=entries.size();
	string home =GetCurrentWorkingDir();
	buff=home;
	enter(buff,entries,1,20);
	string ss =home;
	printf("\033[1;1H");
int x=1,y=20,p=1;
int c=0;
init_keyboard();
while(1){
	c=getchar();
	switch(c){
		case 65:{
			if(p>x){
			p--;
			printf("\033[%d;1H",p-x+1);			
		}else if(p>1){
			p--;
			x--;
			y--;
			enter(buff,entries,x,y);
			printf("\033[1;1H");
		}
		break;
		}
		case 66:{
			if(p<y){
			p++;
			printf("\033[%d;1H",p-x+1);
		}else if(p>=y && p<n){
			p++;
			y++;
			x++;
			enter(buff,entries,x,y);
		 printf("\033[20;1H");
		}
		break;
		}
		case 10: {
			chdir(buff.c_str());
			s1.push(buff);
    		if(entries[p-1]->d_type==DT_DIR){
    			s1.push(buff); 
    			buff=ss+"/"+entries[p-1]->d_name;
			ss=buff;
			x=1;
			y=20;
			p=1;
			enter(buff,entries,1,20);
			n=entries.size();
			if(n<20)
				y=n;
			printf("\033[1;1H");
            			}
    		else{
    			pid_t pin;
				pin=fork();
				if(pin==0){
					string shut=entries[p-1]->d_name;
				execl("usr/bin/xdg-open","xdg-open",shut.c_str(),NULL);
				exit(1);
				}
    			}
			chdir("..");
			break;
		}
		case 'h':{
			s1.push(buff);
			x=1;
			p=1;
			y=20;
			ss=home;
			buff=ss;
			enter(ss,entries,1,20);
			n=entries.size();
			if(n<20)
				y=n;
			printf("\033[1;1H");
			break;
		}
		case ':':{
			break;
		}
		case 68:{
			if(!s1.isEmpty()){
				s2.push(buff);
			buff=s1.pop();
			chdir(buff.c_str());
			x=1;
			p=1;
			y=20;
			enter(buff,entries,1,20);
			n=entries.size();
			if(n<20)
				y=n;
			printf("\033[1;1H");
			}
			break;
		}
		case 67:{
			if(!s2.isEmpty()){
				s1.push(buff);
				buff=s2.pop();
				chdir(buff.c_str());
				x=1;
			y=20;
			p=1;
			enter(buff,entries,1,20);
			n=entries.size();
			if(n<20)
				y=n;
			printf("\033[1;1H");
			}
			break;
		}
		case 127:{
			s1.push(buff);
			buff=buff+"/..";
			chdir(buff.c_str());
			x=1;
			p=1;
			y=20;
			enter(buff,entries,1,20);
			n=entries.size();
			if(n<20)
				y=n;
			printf("\033[1;1H");
			break;
		}
		case 'q': break;
	}
	if(c==':'){
		canon(entries);
		p=x;
	}
	if(c=='q')
		break;
}
close_keyboard();
}
void init_keyboard()
{
tcgetattr(0,&initial_settings);
new_settings = initial_settings;
new_settings.c_lflag &= ~ICANON;
new_settings.c_lflag &= ~ECHO;
tcsetattr(0, TCSANOW, &new_settings);
}
void close_keyboard()
{
tcsetattr(0, TCSANOW, &initial_settings);
}
void canon(vector<direct *> entries){
	printf("\033[25;1H");
	while(1){
		int s=getchar();
		int len,flag=0;
		if(s==127){
			len=command.size();
			command=command.substr(0,len-1);
		}else if(s==27){
			printf("\033[1;1H");
			return;
		}else if(s==10){
			flag=1;
			string str;
			vector<string> task;
			int i=0;
			len=command.size();
			while(i<len){
				str="";
			while(command[i]!=' ' && i<len){
				str=str+command[i];
				i++;
			}
			task.push_back(str);
			i++;
		}
			printf("\033[25;1H");
			perform(task,entries);
		}else{
			command=command+(char)s;
		}
		if(flag==0)	{
			printf("\033[25;1H");
			printf("\033[2K");
			printf("%s",command.c_str());
		}	
	}
}