/**
* @author: Frank Onyema Orji
*/
#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "graphs.h"
#include "queues.h"

#define NUM_DIRECTIONS 4
#define HEURISTIC(x1, y1, x2, y2)  (sqrt(pow((x2) - (x1), 2) + pow((y2) - (y1), 2)))

/**
 * enum Direction - Enumeration for possible directions
 * @RIGHT: Move right (east)
 * @DOWN: Move down (south)
 * @LEFT: Move left (west)
 * @UP: Move up (north)
 */
typedef enum Direction
{
    RIGHT,
    DOWN,
    LEFT,
    UP
} Direction;

/**
 * struct Point - Structure representing a point with x and y coordinates
 * @x: X coordinate
 * @y: Y coordinate
 */
typedef struct Point
{
    int x;
    int y;
} Point;

/**
 * backtracking_array - Finds a path in a 2D map using backtracking
 * @map: 2D array representing the map
 * @rows: Number of rows in the map
 * @cols: Number of columns in the map
 * @start: Starting point
 * @target: Target point
 *
 * Return: Queue containing the path from start to target
 */
queue_t *backtracking_array(char **map, int rows, int cols, const Point *start, const Point *target);

/**
 * backtracking_graph - Finds a path in a graph using backtracking
 * @graph: Graph structure
 * @start: Starting vertex
 * @target: Target vertex
 *
 * Return: Queue containing the path from start to target
 */
queue_t *backtracking_graph(graph_t *graph, const vertex_t *start, const vertex_t *target);

/**
 * dijkstra_graph - Finds the shortest path in a graph using Dijkstra's algorithm
 * @graph: Graph structure
 * @start: Starting vertex
 * @target: Target vertex
 *
 * Return: Queue containing the shortest path from start to target
 */
queue_t *dijkstra_graph(graph_t *graph, const vertex_t *start, const vertex_t *target);

/**
 * a_star_graph - Finds the shortest path in a graph using the A* algorithm
 * @graph: Graph structure
 * @start: Starting vertex
 * @target: Target vertex
 *
 * Return: Queue containing the shortest path from start to target
 */
queue_t *a_star_graph(graph_t *graph, const vertex_t *start, const vertex_t *target);

#endif /* PATHFINDING_H */
