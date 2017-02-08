#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include<regex.h>       
int main(){
DIR *d;
FILE *fp;
char ch,temp[8],fname[20];
struct dirent *dir;
regex_t regex;
int reti;
/* Compile regular expression */
reti = regcomp(&regex,"^(+91)+[ -]?[789][0-9]{9}$",0);
if (reti) {    
fprintf(stderr, "Could not compile regex\n");    
exit(1);    
}
d=opendir("./sample");
system("cd ./sample");
chdir("./sample");
if(d)
{
while((dir=readdir(d))!=NULL) {
sscanf(dir->d_name,"%s\n",fname);  
printf("%s\n",fname);         
fflush(stdout); 
fp=fopen(fname,"r"); 
if(fp==NULL)   {
perror("cant open");    
}     else     {  
fflush(stdout);  
while(fgets(temp,15,fp) != NULL)      {
/* Execute regular expression */     
reti = regexec(&regex,temp, 0, NULL, 0);     
if (!reti) {        
printf("%s:",temp);       
fflush(stdout);           
}       
}       
}       
fclose(fp);   
}       
fp=NULL;  
}     
closedir(d);      
regfree(&regex);   
}
