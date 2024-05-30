#include "heap.h"

/**
 * node_free - Recursively frees the nodes of a binary tree.
 * @node: Pointer to the root of the binary tree.
 * @free_data: Pointer to the function that frees the data in each node.
 */
static void node_free(binary_tree_node_t *node, void (*free_data)(void *))
{
if (!node)
return;

node_free(node->left, free_data);
node_free(node->right, free_data);

if (free_data)
free_data(node->data);

free(node);
}

/**
 * heap_delete - Deallocates a heap.
 * @heap: Pointer to the heap to delete.
 * @free_data: Pointer to a function used to free the content of a node.
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
if (!heap)
return;

node_free(heap->root, free_data);

free(heap);
}