/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:43:02 by atarsi            #+#    #+#             */
/*   Updated: 2022/01/20 11:59:07 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*n;
	t_list	*nlist;

	if (!lst)
		return (NULL);
	n = ft_lstnew(f(lst->content));
	nlist = n;
	lst = lst->next;
	while (lst)
	{
		n = ft_lstnew(f(lst->content));
		if (!n)
		{
			ft_lstclear(&lst, del);
			ft_lstclear(&nlist, del);
			return (0);
		}
		lst = lst->next;
		ft_lstadd_back(&nlist, n);
	}
	return (nlist);
}
