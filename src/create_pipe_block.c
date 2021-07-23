#include "../includes/minishell.h"

void	reg_pipe(int *i, int *this_cmd, t_block **block)
{
	t_block *new = new_block();
	block_add_back(block, new);
	(*block) = (*block)->next;
	(*this_cmd) = 1;
	(*i) += 1;
}

void	reg_file(int *i, t_block **block, char **str, int index)
{
	if (index == HEREDOC)
		init_heredoc(&((*block)->heredoc), str[(*i) + 1], (*block)->order);
	if (index == RDFILE)
		init_rdfile(&((*block)->rdfile), str[(*i) + 1], (*block)->order);
	if (index == WRFILEADD)
		init_addfile(&((*block)->addfile), str[(*i) + 1], (*block)->order);
	if (index == WRFILETR)
		init_trfile(&((*block)->trfile), str[(*i) + 1], (*block)->order);
	((*block)->order)++;
	(*i) += 2;
}

int	reg_file_and_pipe(int *i, char **str, int *this_cmd, t_block **block)
{
	int index;

	index = get_index(str[*i]);
	if (index)
	{
		if (index == PIPE)
			reg_pipe(i, this_cmd, block);
		else
		{
			reg_file(i, block, str, index);
		}
		return (1);
	}
	return (0);
}

void	reg_cmd_and_arg(int *this_cmd, t_block *block, char *str)
{
	size_t size;

	size = 0;
	if(*this_cmd)
	{
		block->cmd->name = str;
		block->cmd->arg[0] = str;
		*this_cmd = 0;
	}
	else
	{
		size = count_arr(block->cmd->arg);
		block->cmd->arg = ft_realloc(block->cmd->arg, size + 1);
		block->cmd->arg[size] = str;
	}
}

t_block *create_pipe_block(char **str)
{
	int i;
	int this_cmd;
	t_block *block;
	t_block *tmp;

	if (!str)
		return (NULL);
	i = 0;
	this_cmd = 1;
	block = new_block();
	tmp = block;
	int size = count_arr(str);
	while (i < size)
	{
		if (reg_file_and_pipe(&i, str, &this_cmd, &block))
			continue;
		else
			reg_cmd_and_arg(&this_cmd, block, str[i]);
		i++;
	}
	return (tmp);
}
