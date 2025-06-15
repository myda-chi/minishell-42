#include "parser.h"

t_parser *init_parser(char *input)
{
    t_parser *parser;

    parser = (t_parser *)malloc(sizeof(t_parser));
    if (!parser)
        return (NULL);
    parser->input = input;
    parser->pos = 0;
    parser->len = ft_strlen(input);
    parser->tokens = NULL;
    return (parser);
}

void free_parser(t_parser *parser)
{
    if (!parser)
        return;
    free_tokens(parser->tokens);
    free(parser);
} 