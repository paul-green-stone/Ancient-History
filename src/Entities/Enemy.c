#include "../../include/Entities/Entity.h"
#include "../../include/Entities/__entity.h"
#include "../../include/Entities/__entity_class.h"
#include "../../include/Entities/__enemy.h"

/* ================================================================ */

static void* Enemy_ctor(void* _self, va_list* app) {

    struct enemy* self = ((const struct entity_class*) Entity)->ctor(_self, app);

    return self;
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct entity_class _Enemy = {
    .size = sizeof(struct enemy),
    .ctor = Enemy_ctor,
};

const void* Enemy = &_Enemy;

/* ================================================================ */
