/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_char_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/01 19:46:41 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/15 18:25:45 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_delete_list(t_letter **list_let)
{
	t_letter	*temp1;

	temp1 = *list_let;
	while (temp1->next != NULL)
	{
		temp1 = temp1->next;
	}
}
