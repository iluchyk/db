#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"

static const char *COMMANDS[] = {"create", "delete", "connect"};
static const char COMMAND_SEPPARATOR = ' ';
static const char *ARGS_SEPPARATOR = " -";

static void parse_command(command_t *cmd, const char *s_cmd);
static void set_argument(command_t *cmd, char *s_cmd);
static int args_cmd_count(const char *s_cmd);
static void free_cmd(command_t *cmd);

extern int run_command(char *s_cmd)
{
    command_t *cmd;

    cmd = malloc(sizeof(command_t));
    parse_command(cmd, s_cmd);
    //free_cmd(cmd);
    return 0;
}

static void parse_command(command_t *cmd, const char *s_cmd)
{
    char *p_char = strchr(s_cmd, COMMAND_SEPPARATOR);
    int cmd_length = (int)(p_char - s_cmd);
    cmd->comand = malloc(sizeof(char) * cmd_length);

    strncpy(cmd->comand, s_cmd, cmd_length);

    set_argument(cmd, p_char);
}

static void set_argument(command_t *cmd, char *s_cmd)
{
    int len = strlen(s_cmd);
    int size_of_argument = strspn(s_cmd, ARGS_SEPPARATOR);
    char a_cmd[len];
    strncpy(a_cmd, s_cmd, len);

    cmd->args = malloc(sizeof(arguments_t) * size_of_argument); 
    
    arguments_t **args_p = &(cmd->args);

    while (*args_p != NULL)
    {
        printf("%p\n", *args_p);
        (*args_p)++;
    }
    
        
}

static void free_cmd(command_t *cmd)
{
    while (cmd->args)
    {
        arguments_t *temp = cmd->args;
        // free(cmd->args->value);
        free(cmd->args);
        cmd->args == temp++;
    }

    free(cmd->comand);
    free(cmd);
}