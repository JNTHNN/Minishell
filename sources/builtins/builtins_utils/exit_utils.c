/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:04:28 by jgasparo          #+#    #+#             */
/*   Updated: 2024/05/31 18:01:59 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Check if result overflow | assign flag as 1 if error
*/
static void	ft_secure(int64_t resu, int64_t temp, int sign, int *flag)
{
	if ((temp > resu && sign == -1 && resu != LLONG_MIN) || (temp > resu && sign == 1))
		*flag = 1;
	// if (resu == LLONG_MIN)
	// 	*flag = 0;
	// printf("ITER n` %d, temp = %lld, resu = %lld, flag %d\n", i, temp, resu, *flag);
}

/*
**	Assign negative sign if minus is encountered
*/
static int	ft_sign(char c)
{
	int	sign;

	sign = 1;
	if (c == '-')
		sign = -1;
	return (sign);
}

/*
**	Convert a string ascii (if number) to a long long int
*/
int64_t	ft_atol(const char *str, int *flag)
{
	int		i;
	int64_t	resu;
	int64_t	temp;
	int		sign;

	i = 0;
	sign = 1;
	resu = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		sign = ft_sign(str[i++]);
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			temp = resu;
			resu = resu * 10 + (str[i] - '0');
			ft_secure(resu, temp, sign, flag);
		}
		else
			*flag = 1;
		i++;
	}
	// printf("res = %lld\n", resu * sign);
	return (resu * sign);
}

/*
**	Prints the error string with the arg in question
*/
void	ft_print_err_exit(char *arg)
{
	ft_putstr_fd(START_EXIT, STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(ERR_NUM_ARG, STDERR_FILENO);
	}
	else
		ft_putstr_fd(ERR_TOO_ARG, STDERR_FILENO);
}
