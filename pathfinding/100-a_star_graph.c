#include "pathfinding.h"

/**
 * get_min_g_score - Finds the vertex with the lowest g_score from the source.
 *
 * @graph: Pointer to the graph.
 * @g_score: Array of g_scores from the start vertex.
 * @visited: Array indicating if a vertex has been visited.
 * @index: Pointer to store the index of the vertex with the minimum g_score.
 *
 * Return: Pointer to the vertex with the minimum
 * g_score, or NULL if none found.
 */
vertex_t *get_min_g_score(graph_t *graph, size_t *g_score, size_t *visited,
size_t *index)
{
	size_t min = ULONG_MAX;
	vertex_t *min_vertex = NULL;
	size_t i;

	for (i = 0; i < graph->nb_vertices; i++)
	{
		if (!visited[i] && g_score[i] < min)
		{
			min = g_score[i];
			min_vertex = graph->vertices + i;
			*index = i;
		}
	}

	return (min_vertex);
}

/**
 * reconstruct_path - Inserts vertices into the queue to form the path.
 *
 * @path: Pointer to the path queue.
 * @came_from: Array of vertices representing the path.
 * @start: Pointer to the start vertex.
 * @target: Pointer to the target vertex.
 */
void reconstruct_path(queue_t *path, vertex_t **came_from,
const vertex_t *start, const vertex_t *target)
{
	const vertex_t *current = target;

	while (current != start)
	{
		if (!queue_push_front(path, strdup(current->content)))
		{
			queue_delete(path);
			return;
		}
		current = came_from[current->index];
	}

	if (!queue_push_front(path, strdup(start->content)))
		queue_delete(path);
}

/**
 * recursive_a_star - Recursive utility to find the shortest path using A-star.
 *
 * @graph: Pointer to the graph.
 * @visited: Array indicating which vertices have been visited.
 * @came_from: Array of vertices representing the path.
 * @start: Pointer to the start vertex.
 * @target: Pointer to the target vertex.
 * @f_score: Array of distance from start + euclidean to target.
 * @g_score: Distance from start to current.
 * @idx: Current index.
 */
void recursive_a_star(graph_t *graph, size_t *visited, vertex_t **came_from,
const vertex_t *start, const vertex_t *target,
size_t *f_score, size_t *g_score, size_t idx)
{
	vertex_t *current = get_min_g_score(graph, f_score, visited, &idx);

	if (!current || current == target)
		return;

	size_t current_idx = current->index;
	edge_t *edge = current->edges;

	while (edge)
	{
		vertex_t *neighbor = edge->dest;
		size_t tentative_g_score = g_score[current_idx] + edge->weight;

		if (tentative_g_score < g_score[neighbor->index])
		{
			came_from[neighbor->index] = current;
			g_score[neighbor->index] = tentative_g_score;
			f_score[neighbor->index] = g_score[neighbor->index] +
			h(neighbor->x, neighbor->y, target->x, target->y);
		}

		edge = edge->next;
	}

	visited[current_idx] = 1;
	recursive_a_star(graph, visited, came_from,
start, target, f_score, g_score, idx);
}

/**
 * a_star_graph - Searches for the shortest path from a starting
 * point to a target point in a graph using A* algorithm.
 *
 * @graph: Pointer to the graph to search.
 * @start: Pointer to the starting vertex.
 * @target: Pointer to the target vertex.
 *
 * Return: Queue containing the path from start to target,
 * or NULL if no path found.
 */
queue_t *a_star_graph(graph_t *graph, const vertex_t *start,
const vertex_t *target)
{
	if (!graph || !start || !target)
		return (NULL);

	size_t *f_score = NULL, *g_score = NULL, *visited = NULL;
	vertex_t **came_from = NULL;
	queue_t *path_queue = NULL;

	if (initialize_a_star(graph, &visited, &came_from,
&f_score, &g_score, start, target) == -1)
		return (NULL);

	path_queue = queue_create();
	if (!path_queue)
	{
		free(visited);
		free(f_score);
		free(g_score);
		free(came_from);
		return (NULL);
	}

	recursive_a_star(graph, visited, came_from, start, target,
f_score, g_score, 0);
	reconstruct_path(path_queue, came_from, start, target);

	free(visited);
	free(f_score);
	free(g_score);
	free(came_from);

	if (!path_queue->front)
	{
		free(path_queue);
		return (NULL);
	}

	return (path_queue);
}
