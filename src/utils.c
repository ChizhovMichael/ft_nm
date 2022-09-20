/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 11:20:36 by tgildero          #+#    #+#             */
/*   Updated: 2022/09/11 11:20:38 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_nm.h"

int is_same_architecture() {
    uint16_t x = 0x0001;

    if (*((uint8_t *) &x) == __g_endian)
        return 1;
    return 0;
}

uint64_t swap_bytes_64(void *pv, long n) {
    char *p, *res;
    uint64_t value;
    long lo, hi;


    value = 0;
    p = pv;
    res = (char *) &value;

    if (is_same_architecture())
        for (hi = 0; hi < n; ++hi)
            res[hi] = p[hi];
    else
        for (hi = n - 1, lo = 0; hi >= 0; --hi, ++lo)
            res[lo] = p[hi];

    return (value);
}

uint32_t swap_bytes_32(void *pv, long n) {
    char *p, *res;
    uint32_t value;
    long lo, hi;


    value = 0;
    p = pv;
    res = (char *) &value;

    if (is_same_architecture())
        for (hi = 0; hi < n; ++hi)
            res[hi] = p[hi];
    else
        for (hi = n - 1, lo = 0; hi >= 0; --hi, ++lo)
            res[lo] = p[hi];

    return (value);
}

int swap_bytes_64_int(void *pv, long n) {
    char *p, *res;
    int value;
    long lo, hi;


    value = 0;
    p = pv;
    res = (char *) &value;

    if (is_same_architecture())
        for (hi = 0; hi < n; ++hi)
            res[hi] = p[hi];
    else
        for (hi = n - 1, lo = 0; hi >= 0; --hi, ++lo)
            res[lo] = p[hi];

    return (value);
}

int swap_bytes_32_int(void *pv, long n) {
    char *p, *res;
    int value;
    long lo, hi;


    value = 0;
    p = pv;
    res = (char *) &value;

    if (is_same_architecture())
        for (hi = 0; hi < n; ++hi)
            res[hi] = p[hi];
    else
        for (hi = n - 1, lo = 0; hi >= 0; --hi, ++lo)
            res[lo] = p[hi];

    return (value);
}

void print_error(int error, char *mess) {
    if (error == ERROR_FILE_EXISTS) {
        ft_putstr_fd("ft_nm: '", 2);
        ft_putstr_fd(mess, 2);
        ft_putstr_fd("': No such file\n", 2);
    } else if (error == ERROR_FORMAT_CODE) {
        ft_putstr_fd("ft_nm: ", 2);
        ft_putstr_fd(mess, 2);
        ft_putstr_fd(": file format not recognized\n", 2);
    } else if (error == ERROR_TYPE_IS_DIR) {
        ft_putstr_fd("ft_nm: Warning: '", 2);
        ft_putstr_fd(mess, 2);
        ft_putstr_fd("' is a directory\n", 2);
    } else if (error == ERROR_FILE_SHORT_RECOGNIZED) {
        ft_putstr_fd("ft_nm: ", 2);
        ft_putstr_fd(mess, 2);
        ft_putstr_fd(": file too short\n", 2);
        ft_putstr_fd("ft_nm: ", 2);
        ft_putstr_fd(mess, 2);
        ft_putstr_fd(": file format not recognized\n", 2);
    } else if (error == ERROR_TYPE_ORDINARY) {
        ft_putstr_fd("ft_nm: Warning: '", 2);
        ft_putstr_fd(mess, 2);
        ft_putstr_fd("' is not an ordinary file\n", 2);
    } else if (error == ERROR_FILE_TRUNCATED) {
        ft_putstr_fd("ft_nm: ", 2);
        ft_putstr_fd(mess, 2);
        ft_putstr_fd(" file truncated\n", 2);
    } else if (error == ERROR_NO_SYMBOLS) {
        ft_putstr_fd("ft_nm: ", 2);
        ft_putstr_fd(mess, 2);
        ft_putstr_fd(": no symbols\n", 2);
    }
}

int ft_strcmp(const char *s1, const char *s2) {
    unsigned char *c1;
    unsigned char *c2;

    c1 = (unsigned char *) s1;
    c2 = (unsigned char *) s2;
    while (c1 && *c1 == '_')
        ++c1;
    while (c2 && *c2 == '_')
        ++c2;
    while (ft_tolower(*c1) == ft_tolower(*c2) && ft_tolower(*c1) && ft_tolower(*c2)) {
        ++c1;
        ++c2;
    }
    if ((ft_tolower(*(unsigned char *) c1) - ft_tolower(*(unsigned char *) c2)) == 0) {
        return (ft_tolower(*(unsigned char *) s1) - ft_tolower(*(unsigned char *) s2));
    }
    return (ft_tolower(*(unsigned char *) c1) - ft_tolower(*(unsigned char *) c2));
}

void free_list(node *head) {
    node *prev = head;
    node *cur = head;
    while (cur) {
        prev = cur;
        cur = prev->ptr;
        free(prev);
    }
}