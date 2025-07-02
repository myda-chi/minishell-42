#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void handle_sigint(int sig)
{
    (void)sig;
    printf("\n");
    rl_on_new_line();
    // rl_replace_line("", 0);
    rl_redisplay();
}

void setup_signals(void)
{
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
} 