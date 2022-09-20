/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 11:20:36 by tgildero          #+#    #+#             */
/*   Updated: 2022/09/11 11:20:38 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "../libft/libft.h"
# include "./elf.h"
# include <stdio.h>
# include <stdint.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>

# define __use_flags 0
# define __validation_file 1
# define INFO "Usage: ft_nm [option(s)] [file(s)]\n List symbols in [file(s)] (a.out by default).\n The options are:\n  -a	Display debugger-only symbols\n  -g	Display only external symbols\n  -p	Do not sort the symbols\n  -r	Reverse the sense of the sort\n  -u	Display only undefined symbols\n  -h	Display this information\n"
# define SUCCESS 0
# define ERROR_FILE_EXISTS 1
# define ERROR_FORMAT_CODE 2
# define ERROR_TYPE_IS_DIR 3
# define ERROR_FILE_SHORT_RECOGNIZED 4
# define ERROR_TYPE_ORDINARY 5
# define ERROR_FILE_TRUNCATED 6
# define ERROR_NO_SYMBOLS 7

# define SWAP32(x) swap_bytes_32(&x, sizeof(x))
# define SWAP64(x) swap_bytes_64(&x, sizeof(x))
# define SWAP32INT(x) swap_bytes_32_int(&x, sizeof(x))
# define SWAP64INT(x) swap_bytes_64_int(&x, sizeof(x))


extern int	__g_flags;
extern char	__g_options[3];
extern int	__g_endian;

typedef void (*handler)(char *);

typedef struct node {
    char type;
    char *name;
    uint64_t offset;
    struct node *ptr;
} node;

void		delete_node(t_list **head, char *value);
void		init_f(int *__flags, char *argv);
int			validate_magic(const char *dst);
int			validate_dir(mode_t mode);
int			validate_size(char *dst, unsigned long size);
int     	validate_another(char *dst);
int     	validate_count_symbols_table(char *dst);
int     	validate_count_sht_strtab(char *dst);
void		handler_none(char *dst);
void		handler_elf32(char *dst);
void		handler_elf64(char *dst);
int			is_same_architecture();
uint32_t	swap_bytes_32(void *pv, long n);
uint64_t	swap_bytes_64(void *pv, long n);
int         swap_bytes_32_int(void *pv, long n);
int         swap_bytes_64_int(void *pv, long n);
void		print_error(int error, char *mess);
int         ft_strcmp(const char *s1, const char *s2);
void        free_list(node *head);

#endif