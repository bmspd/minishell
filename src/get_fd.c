#include "../includes/minishell.h"

t_rdfile	*step_rd(t_rdfile *rdfile, t_cmd *cmd)
{
	if (cmd->in > 2)
		close(cmd->in);
	cmd->in = open_rdfile(rdfile->name_file);
	return (rdfile->next);
}

t_heredoc	*step_hr(t_heredoc *heredoc, t_cmd *cmd)
{
	if (cmd->in > 2)
		close(cmd->in);
	cmd->in = heredoc->fd;
	return (heredoc->next);
}

t_trfile	*step_tr(t_trfile *trfile, t_cmd *cmd)
{
	if (cmd->out > 2)
		close(cmd->out);
	cmd->out = open_trfile(trfile->name_file);
	return (trfile->next);
}

t_addfile	*step_add(t_addfile *addfile, t_cmd *cmd)
{
	if (cmd->out > 2)
		close(cmd->out);
	cmd->out = open_addfile(addfile->name_file);
	return (addfile->next);
}

int	get_fd(t_block *block, t_cmd *cmd, int i)
{
	while (i < block->order)
	{

		if (block->rdfile && i == block->rdfile->order)
			block->rdfile = step_rd(block->rdfile, cmd);
		else if (block->heredoc && i == block->heredoc->order)
			block->heredoc = step_hr(block->heredoc, cmd);
		else if (block->addfile && i == block->addfile->order)
			block->addfile = step_add(block->addfile, cmd);
		else if (block->trfile && i == block->trfile->order)
			block->trfile = step_tr(block->trfile, cmd);
		if(cmd->in == -1 || cmd->out == -1)
			return (1);
		i++;
	}
	
	return (0);
}
