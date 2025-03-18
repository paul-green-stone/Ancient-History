#include <SDL2/SDL.h>

#include "../../include/Entities/Entity.h"
#include "../../include/Entities/__entity.h"
#include "../../include/Entities/__entity_class.h"
#include "Level.h"

/* ================================================================ */

static void* Entity_ctor(void* _self, va_list* app) {

    struct entity* self = _self;

    self->position = va_arg(*app, Vector2D);
    self->position.x *= TILE_SIZE;
    self->position.y *= TILE_SIZE;
    
    self->width = va_arg(*app, int);
    self->height = va_arg(*app, int);

    self->lives = va_arg(*app, int);

    self->texture = va_arg(*app, Texture*);

    self->color = *(va_arg(*app, SDL_Color*));

    /* Completely initialized structure at this point */
    return self;
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct entity_class _Entity = {
    .size = sizeof(struct entity),
    .ctor = Entity_ctor,
};

const void* Entity = &_Entity;

/* ================================================================ */
