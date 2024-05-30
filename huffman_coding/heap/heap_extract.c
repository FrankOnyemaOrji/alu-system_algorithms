#include "heap.h"

/**
 * heapify_down - Maintains the heap property by moving down the tree.
 * @heap: Pointer to the heap.
 */
static void heapify_down(heap_t *heap)
{
binary_tree_node_t *current, *child;
void *temp;

if (!heap || !heap->root)

return;

current = heap->root;

while (current->left)
{
child = current->left;

if (current->right && heap->data_cmp(current->right->data, current->left->data) < 0)

child = current->right;

if (heap->data_cmp(current->data, child->data) > 0)

{
temp = current->data;
current->data = child->data;
child->data = temp;
current = child;

}

else

{

break;
}
}
}
/**
 * heap_extract - Extracts the root value of a Min Binary Heap.
 * @heap: Pointer to the heap.
 * Return: A pointer to the data that was stored in the root node of the heap.
 */
void *heap_extract(heap_t *heap)
{
binary_tree_node_t *root, *last;
void *data;

if (!heap || !heap->root)

return (NULL);

root = heap->root;
data = root->data;

last = root;
while (last->left)
{
if (last->right && last->right->parent == last)
last = last->right;
else
last = last->left;
}

if (last != root)
{
last->parent->left = NULL;
last->parent = root->parent;
last->left = root->left;
last->right = root->right;

if (root->left)
root->left->parent = last;
if (root->right)
root->right->parent = last;

if (root->parent)
{
if (root->parent->left == root)
root->parent->left = last;
else
root->parent->right = last;
}
else
{
heap->root = last;
}
heapify_down(heap);
}
else
{
heap->root = NULL;
}
free(root);
heap->size--;
return (data);
}