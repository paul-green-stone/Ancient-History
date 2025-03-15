#include "Math/Vector2D.h"
#include <stdbool.h>
#include <SDL2/SDL.h>

/* ================================================================ */

/* Maximum number of particles per effect */
#define MAX_PARTICLES (20)

/**
 * Structure for a single particle
 */
typedef struct particle {

	/* Position of particle */
	Vector2D pos;

	/* Speed of particle */
	Vector2D speed;

	/* Velocity of particle (either `0`, `1`, or `-1` for both X and Y directions) */
	int vel[2];

	/* Size of particle */
	float radius;

	/* Decay rate of the particle */
	float decay;

	/* Used to indicate if the particle is still present */
	bool active;

	/* Color of the particle */
	SDL_Color color;
} Particle;

/**
 * Structure for a single particle
 */
typedef struct particle_effect {

	/* Array of all particles */
	Particle particles[MAX_PARTICLES];

	/* Origin of the particles */
	Vector2D origin;

	/* Max speed at which particles can move */
	float spread;

	/* Initial radius of the particles */
	float radius;

	/* Decay rate of particles */
	float decay;

	/* Determines whether to loop the particle effect or not */
	bool loop;

	/* Color of the particles */
	SDL_Color color;

	/* When `true`, the radius of the particles will be randomized */
	bool random_size;
} ParticleEffect;

/**
 * Creates a new particle effect structure.
 *
 * @param origin Origin of the particles
 * @param spread Maximum speed at which the particles can move
 * @param decay How fast the patricles shrink per frame
 * @param radius Initial size of the particles
 * @param color Color of the particles
 * @param loop When `true`, the particles will respawn at origin once more
 * @param random_size When `true`, the radius of the particles will be randomized
 * 
 * @return A new particle effect (`ParticleEffect*`) on success or NULL on failure.
 */
ParticleEffect* ParticleEffect_new(Vector2D origin, float spread, float decay, float radius, SDL_Color color, bool loop, bool random_size);

/**
 * Deletes the particle effect and sets it's pointer to NULL for safety
 * 
 * @param effect that needs to be destroyed (&effect)
 * 
 * @return Returns 0 on success or -1 on failure.
 */
int ParticleEffect_destroy(ParticleEffect **effect);


/**
 * Runs the particle effect physics (NOTE: this does not handle rendering)
 * 
 * @param effect particle effect that needs to be run
 * 
 * @return None.
 */
void ParticleEffect_run(ParticleEffect *effect);

/**
 * Draws the particles
 * 
 * @param effect effect that neds to be rendered on the screen
 * @param context rendering context
 * 
 * @return None.
 */
void ParticleEffect_draw(ParticleEffect *effect, SDL_Renderer *context);

/* ================================================================ */
