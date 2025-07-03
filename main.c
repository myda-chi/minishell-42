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

int main(int argc, char **argv, char **envp)
{
    char *input;
    t_command *cmd;
    t_shell_state *state;
    int exit_status;

    (void)argc;
    (void)argv;
    
    /* Initialize shell state */
    state = init_shell_state(envp);
    if (!state)
    {
        ft_putstr_fd("minishell: failed to initialize shell state\n", 2);
        return (1);
    }
    
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
            cmd = parse_command(input, state);
            if (cmd)
            {
                execute(cmd, state);
                free_commands(cmd);
            }
        }
        free(input);
    }
    exit_status = get_exit_status_from_state(state);
    cleanup_shell_state(state);
    return (exit_status);
}
