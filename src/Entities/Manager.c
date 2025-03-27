#include "../../include/Entities/__collectable.h"
#include "../../include/Entities/__enemy.h"
#include "../../include/Entities/__entity_class.h"
#include "../../include/Entities/__entity.h"
#include "../../include/Entities/entity.h"
#include "../../include/Entities/Entity.h"
#include "../../include/Entities/Manager.h"
#include "../../include/Entities/Player.h"
#include "../../include/States/States.h"
#include "../../include/States/state.h"

#include "../../framework/include/io.h"

/* ================================================================ */

typedef struct entity_manager {

    size_t num_entities;        /* Number of entities */

    struct entity* head;        /* First entity in the list */
    struct entity* tail;        /* Last entity in the list */

    struct entity* player;      /* Player */

    Level* current;             /* Current level */

} EntityManager;

static EntityManager em = {0, 0, 0};

/* ================================================================ */
/* ============================ STATIC ============================ */
/* ================================================================ */

static void* _EntityManager_delete_first(void) {

   struct entity* ent = NULL;

    if (em.num_entities > 0) {

        ent = em.head;

        if (em.num_entities == 1) {
            em.head = em.tail = NULL;
        }
        else {
            em.head = em.head->next;
        }

        em.num_entities--;
    }

    return ent;
}

/* ================================ */

static void _EntityManager_destroy_entity(void* entity) {

    struct entity* current = NULL;
    struct entity* previous = NULL;

    struct entity* ent = NULL;

    if (em.num_entities > 0) {

        if ((em.num_entities == 1) && (entity == em.head)) {
            ent = _EntityManager_delete_first();
        }
        else {

            for (current = em.head; current != entity; previous = current, current = current->next) ;

            ent = current;
            previous->next = current->next;

            if (current == em.tail) {
                em.tail = previous;
            }
        }

        Entity_destroy(ent);

        em.num_entities--;
    }
}

/* ================================================================ */

int EntityManager_add(const void* entity) {

    if (em.num_entities == 0) {
        em.head = em.tail = entity;
    }
    else {
        em.tail->next = entity;
        em.tail = entity;
    }

    em.num_entities++;

    return 0;
}

/* ================================ */

int EntityManager_setPlayer(const void* player) {

    if (em.player == NULL) {
        
        em.player = player;

        return 0;
    }

    return -1;
}

/* ================================ */

void EntityManager_clear(void) {

    struct entity* ent = NULL;

    while (em.num_entities > 0) {

        ent = _EntityManager_delete_first();

        Vector2D* pos = Entity_get_position(ent);

        Entity_destroy(ent);
    }

    if (em.player != NULL) {
        Entity_destroy(em.player);
    }
}

/* ================================ */

void EntityManager_draw(SDL_Renderer* context) {

    struct entity* ent = NULL;

    for (ent = em.head; ent != NULL; ent = ent->next) {

        if (ent->lives > 0) {
            Entity_draw(ent, context);
        }
    }

    Entity_draw(em.player, context);
}

/* ================================ */

void EntityManager_process(void) {

    struct entity* ent = NULL;
    struct entity_class* ent_class = NULL;

    for (ent = em.head; ent != NULL; ent = ent->next) {

        ent_class = *(struct entity_class**) ent;

        if (Entity_isCollided(em.player, ent)) {

            if (ent_class == Collectible) {

                /* Any `Collectible` entity has a single "life" */
                ent->lives--;
                printf("Collision detected\n");

                _EntityManager_destroy_entity(ent);
            }
        }
    }

    State_handle(em.player);
    State_update(em.player);
}

/* ================================ */

Level* EntityManager_getLevel(void) {
    return em.current;
}

/* ================================ */

void EntityManager_setLevel(Level* level) {
    
    if (level == NULL) {
        return ;
    }

    em.current= level;
}

/* ================================================================ */
