#include "get_next_line_bonus.h"
#include <stdio.h>

static char	*ft_move_to_start(char *buffer)
{
	int	nl_index;
	int	i;

	nl_index = ft_strchr(buffer, '\n');
	if (nl_index == -1)
		nl_index = BUFFER_SIZE - 1;
	i = 0;
	while (buffer[nl_index + 1 + i])
	{
		buffer[i] = buffer[nl_index + 1 + i];
		++i;
	}
	while (i < BUFFER_SIZE + 1)
	{
		buffer[i] = '\0';
		i++;
	}
	return (buffer);
}

char	*ft_read_line(char *buffer, int fd, int *nl_index, int *bytes_read)
{
	char	*line;

	line = ft_strndup(buffer, BUFFER_SIZE + 1);
	if (line == NULL)
		return (NULL);
	*nl_index = ft_strchr(line, '\n');
	while (*nl_index == -1 && *bytes_read != 0)
	{
		*bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (*bytes_read == -1)
		{
			free(line);
			return (NULL);
		}
		buffer[*bytes_read] = '\0';
		line = ft_strjoin(line, buffer, *bytes_read);
		if (line == NULL)
			return (NULL);
		*nl_index = ft_strchr(line, '\n');
	}
	return (line);
}

static char	*get_fd_buffer(t_blst **head, int fd)
{
	t_blst	*curr;

	curr = *head;
	while (curr && curr->fd != fd)
		curr = curr->next;
	if (curr)
	{
		ft_move_to_start(curr->buffer);
		return (curr->buffer);
	}
	curr = blst_new(fd, head);
	*head = curr;
	return (curr->buffer);
}

void	free_node(int fd, t_blst **head)
{
	t_blst	*curr;
	t_blst	*node_to_free;

	curr = *head;
	if ((*head)->next == NULL)
	{
		*head = NULL;
		free(curr->buffer);
		free(curr);
		return ;
	}
	if (curr->fd == fd)
	{
		*head = (*head)->next;
		free(curr->buffer);
		free(curr);
		return ;
	}
	while ((curr->next)->fd != fd)
		curr = curr->next;
	node_to_free = curr->next;
	curr->next = (curr->next)->next;
	free(node_to_free->buffer);
	free(node_to_free);
}

char	*get_next_line(int fd)
{
	static t_blst	*head;
	char			*buffer;
	char			*line;
	int				bytes_read;
	int				nl_index;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = get_fd_buffer(&head, fd);
	if (buffer == NULL)
		return (NULL);
	nl_index = 0;
	bytes_read = 1;
	line = ft_read_line(buffer, fd, &nl_index, &bytes_read);
	if (!line || (buffer[0] == '\0' && line[0] == '\0') || bytes_read == -1)
	{
		free(line);
		free_node(fd, &head);
		return (NULL);
	}
	if (nl_index != -1)
		line[nl_index + 1] = '\0';
	return (line);
}
