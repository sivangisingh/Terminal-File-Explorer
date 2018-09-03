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
//to fetch current Directory::
std::string GetCurrentWorkingDir( void ) {
  char home[FILENAME_MAX];
  GetCurrentDir( home, FILENAME_MAX );
  std::string current_working_dir(home);
  return current_working_dir;
}
int main()
{
	//blank screen
	printf("\x1b[2J\x1b[1;1H");
 	   int n=0;
 	   //to store directories and the files within the folder
 	   vector<direct *> entries;
 	   //for backword and forward operations
 	   struct Stack s1,s2,parent;
	//getting the current directory
	string home =GetCurrentWorkingDir();
	buff=home;
	 //function call to print first five entries of the folder 
	enter(buff,entries,1,20);
	//total size of the folder(i.e. the number of files in it)
	n=entries.size();
	string ss =home;
	parent.push(home);
	//to bring pointer to the first location
	printf("\033[1;1H"); 
int x=1,y=20,p=1,flag=1;
int c=0;
//initializing to take keyboard inputs
init_keyboard();
while(1){
	c=getchar();
	//getting input and checking it to do specified operations
	switch(c){
		//if up arrow pressed go one pointer up
		case 65:{
			if(p>x){
			p--;
			printf("\033[%d;1H",p-x+1);			
		}else if(p>1){
			//scroll up
			p--;
			x--;
			y--;
			enter(buff,entries,x,y);
			printf("\033[1;1H");
		}
		break;
		}
		//if down arrow pressed go one pointer down 
		case 66:{
			if(p<y){
			p++;
			printf("\033[%d;1H",p-x+1);
		}else if(p>=y && p<n){
			//scroll down
			p++;
			y++;
			x++;
			enter(buff,entries,x,y);
		 printf("\033[20;1H");
		}
		break;
		}
		//on pressing enter open directory if the file is of directory type
		case 10: {
    		if((entries[p-1]->d_type)==DT_DIR){
    			chdir(buff.c_str());
    			s1.push(ss);
    			parent.push(ss);
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
			chdir("..");
            			}
    		else{
    			//code to open file
    			pid_t pin;
				pin=fork();
				if(pin==0){
					string shut=entries[p-1]->d_name;
				execl("usr/bin/xdg-open","xdg-open",shut.c_str(),NULL);
				exit(1);
				}
    			}
			break;
		}
		//press h to go to home 
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
		//to enter command mode
		case ':':{
			break;
		}
		//on pressing left-arrow key go to previous directory
		case 68:{
			if(!s1.isEmpty()){
				s2.push(buff);
				if(flag==0){
					parent.push(buff);
					flag=1;
				}
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
			}else{
				ss=home;
				buff=home;
			}
			break;
		}
		//on pressing right-arrow key go to previously backed directory
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
			}else{
				ss=home;
				buff=home;
			}
			break;
		}
		//on pressing backspace key go to parent directory
		case 127:{
			if(!parent.isEmpty()){
			s1.push(buff);
			ss=parent.pop();
			flag=0;
			//chdir(buff.c_str());
			x=1;
			p=1;
			y=20;
			enter(ss,entries,1,20);
			buff=ss;
			n=entries.size();
			if(n<20)
				y=n;
			printf("\033[1;1H");
		}else{
				ss=home;
				buff=home;
			}
			break;
		}
		//on pressing q ,quit
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
//changing flag values 
void init_keyboard()
{
tcgetattr(0,&initial_settings);
new_settings = initial_settings;
new_settings.c_lflag &= ~ICANON;
new_settings.c_lflag &= ~ECHO;
tcsetattr(0, TCSANOW, &new_settings);
}
//changing back the flag values
void close_keyboard()
{
tcsetattr(0, TCSANOW, &initial_settings);
}
//function for canonical mode
void canon(vector<direct *> entries){
	printf("\033[25;1H");
	while(1){
		int s=getchar();
		int len,flag=0;
		//on backspace click delete last typed character
		if(s==127){
			len=command.size();
			command=command.substr(0,len-1);
		}else if(s==27){
		    //on pressing esc key ko back to normal mode
			printf("\033[1;1H");
			return;
		}else if(s==10){
		    //on pressing enter do the desired operation
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
			command.clear();
		}else{
		    //on press of any other key, print it
			command=command+(char)s;
		}
		if(flag==0)	{
			printf("\033[25;1H");
			printf("\033[2K");
			printf("%s",command.c_str());
		}	
	}
}
