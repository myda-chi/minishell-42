#include "parser.h"

void print_syntax_error(char *error)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(error, 2);
    ft_putstr_fd("\n", 2);
}

int check_syntax(t_tokenizer *tokens)
{
    t_token *current;
    int pipe_count;
    int redir_count;

    current = tokens->head;
    pipe_count = 0;
    redir_count = 0;

    while (current)
    {
        if (current->type == PIPE)
        {
            pipe_count++;
            if (current->next && current->next->type == PIPE)
            {
                print_syntax_error("syntax error near unexpected token '|'");
                return (0);
            }
        }
        else if (current->type >= REDIR_IN && current->type <= REDIR_HEREDOC)
        {
            redir_count++;
            if (!current->next || current->next->type != WORD)
            {
                print_syntax_error("syntax error near unexpected token '>'");
                return (0);
            }
        }
        current = current->next;
    }
    return (1);
} 