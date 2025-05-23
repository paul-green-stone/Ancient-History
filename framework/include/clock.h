#ifndef _SPARK_CLOCK_H
#define _SPARK_CLOCK_H

typedef struct clock Clock;

typedef enum { STARTED, STOPPED } Clock_State;

/**
 * Create a new instance of the `Clock` data type, which is a simple
 * mechanism for managing time within a game. It allows you to
 * set timers, check if time is up, and adjust the clock's speed, among other features.
 * 
 * @return Returns the `Clock` that was created or NULL on failure.
 */
Clock* Clock_new(void);

/**
 * Destroy a clock.
 * 
 * @param clock the clock to destroy (`&clock`)
 * 
 * @return Returns 0 on success or -1 on failure.
 */
int Clock_destroy(Clock** clock);

/**
 * Start a clock. A clock has two states: `STARTED` and `STOPPED`.
 * When a clock is `STARTED`, it accumulates time passed and can be updated.
 * 
 * @param clock clock to start
 * 
 * @return None.
 */
void Clock_start(Clock* clock);

/**
 * Stop a clock. A clock's time cannot be set or adjusted while it is stopped.
 * 
 * @param clock clock to stop
 * 
 * @return None.
 */
void Clock_stop(Clock* clock);

/**
 * Update the clock. Adjust its internal variable to track time passed.
 * 
 * @param clock clock to update
 * 
 * @return None.
 */
void Clock_update(Clock* clock);

/**
 * Set a clock's time modifier. By default, it's `1.0f`, meaning it is no different from real time.
 * Setting the clock's modifier to `2.0f`, for example, speeds up time,
 * meaning that one second of real time will pass as two seconds on the clock.
 * 
 * @param clock clock to adjust
 * @param speed the clock speed modifier
 * 
 * @return Returns 0 on success or -1 on failure.
 */
int Clock_setSpeed(Clock* clock, double speed);

/**
 * Check if the clock's timer has reached its set time.
 * 
 * @param clock clock to check
 * 
 * @return Returns 1 on success or 0 on failure.
 */
int Clock_isReady(const Clock* clock);

/**
 * Reset the clock's timer.alignas
 * 
 * @param clock the timer on the `clock` that needs to be reset
 * 
 * @return None.
 */
void Clock_reset(Clock* clock);

/**
 * Set the clock's timer.
 * 
 * @param clock the timer on the `clock` that need to be set
 * 
 * @return None.
 */
void Clock_setTimer(Clock* clock, double seconds);

/**
 * Get the time passed between frames.
 * 
 * @param clock 
 * 
 * @return Delta time.
 */
double Clock_getDelta(const Clock* clock);

#endif /* _SPARK_CLOCK_H */
