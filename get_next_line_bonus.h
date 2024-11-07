#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_blst
{
	char			*buffer;
	int				fd;
	struct s_blst	*next;
}	t_blst;

char	*get_next_line(int fd);

// Utils
t_blst	*blst_new(int fd, t_blst **head);
char	*ft_strndup(char *src, int n);
int		ft_strchr(char *str, char c);
char	*ft_strjoin(char *s1, char *s2, int len2);

#endif
