#include "../include/texture.h"

Texture *Texture_new(SDL_Renderer *r, const char *filename)
{

	Texture *t = NULL;

	if ((t = calloc(1, sizeof(Texture))) == NULL)
	{
		return NULL;
	}

	if ((t->t = IMG_LoadTexture(r, filename)) == NULL)
	{
		free(t);
		return NULL;
	}

	t->r = r;

	return t;
}

/* ================================ */

int Texture_destroy(Texture **t)
{

	if ((t == NULL) || (*t == NULL))
	{
		return 1;
	}

	SDL_DestroyTexture((*t)->t);

	free(*t);
	*t = NULL;

	return 0;
}

/* ================================ */

int Texture_draw(const Texture *t, const SDL_Rect *src, const SDL_Rect *dst)
{

	return SDL_RenderCopy(t->r, t->t, src, dst);
}

RenderTexture RenderTexture_new(SDL_Renderer *renderer, int width, int height)
{
	RenderTexture rt = {.width = width, .height = height};
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
	SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	if (texture == NULL)
	{
		const char *error = SDL_GetError();
		printf("ERROR: %s\n", error);
		SDL_ClearError();
	}
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	rt.texture.r = renderer;
	rt.texture.t = texture;
	return rt;
}

void RenderTexture_destroy(RenderTexture rt)
{
	SDL_DestroyTexture(rt.texture.t);
}

void setRenderTarget(RenderTexture rt)
{
	SDL_SetRenderTarget(rt.texture.r, rt.texture.t);
}

void clearRenderTarget(SDL_Renderer *renderer)
{
	SDL_SetRenderTarget(renderer, NULL);
}