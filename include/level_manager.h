#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <ppu.h>

/**
 * Struct for a meta-meta-tile (or mega tile)
 */
typedef struct MegaTile
{
    uint8_t tiles[16];   // Indexes the background pattern table for each tile in the mega tile
    uint8_t palettes[4]; // The color palette to use for each 2x2 tile set
    uint8_t types[16];   // The type of each block in the mega tile, `0` for empty, `1` for solid, `2` for bridges, and `3` for dangerous objects.
} MegaTile;

/**
 * Struct used to contain an entire level
 */
typedef struct Level
{
    MegaTile tile_set[64]; // The tile set for the level
    uint8_t data[224];     // The actual level data, with each element indexing the tileset
    int scroll;            // The scroll value of the level, used when copying the level to the nametables in the ppu
} Level;

/**
 * Allocates memory on the heap for the level.
 * You can call this once and load multiple levels using the same object again.
 */
Level *createLevel();

/**
 * Free's the level from memory.
 */
void destroyLevel(Level *level);

/**
 * Loads a level from a text file into a level object. This also initializes the color palette for the level foreground and background,
 * and places all the entities like players and enemies into the correct places.
 */
void loadLevel(Level *level, const char *file);

#endif // LEVEL_MANAGER_H