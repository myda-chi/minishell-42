#include "parser.h"

void print_tokens(t_token *tokens)
{
    t_token *current = tokens;
    const char *type_str[] = {
        "WORD", "PIPE", "REDIR_IN", "REDIR_OUT", 
        "REDIR_APPEND", "REDIR_HEREDOC", 
        "SINGLE_QUOTE", "DOUBLE_QUOTE", "DOLLAR", "END"
    };

    printf("Tokens:\n");
    while (current)
    {
        printf("Type: %-15s Value: %s\n", 
               type_str[current->type], 
               current->value);
        current = current->next;
    }
    printf("\n");
}

int main(void)
{
    char *input;
    t_parser *parser;
    t_token *tokens;

    dig_prompt();
    while (1)
    {
        input = readline("🤖 minishell➤ ");
        if (!input)
            break;
        
        if (ft_strlen(input) > 0)
        {
            add_history(input);
            parser = init_parser(input);
            if (!parser)
            {
                free(input);
                continue;
            }
            tokens = tokenize(parser);
            if (check_syntax(tokens))
                print_tokens(tokens);
            if (ft_strncmp(input, "exit", 4) == 0)
             			break ;
            free_parser(parser);
        }
        free(input);
    }
    return (0);
}
