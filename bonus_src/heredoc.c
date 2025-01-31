
#include <stdio.h>
#include "./get_next_line/get_next_line_bonus.h"
#include "../libft/libft.h"

int ft_strcmp(char *str1, char *str2)
{
    int i;
    i = 0;
    if (!str1 || !str2)
        return -1;
    while (str1[i] && str2[i] && str1[i] == str2[i])
    {
        i++;
    }
    return (unsigned char)str1[i] - (unsigned char)str2[i];
}
int here_doc_exist(char *argv1)
{
    if (ft_strcmp(argv1, "here_doc") == 0)
        return 1;
    return 0;
}

char *here_doc_wih_get_next_line(char *argv1, char *argv2)
{
    char *buffer;
    buffer = NULL;
    char *s;
    s = NULL;
    int str_cmp_return;
    argv2 = ft_strjoin(argv2, "\n");
    if (here_doc_exist(argv1))
    {
        str_cmp_return = 1;
        while (str_cmp_return != 0)
        {
            s = get_next_line(0);
            str_cmp_return = ft_strcmp(s, argv2);
            if (str_cmp_return != 0)
                buffer = ft_strjoin(buffer, s);
        }
        return buffer;
    }
    return NULL;
}
// void pipe(char **argv)
// {

// }

int main(int argc, char **argv)
{

    printf("%s", here_doc_wih_get_next_line(argv[1], argv[2]));
}
