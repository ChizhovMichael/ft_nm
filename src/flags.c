/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 22:02:36 by tgildero          #+#    #+#             */
/*   Updated: 2022/04/12 22:02:38 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_nm.h"

int __g_flags = 0;
char __g_options[3] = {
        'h',
        'a',
        'A'
};

/**
 * @param  needle   [char]
 * @param  haystack [char[]]
 * @return          [0, 1]
 */
int in_array(char needle, char *haystack) {
    for (int i = 0; haystack[i]; ++i) {
        if (needle == haystack[i])
            return (1);
    }
    return (0);
}

/**
 * @param option [., -, 1, ...]
 */
void option_error(char option) {
    ft_putstr_fd("ft_nm: invalid option -- '", 1);
    ft_putchar_fd(option, 1);
    ft_putstr_fd("'\n", 1);
    ft_putstr_fd(INFO, 1);
    exit(1);
}

/**
 * @param __flags [0]
 * @param argv    [--asdasd, --, -gf, -g, ---sdf] 
 */
void init_f(int *__flags, char *argv) {
    int i = 1;

    while (argv[i]) {
        if (!ft_isalpha(argv[i]) ||
            !in_array(argv[i], __g_options)) {
            option_error(argv[i]);
        }
        if (argv[i] == 'h') {
            ft_putstr_fd(INFO, 1);
            exit(0);
        }
        i++;
    }

    /**
     * this ends the implementation of the bonus part
     */
    (void) __flags;
}

void delete_node(t_list **head, char *value) {
    t_list *tmp = *head;
    t_list *prev;

    if (tmp != NULL && !strcmp(tmp->content, value)) {
        *head = tmp->next;
        free(tmp);
        return;
    }

    while (tmp != NULL && strcmp(tmp->content, value)) {
        prev = tmp;
        tmp = tmp->next;
    }

    if (tmp == NULL)
        return;

    prev->next = tmp->next;
    free(tmp);
}
