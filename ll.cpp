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
void canon();
void init_keyboard();
void close_keyboard();
int main()
{
	//char buff[FILENAME_MAX];
  //GetCurrentDir( buff, FILENAME_MAX );
	printf("\x1b[2J\x1b[1;1H");
 	   int n=0;
 	   std::vector<std::string> v;
 	   vector<direct *> entries;
 	   struct Stack s1;
	enter(buff,entries,1,20);
	n=entries.size();
	string ss ="/home/shivangi/";
	string home ="/home/shivangi/";
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
		    s1.push(buff); 
			buff=ss+"/"+entries[p-1]->d_name;
			//s.push(buff);
			ss=buff;
			x=1;
			y=20;
			p=1;
			enter(buff,entries,1,20);
			n=entries.size();
			//buff=buff+"/..";
			printf("\033[1;1H");
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
			printf("\033[1;1H");
			break;
		}
		case ':':{
			break;
		}
		case 68:{
			buff=s1.pop();
			x=20;
			y=1;
			enter(buff,entries,1,20);
			printf("\033[1;1H");
			break;
		}
		case 'q': break;
	}
	if(c==':')
		canon();
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
void canon(){
	printf("\033[25;1H");
	while(1){
		int s=getchar();
		int len,flag=0;
		if(s==127){
			len=command.size();
			command=command.substr(0,len-1);
		}else if(s==27){
			main();
		}else if((s>=65 && s<=90) || (s>=97 && s<=122) || (s==32)){
			command=command+(char)s;
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
			printf(" %s ",str.c_str());
			i++;
		}
			/*while(i<len){
				file=file+command[i++];
			}*/
			printf("\033[25;1H");
			//printf("\033[2K");
			perform(task);
			//printf("\n%s  %s\n",file.c_str(),task.c_str());
		}
		if(flag==0)	{
			printf("\033[25;1H");
			printf("\033[2K");
			printf("%s",command.c_str());
		}	
	}
}