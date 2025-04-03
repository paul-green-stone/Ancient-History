#include "../../include/Entities/__entity_class.h"
#include "../../include/Entities/__entity.h"
#include "../../include/Entities/entity.h"
#include "../../include/Entities/Entity.h"
#include "../../framework/include/Math/Vector2D.h"
#include "../../include/Entities/Manager.h"
#include "../../include/States/state.h"
#include "../../include/States/__state_class.h"
#include "../../include/constants.h"

#include "../../framework/include/io.h"

/* ================================================================ */

void* Entity_create(const void* _entity_type, ...) {

    const struct entity_class* entity_type = _entity_type;
    void* ent = NULL;

    if ((ent = calloc(1, entity_type->size)) == NULL) {
        return NULL;
    }

    *(const struct entity_class**) ent = entity_type;

    if (entity_type->ctor != NULL) {

        va_list ap;

        va_start(ap, _entity_type);
        /* Partially initialized structure at this point */
        ent = entity_type->ctor(ent, &ap);
        va_end(ap);
    }

    /* Store the entity in the manager */
    if (_entity_type == Player) {
        EntityManager_setPlayer(ent);
    }
    else {
        EntityManager_add(ent);
    }

    return ent;
}

/* ================================ */

void Entity_destroy(void* self) {

    const struct entity_class** ent_p = self;

    if ((self != NULL) && (*ent_p != NULL) && ((*ent_p)->dtor != NULL)) {
        self = (*ent_p)->dtor(self);
    }

    /* State is freed by its own function */
    State_destroy(((struct entity*) self)->state);

    free(self);
}

/* ================================================================ */
/* ================== STATICALLY LINKED FUNCTIONS ================= */
/* ================================================================ */

int Entity_draw(void* _self, SDL_Renderer* context) {

    struct entity* self;
    SDL_Color original_color;
    int status = 0;

    if (_self == NULL) {
        return -1;
    }

    if (State_draw(_self) == 0) {
        return status;
    }

    self = _self;
    SDL_Rect rect = { self->position.x, self->position.y, self->width, self->height };

    SDL_GetRenderDrawColor(context, &original_color.r, &original_color.g, &original_color.b, &original_color.a);
    SDL_SetRenderDrawColor(context, self->color.r, self->color.g, self->color.b, self->color.a);

    status = SDL_RenderFillRect(context, &rect);

    SDL_SetRenderDrawColor(context, original_color.r, original_color.g, original_color.b, original_color.a);

    self->level_x = self->position.x / TILE_SIZE;
    self->level_y = self->position.y / TILE_SIZE;

    return status;
}

/* ================================ */

Vector2D* Entity_get_position(const void* _self) {

    const struct entity* self = _self;

    if (_self == NULL) {
        return NULL;
    }

    return &self->position;
}

/* ================================ */

SDL_Rect Entity_get_dimensions(const void* _self) {
    
    const struct entity* self = _self;

    if (_self == NULL) {
        (SDL_Rect) {0, 0, 0, 0};
    }

    return (SDL_Rect) {self->position.x, self->position.y, self->width, self->height};
}

/* ================================ */

int Entity_isCollided(const void* self, const void* other) {

    SDL_Rect r1, r2;

    if ((self == NULL) || (other == NULL)) {
        return 0;
    }

    r1 = Entity_get_dimensions(self);
    r2 = Entity_get_dimensions(other);

    return does_rect_collide(r1, r2);
}

/* ================================ */

int Entity_isGrounded(const void* _self) {

    const struct entity* self = _self;
    SDL_Rect* env = Level_get_surroundings();

    SDL_Rect hitbox = (SDL_Rect) {.x = self->position.x, .y = self->position.y, .w = self->width, .h = self->height};
    SDL_Rect hitbox_2 = hitbox;

    hitbox_2.x -= 1;

    return does_rect_collide(hitbox, env[Bottom]) || does_rect_collide(hitbox_2, env[BottomRight]);
 }

/* ================================================================ */
