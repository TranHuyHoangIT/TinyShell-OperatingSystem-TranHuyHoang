#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>

// The program displays the current time
//Path of program: /home/hoangtran/newPath/Clock.c (../newPath/Clock.c)
int main() {
    initscr(); // Init ncurses
    curs_set(0); // Hide the flashing cursor

    time_t rawtime;
    struct tm *timeinfo;
    
    while (1) {
        time(&rawtime);
        timeinfo = localtime(&rawtime);

        printf("Current Time: %02d:%02d:%02d\r", 
               timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

        fflush(stdout); // Xoá bộ nhớ đệm để in ra ngay lập tức

        // Chờ 1 giây trước khi cập nhật đồng hồ
        sleep(1);
    }
    endwin(); // End ncurses
    return 0;
}
