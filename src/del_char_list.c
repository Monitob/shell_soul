
void	ft_delete_list(t_letter **list_let)
{
	t_letter *temp1;

	temp1 = *list_let;
	while (temp1->next != NULL)
	{
		temp1 = temp1->next;
	}
}
