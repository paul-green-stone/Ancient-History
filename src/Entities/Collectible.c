#include "../../include/Entities/Entity.h"
#include "../../include/Entities/__entity.h"
#include "../../include/Entities/__entity_class.h"
#include "../../include/Entities/__collectable.h"

/* ================================================================ */

static void* Collectible_ctor(void* _self, va_list* app) {

    struct player* self = ((const struct entity_class*) Entity)->ctor(_self, app);

    return self;
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct entity_class _Collectible = {
    .size = sizeof(struct collectible),
    .ctor = Collectible_ctor,
};

const void* Collectible = &_Collectible;

/* ================================================================ */
