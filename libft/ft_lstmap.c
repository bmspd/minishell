#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*current;

	if (!lst || !f)
		return (NULL);
	first = ft_lstnew(f(lst->content));
	current = first;
	while (lst->next)
	{
		lst = lst->next;
		current->next = ft_lstnew(f(lst->content));
		if (!current->next)
		{
			ft_lstclear(&first, del);
			return (NULL);
		}
		current = current->next;
	}
	return (first);
}
