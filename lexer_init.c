#include "parser.h"

t_tokenizer *init_tokenizer(char *input)
{
    t_tokenizer *tokenizer;

    tokenizer = (t_tokenizer *)malloc(sizeof(t_tokenizer));
    if (!tokenizer)
        return (NULL);
    tokenizer->input = input;
    tokenizer->pos = 0;
    tokenizer->len = ft_strlen(input);
    tokenizer->head = NULL;
    tokenizer->error = 0;
    return (tokenizer);
}
