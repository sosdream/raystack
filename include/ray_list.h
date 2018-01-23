/*-
 * Copyright (c) 2018, Honglin Xiao
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

/* Doubly-List */
struct ray_list {
	struct ray_list *prev; /* Previous list element */
	struct ray_list *next; /* Next List element */
};

#define RAY_LIST_INITIALIZER(list) {list, list}


#define LIST_FOREACH(iter, mem, list)					\
	for ((iter) = list->next;							\
		 (iter) != list;								\
		 (iter) = (iter)->mem->next)


/* Inline implementations. */

/* Initializes 'list' as an empty list. */
static inline void
ray_list_init(struct ray_list *list)
{
    list->next = list->prev = list;
}

/* Inserts 'elem' just after 'before'. */
static inline void
ray_list_insert(struct ray_list *before, struct ray_list *elem)
{
	elem->next = before->next;
	elem->prev = before;
	elem->next->prev = elem;
	before->next = elem;
}

/* Inserts 'elem' after before 'before'. */
static inline void
ray_list_append(struct ray_list *head, struct ray_list *elem)
{
    ray_list_insert(head->prev, elem);
}


/* Removes 'elem' from its list and returns the element that followed it.
   Undefined behavior if 'elem' is not in a list. */
static inline struct ray_list *
ray_list_remove(struct ray_list *elem)
{
    elem->prev->next = elem->next;
    elem->next->prev = elem->prev;
    return elem->next;
}

/* Returns the number of elements in 'list'.
   Runs in O(n) in the number of elements. */
static inline size_t
ray_list_size(const struct ray_list *list)
{
    const struct ray_list *e;
    size_t cnt = 0;

    for (e = list->next; e != list; e = e->next) {
        cnt++;
    }
    return cnt;
}

#ifdef __cplusplus
}
#endif

#endif //__RAY_LIST_H__