#include <stdio.h>
#include "linked_list.h"

int main(void)
{
	node_t* linked_list;
	linked_list = NULL;
	add_front(&linked_list, 1);
	add_front(&linked_list, 2);
	print_list(linked_list);
	remove_node(&linked_list, 2);
	print_list(linked_list);		
	return 0;
}
