#include <dlfcn.h>
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <signal.h>

char *ft_name[] ={
	"ft_memset",//0
	"ft_bzero",
	"ft_memcpy",
	"ft_memccpy",
	"ft_memmove",
	"ft_memchr",//5
	"ft_memcmp",
	"ft_strlen",
	"ft_strdup",
	"ft_strcpy",
	"ft_strncpy",//10
	"ft_strcat",
	"ft_strncat",
	"ft_strlcat",
	"ft_strchr",
	"ft_strrchr",//15
	"ft_strstr",
	"ft_strnstr",
	"ft_strcmp",
	"ft_strncmp",
	"ft_atoi",//20
	"ft_isalpha",
	"ft_isdigit",
	"ft_isalnum",
	"ft_isascii",
	"ft_isprint",//25
	"ft_toupper",
	"ft_tolower",
	"ft_memalloc",
	"ft_memdel",
	"ft_strnew",//30
	"ft_strdel",
	"ft_strclr",
	"ft_striter",
	"ft_striteri",
	"ft_strmap",//35
	"ft_strmapi",
	"ft_strequ",
	"ft_strnequ",
	"ft_strsub",
	"ft_strjoin",//40
	"ft_strtrim",
	"ft_strsplit",
	"ft_itoa",
	"ft_putchar",
	"ft_putstr",//45
	"ft_putendl",
	"ft_putnbr",
	"ft_putchar_fd",
	"ft_putstr_fd",
	"ft_putendl_fd",//50
	"ft_putnbr_fd"
};
typedef		void (*funct2)(unsigned int, char *);

void	destroy(char **tab){
	char ** tmp;

	tmp = tab;
	while(*tab)
		free(*(tab++));
	free(tmp);
}

int		t_strnew(void *(*f)(size_t))
{
	char *a, *b;

	b = (char *)malloc(20 * sizeof(char));

	b = memset(b,0,20);
	a = f(-2);
	if (a != NULL)
	{
		free(a);
		free(b);
		return (1);
	}
	a = f(20);
	if (memcmp(a,b,20) != 0)
	{
		free(a);
		free(b);
		return (2);
	}
	free(a);
	free(b);
	return (0);
}
int	t_memdel(void (*f)(void **))
{
	void	**test;
	void	*test_mem;
	void	*test_sav;

	if (!(test_mem = malloc((size_t)(4000000000))))
		return (-1);
	test_sav = test_mem;
	test = &test_mem;
	f(test);
	if (*test != 0)
		return (2);
	test_mem = 0;
	if (!(test_mem = malloc((size_t)(4000000000))))
		return (-1);
	if	(test_mem == test_sav)
	{
		free(test_mem);
		return (0);
	}
	free(test_mem);
	return (1);
}

int t_strdel(void (*f)())
{
	return (t_memdel(f));
}

int	t_strjoin(char *(*f)(const char *, const char *))
{
	char *s1 = strdup("bobo");
	char *s2 = strdup("tata");
	char	*s4 = strdup("Norminette is back");
	char *s3;
	int i = 1;

	if (!((s3 = f(s4, s2)) && s3 != s4 && s3 != s2 && strcmp(s3, "Norminette is backtata") == 0))
	{
		free(s1);
		free(s2);
		free(s3);
		free(s4);
		return (i);
	}
	++i;
	free(s3);
	if (!((s3 = f(s1, s4)) && s3 != s1 && s3 != s4 && strcmp(s3, "boboNorminette is back") == 0))
	{
		free(s1);
		free(s2);
		free(s3);
		free(s4);
		return (i);
	}
	++i;
	free(s3);
	if (!((s3 = f(s1, s2)) && s3 != s1 && s3 != s2 && strcmp(s3, "bobotata") == 0))
	{
		free(s1);
		free(s2);
		free(s3);
		free(s4);
		return (i);
	}
	++i;
	free(s3);
	if (!((s3 = f(s1, "")) && s3 != s1 && strcmp(s3, "bobo") == 0))
	{
		free(s1);
		free(s2);
		free(s3);
		free(s4);
		return (i);
	}
	++i;
	free(s3);
	if (!((s3 = f("", s2)) && s3 != s2 && strcmp(s3, "tata") == 0))
	{
		free(s1);
		free(s2);
		free(s3);
		free(s4);
		return (i);
	}
	++i;
	free(s3);
	if (!((s3 = f("", "")) && strcmp(s3, "") == 0))
	{
		free(s1);
		free(s2);
		free(s3);
		free(s4);
		return (i);
	}
	free(s1);
	free(s2);
	free(s3);
	free(s4);
	return (0);
}

int		t_memalloc(void *(*f)(size_t))
{
	void *a, *b;

	b = malloc(20 * sizeof(char));
	b = memset(b,0,20);

	a = f(20);
	if (memcmp(a,b,20) != 0)
	{
		free(a);
		free(b);
		return (1);
	}
	free(a);
	a = f(-1);
	if (a != NULL)
	{
		free(a);
		free(b);
		return (2);
	}
	free(b);
	return (0);
}
int		t_strnequ(int (*f)(char const *s1, char const *s2 , size_t))
{
	int	a, b;

	const char	*test[10][2] =
	{
		{"",""},
		{"","abc"},
		{"sbc",""},
		{"abc","abc"},
		{"abcd","abc"},
		{"abc","abcd"},
		{"aaaaaaaaaa","baaaaaaaaa"},
		{"aaaaaaaaaa","aaaaaaaaab"},
		{"baaaaaaaaa","aaaaaaaaaa"},
		{"aaaaaaaaab","aaaaaaaaaa"}
	};
	int		i = 0, j;

	while (i < 10)
	{
		j = 0;
		while (j < 15)
		{
			a = f(test[i][0], test[i][1], j);
			b = strncmp(test[i][0], test[i][1], j);
			if ((b == 0 && a != 1) || (b != 0 && a != 0))
				return (i + 1);
			j++;
		}
		i++;
	}
	return (0);
}

char    **ft_tabstrcpy(char **tab)
{
	size_t  i;
	size_t  j;
	char    **rtn;

	i = 0;
	while (tab[i])
		++i;
	if ((rtn = (char **)calloc((i + 1) ,sizeof(char *))) == 0)
		return (NULL);
	j = 0;
	while (j < i)
	{
		rtn[j] = strdup(tab[j]);
		++j;
	}
	return (rtn);
}

void		my_rot_i(unsigned int i, char *c)
{
	*c = (*c + i);
}

