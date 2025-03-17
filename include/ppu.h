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
 * BACKGROUND COLOR PALETTE
 *
 * C0: 0x0E 0x20 0x21 0x22
 * C1: 0x0E 0x19 0xA0 0x22
 * C2: 0x0E 0x20 0x21 0x22
 * C3: 0x0E 0x20 0x21 0x22
 */

/**
 * 00 00 10 10 10 10 00 00
 * 00 10 10 10 10 10 10 00
 * 00 00 01 01 01 01 00 00
 * 00 00 01 11 01 11 00 00
 * 00 00 01 01 01 01 00 00
 * 00 00 01 01 01 01 00 00
 * 00 00 01 00 00 01 00 00
 * 00 00 01 00 00 01 00 00
 */

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
typedef struct NESSprite
{
    uint8_t pixels[16]; /* Pixel array containing the sprite */
} NESSprite;

/**
 * Color palette attribute table for the nametables.
 */
extern uint8_t _ppu_attribute_table[256];

/* Background color palette */
extern NESPalette _background_palette[4];
/* Foreground color palette */
extern NESPalette _foreground_palette[4];

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

#endif // PPU_H