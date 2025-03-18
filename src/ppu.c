#include <ppu.h>
#include <SDL2/SDL_image.h>

uint32_t PALETTE[] = {
    0X626262,
    0x001FB2,
    0x2400C8,
    0x5200B2,
    0x730076,
    0x800024,
    0x730B00,
    0x522800,
    0x244400,
    0x538E53,
    0x005C00,
    0x005324,
    0x7092B2,
    0x000000,
    0x000000,
    0x000000,
    0xABABAB,
    0x0D57FF,
    0x4B30FF,
    0x8A13FF,
    0xBC01D6,
    0xD21269,
    0xC72E00,
    0x9D5400,
    0x607B00,
    0x209800,
    0x00A300,
    0x009942,
    0x007DB4,
    0x000000,
    0x000000,
    0x000000,
    0xFFFFFF,
    0x53AEFF,
    0x9085FF,
    0xD365FF,
    0xFF57FF,
    0xFF5DCF,
    0xFF7757,
    0xFA9E00,
    0XBDC700,
    0x7AE700,
    0x43F611,
    0x26EF7E,
    0x2CD5F6,
    0x515151,
    0x000000,
    0x000000,
    0xFFFFFF,
    0xB6E1FF,
    0xCED1FF,
    0xE9C3FF,
    0xFFBCFF,
    0xFFBDF4,
    0xFFC6C3,
    0xFFD59A,
    0xE9E681,
    0xCEF481,
    0xB6FB9A,
    0xA9FAC3,
    0xA9F0F4,
    0xB8B8B8,
    0x000000,
    0x000000};

uint8_t _ppu_attribute_table[128] = {};

NESTile _background_pattern_table[256] = {};
NESTile _foreground_pattern_table[256] = {};

uint8_t nametables[2048] = {};

NESSprite oam[64] = {};

NESPalette _background_palette[4] = {};
NESPalette _foreground_palette[4] = {};

SDL_Color getColorFromPalette(uint8_t palette_no)
{
    return (SDL_Color){.r = PALETTE[palette_no] >> 16,
                       .g = (PALETTE[palette_no] >> 8) & 0xFF,
                       .b = PALETTE[palette_no] & 0xFF,
                       .a = 255};
}

static SDL_Color getRGBFromSurface(SDL_Surface *s, int x, int y)
{
    uint32_t pixel = ((uint32_t *)s->pixels)[x + y * s->w];
    return (SDL_Color){
        .r = pixel >> 16,
        .g = pixel >> 8,
        .b = pixel,
        .a = 255,
    };
}

void loadBackgroundPatternTable(const char *file)
{
    SDL_Surface *surface = IMG_Load(file);
    SDL_Surface *rgb_surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGB888, 0);

    SDL_LockSurface(rgb_surface);

    for (int h = 0; h < 16; h++)
    {
        for (int w = 0; w < 16; w++)
        {
            NESTile tile;
            memset(tile.pixels, 0, sizeof(uint8_t) * 16);
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    int px = w * 8 + j;
                    int py = h * 8 + i;
                    SDL_Color color = getRGBFromSurface(rgb_surface, px, py);
                    if (color.r)
                    {
                        tile.pixels[i * 2 + j / 4] |= (uint8_t)1 << (6 - ((j % 4) * 2));
                    }
                    else if (color.g)
                    {
                        tile.pixels[i * 2 + j / 4] |= (uint8_t)2 << (6 - ((j % 4) * 2));
                    }
                    else if (color.b)
                    {
                        tile.pixels[i * 2 + j / 4] |= (uint8_t)3 << (6 - ((j % 4) * 2));
                    }
                }
            }
            _background_pattern_table[w + h * 16] = tile;
        }
    }

    SDL_UnlockSurface(rgb_surface);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(rgb_surface);
}

void setBackgroundPalette(uint8_t palette_no, uint8_t c0, uint8_t c1, uint8_t c2, uint8_t c3)
{
    _background_palette[palette_no] = (NESPalette){
        c0, c1, c2, c3};
}

void setForegroundPalette(uint8_t palette_no, uint8_t c0, uint8_t c1, uint8_t c2, uint8_t c3)
{
    _foreground_palette[palette_no] = (NESPalette){
        c0, c1, c2, c3};
}
