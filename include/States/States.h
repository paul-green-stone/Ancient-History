#ifndef _ANCIENT_HISTORY_STATES_H
#define _ANCIENT_HISTORY_STATES_H

/* ================================================================ */
/* ================== Player's Different States =================== */
/* ================================================================ */

/* The player is IDLEing*/
extern const void* Standing;

/* The player is running */
extern const void* Running;

/* The player is ducking */
extern const void* Ducking;

/* The player is crouching */
extern const void* Crouching;

/* The player is jumping */
extern const void* Jumping;

/* Handles player falling — either off the platform or after a jump */
extern const void* Falling;

/* ================================================================ */
/* ==================== Other Different States ==================== */
/* ================================================================ */

/**
 * Going back and forth.
 * 
 * Usage: `State_create(Patrolling, row, column, distance, direction);`
 * 
 * @param row the row of the origin tile from which the patrolling starts
 * @param column the column of the origin tile from which the patrolling starts
 * @param distance the distance to travel in one direction from the origin tile
 * @param direction direction of movement, either `1` or `-1`
 */
extern const void* Patrolling;

/* Resting after patrolling */
extern const void* Resting;

/* Enemy falling state */
extern const void* EnemyFalling;

/* ================================================================ */

#endif /* _ANCIENT_HISTORY_STATES_H */
