#include <camera.h>
#include <stdlib.h>
#include <math.h>

Camera *createCamera(SDL_Renderer *context, int width, int height)
{
    Camera *camera = (Camera *)malloc(sizeof(Camera));
    if (camera == NULL)
    {
        perror("ALLOC ERROR: Could not allocate memory for camera :");
        return NULL;
    }

    camera->width = width;
    camera->height = height;
    camera->pos[0] = 0;
    camera->pos[1] = 0;
    camera->context = context;

    camera->texture = RenderTexture_new(context, width, height);

    return camera;
}

void setRenderCamera(Camera *camera)
{
    SDL_SetRenderTarget(camera->context, camera->texture.texture.t);
}

void setCameraScroll(Camera *camera, int x, int y)
{
    camera->pos[0] = x;
    camera->pos[1] = y;
}

void drawLevelToCamera(Camera *camera, Level *level)
{
    // Rect used for drawing the tiles, along with it's color set to black.
    SDL_Rect tile_rect = {.w = level->tile_size, .h = level->tile_size};
    SDL_SetRenderDrawColor(camera->context, 0, 0, 0, 255);

    // Get the starting x and y tiles from the level map.
    int tile_x = (camera->pos[0] / level->tile_size);
    int tile_y = (camera->pos[1] / level->tile_size);

    for (int h = 0; h < level->height; h++)
    {
        if (h < 0 || h > level->height)
        {
            continue;
        }
        for (int w = 0; w < level->width; w++)
        {
            if (w < 0 || w > level->width)
            {
                continue;
            }
            if (level->map[w + h * level->width] != 0)
            {
                tile_rect.x = (w * level->tile_size) - camera->pos[0];
                tile_rect.y = (h * level->tile_size) - camera->pos[1];
                SDL_RenderFillRect(camera->context, &tile_rect);
            }
        }
    }
}

/**
 * Frees the camera's heap memory.
 */
void deleteCamera(Camera *camera)
{
    RenderTexture_destroy(camera->texture);
    free(camera);
}