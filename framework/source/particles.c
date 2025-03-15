#include <stdbool.h>
#include <stdlib.h>

#include "../include/particles.h"
#include "../include/shapes.h"
#include "../include/Math/math.h"

/* ================================================================ */

#define rand_range_f(min, max) (((float)rand()/(float)RAND_MAX)*(max-min) + min)

const int VELS[2] = {-1, 1};

/* ================================ */

static inline Particle Particle_spawn(Vector2D origin, float radius, float decay, float spread, SDL_Color color, bool random_size) {

	Particle particle = (Particle) {
		.active = true,
		.pos = origin,
		.radius = random_size ? (float) rand_range_f(1, radius) : radius,
		.decay = decay,
		.speed = (Vector2D) { rand_range_f(0, spread), rand_range_f(0, spread) },
		.vel = {VELS[rand_range(0, 1)], VELS[rand_range(0, 1)]},
		.color = color,
	};

	return particle;
}

/* ================================ */

/**
 * Handles the physics for a single particle
 * 
 * @return Returns `true` if the particle is no longer active. This is used in for the loop function.
 */
static bool handle_particle(Particle *particle) {
	
	if (!particle->active) {
		return true;
	}

	/* Move the particle */
	particle->pos.x += particle->speed.x * particle->vel[0];
	particle->pos.y += particle->speed.y * particle->vel[1];

	/* Let the particle decay */
	particle->radius -= particle->decay;

	/* If the particle gets bellow one pixel radius, mark it as no longer active */
	bool deleted = false;

	if (particle->radius < 1) {

		particle->active = false;
		deleted = true;
	}

	return deleted;
}

/* ================================ */

ParticleEffect* ParticleEffect_new(Vector2D origin, float spread, float decay, float radius, SDL_Color color, bool loop, bool random_size) {

	ParticleEffect *effect = NULL;

	if ((effect = calloc(1, sizeof(struct particle_effect))) == NULL) {
		return NULL;
	}

	effect->origin = origin;
	effect->spread = spread;
	effect->radius = radius;
	effect->decay = decay;
	effect->color = color;
	effect->loop = loop;
	effect->random_size = random_size;

	for (int i = 0; i < MAX_PARTICLES; i++) {
		effect->particles[i] = Particle_spawn(origin, radius, decay, spread, color, random_size);
	}

	return effect;
}

/* ================================ */

int ParticleEffect_destroy(ParticleEffect **effect) {

	if ((effect == NULL) || (*effect == NULL)) {
		return -1;
	}

	free(*effect);
	*effect = NULL;

	return 0;
}

/* ================================ */

void ParticleEffect_run(ParticleEffect *effect) {

	for (int i = 0; i < MAX_PARTICLES; i++) {

		/* If loop is enabled, respawn the particle */
		if (handle_particle(&(effect->particles[i])) && effect->loop) {

			effect->particles[i] = Particle_spawn(effect->origin, effect->radius, effect->decay, effect->spread, effect->color, effect->random_size);
		}
	}
}

/* ================================ */

void ParticleEffect_draw(ParticleEffect *effect, SDL_Renderer *context) {

	for (int i = 0; i < MAX_PARTICLES; i++) {

		if (!effect->particles[i].active) { continue; }

		Particle particle = effect->particles[i];
		draw_circle(context, particle.pos, particle.radius, particle.color);
	}
}

/* ================================================================ */
