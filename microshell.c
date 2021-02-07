#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#define yellow "\x1b[33m"
#define green "\x1b[92m"
#define cyan "\x1b[36m"
#define zero "\x1b[0m"


char* path;
char* loc = "";
char* temp;

void help(){
	printf("Erwin Picinski Microshell\nDostepne polecenia:\nhelp\ncd\nexit\n");
}

void cd(char* arg){
    if(!strcmp("~",arg)){
        loc = getcwd(NULL,0);
        chdir(getenv("HOME"));
    }
    else if(!strcmp("-",arg)){

        temp = getcwd(NULL,0);
        if(loc == ""){
            perror(yellow "Blad polecenia");
            printf(zero);
        }
        else{
        chdir(loc);
        loc = strcpy(loc,temp);
        }

    }
    else{
        loc = getcwd(NULL,0);
        if((chdir(arg)) == -1){
            perror(yellow "Blad polecenia");
            printf(zero);
        }
    }
}

void getInput(char* input){

    int i = 0;
    fgets(input, 250, stdin);
    int len = strcspn(input, "\n");
    input[len] = '\0';


}


void exec(char* input){
    int x = 0;
    int i;
    for(i = 0; i<250; i++){
        if(input[i] == ' '){
            x++;
        }
        if(input[i] == '\0'){
            x++;
            break;
        }
    }
    char* parm = strtok(input, " ");
    char* args[x+1];
    args[0] = parm;

    for(i = 1; i<=x; i++){
        parm = strtok(NULL, " ");
        args[i] = parm;
    }


    if(args[0]!= NULL){

        if(!strcmp("help", args[0]))
            help();
        else if(!strcmp("exit", args[0]))
            exit(0);
        else if(!strcmp("cd", args[0])){
            if (args[1] == NULL){
                loc = getcwd(NULL,0);
                chdir(getenv("HOME"));
            }
            else{
            cd(args[1]);
            }
        }
        else
        {

            if(fork() == 0)
            {
                execvp(args[0],args);
                perror(yellow "Blad polecenia");
                printf(zero);
                exit(0);
            }else
            {

                wait(0);
            }

        }
    }
}
void key(){
}
int main(){
	char* name;
	char input[250];

	while(1){

        name = getlogin();
        path = getcwd(NULL,0);
        printf("[" cyan "%s" zero ":" green "%s" zero "] \n$ " zero,name,path);
        printf(zero);
        getInput(input);
        exec(input);
}
}

