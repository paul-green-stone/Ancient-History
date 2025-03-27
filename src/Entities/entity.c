#include "../../include/Entities/__entity_class.h"
#include "../../include/Entities/__entity.h"
#include "../../include/Entities/entity.h"
#include "../../include/Entities/Entity.h"
#include "../../framework/include/Math/Vector2D.h"
#include "../../include/Entities/Manager.h"
#include "../../include/States/state.h"
#include "../../include/States/__state_class.h"
#include "../../include/constants.h"

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

    return ((r1.x < r2.x + r2.w) && (r1.x + r1.w > r2.x) && (r1.y < r2.y + r2.h) && (r1.y + r1.h > r2.y));
}

/* ================================ */

int Entity_isGrounded(const void* _self, Level* level) {

    const struct entity* self = _self;

    /* Check only the presence of a platform beneath the player */
    return level->level[(int) (self->position.y + self->height) / TILE_SIZE][self->level_x] > 0;
}

/* ================================ */

int Entity_isPlatformAbove(const void* _self, Level* level) {

    const struct entity* self = _self;

    /* Check only the presence of a platform above the player */
    return level->level[(int) (self->position.y / TILE_SIZE)][self->level_x] > 0;
}

/* ================================================================ */
