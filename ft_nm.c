/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 11:20:36 by tgildero          #+#    #+#             */
/*   Updated: 2022/09/11 11:20:38 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_nm.h"

int __g_endian;

handler handlers[2] = {
        &handler_elf32,
        &handler_elf64
};

int processor(char *file, int show_name) {
    struct stat buf;
    char *dst;
    int fd;
    int error;

    fd = open(file, O_RDONLY);

    if (fd == -1)
        return ERROR_FILE_EXISTS;

    if (fstat(fd, &buf) != 0) {
        ft_putstr_fd("fstat error\n", 2);
        return (0);
    }

    if ((error = validate_dir(buf.st_mode)) != SUCCESS)
        return error;

    if (buf.st_size == 0)
        return (0);

    if ((dst = mmap(0, buf.st_size, PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED) {
        ft_putstr_fd("mmap error\n", 2);
        return (0);
    }

    __g_endian = dst[EI_DATA];


    if ((error = validate_magic(dst)) != SUCCESS)
        return error;

    if ((error = validate_size(dst, buf.st_size)) != SUCCESS)
        return error;

    if ((error = validate_count_symbols_table(dst)) != SUCCESS)
        return error;

    if ((error = validate_count_sht_strtab(dst)) != SUCCESS)
        return error;

    if (show_name) {
        ft_putchar_fd('\n', 1);
        ft_putstr_fd(file, 1);
        ft_putstr_fd(":\n", 1);
    }

    // основная логика
    handlers[dst[EI_CLASS] - 1](dst);

    if (munmap(dst, buf.st_size) == -1) {
        ft_putstr_fd("unmmap error\n", 2);
        return (0);
    }

    close(fd);
    return (0);
}


int main(int argc, char **argv) {

    t_list *_ar = NULL;
    t_list *_head = NULL;
    int ret = 0;


    for (int i = 1; i < argc; ++i) {
        ft_lstadd_back(&_ar, ft_lstnew(argv[i]));
    }

    if (!ft_lstsize(_ar))
        ft_lstadd_back(&_ar, ft_lstnew("a.out"));

    _head = _ar;

    while (_head) {
        ret = processor((char *) _head->content, ft_lstsize(_ar) > 1 ? 1 : 0);

        print_error(ret, (char *) _head->content);

        _head = _head->next;
    }

    while (_ar) {
        t_list *tmp = _ar;
        _ar = _ar->next;
        free(tmp);
    }
    if (ret == ERROR_FORMAT_CODE) {
        return 1;
    }

    return (0);
}