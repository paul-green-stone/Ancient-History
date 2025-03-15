#include "../include/text.h"

Text* Text_new(SDL_Renderer* r, TTF_Font* font, SDL_Color* color, const char* str) {

    Text* text = NULL;

    if ((text = calloc(1, sizeof(Text))) == NULL) {
        return NULL;
    }

    if ((text->t = calloc(1, sizeof(Texture))) == NULL) {
        free(text);

        return NULL;
    }

    text->t->r = r;

    strncpy(text->content, str, TEXT_BUFFER - 1);
    text->content[TEXT_BUFFER - 1] = '\0';

    text->color = *color;
    text->font = font;

    text = Text_update(text, str);

    return text;
}

/* ================================ */

int Text_destroy(Text** text) {

    if ((text == NULL) || (*text == NULL)) {
        return 1;
    }

    Texture_destroy(&(*text)->t);
    free(*text);

    *text = NULL;

    return 0;
}

/* ================================ */

Text* Text_update(Text* text, const char* str) {

    SDL_Surface* s;

    if (text->t->t != NULL) {
        SDL_DestroyTexture(text->t->t);
    }

    if ((s = TTF_RenderText_Solid(text->font, str, text->color)) == NULL) {

        /* If something bad happens here, the original text is returned */
        /* Need to think of some kind of error handling mechanism */

        return text;
    }

    if ((text->t->t = SDL_CreateTextureFromSurface(text->t->r, s)) == NULL) {

        return text;
    }

    SDL_FreeSurface(s);

    Texture_getDimensons(text->t->t, &text->width, &text->height);

    return text;
}

/* ================================ */

void Text_setColor(Text* text, SDL_Color* color) {

    text->color = *color;

    /* Update the text with a new color */
    text = Text_update(text, text->content);
}

/* ================================ */

int Text_draw(const Text* text, SDL_Rect* dst) {

    /* Do we need to partially draw text? */
    return SDL_RenderCopy(text->t->r, text->t->t, NULL, dst);
}

/* ================================ */

void Text_setFont(Text* text, TTF_Font* font) {

    text->font = font;

    /* Update the text with a new font */
    text = Text_update(text, text->content);
}

/* ================================ */
