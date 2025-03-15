#include "../include/io.h"

/* ================================================================ */

typedef struct input_manager {

    /* Array to hold the state of each key */
    Uint8 current_state[SDL_NUM_SCANCODES];
    Uint8 previous_state[SDL_NUM_SCANCODES];

    /* Left, Middle, and Right mouse buttons */
    Uint8 current_BTN_state[3];
    Uint8 previous_BTN_state[3];

    /* Mouse cursor position */
    int X;
    int Y;
} InputManager;

static InputManager IO;

/* ================================================================ */

void Input_update(void) {

    /* Store current key states in the previous states */
    memcpy(IO.previous_state, IO.current_state, sizeof(IO.current_state));

    /* Update current key states */
    const Uint8* current_state = SDL_GetKeyboardState(NULL);
    memcpy(IO.current_state, current_state, sizeof(IO.current_state));

    memcpy(IO.previous_BTN_state, IO.current_BTN_state, sizeof(IO.current_BTN_state));

    /* Update mouse states */
    IO.current_BTN_state[0] = SDL_GetMouseState(&IO.X, &IO.Y) & SDL_BUTTON(SDL_BUTTON_LEFT);
    IO.current_BTN_state[1] = SDL_GetMouseState(&IO.X, &IO.Y) & SDL_BUTTON(SDL_BUTTON_MIDDLE);
    IO.current_BTN_state[2] = SDL_GetMouseState(&IO.X, &IO.Y) & SDL_BUTTON(SDL_BUTTON_RIGHT);
}

/* ================================ */

int Input_isKey_pressed(SDL_Scancode key) {
    return IO.current_state[key];
}

/* ================================ */

int Input_isKey_just_pressed(SDL_Scancode key) {
    return IO.current_state[key] && !IO.previous_state[key];
}

/* ================================ */

int Input_isBtn_pressed(MouseButton btn) {

    if ((btn < 0) || (btn > 2)) {
        return -1;
    }

    return IO.current_BTN_state[btn];
}

/* ================================ */

int Input_isBtn_just_pressed(MouseButton btn) {

    if ((btn < 0) || (btn > 2)) {
        return -1;
    }

    return IO.current_BTN_state[btn] && !IO.previous_BTN_state[btn];
}

/* ================================================================ */