int			t_striteri(void (*f)(char *, void (*f)(unsigned int,char *)))
{
	int i;
	funct2 func[] = {
		&my_rot_i
	};
	char *tab[] = {
		"",
		"aaaaaaaaa",
		"aaaaAAAA",
		"BBcc",
		"CCCC",
		0
	};
	char *ref[5] = {
		"",
		"abcdefghi",
		"abcdEFGH",
		"BCef",
		"CDEF"
	};
	char **test;
	test = ft_tabstrcpy(tab);

	i = 0;
	while (i < 5)
	{
		f(test[i], func[0]);
		if (strcmp(test[i], ref[i]) != 0)
		{
			destroy(test);
			return (i + 1);
		}
		++i;
	}
	destroy(test);
	return (0);
}

typedef	char (*funct3)(char);

char	my_tolower2(char c)
{
	return ((char)tolower(c));
}

char	my_toupper2(char c)
{
	return ((char)toupper(c));
}

int		t_strmap(char *(*f)(char const *, char (*f)(char)))
{
	int		i;
	funct3	func[] = {
		&my_tolower2,
		&my_toupper2
	};
	char	*tab[] = {
		"",
		"aaaaaaaaa",
		"aaaaAAAA",
		"BBcc",
		"CCCC",
		0
	};
	char	*ref[2][6] = {
		{
			"",
			"aaaaaaaaa",
			"aaaaaaaa",
			"bbcc",
			"cccc"
		},
		{
			"",
			"AAAAAAAAA",
			"AAAAAAAA",
			"BBCC",
			"CCCC"
		}
	};
	char	**test;
	char	*result;
	int		j;

	j = 0;
	test = ft_tabstrcpy(tab);

	while (j < 2)
	{
		i = 0;
		while (i < 5)
		{
			result = f(test[i], func[j]);
			if (strcmp(result, ref[j][i]) != 0 || test[i] == result)
			{
				destroy(test);
				free(result);
				return (i + 1);
			}
			free(result);
			++i;
		}
		++j;
	}
	destroy(test);
	return (0);
}


char	*test_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*ret;
	char			*temp_ret;

	i = 0;
	ret = (char *)malloc((len + 1) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	ret[len] = '\0';
	temp_ret = ret;
	while (i != start)
		i++;
	while (len--)
		*temp_ret++ = s[i++];
	return (ret);
}
typedef	char (*funct4)(unsigned int, char);

char	my_rot_i2(unsigned int i, char c)
{
	return (c + i);
}
int		t_strmapi(char *(*f)(char const *, char (*f)(unsigned int, char)))
{
	int		i;
	funct4	func[] = {
		&my_rot_i2
	};
	char	*tab[] = {
		"",
		"aaaaaaaaa",
		"aaaaAAAA",
		"BBcc",
		"CCCC",
		0
	};
	char	*ref[5] = {
		"",
		"abcdefghi",
		"abcdEFGH",
		"BCef",
		"CDEF"
	};
	char	**test;
	char	*result;

	test = ft_tabstrcpy(tab);

	i = 0;
	while (i < 5)
	{
		result = f(test[i], func[0]);
		if (strcmp(result, ref[i]) != 0 || test[i] == result)
		{
			free(result);
			destroy(tab);
			return (i + 1);
		}
		free(result);
		++i;
	}
	destroy(test);
	return (0);
}

int t_strsub (char *(*f)(char const *, unsigned int, size_t))
{
	int i = 0, j = 0;
	char	*a, *b;
	char	str[] = "Coucou je suis une phrase de test";
	int		length = strlen(str);

	while (i <= length)
	{
		while (j <= (length - i))
		{
			a = (*f)(str, i, j);
			b = test_strsub(str, i, j);
			if (strcmp(a, b) != 0 || a == (str + i))
			{
				free(a);
				free(b);
				return 1;
			}
			free(a);
			free(b);
			j++;
		}
		i++;
		j = 0;
	}
	return 0;
}

int		t_strstr(char *(*f)(const char *, const char *))
{
	int i = 1;
	char *vide = "";
	char *ref = "qwertyuiopasdfghjklzxcvbnm1234567890)(*&^%$#@!\n\t\v\f QWERTYUIOPASDFGHJKLZXCVBNM<>:{}|";
	char *find = "zxc";
	char *find1 = "\v\f";
	char *find2 = "\n\v\f";
	char *find3 = "}|";

	if (!(f(ref, vide) == strstr(ref, vide) && strcmp(f(ref, vide), strstr(ref, vide)) == 0))
		return (i);
	++i;

	if (!(f(ref, find2) == strstr(ref, find2) && f(ref, find2) == 0))
		return (i);
	++i;

	if (!(f(ref, find) == strstr(ref, find) && strcmp(f(ref, find), strstr(ref, find)) == 0))
		return (i);
	++i;

	if (!(f(ref, find1) == strstr(ref, find1) && strcmp(f(ref, find1), strstr(ref, find1)) == 0))
		return (i);
	++i;

	if (!(f(ref, find3) == strstr(ref, find3) && strcmp(f(ref, find3), strstr(ref, find3)) == 0))
		return (i);
	++i;

	if (!(f(vide, vide) == strstr(vide, vide) && strcmp(f(vide, vide), strstr(vide, vide)) == 0))
		return (i);

	++i;
	if (!(f(vide, find) == strstr(vide, find) && f(vide, find) == 0))
		return (i);

	return (0);
}

void my_tolower(char *c)
{
	*c = tolower(*c);
}

void my_toupper(char *c)
{
	*c = toupper(*c);
}



typedef void (*funct)(char *);

int		t_strncmp(int (*f)(const char *, const char *, size_t))
{
	int i = 0, j = 0;
	int a, b;
	char *s[] = {
		"",
		"abc",
		"",
		"abc",
		"abcd",
		"abc",
		"aaaaaaaaaa",
		"aaaaaaaaaa",
		"aaaaaaaaab",
		"aaaaabaaaa"
	};
	char *str[] = {
		"",
		"",
		"abc",
		"abc",
		"abc",
		"abcd",
		"baaaaaaaaa",
		"aaaaaaaaab",
		"aaaaaaaaaa",
		"aaaaaaaaaa"
	};

	while (i < 10)
	{
		j = 0;
		while (j < 20){
			a = f(s[i], str[i], j);
			b = strncmp(s[i], str[i], j);
			if ((b == 0 && a != 0) || ( b > 0 && a <= 0 ) ||(b < 0 && a >= 0))
				return (i + 1);
			j++;
		}
		i++;
	}

	return 0;
}

