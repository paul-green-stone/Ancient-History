#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <stdint.h>

// Level object/struct
//
// Also contains the information for the camera (this may change later on...)
typedef struct Level
{
    int width;         // Width of entire level (measured in number of tiles)
    int height;        // Height of entire level (measured in number of tiles)
    int tile_size;     // Size of an individual squar tile side
    uint8_t *map;      // The actual level map data (for a single layer)
    int camera_pos[2]; // Position of the camera, used for scrolling the screen
} Level;

/**
 * Load and create a new level based off of a pixel map of the level
 */
Level *loadLevel(const char *level_pixel_map, int tile_size);

/**
 * Frees the level data from heap
 */
void unloadLevel(Level *level);

#endif // LEVEL_MANAGER_H