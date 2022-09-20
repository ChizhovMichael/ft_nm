/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_elf32.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 22:02:36 by tgildero          #+#    #+#             */
/*   Updated: 2022/04/12 22:02:38 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_nm.h"

static char get_sym_type_32(Elf32_Shdr *shdr, Elf32_Sym sym) {
    unsigned char c = '?';
    Elf32_Half st_shndx = SWAP32(sym.st_shndx);
    Elf32_Word type = SWAP32(shdr[st_shndx].sh_type);
    Elf32_Word flags = SWAP32(shdr[st_shndx].sh_flags);

    if (ELF32_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
        c = 'u';
    else if (ELF32_ST_TYPE(sym.st_info) == STT_GNU_IFUNC)
        c = 'i';
    else if (ELF32_ST_BIND(sym.st_info) == STB_WEAK) {
        if (ELF32_ST_TYPE(sym.st_info) == STT_OBJECT) {
            c = (st_shndx == SHN_UNDEF) ? 'v' : 'V';
        } else {
            c = (st_shndx == SHN_UNDEF) ? 'w' : 'W';
        }
    } else if (st_shndx == SHN_UNDEF)
        c = 'U';
    else if (st_shndx == SHN_ABS)
        c = 'A';
    else if (st_shndx == SHN_COMMON)
        c = 'C';
    else if ((flags & (SHF_ALLOC | SHF_EXECINSTR | SHF_WRITE)) == (SHF_ALLOC | SHF_EXECINSTR))
        c = 'T';
    else if (type == SHT_NOBITS)
        c = (flags & SHF_IA_64_SHORT) ? 'S' : 'B';
    else if (type == SHT_IA_64_UNWIND)
        c = 'p';
    else if ((flags & (SHF_ALLOC | SHF_EXECINSTR | SHF_WRITE)) == SHF_ALLOC)
        c = 'R';
    else if ((flags & (SHF_ALLOC | SHF_EXECINSTR | SHF_WRITE)) == (SHF_ALLOC | SHF_WRITE))
        c = (flags & SHF_IA_64_SHORT) ? 'G' : 'D';
    else if (flags == 0)
        c = 'N';

    if (ELF32_ST_BIND(sym.st_info) == STB_LOCAL)
        c = ft_tolower(c);

    return c;
}

void print_symbs_32(node *symbs) {
    node *_head = NULL;

    _head = symbs;
    while (_head) {
        if (_head->offset > 0 ||
            't' == ft_tolower(_head->type) ||
            'a' == ft_tolower(_head->type) ||
            'D' == _head->type ||
            'W' == _head->type ||
            'R' == _head->type ||
            'b' == ft_tolower(_head->type)) {
            printf("%08lx %c %s\n", _head->offset, _head->type, _head->name);
        } else {
            printf("%8.d %c %s\n", 0, _head->type, _head->name);
        }
        _head = _head->ptr;
    }
}

node *insert_32(node *head, char type, char *name, uint32_t offset) {
    node *temp, *prev, *next;
    temp = (node *) malloc(sizeof(node));
    temp->type = type;
    temp->name = name;
    temp->offset = offset;
    temp->ptr = NULL;
    if (!head) {
        head = temp;
    } else {
        prev = NULL;
        next = head;
        while (next && ft_strcmp(next->name, name) <= 0) {
            prev = next;
            next = next->ptr;
        }
        if (!next) {
            prev->ptr = temp;
        } else {
            if (prev) {
                temp->ptr = prev->ptr;
                prev->ptr = temp;
            } else {
                temp->ptr = head;
                head = temp;
            }
        }
    }
    return head;
}

void handler_elf32(char *dst) {
    int sym_count = 0;
    Elf32_Ehdr *ehdr;
    Elf32_Shdr *shdr;
    Elf32_Sym *symtab;
    char *name;
    node *symbs = NULL;

    ehdr = (Elf32_Ehdr *) dst;
    shdr = (Elf32_Shdr *) (dst + SWAP32(ehdr->e_shoff));

    char *symbol_names;
    for (int i = 0; i < SWAP32INT(ehdr->e_shnum); i++) {
        if (SWAP32(shdr[i].sh_type) == SHT_SYMTAB) {
            symtab = (Elf32_Sym *) (dst + SWAP32(shdr[i].sh_offset));
            sym_count = SWAP32(shdr[i].sh_size) / SWAP32(shdr[i].sh_entsize);
            symbol_names = (char *) (dst + shdr[shdr[i].sh_link].sh_offset);
            for (int j = 0; j < sym_count; j++) {
                if (ELF32_ST_TYPE(SWAP32(symtab[j].st_info)) == STT_FILE ||
                    ELF32_ST_TYPE(SWAP32(symtab[j].st_info)) == STT_SECTION) {
                    continue;
                }

                name = symbol_names + SWAP32(symtab[j].st_name);

                if (STT_NOTYPE == ELF32_ST_TYPE(SWAP32(symtab[j].st_info)) && '$' == *name)
                    continue;

                if (!name || !*name)
                    continue;

                symbs = insert_32(symbs, get_sym_type_32(shdr, symtab[j]), name, SWAP32(symtab[j].st_value));
            }
        }
    }

    print_symbs_32(symbs);
    free_list(symbs);
}