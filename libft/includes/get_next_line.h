/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 21:18:10 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 10:19:45 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# define BUFF_SIZE 256

int				get_next_line(const int fd, char **line);

/*
** fid = array of file descriptors
** b = array of overflow buffers, one for each distinct file descriptor
** fn = total number of distinct file descriptors
** afd = active file descriptors, used to make sure the struct is only
**		freed when all files have been read completely
*/

typedef struct	s_line
{
	int		*fid;
	char	**b;
	int		fn;
	int		afd;
}				t_line;

#endif