int		t_striter(void (*f)(char *, void (*f)(char *)))
{
	int i;
	funct func[] = {
		&my_tolower,
		&my_toupper,
		0
	};
	char *tab[] = {
		"",
		"aaaaaaaaa",
		"aaaaAAAA",
		"BBcc",
		"CCCC",
		0
	};
	char *ref[2][6] = {
		{
			"",
			"aaaaaaaaa",
			"aaaaaaaa",
			"bbcc",
			"cccc",
			0
		},
		{
			"",
			"AAAAAAAAA",
			"AAAAAAAA",
			"BBCC",
			"CCCC",
			0
		}
	};
	char **test;
	int j;

	j = 0;
	test = ft_tabstrcpy(tab);

	while (j < 2)
	{
		i = 0;
		while (i < 5)
		{
			f(test[i], func[j]);
			if (strcmp(test[i], ref[j][i]) != 0)
			{
				destroy(test);
				return (i + 1);
			}
			++i;
		}
		++j;
	}
	destroy(test);
	return (0);
}

int		t_strequ(int (*f)(char const *s1, char const *s2))
{
	int	a, b;

	const char	*test[7][2] =
	{
		{"",""},
		{"ble","ble"},
		{"bleh","ble"},
		{"ble","bleh"},
		{"ble","ale"},
		{"ble",""},
		{"","ble"}
	};
	int		i;

	i = 0;
	while (i < 7)
	{
		a = f(test[i][0], test[i][1]);
		b = strcmp(test[i][0],test[i][1]);
		if ((b == 0 && a != 1) || (b != 0 && a != 0))
			return (i + 1);
		i++;
	}
	return (0);
}


int		t_strrchr(char *(*f)(const char *, int))
{
	int i = 1;
	int j;
	char *vide = "";
	char *ref;
	char *test = "aaaaaaaaaaa";
	char *test2 = "\0\0\0\0\0";

	ref = malloc(512);
	for (j = 1; j <= 256; j++)
		ref[j - 1] = j;
	for (j = 1; j <= 256; j++)
	{
		if (f(ref, j) != strrchr(ref, j))
		{
			free(ref);
			return (i);
		}
	}

	i++;
	for (j = 1; j <= 256; j++)
	{
		if (f(vide, j) != strrchr(vide, j))
		{
			free(ref);
			return (i);
		}
	}

	i++;
	for (j = 1; j <= 256; j++)
	{
		if (f(test, j) != strrchr(test, j))
		{
			free(ref);
			return (i);
		}
	}

	i++;
	for (j = 1; j <= 256; j++)
	{
		if (f(test2, j) != strrchr(test2, j))
		{
			free(ref);
			return (i);
		}
	}
	free(ref);
	return (0);
}


int		t_strclr(void (*f)(char *))
{
	int		i = 1;
	char	*str = malloc (sizeof(char) * 20);
	char	*str2 = malloc (sizeof(char) * 20);

	str = memset(str, 'a', 20);
	str2 = memset(str2, 'a', 20);
	str = memcpy(str, "", 1);
	str2 = memcpy(str2, "", 1);
	f(str);
	if (memcmp(str, str2, 20) != 0)
	{
		free(str);
		free(str2);
		return (i);
	}

	i++;
	str = memset(str, 'a', 20);
	str2 = memset(str2, 'a', 20);
	str = memcpy(str, " ", 2);
	str2 = memcpy(str2, "\0", 2);
	f(str);
	if (memcmp(str, str2, 20) != 0)
	{
		free(str);
		free(str2);
		return (i);
	}

	i++;
	str = memset(str, 'a', 20);
	str2 = memset(str2, 'a', 20);
	str = memcpy(str, "Coucou", 7);
	str2 = memcpy(str2, "\0\0\0\0\0\0", 7);
	f(str);
	if (memcmp(str, str2, 20) != 0)
	{
		free(str);
		free(str2);
		return (i);
	}

	free(str);
	free(str2);
	return (0);
}

int		t_strncat(char *(*f)(char *, const char *, size_t))
{
	int i = 0;
	int j = 0;
	const char *src[] = {
		"Blop.",
		"",
		"Blop.",
		"",
		"Blop.",
		""
	};
	char *dst1;
	char *dst2;

	dst1 = (char *) malloc(sizeof(char) * 20);
	dst2 = (char *) malloc(sizeof(char) * 20);

	while (i < 2)
	{
		j = 0;
		while (j <= 10)
		{
			dst1 = memset(dst1, 'a', 19);
			dst1[19] = '\0';
			dst2 = memset(dst2, 'a', 19);
			dst2[19] = '\0';
			dst1 = memcpy(dst1, "", 1);
			dst2 = memcpy(dst2, "", 1);

			dst1 = f(dst1, src[i], j);
			dst2 = strncat(dst2, src[i], j);
			if (strcmp(dst1, dst2) != 0)
			{
				free(dst1);
				free(dst2);
				return (i + 1);
			}
			j++;
		}
		i++;
	}

	while (i < 4)
	{
		j = 0;
		while (j <= 10)
		{
			dst1 = memset(dst1, 'a', 19);
			dst1[19]= '\0';
			dst2 = memset(dst2, 'a', 19);
			dst2[19] = '\0';
			dst1 = memcpy(dst1, "bip", 4);
			dst2 = memcpy(dst2, "bip", 4);

			dst1 = f(dst1, src[i], j);
			dst2 = strncat(dst2, src[i], j);
			if (strcmp(dst1, dst2) != 0)
			{
				free(dst1);
				free(dst2);
				return (i + 1);
			}
			j++;
		}
		i++;
	}

	while (i < 6)
	{
		j = 0;
		while (j <= 10)
		{
			dst1 = memset(dst1, 'a', 19);
			dst1[19]= '\0';
			dst2 = memset(dst2, 'a', 19);
			dst2[19] = '\0';
			dst1 = memcpy(dst1, "trololololololol", 17);
			dst2 = memcpy(dst2, "trololololololol", 17);

			dst1 = f(dst1, src[i], j);
			dst2 = strncat(dst2, src[i], j);
			if (strcmp(dst1, dst2) != 0)
			{
				free(dst1);
				free(dst2);
				return (i + 1);
			}
			j++;
		}
		i++;
	}

	free(dst1);
	free(dst2);
	return 0;
}

int		t_strchr(char *(*f)(const char *, int))
{
	int i = 1;
	int j;
	char *vide = "";
	char *ref;
	char *test = "aaaaaaaaaaa";
	char *test2 = "\0\0\0\0\0";

	ref = malloc(512);
	for (j = 1; j <= 256; j++)
		ref[j - 1] = j;
	for (j = 1; j <= 256; j++)
	{
		if (f(ref, j) != strchr(ref, j))
		{
			free(ref);
			return (i);
		}
	}

	i++;
	for (j = 1; j <= 256; j++)
	{
		if (f(vide, j) != strchr(vide, j))
		{
			free(ref);
			return (i);
		}
	}

	i++;
	for (j = 1; j <= 256; j++)
	{
		if (f(test, j) != strchr(test, j))
		{
			free(ref);
			return (i);
		}
	}

	i++;
	for (j = 1; j <= 256; j++)
	{
		if (f(test2, j) != strchr(test2, j))
		{
			free(ref);
			return (i);
		}
	}
	free(ref);
	return (0);
}



