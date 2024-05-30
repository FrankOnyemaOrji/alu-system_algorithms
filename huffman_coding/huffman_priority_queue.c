#include "huffman.h"
#include "heap.h"

/**
 * freq_cmp - Compares the frequencies of two symbols for heap ordering.
 *
 * @fqa: Pointer to the first symbol.
 * @fqb: Pointer to the second symbol.
 *
 * Return: The difference in frequencies (f1 - f2).
 */
int freq_cmp(void *fqa, void *fqb)
{
	symbol_t *symla, *symlb;
	binary_tree_node_t *nodea, *nodeb;

	nodea = (binary_tree_node_t *)fqa;
	nodeb = (binary_tree_node_t *)fqb;
	symla = (symbol_t *)nodea->data;
	symlb = (symbol_t *)nodeb->data;

	return ((int)symla->freq - (int)symlb->freq);
}

/**
 * huffman_priority_queue - creates a priority queue
 *							for the Huffman coding algorithm
 * @data: array of characters of size size
 * @freq: array containing the associated frequencies (of size size too)
 * @size: size of queue
 * Return: pointer to the created min heap (also called priority queue)
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	symbol_t *syml = NULL;
	heap_t *new_heap = NULL;
	binary_tree_node_t *new_node = NULL;
	size_t index = 0;

	new_heap = heap_create(freq_cmp);

	if (!new_heap)
		return (NULL);
	new_heap->root = NULL;

	while (index < size)
	{
		syml = symbol_create(data[index], freq[index]);
		new_node = binary_tree_node(NULL, syml);

		if (!heap_insert(new_heap, new_node))
		{
			free(syml);
			free(new_node);
			return (NULL);
		}
		index++;
	}

	return (new_heap);
}
