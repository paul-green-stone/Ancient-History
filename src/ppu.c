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

uint8_t _ppu_attribute_table[512];

NESTile _background_pattern_table[256];
NESTile _foreground_pattern_table[256];

uint8_t nametables[KB_2];

NESSprite oam[64] = {};

NESPalette _background_palette[4];
NESPalette _foreground_palette[4];

void initPPU()
{
    memset(_ppu_attribute_table, 0, sizeof(uint8_t) * 512);
    memset(_background_pattern_table, 0, sizeof(NESTile) * 256);
    memset(_foreground_pattern_table, 0, sizeof(NESTile) * 256);
    memset(nametables, 0, sizeof(uint8_t) * KB_2);
    memset(oam, 0, sizeof(NESSprite) * 64);
    memset(_background_palette, 0, sizeof(NESPalette) * 4);
    memset(_foreground_palette, 0, sizeof(NESPalette) * 4);
}

SDL_Color getColorFromPalette(uint8_t palette_no)
{
    return (SDL_Color){.r = PALETTE[palette_no] >> 16,
                       .g = PALETTE[palette_no] >> 8,
                       .b = PALETTE[palette_no],
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

static NESTile getTileFromSurface(SDL_Surface *s, int x, int y)
{
    NESTile tile;
    memset(tile.pixels, 0, sizeof(uint8_t) * 16);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            int px = x * 8 + j;
            int py = y * 8 + i;
            SDL_Color color = getRGBFromSurface(s, px, py);
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

    return tile;
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
            _background_pattern_table[w + h * 16] = getTileFromSurface(rgb_surface, w, h);
        }
    }

    SDL_UnlockSurface(rgb_surface);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(rgb_surface);
}

void loadForegroundPatternTable(const char *file)
{
    SDL_Surface *surface = IMG_Load(file);
    SDL_Surface *rgb_surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGB888, 0);

    SDL_LockSurface(rgb_surface);

    for (int h = 0; h < 16; h++)
    {
        for (int w = 0; w < 16; w++)
        {
            _foreground_pattern_table[w + h * 16] = getTileFromSurface(rgb_surface, w, h);
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

void setNametableTile(uint8_t nametable_no, uint8_t x, uint8_t y, uint8_t tile)
{
    nametables[(KB_1 * nametable_no) + x + y * 32] = tile;
}

uint8_t getNametableTile(uint8_t nametable_no, uint8_t x, uint8_t y)
{
    return nametables[(KB_1 * nametable_no) + x + y * 32];
}

void setAttributeTable(uint8_t nametable_no, uint8_t x, uint8_t y, uint8_t palette_no)
{
    _ppu_attribute_table[(nametable_no * 256) + x + y * 16] = palette_no;
}

uint8_t getAttributeTable(uint8_t nametable_no, uint8_t x, uint8_t y)
{
    return _ppu_attribute_table[(nametable_no * 256) + x + y * 16];
}

void drawNESTile(SDL_Renderer *r, NESPalette palette, NESTile tile, uint8_t x, uint8_t y)
{
    SDL_Color color1 = getColorFromPalette(palette.c1);
    SDL_Color color2 = getColorFromPalette(palette.c2);
    SDL_Color color3 = getColorFromPalette(palette.c3);

    SDL_Color colors[] = {
        (SDL_Color){0, 0, 0, 0}, color1, color2, color3};

    uint8_t pixel_count = 0;
    for (uint8_t i = 0; i < 16; i++)
    {
        for (uint8_t j = 0; j < 4; j++)
        {
            uint8_t color = (tile.pixels[i] >> (6 - j * 2)) & 0b11;
            SDL_SetRenderDrawColor(r, colors[color].r, colors[color].g, colors[color].b, colors[color].a);
            SDL_RenderDrawPoint(r, x + pixel_count % 8, y + pixel_count / 8);
            pixel_count++;
        }
    }
}

/**
 * Draws a tile from the nametable to the screen.
 */
static void drawNametableXY(SDL_Renderer *context, int nametable_no, int x, int y, int scroll_x)
{
    if (getNametableTile(nametable_no, x, y) != 0)
    {
        printf("Not zero! %d %d %d %d\n", nametable_no, x, y, getNametableTile(nametable_no, x, y));
    }
    NESTile tile = _background_pattern_table[getNametableTile(nametable_no, x, y)];
    int x_pos = ((nametable_no * 32) + (x * 8) - scroll_x) % 256;
    x_pos = (x_pos < 0) ? x_pos + 256 : x_pos;
    int y_pos = y * 8;
    NESPalette palette = _background_palette[getAttributeTable(nametable_no, x / 2, y / 2)];
    drawNESTile(context, palette, tile, x_pos, y_pos);
}

void drawNametables(SDL_Renderer *context, int scroll_x)
{
    // Clear the screen with the set background color.
    SDL_Color bg_color = getColorFromPalette(PALETTE[_background_palette[0].c0]);
    SDL_SetRenderDrawColor(context, bg_color.r, bg_color.g, bg_color.b, 255);
    SDL_RenderClear(context);

    scroll_x %= 512;
    int first, second;
    if (scroll_x >= 256)
    {
        first = 1;
        second = 0;
    }
    else
    {
        first = 0;
        second = 1;
    }

    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 28; j++)
        {
            int tile_index = getNametableTile(first, i, j);
            int palette_index = getAttributeTable(first, i, j);
            NESTile tile = _background_pattern_table[tile_index];
            NESPalette palette = _background_palette[palette_index];
            drawNESTile(context, palette, tile, i * 8 - scroll_x, j * 8);
        }
    }

    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 28; j++)
        {
            int tile_index = getNametableTile(first == 0, i, j);
            int palette_index = getAttributeTable(first == 0, i, j);
            if (tile_index != 0)
            {
                // printf("Not equal to zero! %d %d %d %d\n", i, j, first == 0, tile_index);
            }
            NESTile tile = _background_pattern_table[tile_index];
            NESPalette palette = _background_palette[palette_index];
            drawNESTile(context, palette, tile, i * 8 - scroll_x + 256, j * 8);
        }
    }
    // int tile_x = scroll_x / 8 - 1;
    // tile_x = (tile_x < 0) ? 64 + tile_x : tile_x;
    // for (int i = tile_x; i < tile_x + 33; i++)
    // {
    //     int nametable_no = i / 32;
    //     if (nametable_no = 1) {
    //         printf("%d %d\n", i, tile_x);
    //     }
    //     int x = i % 32;
    //     for (int j = 0; j < 28; j++)
    //     {
    //         drawNametableXY(context, nametable_no, x, j, scroll_x);
    //     }
    // }
}