int		t_strsplit(char **(*f)(char const *s, char c))
{
	int		i = 0;
	char	**tab;
	char	*srcs[] = { "",
		"*salut*kiki*le*****pingouin*",
		"*****salut*lol",
		"salut",
		"iiiiiiisalutiiiiii",
		"*********"
	};

//	tab = f(srcs[i], '*');
//	if (strcmp(tab[0], "") != 0 || tab[1] != NULL)
//	{
//		destroy(tab);
//		return (i + 1);
//	}
//	destroy(tab);
	i++;
	tab = f(srcs[i], '*');
	if (strcmp(tab[0], "salut") != 0
			|| strcmp(tab[1], "kiki") != 0
			|| strcmp(tab[2], "le") != 0
			|| strcmp(tab[3], "pingouin") != 0
			|| tab[4] != NULL)
	{
		destroy(tab);
		return (i + 1);
	}
	destroy(tab);
	i++;
	tab = f(srcs[i], '*');
	if (strcmp(tab[0], "salut") != 0
			|| strcmp(tab[1], "lol") != 0
			|| tab[2] != NULL)
	{
		destroy(tab);
		return (i + 1);
	}
	destroy(tab);
	i++;
	tab = f(srcs[i], '*');
	if (strcmp(tab[0], "salut") != 0 || tab[1] != NULL)
	{
		destroy(tab);
		return (i + 1);
	}
	destroy(tab);
	i++;
	tab = f(srcs[i], 'i');
	if (strcmp(tab[0], "salut") != 0 || tab[1] != NULL)
	{
		destroy(tab);
		return (i + 1);
	}
	destroy(tab);
	i++;
	tab = f(srcs[i], '*');
	if (strcmp(tab[0], "") != 0 || tab[1] != NULL)
	{
		destroy(tab);
		return (i + 1);
	}
	destroy(tab);
	return (0);
}

int				t_strcmp(int (*f)(const char *s1, const char *s2))
{
	int a, b;
	const char	*test[7][2] =
	{
		{"bleh", "ble"},
		{"ble", "bleh"},
		{"blah", "blah"},
		{"blah", "bleh"},
		{"", "blah"},
		{"blah", ""},
		{"", ""}
	};
	int			i = 0;

	while (i < 7)
	{
		b = strcmp(test[i][0], test[i][1]);
		a = f(test[i][0], test[i][1]);
		if ((b = 0 && a != 0) || (b < 0 && a >= 0) || ( b > 0 && a <= 0))
			return (i + 1);
		i++;
	}
	return (0);
}

int t_strnstr(char *(*f)(char const*,const char *,size_t))
{
	int i = 1;
	int j = 0;
	char *a,*b;
	char *str[]={
		"",
		"abc",
		"",
		"qwertyuiopasdfghjklzxvbnm1234567890)(*&^%$#@!\n\t\v\f QWERTYUIOPASDFGHJKLZXCVBNM<>:{}|ab",
		"a",
		"\n\t\v",
		"",
		"c"
	};
	char *ref[]={
		"",
		"",
		"abc",
		"qwertyuiopasdfghjklzxvbnm1234567890)(*&^%$#@!\n\t\v\f QWERTYUIOPASDFGHJKLZXCVBNM<>:{}|abc",
		"qwertyuiopasdfghjklzxvbnm1234567890)(*&^%$#@!\n\t\v\f QWERTYUIOPASDFGHJKLZXCVBNM<>:{}|abc",
		"qwertyuiopasdfghjklzxvbnm1234567890)(*&^%$#@!\n\t\v\f QWERTYUIOPASDFGHJKLZXCVBNM<>:{}|abc",
		"qwertyuiopasdfghjklzxvbnm1234567890)(*&^%$#@!\n\t\v\f QWERTYUIOPASDFGHJKLZXCVBNM<>:{}|abc",
		"qwertyuiopasdfghjklzxvbnm1234567890)(*&^%$#@!\n\t\v\f QWERTYUIOPASDFGHJKLZXCVBNM<>:{}|abc"
	};

	for (i = 0; i<7;i++)
	{
		for (j = 0; j < 200; j++)
		{
			a = f(ref[i],str[i],j);
			b = strnstr(ref[i],str[i],j);
			if (b == NULL && a == b)
				continue;
			if (!(a == b && strcmp(a,b) == 0))
				return (i+1);
		}
	}
	return (0);
}

int		t_strcat(char *(*f)(char *, const char *))
{
	int i = 0;
	const char *src[] = {
		"Blop.",
		"",
		"Blop.",
		""
	};
	char *dst1;
	char *dst2;

	dst1 = (char *) malloc(sizeof(char) * 100);
	dst2 = (char *) malloc(sizeof(char) * 100);

	while (i < 2)
	{
		dst1 = memcpy(dst1, "\0", 1);
		dst2 = memcpy(dst2, "\0", 1);
		dst1 = f(dst1, src[i]);
		dst2 = strcat(dst2, src[i]);
		if (strcmp(dst1, dst2) != 0)
		{
			free(dst1);
			free(dst2);
			return (i + 1);
		}
		i++;
	}
	while (i < 4)
	{
		dst1 = memcpy(dst1, "kariboubou\0", 11);
		dst2 = memcpy(dst2, "kariboubou\0", 11);
		dst1 = f(dst1, src[i]);
		dst2 = strcat(dst2, src[i]);
		if (strcmp(dst1, dst2) != 0)
		{
			free(dst1);
			free(dst2);
			return (i + 1);
		}
		i++;
	}
	free(dst1);
	free(dst2);
	return 0;
}


