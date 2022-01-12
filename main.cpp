#include <ncurses.h>
#include <clocale>

using namespace std;

#define WIDTH 12
#define HEIGHT 7

int main() {
    // init
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    raw();
    keypad(stdscr, true);
    noecho();
    curs_set(0);

    const char amogus[85] = R"( /MMMMNNMM\ /MM/    \MM\MNM\    /MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM    MMMM\MM/    \MM/)";

    // /MMMMNNMM\
    ///MM/    \MM\
    //MNM\    /MMM
    //MMMMMMMMMMMM
    //MMMMMMMMMMMM
    //MMMM    MMMM
    //\MM/    \MM/

    int posx = 0;
    int posy = 0;
    int velx = 2;
    int vely = 1;
    int _x, _y;
    int row,col;
    getmaxyx(stdscr,row,col);

    bool quit = false;
    while (!quit) {

        // clock
        timeout(16);

        // handle input
        int input;
        input = getch();
        switch (input) {
            case 'q':
                quit = true;
                break;
        }

        // clear previous amogus
        _x = 0;
        _y = 0;
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                mvaddch(posy-vely +_y, posx-velx+_x, ' ');
                _x++;
            }
            _x = 0;
            _y++;
        }

        // render amogus
        _x = 0;
        _y = 0;
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                char sus = amogus[i*WIDTH + j];
                mvaddch(posy+_y, posx+_x, sus);
                _x++;
            }
            _x = 0;
            _y++;
        }

        // move amogus
        posx += velx;
        posy += vely;

        // check amogus collision
        if (posx+WIDTH >= col || posx <= 0) velx *= -1;
        if (posy+HEIGHT >= row || posy <= 0) vely *= -1;

        // refresh screen
        wrefresh(stdscr);
    }
    
    endwin();

    return 0;
}

