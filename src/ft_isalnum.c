/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 19:24:57 by schiad            #+#    #+#             */
/*   Updated: 2017/04/25 19:03:59 by schiad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	int	retour;

	retour = 0;
	if (ft_isalpha(c))
		retour = 1;
	if (ft_isdigit(c))
		retour = 1;
	return (retour);
}