int t_memmove(void *(*ft)(void *, void *, size_t))
{
	void *s1;
	void *s2;
	void *str;
	int i;
	size_t size;

	size = 10;
	i=1;
	s1 = malloc(size * sizeof(char));
	s2 = malloc(size * sizeof(char));
	str = malloc (size * sizeof(char));
	str = memset(str,'a', size);
	s1 = ft(s1, str, size);
	s2 = memmove(s2, str, size);
	if (memcmp(s1, s2, size) != 0)
	{
		free(s1);
		free(s2);
		free(str);
		return (i);
	}
	i++;
	s1 = memset(s1,'b', size);
	s2 = memset(s2,'b', size);
	s1 = ft(s1, str, size - 5);
	s2 = memmove(s2, str, size - 5);
	if (memcmp(s1, s2, size) != 0)
	{
		free(s1);
		free(s2);
		free(str);
		return (i);
	}
	i++;
	s1 = memset(s1,'0', size);
	s2 = memset(s2,'0', size);
	s1 = ft(s1, str, 0);
	s2 = memmove(s2, str, 0);
	if (memcmp(s1, s2, size) != 0)
	{
		free(s1);
		free(s2);
		free(str);
		return (i);
	}
	i++;
	s1 = memset(s1,'0', size);
	s2 = memset(s2,'0', size);
	s1 = memset(s1,'1', 3);
	s2 = memset(s2,'1', 3);
	ft(s1 + 3, s1, 5);
	memmove(s2 + 3, s2, 5);
	if (memcmp(s1, s2, size) != 0)
	{
		free(str);
		free(s1);
		free(s2);
		return (i);
	}
	free(str);
	free(s1);
	free(s2);
	return 0;
}

int		t_strncpy(char *(*f)(char *, const char *, size_t))
{
	int i = 0;
	const char *src[] = {
		"Coucou.",
		"Coucou.",
		"Coucou.",
		"",
		"",
		"",
		"Hello je copiee\t   ",
		"Hello je copiee\t   ",
		"Hello je copiee\t   ",
		"Coucou c est kiki le pinguin.",
		"Coucou c est kiki le pinguin.",
		"Coucou c est kiki le pinguin."
	};
	size_t	size[] = { 0, 10, 20, 0, 10, 20, 0, 10, 20, 0, 10, 20 };
	char *dst1;
	char *dst2;

	dst1 = (char *) malloc(sizeof(char) * 512);
	dst2 = (char *) malloc(sizeof(char) * 512);
	while (i < 9)
	{
		dst1 = memset(dst1, 'a', 512);
		dst2 = memset(dst2, 'a', 512);
		dst1[511] = '\0';
		dst2[511] = '\0';
		dst1 = f(dst1, src[i], size[i]);
		dst2 = strncpy(dst2, src[i], size[i]);
		if (strcmp(dst1, dst2) != 0)
		{
			free(dst1);
			free(dst2);
			return (i+1);
		}
		i++;
	}
	dst1 = memcpy(dst1, "               \0       ", 20);
	dst2 = memcpy(dst2, "               \0       ", 20);
	dst1 = f(dst1, src[1], 20);
	dst2 = strncpy(dst2, src[1], 20);
	if (dst1[17] != dst2[17] || dst1[9] != dst2[9])
	{
		free(dst1);
		free(dst2);
		return (i+1);
	}
	free(dst1);
	free(dst2);
	return (0);
}

int		t_itoa(char *(*f)(int))
{
	int i = 1;
	char *s;
	if (strcmp((s = f(0)), "0") == 0)
		i++;
	else
		return (i);
	if (strcmp((s=f(10)), "10") == 0)
		i++;
	else
		return (i);
	if (strcmp((s = f(-42)), "-42") == 0)
		i++;
	else
		return (i);
	if (strcmp((s=f(-2147483648)), "-2147483648") == 0)
		i++;
	else
		return (i);
	if (strcmp((s=f(2147483647)), "2147483647") == 0)
		i++;
	else
		return (i);
	if (strcmp((s=f(987654321)), "987654321") == 0)
		i++;
	else
		return (i);
	if (strcmp((s=f(-10)), "-10") == 0)
		i++;
	else
		return (i);
	return (0);
}

int		t_strlcat(size_t (*f)(char *, const char *, size_t))
{
	char *tmp = strdup("toto");
	char *tmp2 = strdup("baba");
	char *tmp3 = strdup("toto");
	size_t i;

	for (i = 0; i < 15; i++)
	{
		if (f(tmp, tmp2, i) != strlcat(tmp3, tmp2, i))
		{
			free(tmp);
			free(tmp2);
			free(tmp3);
			return (++i);
		}
		if (strcmp(tmp, tmp3) != 0)
		{
			free(tmp);
			free(tmp3);
			free(tmp2);
			return (++i);
		}
		free(tmp);
		tmp = strdup("toto");
		free(tmp3);
		tmp3 = strdup("toto");
	}
	for (i = 0; i < 20; i++)
	{
		free(tmp);
		tmp = strdup("bdc");
		free(tmp3);
		tmp3 = strdup("bdc");
		if (f(tmp, tmp2, i) != strlcat(tmp3, tmp2, i))
		{
			free(tmp);
			free(tmp2);
			free(tmp3);
			return (++i);
		}
		if (strcmp(tmp, tmp3) != 0)
		{
			free(tmp);
			free(tmp2);
			free(tmp3);
			return (++i);
		}
	}
	for (i = 0; i < 25; i++)
	{
		free(tmp);
		tmp = strdup("bdcrw");
		free(tmp3);
		tmp3 = strdup("bdcrw");
		if (f(tmp, tmp2, i) != strlcat(tmp3, tmp2, i))
		{
			free(tmp);
			free(tmp2);
			free(tmp3);
			return (++i);
		}
		if (strcmp(tmp, tmp3) != 0)
		{
			free(tmp);
			free(tmp2);
			free(tmp3);
			return (++i);
		}
	}
	for (i = 0; i < 15; i++)
	{
		free(tmp);
		tmp = strdup("");
		free(tmp3);
		tmp3 = strdup("");
		if (f(tmp, tmp2, i) != strlcat(tmp3, tmp2, i))
		{
			free(tmp);
			free(tmp2);
			free(tmp3);
			return (++i);
		}
		if (strcmp(tmp, tmp3) != 0)
		{
			free(tmp);
			free(tmp2);
			free(tmp3);
			return (++i);
		}
	}
	free(tmp2);
	tmp2 = strdup("");
	for (i = 0; i < 15; i++)
	{
		free(tmp);
		tmp = strdup("bdc");
		free(tmp3);
		tmp3 = strdup("bdc");
		if (f(tmp, tmp2, i) != strlcat(tmp3, tmp2, i))
			return (++i);
		if (strcmp(tmp, tmp3) != 0)
			return (++i);
	}
	free(tmp2);
	tmp2 = strdup("");
	for (i = 0; i < 15; i++)
	{
		free(tmp);
		tmp = strdup("");
		free(tmp3);
		tmp3 = strdup("");
		if (f(tmp, tmp2, i) != strlcat(tmp3, tmp2, i))
		{
			free(tmp);
			free(tmp2);
			free(tmp3);
			return (++i);
		}
		if (strcmp(tmp, tmp3) != 0)
		{
			free(tmp);
			free(tmp2);
			free(tmp3);
			return (++i);
		}
	}
	free(tmp);
	free(tmp2);
	free(tmp3);
	return (0);
}

