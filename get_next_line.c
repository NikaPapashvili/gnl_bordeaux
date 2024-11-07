#include "get_next_line.h"

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

static char	*ft_init_buffer(char *buffer, int fd)
{
	int	i;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (buffer);
	if (buffer)
	{
		buffer = ft_move_to_start(buffer);
		return (buffer);
	}
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	i = 0;
	while (i < BUFFER_SIZE + 1)
	{
		buffer[i] = 0;
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

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			bytes_read;
	int			nl_index;
	char		**tmp_buffer;

	buffer = ft_init_buffer(buffer, fd);
	if (buffer == NULL || fd < 0)
		return (NULL);
	nl_index = 0;
	bytes_read = 1;
	line = ft_read_line(buffer, fd, &nl_index, &bytes_read);
	if (!line || (buffer[0] == '\0' && line[0] == '\0') || bytes_read == -1)
	{
		free(line);
		tmp_buffer = &buffer;
		free(buffer);
		*tmp_buffer = NULL;
		return (NULL);
	}
	if (nl_index != -1)
		line[nl_index + 1] = '\0';
	return (line);
}
