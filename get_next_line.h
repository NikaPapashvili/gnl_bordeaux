#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);

// Utils
char	*ft_strndup(char *src, int n);
int		ft_strchr(char *str, char c);
char	*ft_strjoin(char *s1, char *s2, int len2);

#endif