int		t_memcmp(int (*ft)(const void *, const void *, size_t))
{
	void *s1;
	void *s2;
	int i, a, b;
	size_t size;

	size = 10;
	i=1;
	s1 = malloc(size * sizeof(char));
	s2 = malloc(size * sizeof(char));
	s1 = memset(s1, 'a', 10);
	s2 = memset(s2, 'a', 10);
	a = ft(s1, s2, size);
	b = memcmp(s1, s2, size);
	if (!((a == 0 && b == 0) || ( a > 0 && b > 0) || (a < 0 && b < 0)))
	{
		free(s2);
		free(s1);
		return (i);
	}
	i++;
	s1 = memset(s1, 'a', 10);
	s2 = memset(s2, 'b', 10);
	a = ft(s1, s2, size);
	b = memcmp(s1, s2, size);
	if (!((a == 0 && b == 0) || ( a > 0 && b > 0) || (a < 0 && b < 0)))
	{
		free(s1);
		free(s2);
		return (i);
	}
	i++;
	s1 = memset(s1, 'b', 10);
	s2 = memset(s2, 'a', 10);
	a = ft(s1, s2, size);
	b = memcmp(s1, s2, size);
	if (!((a == 0 && b == 0) || ( a > 0 && b > 0) || (a < 0 && b < 0)))
	{
		free(s1);
		free(s2);
		return (i);
	}
	i++;
	s1 = memset(s1, 'a', 10);
	s2 = memset(s2, 'b', 10);
	a = ft(s1, s2, 0);
	b = memcmp(s1, s2, 0);
	if (!((a == 0 && b == 0) || ( a > 0 && b > 0) || (a < 0 && b < 0)))
	{
		free(s1);
		free(s2);
		return (i);
	}
	i++;
	s1 = memset(s1, 'a', 10);
	s2 = memset(s2, 'b', 10);
	s1 = memset(s1, 'c', 5);
	s2 = memset(s2, 'c', 5);
	a = ft(s1, s2, 5);
	b = memcmp(s1, s2, 5);
	if (!((a == 0 && b == 0) || ( a > 0 && b > 0) || (a < 0 && b < 0)))
	{
		free(s1);
		free(s2);
		return (i);
	}
	i++;
	s1 = memset(s1, 'a', 10);
	s2 = memset(s2, 'b', 10);
	s1 = memset(s1, 'c', 9);
	s2 = memset(s2, 'c', 9);
	a = ft(s1, s2, 10);
	b = memcmp(s1, s2, 10);
	if (!((a == 0 && b == 0) || ( a > 0 && b > 0) || (a < 0 && b < 0)))
	{
		free(s1);
		free(s2);
		return (i);
	}
	free(s1);
	free(s2);
	return 0;
}

int t_strtrim(char *(*f)(char const *))
{
	int i = 0;
	char *a;
	char *name;
	char *str[2][15] =
	{
		{
			"",
			"     ",
			"\t",
			"a",
			"abc",
			"  a",
			"  a c",
			"a  ",
			"a c  ",
			" a ",
			" a c ",
			"\n",
			" \t ",
			"       hello je suis une longue chaine       ",
			"     \n   hello je\nsuis\tune longue chaine   \t   "
		},
		{
			"",
			"",
			"",
			"a",
			"abc",
			"a",
			"a c",
			"a",
			"a c",
			"a",
			"a c",
			"",
			"",
			"hello je suis une longue chaine",
			"hello je\nsuis\tune longue chaine"
		}
	};

	while (i < 15)
	{
		a = (*f)(str[0][i]);
		if (strcmp(a, str[1][i]) != 0)
		{
			free(a);
			return (i+1);
		}
		free(a);
		i++;
	}
	return 0;
}

int		t_memcpy(void *(*f)(void *, const void *, size_t))
{
	void	*s1, *t1;
	void	*s2, *t2;
	void	*str;
	int		i;
	int		size = 10;

	s1 = malloc(size * sizeof(char));
	s2 = malloc(size * sizeof(char));
	str = malloc (size * sizeof(char));

	for (i = 0; i < 10; i++)
	{
		str = memcpy(str, (void *)"qwertyuiop", size);
		s1 = memset(s1,'b', size);
		s2 = memset(s2,'b', size);
		t1 = f(s1, str, i);
		t2 = memcpy(s2, str, i);
		if (memcmp(s1, s2, size) != 0 || (t1 && (t1 - s1 != t2 - s2)) || (!t1 && t2))
		{
			free(s1);
			free(s2);
			free(str);
			return (i+1);
		}
	}
	for (i = 0; i < 10; i++)
	{
		str = memset(str,'\0', size);
		s1 = memset(s1,'b', size);
		s2 = memset(s2,'b', size);
		t1 = f(s1, str, i);
		t2 = memcpy(s2, str, i);
		if (memcmp(s1, s2, size) != 0 || (t1 && (t1 - s1 != t2 - s2)) || (!t1 && t2))
		{
			free(s1);
			free(s2);
			free(str);
			return (i+1);
		}
	}
	for (i = 0; i < 10; i++)
	{
		str = memset(str, 'A' + 128, size);
		s1 = memset(s1,'c', size);
		s2 = memset(s2,'c', size);
		t1 = f(s1, str, i);
		t2 = memcpy(s2, str, i);
		if (memcmp(s1, s2, size) != 0 || (t1 && (t1 - s1 != t2 - s2)) || (!t1 && t2))
		{
			free(s1);
			free(s2);
			free(str);
			return (i+1);
		}
	}
	free(str);
	free(s1);
	free(s2);
	return 0;
}


int		t_memccpy(void *(*f)(void *, const void *, int, size_t))
{
	void	*s1, *t1;
	void	*s2, *t2;
	void	*str;
	int		i, j;
	int		size = 10;

	s1 = malloc(size * sizeof(char));
	s2 = malloc(size * sizeof(char));
	str = malloc (size * sizeof(char));

	for (j = 10; j > 0; j--)
		for (i = 1; i <= j; i++)
		{
			str = memset(str,'a', size);
			((char *)str)[10 - i] = 'b';
			s1 = memset(s1,'c', size);
			s2 = memset(s2,'c', size);
			t1 = f(s1, str,'b', j);
			t2 = memccpy(s2, str,'b', j);
			if ((t2 == NULL && t2 != t1) || memcmp(s1, s2, size) != 0 || (t1 != NULL && t1 - s1 != t2 - s2))
			{
				free(str);
				free(s1);
				free(s2);
				return (i);
			}
		}
	for (i = 1; i <= j; i++)
	{
		str = memset(str,'a', size);
		((char *)str)[10 - i] = 'b';
		s1 = memset(s1,'c', size);
		s2 = memset(s2,'c', size);
		t1 = f(s1, str,'b', j);
		t2 = memccpy(s2, str,'b', j);
		if ((t1 && !t2) || (!t1 && t2) || (t1 && memcmp(s1, s2, size) !=0))
		{
			free(s1);
			free(s2);
			free(str);
			return (i);
		}
	}
	free(str);
	free(s1);
	free(s2);
	return 0;
}

