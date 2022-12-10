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
    free_cmd(cmd);
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

    char *token = strtok(a_cmd, ARGS_SEPPARATOR);
    for (size_t i = 0; i < size_of_argument; i++)
    {
        (cmd->args + i)->key = token[0];
        token = strtok(NULL, ARGS_SEPPARATOR);
        int value_l = strlen(token);
        (cmd->args + i)->value = malloc(sizeof(char) * value_l);
        strncpy((cmd->args + i)->value, token, value_l);
        token = strtok(NULL, ARGS_SEPPARATOR);
    }
}

static void free_cmd(command_t *cmd)
{

    for (size_t i = 0; i <= sizeof(*(cmd->args))/sizeof(arguments_t); i++)
    {
        free((cmd->args + i)->value);
    }
    
    free(cmd->comand);
    free(cmd);
}