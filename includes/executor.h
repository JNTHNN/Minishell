#ifndef EXECUTOR_H
# define EXECUTOR_H

enum	e_pipe_end
{
	READ_END,
	WRITE_END
};

void	execute_command(t_data *data);
char	**ft_pathiter(char **path, t_data *data);
char	**ft_path_abs(t_data *data);
int		ft_create_exec(t_data *data);
int		ft_executor(t_data *data);
int		ft_cmd_exec(t_data *data);



#endif