int		t_memchr(void *(*f)(const void *, int, size_t))
{
	void *s1,*t1;
	void *s2,*t2;
	int i, j;
	int size;

	size = 10;
	s1 = malloc(size * sizeof(char));
	s2 = malloc(size * sizeof(char));
	for (j = 0; j <= size; j++)
		for (i = 0; i < size; i++)
		{
			s1 = memset(s1,'a', size);
			s2 = memset(s2,'a', size);
			((unsigned char *)s1)[i] = 'b';
			((unsigned char *)s2)[i] = 'b';
			t1 = f(s1,'b', j);
			t2 = memchr(s2,'b', j);
			if (memcmp(s1, s2, size) != 0 || (t2 && !t1) || (t1 && (t1 - s1) != (t2 - s2)))
			{
				free(s1);
				free(s2);
				return (i+1);
			}
		}
	/* test chaine a 0 */
	for (j = 0; j <= size; j++)
		for (i = 0; i < size; i++)
		{
			s1 = memset(s1,'\0', size);
			s2 = memset(s2,'\0', size);
			((unsigned char *)s1)[i] = 'b';
			((unsigned char *)s2)[i] = 'b';
			t1 = f(s1,'b', j);
			t2 = memchr(s2,'b', j);
			if (memcmp(s1, s2, size) != 0 || (t2 && !t1) || (t1 && (t1 - s1) != (t2 -\
							s2)))
			{
				free(s1);
				free(s2);
				return (i+101);
			}
		}
	/* test find 0 */
	for (j = 0; j <= size; j++)
		for (i = 0; i < size; i++)
		{
			s1 = memset(s1,'a', size);
			s2 = memset(s2,'a', size);
			((unsigned char *)s1)[i] = '\0';
			((unsigned char *)s2)[i] = '\0';
			t1 = f(s1,'\0', j);
			t2 = memchr(s2,'\0', j);
			if (memcmp(s1, s2, size) != 0 || (t2 && !t1) || (t1 && (t1 - s1) != (t2 -\
							s2)))
			{
				free(s1);
				free(s2);
				return (i+201);
			}
		}
	/* depassement unsigned char */
	for (j = 0; j <= size; j++)
		for (i = 0; i < size; i++)
		{
			s1 = memset(s1,'a', size);
			s2 = memset(s2,'a', size);
			((unsigned char *)s1)[i] = (unsigned char)500;
			((unsigned char *)s2)[i] = (unsigned char)500;
			t1 = f(s1, 500, j);
			t2 = memchr(s2, 500, j);
			if (memcmp(s1, s2, size) != 0 || (t2 && !t1) || (t1 && (t1 - s1) != (t2 -\
							s2)))
			{
				free(s1);
				free(s2);
				return (i+301);
			}
		}
	/* depassement char */
	for (j = 0; j <= size; j++)
		for (i = 0; i < size; i++)
		{
			s1 = memset(s1,'a', size);
			s2 = memset(s2,'a', size);
			((unsigned char *)s1)[i] = 145;
			((unsigned char *)s2)[i] = 145;
			t1 = f(s1, 145, j);
			t2 = memchr(s2, 145, j);
			if (memcmp(s1, s2, size) != 0 || (t2 && !t1) || (t1 && (t1 - s1) != (t2 -\
							s2)))
			{
				free(s1);
				free(s2);
				return (i+401);
			}
		}
	free(s1);
	free(s2);
	return 0;
}


int	t_memset(void *(*f)(void *, int, size_t))
{
	void *s1;
	void *s2;
	int i, j;
	int size = 512;
	char *name;

	s1 = malloc(size * sizeof(char));
	s2 = malloc(size * sizeof(char));
	memset(s1, '\v', size);
	memset(s2, '\v', size);
	for (i = 0; i < 300; i++)
	{
		for (j = 0; j < 256; j++)
		{
			s1 = f(s1, i, j);
			s2 = memset(s2, i, j);
			if (s1 == NULL)
			{
				free(s2);
				return (1);
			}
			if (memcmp(s1, s2, size) != 0)
			{
				free(s1);
				free(s2);
				return (i+1);
			}
		}
	}
	free(s1);
	free(s2);
	return 0;
}

int	t_bzero(void *(*f)(void *, size_t))
{
	void *s1;
	void *s2;
	int i;
	int size = 257;
	char *name;

	s1 = malloc(size * sizeof(char));
	s2 = malloc(size * sizeof(char));
	bzero(s1, size);
	bzero(s2, size);
	for (i = 0; i < 256; i++)
	{
		f(s1, i);
		bzero(s2, i);
		if (memcmp(s1, s2, size) != 0)
		{
			free(s1);
			free(s2);
			return (i +1);
		}
	}
	free(s1);
	free(s2);
	return 0;
}


int t_atoi (int (*f)(const char *))
{
	int i = 0;
	int a,b;
	char *str[] = {
		"0",//1
		"10",
		"-10",
		"123456789",
		"987654321",//5
		"424242",
		"+424242",
		"-424242",
		"++42",
		"--42",//10
		"+-42",
		"-+42",
		"-2147483648",
		"2147483647",
		"42a",//15
		"-42b",
		"42/0",
		"42:0",
		" \n\t1337",
		"\r\v\f\r42",//20
		""
	};

	while (i < 21)
	{
		a = (*f)(str[i]);
		b = atoi(str[i]);
		if (a != b)
			return (i + 1);
		i++;
	}
	return 0;
}

int	t_strlen (size_t (*f)(const char *))
{
	int i = 0;
	int a,b;
	char *str[] = {
		"",//1
		" ",
		"123456789",
		"qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASHJKL:ZXCVBNMQWERTYUIO:LKJHGFDSZXCVBNM<"
	};

	while (i < 4)
	{
		a = (*f)(str[i]);
		b = strlen(str[i]);
		if (a != b)
			return (i + 1);
		i++;
	}
	return 0;
}

