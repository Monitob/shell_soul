#include "shell.h"

void	tercs_return(t_command **c_line, t_letter **let)
{
	t_history	*h_line;

	h_line = NULL;
	if ((*let)->next == NULL)
		return ;
	if (let)
	{
		init_history(*let, &h_line);
	}


}
