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
	t_rdfile	*rdfile;
	t_trfile	*trfile;
	t_heredoc	*heredoc;
	t_addfile	*addfile;
	
	rdfile = block->rdfile;
	trfile = block->trfile;
	heredoc = block->heredoc;
	addfile = block->addfile;
	while (i < block->order)
	{
		if (rdfile && i == rdfile->order)
			rdfile = step_rd(rdfile, cmd);
		else if (heredoc && i == heredoc->order)
			heredoc = step_hr(heredoc, cmd);
		else if (addfile && i == addfile->order)
			addfile = step_add(addfile, cmd);
		else if (trfile && i == trfile->order)
			trfile = step_tr(trfile, cmd);
		if (cmd->in == -1 || cmd->out == -1)
			return (1);
		i++;
	}
	return (0);
}