int	t_strdup(char *(*f)(const char *))
{
	int i = 0;
	char *a;
	char *str[] = {
		"123456789",
		"QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnmi",
		""
	};

	while (i < 3)
	{
		a = f(str[i]);
		if (a == NULL)
			return (i+1);
		if (strcmp(a,str[i]) != 0 || a == str[i])
		{
			free(a);
			return i+1;
		}
		free(a);
		i++;
	}
	return 0;
}

int	t_strcpy(char* (*f)(char *s1,const char *s2))
{
	int		i = 0;
	char	*s1[]={
		"",
		"123456789",
		"",
		"\0\0\0\0\0\0\0\0\0",
		"123456789aa",
		"123456789aabb",
		"123456789aabbcc",
		"12345",
		"123456789aabbccdd"
	};
	char	*s2[] = {
		"",
		"",
		"123456789",
		"123",
		"\0\0\0\0\0\0\0\0\0\0",
		"123456789",
		"12345",
		"123456789",
		"qwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM123456789"
	};
	char	*str,*str2;

	str = (char *)malloc(512 * sizeof(char));
	while (i< 512)
		str[i++] = '\v';
	str[511] = '\0';
	str2 = strdup(str);
	i=0;
	while (i < 9)
	{
		str = strcpy(str,s1[i]);
		str2 = strcpy(str2,s1[i]);
		str = f(str,s2[i]);
		str2 = f(str2,s2[i]);
		if (strcmp(str,str2) != 0 || str == s1[i])
		{
			free(str);
			free(str2);
			return (i+1);
		}
		i++;
	}
	free(str);
	free(str2);
	return 0;
}

int	t_isalpha(int (*f)(int))
{
	int i = -1;
	while(++i < 300)
		if (f(i) != isalpha(i))
			return (i+1);
	return 0;
}

int	t_isdigit(int (*f)(int))
{
	int i = -1;
	while(++i < 300)
		if (f(i) != isdigit(i))
			return (i+1);
	return 0;
}

int	t_isalnum(int (*f)(int))
{
	int i = -1;
	while(++i < 300)
		if (f(i) != isalnum(i))
			return (i+1);
	return 0;
}

int	t_isascii(int (*f)(int))
{
	int i = -1;
	while(++i < 300)
		if (f(i) != isascii(i))
			return (i+1);
	return 0;
}

int	t_isprint(int (*f)(int))
{
	int i = -1;
	while(++i < 300)
		if (f(i) != isprint(i))
			return (i+1);
	return 0;
}

int	t_toupper(int (*f)(int))
{
	int i = -1;
	while(++i < 300)
		if (f(i) != toupper(i))
			return (i+1);
	return 0;
}

int	t_tolower(int (*f)(int))
{
	int i = -1;
	while(++i < 300)
		if (f(i) != tolower(i))
			return (i+1);
	return 0;
}

void		ft_test(void *f, int name)
{
	int flag=-1;
	switch(name)
	{
		case 0:
			flag = t_memset(f);
			break;
		case 1:
			flag = t_bzero(f);
			break;
		case 2:
			flag = t_memcpy(f);
			break;
		case 3:
			flag = t_memccpy(f);
			break;
		case 4:
			flag = t_memmove(f);
			break;
		case 5:
			flag = t_memchr(f);
			break;
		case 6:
			flag = t_memcmp(f);
			break;
		case 7:
			flag = t_strlen(f);
			break;
		case 8:
			flag = t_strdup(f);
			break;
		case 9:
			flag = t_strcpy(f);
			break;
		case 10:
			flag = t_strncpy(f);
			break;
		case 11:
			flag = t_strcat(f);
			break;
		case 12:
			flag = t_strncat(f);
			break;
		case 13:
			flag = t_strlcat(f);
			break;
		case 14:
			flag = t_strchr(f);
			break;
		case 15:
			flag = t_strrchr(f);
			break;
		case 16:
			flag = t_strstr(f);
			break;
		case 17:
			flag = t_strnstr(f);
			break;
		case 18:
			flag = t_strcmp(f);
			break;
		case 19:
			flag = t_strncmp(f);
			break;
		case 20:
			flag = t_atoi(f);
			break;
		case 21:
			flag = t_isalpha(f);
			break;
		case 22:
			flag = t_isdigit(f);
			break;
		case 23:
			flag = t_isalnum(f);
			break;
		case 24:
			flag = t_isascii(f);
			break;
		case 25:
			flag = t_isprint(f);
			break;
		case 26:
			flag = t_toupper(f);
			break;
		case 27:
			flag = t_tolower(f);
			break;
		case 28:
			flag = t_memalloc(f);
			break;
		case 29:
			flag = t_memdel(f);
			break;
		case 30:
			flag = t_strnew(f);
			break;
		case 31:
			flag = t_strdel(f);
			break;
		case 32:
			flag = t_strclr(f);
			break;
		case 33:
			flag = t_striter(f);
			break;
		case 34:
			flag = t_striteri(f);
			break;
		case 35:
			flag = t_strmap(f);
			break;
		case 36:
			flag = t_strmapi(f);
			break;
		case 37:
			flag = t_strequ(f);
			break;
		case 38:
			flag = t_strnequ(f);
			break;
		case 39:
			flag = t_strsub(f);
			break;
		case 40:
			flag = t_strjoin(f);
			break;
		case 41:
			flag = t_strtrim(f);
			break;
		case 42:
			flag = t_strsplit(f);
			break;
		case 43:
			flag = t_itoa(f);
			break;
		default :
			;
	}
	if( flag == -1)
	{
		write(1,ft_name[name],strlen(ft_name[name]));
		write(1,"() : \033[33mcheck manuel\033[0m\n",strlen("() : \033[33mcheck manuel\033[0m\n"));
	}
	else if (flag)
	{
		write(1,ft_name[name],strlen(ft_name[name]));
		write(1,"() : \033[31mfail\033[0m\n",strlen("() : \033[33mfail\033[0m\n"));
	}
	else
	{
		write(1,ft_name[name],strlen(ft_name[name]));
		write(1,"() : \033[32mok\033[0m\n",strlen("() : \033[33mok\033[0m\n"));
	}
}

int main()
{
	void *handle;
	void *fun;
	int nb_fun = 52;
	int i;

	i = 0;
	if ((handle = dlopen("libft.so" , RTLD_LAZY)) != NULL)
	{
		while (i < nb_fun)
		{
			if ((fun = dlsym(handle, ft_name[i] )) != NULL)
			{
				ft_test(fun,i);
			}
			else
				printf("%s() : \033[31minexistante\033[0m\n",ft_name[i]);
			i++;
		}
		dlclose(handle);
	}
	else
		write(1, "libft.so inexsistante\n",strlen("libft.so inexsistante\n"));
	return 0;
}

