#include "parser.h"

t_token *create_token(t_token_type type, char *value)
{
    t_token *token;

    token = (t_token *)malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = type;
    token->value = value;
    token->next = NULL;
    return (token);
}

void add_token(t_tokenizer *tokens, t_token *new_token)
{
    t_token *current;

    if (!tokens)
        return ;
    if (!tokens->head)
    {
        tokens->head = new_token;
        return ;
    }
    current = tokens->head;
    while (current->next)
        current = current->next;
    current->next = new_token;
}

void free_tokens(t_tokenizer *tokens)
{
    t_token *current;
    t_token *next;

    if (!tokens)
        return ;
    current = tokens->head;
    while (current)
    {
        next = current->next;
        if(current->value)
            free(current);
        current = next;
    }
} 