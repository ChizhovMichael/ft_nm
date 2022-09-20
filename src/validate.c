/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_magic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 11:20:36 by tgildero          #+#    #+#             */
/*   Updated: 2022/09/11 11:20:38 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_nm.h"

int validate_magic(const char *dst) {
    if ((dst[EI_MAG0] != ELFMAG0) ||
        (dst[EI_MAG1] != ELFMAG1) ||
        (dst[EI_MAG2] != ELFMAG2) ||
        (dst[EI_MAG3] != ELFMAG3))
        return ERROR_FORMAT_CODE;

    if (!(dst[EI_CLASS] >= 1 && dst[EI_CLASS] <= 2))
        return ERROR_FORMAT_CODE;


    if (dst[EI_VERSION] != 1)
        return ERROR_FORMAT_CODE;


    if (!((dst[EI_OSABI] >= 0 && dst[EI_OSABI] <= 4) ||
          (dst[EI_OSABI] >= 6 && dst[EI_OSABI] <= 18)))
        return ERROR_FORMAT_CODE;

    if (dst[EI_PAD] != 0)
        return ERROR_FORMAT_CODE;

    if (dst[EI_DATA] != 1 && dst[EI_DATA] != 2)
        return ERROR_FORMAT_CODE;

    return SUCCESS;
}

int validate_dir(mode_t mode) {
    if (S_ISDIR(mode))
        return ERROR_TYPE_IS_DIR;

    if (!S_ISREG(mode))
        return ERROR_TYPE_ORDINARY;

    return SUCCESS;
}

int validate_size(char *dst, unsigned long size) {
    Elf32_Ehdr *ehdr32;
    Elf64_Ehdr *ehdr64;

    if (dst[EI_CLASS] == 1) {
        ehdr32 = (Elf32_Ehdr *) dst;

        if (SWAP32(ehdr32->e_shoff) +
            SWAP32(ehdr32->e_shentsize) * SWAP32(ehdr32->e_shnum) > size)
            return ERROR_FILE_SHORT_RECOGNIZED;

        if ((dst + SWAP32(ehdr32->e_shoff)) > (dst + size))
            return ERROR_FORMAT_CODE;

//        if (SWAP32(ehdr32->e_shentsize) >
//            SWAP32(ehdr32->e_phoff) + SWAP32(ehdr32->e_phentsize) * SWAP32(ehdr32->e_phnum)) {
//            return ERROR_FORMAT_CODE;
//        }

        if (SWAP32(ehdr32->e_phoff) +
            SWAP32(ehdr32->e_phentsize) * SWAP32(ehdr32->e_phnum) > size)
            return ERROR_FORMAT_CODE;

        if (SWAP32(ehdr32->e_shnum) < 1)
            return ERROR_FORMAT_CODE;
    }


    if (dst[EI_CLASS] == 2) {
        ehdr64 = (Elf64_Ehdr *) dst;

        if (SWAP64(ehdr64->e_shoff) +
            SWAP64(ehdr64->e_shentsize) * SWAP64(ehdr64->e_shnum) > size)
            return ERROR_FILE_SHORT_RECOGNIZED;

        if ((dst + SWAP64(ehdr64->e_shoff)) > (dst + size))
            return ERROR_FORMAT_CODE;

//        if (SWAP64(ehdr64->e_shentsize) >
//            SWAP64(ehdr64->e_phoff) + SWAP64(ehdr64->e_phentsize) * SWAP64(ehdr64->e_phnum)) {
//            return ERROR_FORMAT_CODE;
//        }

        if (SWAP64(ehdr64->e_phoff) +
            SWAP64(ehdr64->e_phentsize) * SWAP64(ehdr64->e_phnum) > size)
            return ERROR_FORMAT_CODE;

        if (SWAP64(ehdr64->e_shnum) < 1)
            return ERROR_FORMAT_CODE;
    }

    return SUCCESS;
}

int validate_count_symbols_table(char *dst) {
    unsigned long i;
    int count;
    Elf64_Ehdr *ehdr64;
    Elf64_Shdr *shdr64;
    Elf32_Ehdr *ehdr32;
    Elf32_Shdr *shdr32;
    int sym_count = 0;


    i = 0;
    count = 0;

    if (dst[EI_CLASS] == 1) {
        ehdr32 = (Elf32_Ehdr *) dst;
        shdr32 = (Elf32_Shdr *) (dst + SWAP32(ehdr32->e_shoff));

        while (i < SWAP32(ehdr32->e_shnum)) {
            if (SWAP32(shdr32[i].sh_type) == SHT_SYMTAB) {
                sym_count = SWAP32(shdr32[i].sh_size) / SWAP32(shdr32[i].sh_entsize);
                count++;
            }
            i++;
        }

        if (sym_count == 0) {
            return ERROR_NO_SYMBOLS;
        }

        if (count == 0)
            return ERROR_FORMAT_CODE;

        if (count > 1)
            return ERROR_FORMAT_CODE;
    }


    if (dst[EI_CLASS] == 2) {
        ehdr64 = (Elf64_Ehdr *) dst;
        shdr64 = (Elf64_Shdr *) (dst + SWAP64(ehdr64->e_shoff));

        while (i < SWAP64(ehdr64->e_shnum)) {
            if (SWAP64(shdr64[i].sh_type) == SHT_SYMTAB) {
                sym_count = SWAP64(shdr64[i].sh_size) / SWAP64(shdr64[i].sh_entsize);
                count++;
            }
            i++;
        }

        if (sym_count == 0) {
            return ERROR_NO_SYMBOLS;
        }

        if (count == 0)
            return ERROR_FORMAT_CODE;

        if (count > 1)
            return ERROR_FORMAT_CODE;

    }

    return SUCCESS;
}

int validate_count_sht_strtab(char *dst) {
    unsigned long i;
    int count;
    Elf64_Ehdr *ehdr64;
    Elf64_Shdr *shdr64;
    Elf32_Ehdr *ehdr32;
    Elf32_Shdr *shdr32;


    i = 0;
    count = 0;

    if (dst[EI_CLASS] == 1) {
        ehdr32 = (Elf32_Ehdr *) dst;
        shdr32 = (Elf32_Shdr *) (dst + SWAP32(ehdr32->e_shoff));

        if (SWAP32(ehdr32->e_shentsize) == 0) {
            return ERROR_FORMAT_CODE;
        }

        while (i < SWAP32(ehdr32->e_shnum)) {
            if (SWAP32(shdr32[i].sh_type) > SHT_HIUSER) {
                return ERROR_FORMAT_CODE;
            }
            if (SWAP32(shdr32[i].sh_type) == SHT_STRTAB) {
                count++;
            }
            i++;
        }

        if (count == 0)
            return ERROR_FORMAT_CODE;
    }


    if (dst[EI_CLASS] == 2) {
        ehdr64 = (Elf64_Ehdr *) dst;
        shdr64 = (Elf64_Shdr *) (dst + SWAP64(ehdr64->e_shoff));

        if (SWAP64(ehdr64->e_shentsize) == 0) {
            return ERROR_FORMAT_CODE;
        }

        while (i < SWAP64(ehdr64->e_shnum)) {
            if (SWAP64(shdr64[i].sh_type) > SHT_HIUSER) {
                return ERROR_FORMAT_CODE;
            }
            if (SWAP64(shdr64[i].sh_type) == SHT_STRTAB) {
                count++;
            }
            i++;
        }

        if (count == 0)
            return ERROR_FORMAT_CODE;

    }

    return SUCCESS;
}