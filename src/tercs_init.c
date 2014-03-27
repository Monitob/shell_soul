/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tercs_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 23:02:18 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/26 20:21:01 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				set_fd(void)
{
	int		fd;
	char	*path_fd;

	if (!(isatty(STDIN_FILENO)))
		error_fd("Not a terminal", 2);
	if ((path_fd = ttyname(STDIN_FILENO)) == NULL)
		error_fd("ttayname fail", 2);
	fd = dup(STDIN_FILENO);
	if (fd < 0)
		return (0);
	return (fd);
}

static void		init_term(void)
{
	char	*term_type;

	term_type = getenv("TERM");
	if (term_type == 0)
		error_command("specify a terminal type with setenv TERM <yourtype>");
	if (tgetent(NULL, term_type) <= 0)
		error_command("Could not access to termcap database");
}

void			init_trcs(t_tercs *tcs)
{
	init_term();
	tcgetattr(tcs->tty_fd, &(tcs->term_save));
	tcs->term_fd.c_lflag &= ~(ECHO | ICANON);
	tcs->term_fd.c_cc[VMIN] = 1;
	tcs->term_fd.c_cc[VTIME] = 0;
	tcsetattr(tcs->tty_fd, TCSADRAIN, &(tcs->term_fd));
	tputs(tgetstr("cl", NULL), 1, trcs_putchar);
	tputs(tgetstr("ei", NULL), 1, trcs_putchar);
}

int				trcs_putchar(int c)
{
	write(3, &c, 1);
	return (1);
}

void			reset_term(t_shell *root)
{
	root->tcs->term_save.c_lflag = (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &root->tcs->term_save);
	tputs(tgetstr("cl", NULL), 1, trcs_putchar);
	tputs(tgetstr("te", NULL), 1, trcs_putchar);
	tputs(tgetstr("ve", NULL), 1, trcs_putchar);
	free(root);
}
