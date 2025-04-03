#ifndef _ANCIENT_HISTORY_ENEMY_REPRESENTATION_H
#define _ANCIENT_HISTORY_ENEMY_REPRESENTATION_H

#include "../../include/Entities/__entity.h"
#include "../../include/Entities/__entity_class.h"

/* ================================================================ */

struct enemy {

    struct entity _;

    int patrolling_distance;
};

/* ================================================================ */

#endif /* _ANCIENT_HISTORY_ENEMY_REPRESENTATION_H */
