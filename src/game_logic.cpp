// game_logic.cpp

#include "game_logic.h"

void logic(GameState &state, const Input usr_input) {
    switch (state.type) {
        case StateType::exit:
            quitting = true;
            break;
        case StateType::alive:
            if (int(Input::up) <= int(usr_input) <= int(Input::right))
                movePlayer(state, usr_input);
            break;

            // TODO: Process other types of states
    }
}

// IN-GAME LOGICS

// 4 movement directions represented in coordinate offsets
const Pos movement[4] = {
    {0, 1},   // Up
    {0, -1},  // Down
    {1, 0},   // Left
    {-1, 0}   // Right
};

/**
 * Handles what happens when player run into an entity.
 * Default response is to do nothing and block movement.
 */
template <typename T>
void entityInteraction(T *entity, Player *player, const Pos movement) {}
template <>
void entityInteraction(PowerUp *power_up, Player *player, const Pos movement) {
    // TODO: Handle power-ups
}
template <>
void entityInteraction(Bomb *bomb, Player *player, const Pos movement) {
    // TODO: Handle bombs
}

// Process the movement of player character
void movePlayer(GameState &state, const Input usr_input) {
    Pos destination = state.player->getPosition() + movement[int(usr_input)];
    // Check if player is trying to enter an inaccessible tile
    if (state.playfield->isObstacle(destination)) return;

    Entity *entity_encounter = state.playfield->locateEntityAt(destination);
    // Check if player runs into an entity
    if (!entity_encounter) {
        state.player->setPosition(destination);
        return;
    } else {
        entityInteraction(entity_encounter, state.player,
                          movement[int(usr_input)]);
    }
}

bool checkRunning() { return !quitting; }