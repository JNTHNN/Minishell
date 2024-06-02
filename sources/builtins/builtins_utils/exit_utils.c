/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgasparo <jgasparo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:04:28 by jgasparo          #+#    #+#             */
/*   Updated: 2024/06/02 18:33:56 by jgasparo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Check if result overflow | assign flag as 1 if error
*/
static void	ft_secure(int64_t resu, int64_t temp, int sign, int *flag)
{
	if ((temp > resu && sign == -1 && resu != LLONG_MIN)
		|| (temp > resu && sign == 1))
		*flag = 1;
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
**	Check the begin of str if whitespace or sign.
**	Modify +/- and return index when is digit
*/
static int	ft_check(const char *str, int *sign)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		*sign = ft_sign(str[i++]);
	return (i);
}

/*
**	Convert char ascii into long long int
*/
static void	ft_convert(const char c, int64_t *resu, int sign, int *flag)
{
	int64_t	temp;

	temp = *resu;
	*resu = *resu * 10 + (c - '0');
	ft_secure(*resu, temp, sign, flag);
}

/*
**	Convert a string ascii (if number) to a long long int
*/
int64_t	ft_atol(const char *str, int *flag)
{
	int		i;
	int64_t	resu;
	int		sign;

	sign = 1;
	i = 0;
	resu = 0;
	if (ft_strlen(str) == 1 && !ft_isdigit(str[i]))
		return (*flag = 1);
	i = ft_check(str, &sign);
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			ft_convert(str[i], &resu, sign, flag);
		else
		{
			if (str[i] != ' ')
				*flag = 1;
			else if (str[i] == ' ' && str[i + 1] == '\0')
				break ;
		}
		i++;
	}
	return (resu * sign);
}
