#include <player.h>
#include <stdlib.h>

Player *createPlayer(int width, int height, int pos_x, int pos_y) {
    Player *player = (Player *)malloc(sizeof(Player));
    if (player == NULL) {
        perror("ALLOC ERROR : Could not allocate memory for player :");
        return NULL;
    }

    return player;
}

void drawPlayer(SDL_Renderer *context);

void destroyPlayer(Player *player) {
    free(player);
}