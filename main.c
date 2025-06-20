#include "minishell.h"
#include "parser.h"
#include "executor.h"
#include "utils.h"
#include "signals.h"

void print_tokens(t_tokenizer *tokens)
{
    t_token *current = tokens->head;
    const char *type_str[] = {
        "WORD", "PIPE", "REDIR_IN", "REDIR_OUT",
        "REDIR_APPEND", "REDIR_HEREDOC",
        "SINGLE_QUOTE", "DOUBLE_QUOTE", "DOLLAR", "END"};

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
t_command *parse_command(char *input);

int main(int argc, char **argv, char **envp)
{
    char *input;
    t_command *cmd;
    char **my_envp;

    (void)argc;
    (void)argv;
    my_envp = copy_envp(envp);
    setup_signals();
    while (1)
    {
        input = readline("🤖 minishell➤ ");
        if (!input) // Ctrl+D
        {
            ft_putstr_fd("exit\n", 1);
            break;
        }
        if (ft_strlen(input) > 0)
        {
            add_history(input);
            cmd = parse_command(input);
            if (cmd)
            {
                execute(cmd, &my_envp);
                // free_commands(cmd);
            }
        }
        free(input);
    }
    // free_envp(my_envp);
    return (0);
}
