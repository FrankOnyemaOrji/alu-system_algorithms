#include "huffman.h"
#include "heap.h"

/**
 * huffman_extract_and_insert - extracts the two nodes of
 *								the priority queue and insert a new one
 * @priority_queue:  pointer to the priority queue to extract from
 * Return: 1 on success or 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *new_node, *nodea, *nodeb;
	symbol_t *symbol;
	size_t combined_freq;

	if (!priority_queue || !priority_queue->root)
		return (0);
	/* Check if there are at least two nodes in the priority queue */
	if (priority_queue->size < 2)
		return (0);

	nodea = heap_extract(priority_queue);
	nodeb = heap_extract(priority_queue);

	if (!nodea || !nodeb)
	{
		free(nodea);
		free(nodeb);
		return (0);
	}

	combined_freq = ((symbol_t *)nodea->data)->freq +
														((symbol_t *)nodeb->data)->freq;

	symbol = symbol_create(-1, combined_freq);
	new_node = binary_tree_node(NULL, symbol);

	if (new_node == NULL)
	{
		free(symbol);
		return (0);
	}
	new_node->left = nodea;
	new_node->right = nodeb;
	nodea->parent = new_node;
	nodeb->parent = new_node;
	heap_insert(priority_queue, new_node);
	return (1);
}