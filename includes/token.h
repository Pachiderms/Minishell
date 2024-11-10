

#ifndef TOKEN_H
#define TOKEN_H

# include "minishell.h"

enum e_type
{
    infile, outfile, instruction;
}

typedef struct token_t
{
    enum e_type type;
    char        *value;
}   t_token;

#endif