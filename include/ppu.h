/**
 * This header emulates the NES PPU system, including the color palette, nametable and sprite table system.
 */
#ifndef PPU_H
#define PPU_H

#include <SDL2/SDL.h>

#include <stdint.h>

#define KB_1 (1024) // Size of 1 kilobyte
#define KB_2 (2048) // Size of 2 kilobytes

/* NES Color palette */
extern uint32_t PALETTE[64];

/**
 * NES palette structure
 */
typedef struct NESPalette
{
    uint8_t c0;
    uint8_t c1;
    uint8_t c2;
    uint8_t c3;
} NESPalette;

/**
 * Struct representing a single NES tile/background/sprite from the PPU
 */
typedef struct NESTile
{
    uint8_t pixels[16]; /* Pixel array containing the sprite */
} NESTile;

/**
 * Sprite attribute field for OAM.
 */
typedef struct OAMAttr
{
    uint8_t palette : 2; // Foregorund palette to use
    uint8_t flip_h : 1;  // If 1, flip horizontally
    uint8_t flip_v : 1;  // If 1, flip vertically
    uint8_t _ : 4;       // Unused
} OAMAttr;

/**
 * Representation of NES sprites in OAM
 */
typedef struct NESSprite
{
    uint8_t tile; // Index of the tile from the pattern table
    OAMAttr attr; // Attributes of the tile
    uint8_t x;    // x position on screen
    uint8_t y;    // y position on screen
} NESSprite;

/**
 * Color palette attribute table for the nametables.
 */
extern uint8_t _ppu_attribute_table[512];

extern NESTile _background_pattern_table[256];
extern NESTile _foreground_pattern_table[256];

/**
 * Memory for the nametables, exactly 2KB
 */
extern uint8_t nametables[KB_2];

/**
 * OAM memory table for sprites
 */
extern NESSprite oam[64];

/* Background color palette */
extern NESPalette _background_palette[4];
/* Foreground color palette */
extern NESPalette _foreground_palette[4];

// Initialize the PPU
void initPPU();

/**
 * Convert NES palette index to SDL_Color
 */
SDL_Color getColorFromPalette(uint8_t palette_no);

/** Load the background pattern table */
void loadBackgroundPatternTable(const char *file);

/** Load the foreground pattern table */
void loadForegroundPatternTable(const char *file);

/**
 * Set the background color palette
 *
 * @param palette_no The color palette to set (either 0, 1, 2, or 3)
 * @param cn The `n`th color to set in the palette
 */
void setBackgroundPalette(uint8_t palette_no, uint8_t c0, uint8_t c1, uint8_t c2, uint8_t c3);

/**
 * Set the foreground color palette
 *
 * @param palette_no The color palette to set (either 0, 1, 2, or 3)
 * @param cn The `n`th color to set in the palette
 */
void setForegroundPalette(uint8_t palette_no, uint8_t c0, uint8_t c1, uint8_t c2, uint8_t c3);

/**
 * Sets a tile in the nametable
 * 
 * @param nametable_no The nametable to add the tile to; either `0` or `1`
 * @param x The x index in the nametable to set the tile, between `[0-31]`
 * @param y The y index in the nametable to set the tile, between `[0-31]`
 * @param tile The tile index from the background palette table to set
 */
void setNametableTile(uint8_t nametable_no, uint8_t x, uint8_t y, uint8_t tile);

/**
 * Gets a tile from the nametable
 * 
 * @param nametable_no The nametable to get the tile from; either `0` or `1`
 * @param x The x index in the nametable to get the tile, between `[0-31]`
 * @param y The y index in the nametable to get the tile, between `[0-31]`
 * 
 * @return The tile index from the background pattern table
 */
uint8_t getNametableTile(uint8_t nametable_no, uint8_t x, uint8_t y);

/**
 * Set the color palette number in the attribute table
 * 
 * @param nametable_no The nametable to set the attribute table value
 * @param x The x index of the color attribute, between `[0-15]`
 * @param y The y index of the color attribute, between `[0-15]`
 * @param palette_no The color palette number to ascociate with
 */
void setAttributeTable(uint8_t nametable_no, uint8_t x, uint8_t y, uint8_t palette_no);

/**
 * Gets the color palette number in the attribute table
 * 
 * @param nametable_no The nametable to get the attribute table value
 * @param x The x index of the color attribute, between `[0-15]`
 * @param y The y index of the color attribute, between `[0-15]`
 * 
 * @return The palatte number from the attribute table
 */
uint8_t getAttributeTable(uint8_t nametable_no, uint8_t x, uint8_t y);

/**
 * Draws a tile to the screen
 */
void drawNESTile(SDL_Renderer *r, NESPalette palette, NESTile tile, int x, int y);

/**
 * Copy the nametables to the screen along with their scroll position of the camera
 */
void drawNametables(SDL_Renderer *context, int scroll_x);

#endif // PPU_H