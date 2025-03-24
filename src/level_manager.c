#include <level_manager.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_LEN (256)

Level *createLevel()
{
    Level *level = (Level *)calloc(1, sizeof(Level));
    if (level == NULL)
    {
        perror("Could not allocate memory for the level:");
    }
    return level;
}

void destroyLevel(Level *level)
{
    free(level);
}

void loadLevel(Level *level, const char *file)
{
    char line_buffer[BUFFER_LEN]; // Used to store each line being parsed.

    FILE *fp = fopen(file, "r");

    // Load the background color palettes
    for (int i = 0; i < 4; i++)
    {
        int c0, c1, c2, c3;
        fgets(line_buffer, BUFFER_LEN, fp);
        sscanf(line_buffer, "%d %d %d %d", &c0, &c1, &c2, &c3);
        setBackgroundPalette(i, c0, c1, c2, c3);
    }

    // Load the foreground color palettes
    for (int i = 0; i < 4; i++)
    {
        int c0, c1, c2, c3;
        fgets(line_buffer, BUFFER_LEN, fp);
        sscanf(line_buffer, "%d %d %d %d", &c0, &c1, &c2, &c3);
        setForegroundPalette(i, c0, c1, c2, c3);
    }

    fgets(line_buffer, BUFFER_LEN, fp); // Skip th next line

    // Load the tile set for the level
    MegaTile mega_tile;
    int tile_set_index = 0;
    while (true)
    {
        // Read the first line which has the list of tiles
        fgets(line_buffer, BUFFER_LEN, fp);
        int tile, chr_read, offset = 0, tile_no = 0;
        while (sscanf(line_buffer + offset, " %d %n", &tile, &chr_read) == 1)
        {
            offset += chr_read;
            mega_tile.tiles[tile_no] = (uint8_t)tile;
            tile_no++;
        }

        // Read the second line which has the palette for each tile
        fgets(line_buffer, BUFFER_LEN, fp);
        int p0, p1, p2, p3;
        sscanf(line_buffer, "%d %d %d %d", &p0, &p1, &p2, &p3);
        mega_tile.palettes[0] = (uint8_t)p0;
        mega_tile.palettes[0] = (uint8_t)p1;
        mega_tile.palettes[0] = (uint8_t)p2;
        mega_tile.palettes[0] = (uint8_t)p3;

        // Load the types of tiles for the mega tile
        fgets(line_buffer, BUFFER_LEN, fp);
        chr_read = 0;
        offset = 0;
        tile_no = 0;
        while (sscanf(line_buffer + offset, " %d %n", &tile, &chr_read) == 1)
        {
            offset += chr_read;
            mega_tile.types[tile_no] = tile;
            tile_no++;
        }

        level->tile_set[tile_set_index] = mega_tile;
        tile_set_index++;

        fgets(line_buffer, BUFFER_LEN, fp);
        if (strcmp(line_buffer, "/\n") == 0)
        {
            break;
        }
    }

    // Load the level map
    for (int i = 0; i < 7; i++)
    {
        fgets(line_buffer, BUFFER_LEN, fp);
        int tile, tile_no = 0, chr_read, offset = 0;
        while (sscanf(line_buffer + offset, " %d %n", &tile, &chr_read) == 1)
        {
            offset += chr_read;
            level->data[tile_no + i * 32] = tile;
            tile_no++;
        }
    }

    fclose(fp);
}