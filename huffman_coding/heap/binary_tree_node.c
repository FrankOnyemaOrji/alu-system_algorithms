#include <stdlib.h>
#include "heap.h"

/**
 *binary_tree_node - function that creates a generic Binary tree node
 *
 * @parent: pointer to the parent node.
 * @data: The data to be stored in the node.
 * Return: A pointer to the created binary_tree_node, or NULL if it fails.
 */
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data)
{

	binary_tree_node_t *new_node = malloc(sizeof(binary_tree_node_t));

	if (new_node == NULL)
	{
		return (NULL);
	}

	new_node->parent = parent;
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;

	return (new_node);
}
