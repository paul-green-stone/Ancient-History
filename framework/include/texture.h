#ifndef _SPARK_TEXTURE_H
#define _SPARK_TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**
 * Get dimensions of the texture.
 *
 * @param t the texture to get dimensions of
 * @param w width of the texture
 * @param h height of the texture
 *
 * @return Returns 0 on success or a negative error code on failure.
 */
#define Texture_getDimensons(t, w, h) (SDL_QueryTexture((t), NULL, NULL, (w), (h)))

typedef struct texture
{
	SDL_Texture *t;
	SDL_Renderer *r;
} Texture;

typedef struct RenderTexture
{
	Texture texture;
	int width;
	int height;
} RenderTexture;

/* ================================================================ */

/**
 * Create (load) a new texture for the specified renderer.
 *
 * @param r the `SDL_Renderer*` a texture will be associated with
 * @param filename path to the texture
 *
 * @return Returns the `Texture` or NULL on failure.
 */
Texture *Texture_new(SDL_Renderer *r, const char *filename);

/**
 * Destroy the texture.
 *
 * @param texture to destroy (&texture)
 *
 * @return Returns 0 on success or -1 on failure.
 */
int Texture_destroy(Texture **t);

/**
 * Draw a texture on the screen.
 *
 * @param src a region of the texture to be drawn. `NULL` for the whole texture
 * @param dst the destination area on the screen where the texture will be rendered. `NULL` for the entire screen
 *
 * @return Returns 0 on success or -1 on failure.
 */
int Texture_draw(const Texture *t, const SDL_Rect *src, const SDL_Rect *dst);

/**
 * Creates a new render texture for drawing to.
 *
 * @param renderer the window context to attach the render texture to
 * @param width
 * @param height
 *
 * @return Returns the new render texture
 *
 * @note Make sure to free the render texture at the end of the program with `RenderTexture_destroy`
 */
RenderTexture RenderTexture_new(SDL_Renderer *renderer, int width, int height);

/**
 * Destroys and frees the render texture's memory
 *
 * @param rt Render texture to destroy
 */
void RenderTexture_destroy(RenderTexture rt);

/**
 * Sets a render texture as the rendering target.
 *
 * @param renderer The window context
 * @param rt The render texture to draw to
 */
void setRenderTarget(RenderTexture rt);

/**
 * Resets the render target back to the window.
 *
 * @param rendere the window's render context
 */
void clearRenderTarget(SDL_Renderer *renderer);

#endif /* _SPARK_TEXTURE_H */