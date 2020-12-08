#include<stdio.h>
#include<string.h>
#include<stdlib.h>


typedef unsigned char bool;

#define true 1
#define false 0
#define N_ARGS 10

void prompt_print(bool write_prompt_control){
    if(write_prompt_control)
        printf("wish> ");

}


char **tokenize_cmd(char *cmd, int *n){
    char **cmd_matrix;
    cmd_matrix = (char **)malloc(N_ARGS*sizeof(char*));
    if(cmd_matrix == NULL)
        return NULL;

    int capacity = N_ARGS;

    (*n)=0;
    cmd_matrix[(*n)] = strtok(cmd, " \t");
    (*n)++;

    while(cmd_matrix[(*n)-1] != NULL){
        if((*n)==capacity){
            capacity+=N_ARGS;
            cmd_matrix = (char**) realloc(cmd_matrix,capacity*sizeof(char*));
            if(cmd_matrix == NULL)
                return NULL;
        }
        //printf("|%s|\n",cmd_matrix[(*n)-1]);
        cmd_matrix[(*n)] = strtok(NULL, " \t");
        (*n)++;
    }


    return cmd_matrix;

}

int main(int argc,char *argv[]){
    
    bool write_prompt_control = false, prompt_loop_control=true;
    
    if(argc == 1){
        write_prompt_control = true;
    }



    do{
        prompt_print(write_prompt_control);
        char *cmd = NULL;
        size_t cmd_bytes = 0;

        ssize_t cmd_size = getline(&cmd,&cmd_bytes,stdin);
        cmd[cmd_size-1]='\0';cmd_size--;

        if(cmd_size == 0){
            prompt_loop_control = false;
        }
        else{
            int n_args = 0;
            char **cmd_matrix = tokenize_cmd(cmd,&n_args);
            printf("%d",n_args);
        }




        free(cmd);
    }while(prompt_loop_control);
    exit(0);
}