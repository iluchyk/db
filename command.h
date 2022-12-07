#ifndef COMANDS_H

#if !defined(ARRAY_SIZE)
    #define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif

typedef struct argument
{
    char key;
    char *value;
} arguments_t;

typedef struct command
{
    char *comand;
    arguments_t *args;
} command_t;

extern int run_command(char *s_cmd);
#endif