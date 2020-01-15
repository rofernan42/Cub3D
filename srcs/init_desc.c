/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_desc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:07:22 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/15 12:08:37 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_buffer(int fd, t_buf *buf)
{
	char	*line;
	int		ret;

	buf->content = ft_strdup("");
	while ((ret = get_next_line(fd, &line)))
	{
		buf->content = ft_strjoin_free(buf->content, line, 2);
		buf->content = ft_strjoin_free(buf->content, "\n", 1);
	}
	buf->content = ft_strjoin_free(buf->content, line, 2);
}

void		init_desc(t_cub3d *cub, char *desc, t_buf *buf)
{
	int		fd;

	if ((fd = open(desc, O_RDONLY)) < 0)
	{
		cub->error = 1;
		cub->err_message = ft_strdup("Could not find map description.\n");
		close(fd);
		return ;
	}
	set_buffer(fd, buf);
	buf->buffer = ft_split_nl(buf->content);
	close(fd);
}
