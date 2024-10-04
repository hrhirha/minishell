/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:43:25 by ler-rech          #+#    #+#             */
/*   Updated: 2019/10/25 19:58:48 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*d)(void *))
{
	t_list			*new;
	t_list			*current;

	current = NULL;
	if (!f || !d)
		return (NULL);
	while (lst != NULL)
	{
		if (current == NULL)
		{
			new = ft_lstnew(f(lst->content));
			if (!new && !f(lst->content))
				return (NULL);
			current = new;
		}
		else
		{
			current->next = ft_lstnew(f(lst->content));
			if (!current->next)
				ft_lstclear(&new, d);
			current = current->next;
		}
		lst = lst->next;
	}
	return (new);
}
