/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:04:50 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/16 23:28:57 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void    disable_echoctl(void)
{
    struct termios  term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void    signal_handler(int signum)
{
    if (signum == SIGINT)
    {
        if (!g_signal_received)
        {
            write(STDERR_FILENO, "\n", 1);
            rl_replace_line("", 0);
            rl_on_new_line();
            rl_redisplay();
        }
        else
		{
            // write(STDERR_FILENO, "\n", 1);
		}
    }
    else if (signum == SIGQUIT)
    {
        if (g_signal_received)
        {
            printf("Quit: %d", SIGQUIT);
            write(STDERR_FILENO, "\n", 1);
        }
    }
}
void    signal_handler_heredoc(int signum)
{
    if (signum == SIGINT)
    {
        rl_replace_line("", 0);
        rl_on_new_line();
        exit(1);
    }
}
void    signal_handler_input(int signum)
{
    if (signum == SIGINT)
    {
        write(STDERR_FILENO, "\n", 1);
    }
    else if (signum == SIGQUIT)
    {
        printf("Quit: %d\b", SIGQUIT);
        write(STDERR_FILENO, "\n", 1);
    }
}
void    setup_signals(void)
{
    disable_echoctl();
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
    signal(SIGTSTP, signal_handler);
}
void    set_signal_handler()
{
        signal(SIGINT, signal_handler_input);
        signal(SIGQUIT, signal_handler_input);
}