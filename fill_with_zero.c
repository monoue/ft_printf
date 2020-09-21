/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_with_zero.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:08:33 by monoue            #+#    #+#             */
/*   Updated: 2020/08/24 10:13:24 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fill_output_with_zero(char **str, int margin)
{
	while (margin)
	{
		*str = ft_strjoin_free_both(ft_ctoa_malloc('0'), *str);
		margin--;
	}
}

void	fill_empty_with_zero(char **str, int margin, t_format_info *info)
{
	if (info->minus == true && info->precision == NOT_SET)
	{
		while (margin)
		{
			*str = ft_strjoin_free_both(*str, ft_ctoa_malloc('0'));
			margin--;
		}
	}
	else
	{
		while (margin)
		{
			*str = ft_strjoin_free_both(ft_ctoa_malloc('0'), *str);
			margin--;
		}
	}
}
