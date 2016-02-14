/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 22:13:23 by crenault          #+#    #+#             */
/*   Updated: 2016/01/21 11:44:07 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char		*get_file_content(const char *file)
{
	int			fd;
	char		*buffer;
	off_t		curr_pos;
	off_t		fsize;

	if ((fd = open(file, O_RDONLY)) != -1)
	{
		curr_pos = lseek(fd, (size_t)0, SEEK_CUR);
		fsize = lseek(fd, (size_t)0, SEEK_END);
		lseek(fd, curr_pos, SEEK_SET);
		if ((buffer = (char*)malloc(fsize + 1)) == NULL)
			return (NULL);
		if ((fsize = read(fd, buffer, fsize)) == -1)
		{
			dprintf(2, "Error while trying to read %s\n", file);
			close(fd);
			return (NULL);
		}
		close(fd);
		buffer[fsize] = '\0';
		return (buffer);
	}
	dprintf(2, "Error: Unable to open \"%s\", %s\n", file, strerror(errno));
	return (NULL);
}
