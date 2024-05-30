#include "huffman.h"

/**
 * symbol_create - Creates a symbol data structure.
 * @data: The data to be stored in the structure.
 * @freq: Its associated frequency.
 *
 * Return: A pointer to the created symbol structure, or NULL if it fails.
 */
symbol_t *symbol_create(char data, size_t freq)
{
symbol_t *newsymbol;

newsymbol = malloc(sizeof(symbol_t));

if (!newsymbol)

return (NULL);
newsymbol->data = data;
newsymbol->freq = freq;

return (newsymbol);
}