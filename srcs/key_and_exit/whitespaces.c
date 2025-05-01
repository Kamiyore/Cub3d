/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitespaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:26:04 by knemcova          #+#    #+#             */
/*   Updated: 2025/05/01 12:27:36 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*skip_ws(char *s)
{
	while (*s && ft_isspace(*s))
		s++;
	return (s);
}

char	*trim_ws(const char *s)
{
	const char	*beg;
	const char	*end;

	beg = s;
	while (*beg && ft_isspace(*beg))
		beg++;
	end = beg + ft_strlen(beg);
	while (end > beg && ft_isspace(*(end - 1)))
		end--;
	return (ft_substr(beg, 0, end - beg));
}
