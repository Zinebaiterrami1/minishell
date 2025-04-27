/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:57:29 by nel-khad          #+#    #+#             */
/*   Updated: 2025/04/24 15:54:34 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
#define GC_H


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


// t_garbage **gc;

typedef struct s_garbage
{
    void *adress;
    struct s_garbage *next;
}t_garbage;

t_garbage **getter();
void free_all(t_garbage **list);
void *gc_malloc(size_t size, t_garbage **list);
// static t_garbage *get_last_node(t_garbage *list);
// static void add_node(t_garbage **list, t_garbage *new);




#endif