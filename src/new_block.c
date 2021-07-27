#include "../includes/minishell.h"

t_block	*last_block(t_block *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	block_add_back(t_block **lst, t_block *new)
{
	t_block	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = last_block(*lst);
	last->next = new;
}

t_block	*new_block(void)
{
	t_block	*block;

	block = malloc_x(sizeof(t_block));
	if (!block)
		exit(42);
	block->cmd = new_cmd(NULL);
	block->heredoc = NULL;
	block->rdfile = NULL;
	block->trfile = NULL;
	block->addfile = NULL;
	block->order = 0;
	block->next = NULL;
	return (block);
}

void	free_block(t_block *block)
{
	t_block	*tmp;

	while (block)
	{
		tmp = block->next;
		free_addfile(block->addfile);
		free_trfile(block->trfile);
		free_rdfile(block->rdfile);
		free_heredoc(block->heredoc);
		free_cmd(block->cmd);
		free(block);
		block = tmp;
	}	
}