#ifndef _SPARK_TEXT_H
#define _SPARK_TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "texture.h"

#define TEXT_BUFFER 64

typedef struct text {

    Texture* t;

    char content[TEXT_BUFFER];

    SDL_Color color;
    TTF_Font* font;

    int width;
    int height;
} Text;

/* ================================================================ */

/**
 * The function creates a new instance of `Text`, which relies on `Texture`. Therefore, specifying the rendering context is necessary.
 * 
 * @param r a rendering context used for texture rendering
 * @param font the font used in the text
 * @param color a color of the text
 * @param str a string of textual data to be rendered
 * 
 * @return Returns the `Text` or NULL on failure.
 */
Text* Text_new(SDL_Renderer* r, TTF_Font* font, SDL_Color* color, const char* str);

/**
 * The function deallocates the text, reclaiming all memory occupied by it.
 * 
 * @param text text to destroy
 * 
 * @return Returns 0 on success or -1 on failure.
 */
int Text_destroy(Text** text);

/**
 * The function updates the text with the provided string
 * 
 * @param text text to update (change its content)
 * @param str a string used to update the text
 * 
 * @return Returns text of `Text` containing the string `str`.
 */
Text* Text_update(Text* text, const char* str);

/**
 * The function sets a color for text.
 * 
 * @param text text to update (set a new color)
 * @param color a new color of the text
 * 
 * @return None.
 */
void Text_setColor(Text* text, SDL_Color* color);

/**
 * The function renders text on the screen.
 * 
 * @param text text to be rendered on the screen
 * @param dst the region into which text should be rendered
 * 
 * @return 0 on success or a negative error code on failure.
 */
int Text_draw(const Text* text, SDL_Rect* dst);

/**
 * The function sets a font for text.
 * 
 * @param text text to update (set a new font)
 * @param font a font used to update the text
 * 
 * @return None.
 */
void Text_setFont(Text* text, TTF_Font* font);

#endif /* _SPARK_TEXT_H */
