// main.cpp

#include <curses.h>
#include <unistd.h>

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "control.h"
#include "display.h"
#include "game_logic.h"
#include "gamestate.h"

const int FRAMES_PER_SECOND = 30;

int main() {
    using namespace std::chrono;
    microseconds frame_time =
        seconds(1) / FRAMES_PER_SECOND;  // Length of a frame

    Input usr_input = Input::none;
    GameState gamestate;

    // Initialize curses
    initscr();
    keypad(stdscr, true);

    while (checkRunning()) {
        display();
        usr_input = getInput();
        logic(gamestate, usr_input);

        usleep(frame_time.count());  // Wait until next frame
    }

    // Cleanup for curses
    endwin();

    return 0;
}
