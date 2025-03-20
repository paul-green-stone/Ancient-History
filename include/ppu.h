/**
 * This header emulates the NES PPU system, including the color palette, nametable and sprite table system.
 */
#ifndef PPU_H
#define PPU_H

#include <SDL2/SDL.h>

#include <stdint.h>

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
extern uint8_t _ppu_attribute_table[128];

extern NESTile _background_pattern_table[256];
extern NESTile _foreground_pattern_table[256];

/**
 * Memory for the nametables, exactly 2KB
 */
extern uint8_t nametables[2048];

/**
 * OAM memory table for sprites
 */
extern NESSprite oam[64];

/* Background color palette */
extern NESPalette _background_palette[4];
/* Foreground color palette */
extern NESPalette _foreground_palette[4];

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
 * Copy the nametables to the screen along with their scroll position of the camera
 */
void drawNametables(SDL_Renderer *context, int scroll_x, int scroll_y);

#endif // PPU_H