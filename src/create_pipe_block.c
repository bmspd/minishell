#include "../includes/minishell.h"

void	reg_pipe(int *i, t_block **block)
{
	t_block *new = new_block();
	block_add_back(block, new);
	(*block) = (*block)->next;
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

int	reg_file_and_pipe(int *i, char **str, char **check, t_block **block)
{
	int index;

	index = get_index(str[*i], check[*i]);
	if (index)
	{
		if (index == PIPE)
			reg_pipe(i, block);
		else
		{
			reg_file(i, block, str, index);
		}
		return (0);
	}
	return (1);
}

void	reg_cmd_and_arg(t_block *block, char *str)
{
	size_t size;

	size = 0;
	if (!block->cmd->name)
		block->cmd->name = str;
	if (block->cmd->arg[0])
	{
		size = count_arr(block->cmd->arg);
		block->cmd->arg = ft_realloc(block->cmd->arg, size + 1);
	}
	block->cmd->arg[size] = str;
}

t_block *create_pipe_block(char **str, char **check)
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
		this_cmd = reg_file_and_pipe(&i, str, check, &block);
		if (!this_cmd)
			continue;
		else
			reg_cmd_and_arg(block, str[i]);
		i++;
	}
	return (tmp);
}
