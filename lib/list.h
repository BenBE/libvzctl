/*
 *  Copyright (c) 1999-2017, Parallels International GmbH
 * Copyright (c) 2017-2019 Virtuozzo International GmbH. All rights reserved.
 *
 * This file is part of OpenVZ libraries. OpenVZ is free software; you can
 * redistribute it and/or modify it under the terms of the GNU Lesser General
 * Public License as published by the Free Software Foundation; either version
 * 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/> or write to Free Software Foundation,
 * 51 Franklin Street, Fifth Floor Boston, MA 02110, USA.
 *
 * Our contact details: Virtuozzo International GmbH, Vordergasse 59, 8200
 * Schaffhausen, Switzerland.
 *
 */

#ifndef __LIST_H__
#define __LIST_H__
#include "stdlib.h"

struct list_elem;
typedef struct {
	struct list_elem *prev, *next;
} list_head_t;

typedef struct list_elem {
	struct list_elem *prev, *next;
} list_elem_t;

struct vzctl_str_param {
	list_elem_t list;
	char *str;
};

#ifdef __cplusplus
extern "C" {
#endif
static inline void list_head_init(list_head_t *head)
{
	head->next = (list_elem_t *)head;
	head->prev = (list_elem_t *)head;
}

static inline void list_elem_init(list_elem_t *entry)
{
	entry->next = entry;
	entry->prev = entry;
}

static inline void list_add(list_elem_t *new_el, list_head_t *list)
{
	new_el->next = list->next;
	new_el->prev = (list_elem_t *)list;
	list->next->prev = new_el;
	list->next = new_el;
}

static inline void list_add_tail(list_elem_t *new_el, list_head_t *list)
{
	new_el->next = (list_elem_t *)list;
	new_el->prev = list->prev;
	list->prev->next = new_el;
	list->prev = new_el;
}

static inline void list_del(list_elem_t *el)
{
	el->prev->next = el->next;
	el->next->prev = el->prev;
	el->prev = NULL;
	el->next = NULL;
}

static inline void list_del_init(list_elem_t *el)
{
	el->prev->next = el->next;
	el->next->prev = el->prev;
	list_elem_init(el);
}

static inline int list_is_init(const list_head_t *h)
{
        return h->next == NULL;
}

static inline int list_empty(const list_head_t *h)
{
	if (list_is_init(h))
		return 1;
	return h->next == (const list_elem_t *)h;
}

static inline int list_elem_inserted(const list_elem_t *el)
{
	return el->next != el;
}

static inline void list_moveall(list_head_t *src, list_head_t *dst)
{
	list_add((list_elem_t *)dst, src);
	list_del((list_elem_t *)src);
	list_head_init(src);
}
#ifdef __cplusplus
}
#endif


#define LIST_HEAD_INIT(head) {(void *) &(head), (void *) &(head)}

#define LIST_HEAD(name) \
	list_head_t name = LIST_HEAD_INIT(name)

#define list_entry(ptr, type, field)					\
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->field)))

#define list_first_entry(head, type, field)				\
	list_entry((head)->next, type, field)

#define list_for_each(entry, head, field)				\
	for (entry = list_entry((head)->next, typeof(*entry), field);\
	     &entry->field != (list_elem_t*)(head);			\
	     entry = list_entry(entry->field.next, typeof(*entry), field))

#define list_for_each_prev(entry, head, field)				\
	for (entry = list_entry((head)->prev, typeof(*entry), field);\
	     &entry->field != (list_elem_t*)(head);			\
	     entry = list_entry(entry->field.prev, typeof(*entry), field))

#define list_for_each_prev_continue(pos, head, field)			\
	for (pos = list_entry(pos->field.prev, typeof(*pos), field);	\
             &pos->field != (list_elem_t*)(head);			\
	     pos = list_entry(pos->field.prev, typeof(*pos), field))	

#define list_for_each_safe(entry, tmp, head, field)			\
	for (entry = list_entry((head)->next, typeof(*entry), field),\
		tmp = list_entry(entry->field.next, typeof(*entry), field); \
	     &entry->field != (list_elem_t*)(head);			\
	     entry = tmp,						\
	        tmp = list_entry(tmp->field.next, typeof(*tmp), field))

#endif /* __LIST_H__ */
