#include "heap.h"
#include <stdlib.h>

/**
 * heap_insert - Inserts a value into a Min Binary Heap.
 * @heap: Pointer to the heap in which the node has to be inserted.
 * @data: Pointer containing the data to store in the new node.
 *
 * Return: A pointer to the created binary_tree_node_t structure,
 *         or NULL if it fails.
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
binary_tree_node_t *new_node, *parent;

if (!heap || !data)
return (NULL);

new_node = binary_tree_node(NULL, data);
if (!new_node)

return (NULL);
  
heap->size++;

if (!heap->root)
{
heap->root = new_node;
return (new_node);
}

parent = heap->root;
while (parent->left)
{
if (!parent->right || heap->data_cmp(parent->left->data, parent->right->data) <= 0)
{
parent = parent->left;
}
else
{
parent = parent->right;
}
}

new_node->parent = parent;
if (!parent->left)
{
parent->left = new_node;
}
else
{
parent->right = new_node;
}

/* Heapify Up */
while (new_node->parent && heap->data_cmp(new_node->data, new_node->parent->data) < 0)
{
/* Swap data between current node and parent */
void *temp = new_node->data;
new_node->data = new_node->parent->data;
new_node->parent->data = temp;

new_node = new_node->parent;
}

return (new_node);
}
