/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-khad <nel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:57:29 by nel-khad          #+#    #+#             */
/*   Updated: 2025/04/22 15:17:19 by nel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
#define GC_H


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


t_garbage **gc;
typedef struct s_garbage
{
    void *adress;
    t_garbage *next;
    t_garbage *prev;
}t_garbage;






#endif