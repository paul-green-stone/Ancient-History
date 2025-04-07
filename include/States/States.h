#ifndef _ANCIENT_HISTORY_STATES_H
#define _ANCIENT_HISTORY_STATES_H

/* ================================================================ */
/* ================== Player's Different States =================== */
/* ================================================================ */

/**
 * The player is IDLEing
 * 
 * Usage: `State_create(Standing);`
 */
extern const void* Standing;

/**
 * The player is running.
 * 
 * Usage: `State_create(Running);`
 */
extern const void* Running;

/**
 * The player is ducking.
 * 
 * Usage: `State_create(Ducking);`
 */
extern const void* Ducking;

/**
 * The player is crouching.
 * 
 * Usage: `State_create(Crouching);`
 */
extern const void* Crouching;

/**
 * The player is jumping.
 * 
 * Usage: `State_create(Jumping);`
 */
extern const void* Jumping;

/*
 * Handles player falling — either off the platform or after a jump.
 * 
 * Usage: `State_create(Falling);`
 */
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

/** 
 * Resting after patrolling or any other activity.
 * 
 * Usage: `State_create(Resting, direction, time);`
 * 
 * @param direction direction into which to travel after resting
 * @param time the time during which the enemy should be in this state
 */
extern const void* Resting;

/**
 * Enemy falling state.
 * 
 * Usage: `State_create(EnemyFalling);`
 */
extern const void* EnemyFalling;

/* ================================================================ */

#endif /* _ANCIENT_HISTORY_STATES_H */
