#ifndef CAMERA_H
#define CAMERA_H

#include <texture.h>
#include <level_manager.h>

typedef struct camera
{
    int width;             // Width of camera viewport.
    int height;            // Height of the camera viewport.
    int pos[2];            // Scroll position of the camera.
    RenderTexture texture; // Render texture used for the camera.
    SDL_Renderer *context; // Context of the window, used for rendering.
} Camera;

/**
 * Creates a new camera object.
 */
Camera *createCamera(SDL_Renderer *context, int width, int height);

/**
 * Set the camera as the current rendering target.
 */
void setRenderCamera(Camera *camera);

/**
 * Set the camera scroll value. Use this instead of directly writing to the scroll value.
 */
void setCameraScroll(Camera *camera, int x, int y);

/**
 * Draws the level data to the camera. This should be drawn before any other entities are drawn like the player.
 */
void drawLevelToCamera(Camera *camera, Level *level);

/**
 * Frees the camera's heap memory.
 */
void deleteCamera(Camera *camera);

#endif // CAMERA_H