#include "minishell.h"
#include "parser.h"
#include "libft/libft.h"

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

int main(void)
{
    char *input;
    t_command *cmd;

    dig_prompt();
    while (1)
    {
        input = readline("🤖 minishell➤ ");
        if (!input)
            break;

        if (ft_strlen(input) > 0)
        {
            add_history(input);
            cmd = parse_command(input);
            if (!cmd)
            {
                free(input);
                continue;
            }
            
            while (cmd)
            {
                if (cmd->type == PIPE)
                {
                    printf("This is a PIPE\n");
                    cmd = cmd->next;
                    printf("\n");
                    continue;
                }
                int i = 0;
                while (i < cmd->argc)
                {
                    printf("argv %d %s\n", i, cmd->argv[i]);
                    i++;
                }
                printf("\n");
                cmd = cmd->next;
            }

            // tokens = tokenize(tokenizer);
            // if (tokens && check_syntax(tokens))
            //     print_tokens(tokens);
            // cmd_table = parse_commands(input);
            // print_command_table(cmd_table);
            // free_commands(cmd_table);
            if (ft_strncmp(input, "exit", 4) == 0)
                break;
            // free_tokenizer(tokens);
            // free(tokenizer);
        }
        free(input);
    }
    // free_tokenizer(tokens);
    // free(tokenizer);
    return (0);
}
