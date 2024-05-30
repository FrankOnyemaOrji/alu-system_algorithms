#include "huffman.h"
#include "heap.h"

/**
 * freeNestedNode - meant to be used as free_data parameter to heap_delete;
 *   frees memory allocated for a binary_tree_node_t node containing a
 *   symbol_t struct
 *
 * @data: void pointer intended to be cast into binary_tree_node_t pointer
 */
void freeNestedNode(void *data)
{
	binary_tree_node_t *a_data = NULL;
	symbol_t *b_data = NULL;

	a_data = (binary_tree_node_t *)data;

	if (a_data)
	{
		b_data = (symbol_t *)(a_data->data);

		if (b_data)
			free(b_data);

		free(a_data);
	}
}

/**
 * huffman_tree - function that builds the Huffman tree
 * @data: array of characters of size size
 * @freq: array containing the associated frequencies (of size size too)
 * @size: size of queue
 * Return: pointer to the root node of the Huffman tree, or NULL if it fails
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *priority_queue;
	binary_tree_node_t *root_node;

	setbuf(stdout, NULL);

	priority_queue = huffman_priority_queue(data, freq, size);

	if (!priority_queue)
		return (NULL);

	while (priority_queue->size > 1)
	{
		if (!huffman_extract_and_insert(priority_queue))
		{
			return (NULL);
		}
	}

	root_node = heap_extract(priority_queue);
	heap_delete(priority_queue, NULL);
	return (root_node);
}
