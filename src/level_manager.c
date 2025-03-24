#include <level_manager.h>

#include <stdio.h>
#include <stdlib.h>

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
        printf("%d %d %d %d\n", c0, c1, c2, c3);
    }

    // Load the foreground color palettes
    for (int i = 0; i < 4; i++)
    {
        int c0, c1, c2, c3;
        fgets(line_buffer, BUFFER_LEN, fp);
        sscanf(line_buffer, "%d %d %d %d", &c0, &c1, &c2, &c3);
        setForegroundPalette(i, c0, c1, c2, c3);
        printf("%d %d %d %d\n", c0, c1, c2, c3);
    }

    fgets(line_buffer, BUFFER_LEN, fp);

    printf(line_buffer);

    fgets(line_buffer, BUFFER_LEN, fp);

    printf(line_buffer);

    fclose(fp);
}