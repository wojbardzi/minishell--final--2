/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:03:04 by wojti             #+#    #+#             */
/*   Updated: 2025/08/13 13:03:09 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_delimiter(const char *buf, const char *delimiter)
{
	size_t	len;

	len = ft_strlen(delimiter);
	return (ft_strncmp(buf, delimiter, len) == 0 && buf[len] == '\n');
}

static int	write_heredoc_line(int fd, char *buf, ssize_t len)
{
	ssize_t	written;

	written = write(fd, buf, len);
	if (written != len)
	{
		perror("write");
		return (-1);
	}
	return (0);
}

static int	read_heredoc_loop(int fd, const char *delimiter)
{
	char		buffer[4096];
	ssize_t		read_bytes;

	write(1, "> ", 2);
	read_bytes = read(0, buffer, sizeof(buffer) - 1);
	while (read_bytes > 0)
	{
		buffer[read_bytes] = '\0';
		if (is_delimiter(buffer, delimiter))
			break ;
		if (write_heredoc_line(fd, buffer, read_bytes) == -1)
			return (-1);
		write(1, "> ", 2);
		read_bytes = read(0, buffer, sizeof(buffer) - 1);
	}
	if (read_bytes < 0)
	{
		perror("read");
		return (-1);
	}
	return (0);
}

int	handle_heredoc(const char *delimiter)
{
	int	tmp_fd;

	tmp_fd = open("heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (tmp_fd == -1)
	{
		perror("open");
		return (-1);
	}
	if (read_heredoc_loop(tmp_fd, delimiter) == -1)
	{
		close(tmp_fd);
		return (-1);
	}
	close(tmp_fd);
	return (open("heredoc_tmp", O_RDONLY));
}
