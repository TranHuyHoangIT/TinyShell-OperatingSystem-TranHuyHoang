#include <ncurses.h>
#include <unistd.h>

// gcc -o Countdown Countdown.c -lncurses
int main() {
    initscr(); // Init ncurses
    curs_set(0); // Hide the flashing cursor

    int seconds = 60;
    int minutes, seconds_remain;

    while (seconds >= 0) {
        minutes = seconds / 60;
        seconds_remain = seconds % 60;

        mvprintw(0, 0, "Countdown Timer: %02d:%02d", minutes, seconds_remain);
        refresh(); // Update screen

        sleep(1); // Slepp 1 secend
        seconds--;

        clear(); // Clear screen to update clock
    }

    mvprintw(0, 0, "Countdown Timer: 00:00");
    refresh(); // Update screen
    endwin(); // End ncurses
    return 0;
}
