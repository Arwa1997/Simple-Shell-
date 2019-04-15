#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>


void removeEnter(char line[])
{


    int i =0;
    while(line[i]!='\n')
        i++;

    line[i]='\0';


}

void readLine(char line[])
{
    printf("user:~$ ");
    fgets(line,100,stdin);
    if(strcmp(line,"\n")!=0)
    {

        removeEnter(line);
    }

}

int splitLine (char* args[], char line[])
{
    int i =0;

    args[i]=strtok(line," ");

    if(args[i]==NULL)
        return 0;

    while (args[i]!=NULL)
    {
        i++;
        args[i]=strtok(NULL," ");

    }

    return i;

}

int isBackground (char* args[],int size)
{
    if (size>0)
    {
        int x = size-1;
        if(strcmp(args[x],"&")==0)
        {
            args[x]==NULL;
            return 1;
        }
        else
            return 0;
    }
    return 0;
}

void signalhandler (int sig)
{
 pid_t pid;
//a+ allows me to append everytime
if (pid > 0){

    FILE *f = fopen("log.log","a+");
    if(f==NULL)
        printf("Error logging into file\n");

    fprintf(f,"Child process # %d has been terminated.\n",pid);
    fclose(f);}

}




void main()
{
    char string[100];
    char* args[10];
    int status;
    int size;
    int background;
    pid_t child_pid;

    //1 read line input from user.
    // readLine(string);


    while(1)
    {
        //2 parse line and get size

        readLine(string);
        size = splitLine(args,string);

        //find the "&"
        if(size!=0)
            background = isBackground(args,size);



       //exit command
        if(strcmp(args[0],"exit")==0)
            exit(0);

        //cd command
        else if(strcmp(args[0],"cd")==0)
        {

            chdir(args[1]);
            //add to input message


        }


        //3 fork
        else
        {
            child_pid = fork();

            if(child_pid==0)
            {

                //child

                if(execvp(args[0],args)<0 && strcmp(args[0],"cd")!=0 && strcmp(args[0],"\n")!=0  )
                {
                    printf("%s: command not found.\n",args[0]);
                    exit(1);
                }


            }
            else if(child_pid>0 && !background)
            {

                //parent
                waitpid(child_pid,NULL,0);
                signal(SIGCHLD, signalhandler);

            }
            else if(child_pid<0)
            {
                printf("Forking child failed..\n");
                exit(1);
            }
        }


    }
}

