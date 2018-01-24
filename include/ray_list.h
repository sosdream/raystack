/*
 * This file base on @(#)queue.h     8.5 (Berkeley) 8/20/94
 *
 * Copyright (c) 1991, 1993
 *          The Regents of the University of California.
 * Copyright (c) 2018
 *          Honglin Xiao
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#ifndef __RAY_LIST_H__
#define  __RAY_LIST_H__ 1

#include "ray_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LIST_POISON ((void *)(UINTPTR_MAX + 0x1000))
/*
 * Singly-linked Tail queue declarations.
 */
#define RAY_STAILQ_HEAD(name, type)                                             \
struct name {                                                                   \
        struct type *stqh_first;        /* first element */                     \
        struct type **stqh_last;        /* addr of last next element */         \
}

#define RAY_STAILQ_HEAD_INITIALIZER(head)                                       \
        { NULL, &(head).stqh_first }

#define RAY_STAILQ_ENTRY(type)                                                  \
struct {                                                                        \
        struct type *stqe_next; /* next element */                              \
}

/*
 * Singly-linked Tail queue functions.
 */
#define RAY_STAILQ_INIT(head) do {                                              \
        (head)->stqh_first = NULL;                                              \
        (head)->stqh_last = &(head)->stqh_first;                                \
} while (/*CONSTCOND*/0)

#define RAY_STAILQ_INSERT_HEAD(head, elm, field) do {                           \
        if (((elm)->field.stqe_next = (head)->stqh_first) == NULL)              \
                (head)->stqh_last = &(elm)->field.stqe_next;                    \
        (head)->stqh_first = (elm);                                             \
} while (/*CONSTCOND*/0)

#define RAY_STAILQ_INSERT_TAIL(head, elm, field) do {                           \
        (elm)->field.stqe_next = NULL;                                          \
        *(head)->stqh_last = (elm);                                             \
        (head)->stqh_last = &(elm)->field.stqe_next;                            \
} while (/*CONSTCOND*/0)

#define RAY_STAILQ_INSERT_AFTER(head, listelm, elm, field) do {                 \
        if (((elm)->field.stqe_next = (listelm)->field.stqe_next) == NULL)      \
                (head)->stqh_last = &(elm)->field.stqe_next;                    \
        (listelm)->field.stqe_next = (elm);                                     \
} while (/*CONSTCOND*/0)

#define RAY_STAILQ_REMOVE_HEAD(head, field) do {                                \
        if (((head)->stqh_first = (head)->stqh_first->field.stqe_next) == NULL) \
                (head)->stqh_last = &(head)->stqh_first;                        \
} while (/*CONSTCOND*/0)

#define RAY_STAILQ_REMOVE(head, elm, type, field) do {                          \
        if ((head)->stqh_first == (elm)) {                                      \
                STAILQ_REMOVE_HEAD((head), field);                              \
        } else {                                                                \
                struct type *curelm = (head)->stqh_first;                       \
                while (curelm->field.stqe_next != (elm))                        \
                        curelm = curelm->field.stqe_next;                       \
                if ((curelm->field.stqe_next =                                  \
                        curelm->field.stqe_next->field.stqe_next) == NULL)      \
                            (head)->stqh_last = &(curelm)->field.stqe_next;     \
        }                                                                       \
} while (/*CONSTCOND*/0)

#define RAY_STAILQ_FOREACH(var, head, field)                                    \
        for ((var) = ((head)->stqh_first);                                      \
                (var);                                                          \
                (var) = ((var)->field.stqe_next))

#define RAY_STAILQ_CONCAT(head1, head2) do {                                    \
        if (!STAILQ_EMPTY((head2))) {                                           \
                *(head1)->stqh_last = (head2)->stqh_first;                      \
                (head1)->stqh_last = (head2)->stqh_last;                        \
                STAILQ_INIT((head2));                                           \
        }                                                                       \
} while (/*CONSTCOND*/0)

/*
 * Singly-linked Tail queue access methods.
 */
#define RAY_STAILQ_EMPTY(head)      ((head)->stqh_first == NULL)
#define RAY_STAILQ_FIRST(head)      ((head)->stqh_first)
#define RAY_STAILQ_NEXT(elm, field) ((elm)->field.stqe_next)

#ifdef __cplusplus
}
#endif

#endif //__RAY_LIST_H__