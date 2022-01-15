#include <ncurses.h>
#include <clocale>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {

    // init
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    raw();
    keypad(stdscr, true);
    noecho();
    curs_set(0);
    // default values
    int posx = 0;
    int posy = 0;
    int speed = 1;
    int delay = 16;
    int logo_total = 0;
    int logo_columns = 0;
    int logo_rows = 0;
    string logopath = "logo0.txt";

    // process arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-s") == 0) {
            speed = atoi(argv[i+1]);
            i++;
        } else if (strcmp(argv[i], "-d") == 0) {
            delay = atoi(argv[i+1]);
            i++;
        } else if (strcmp(argv[i], "-l") == 0) {
            logopath = argv[i+1];
            i++;
        } else if (strcmp(argv[i], "-f") == 0) {
            string command = "figlet \"" + (string) argv[i+1] + "\" > _cbounce.txt";
            const char * _command = command.c_str();
            system(_command);
            logopath = "_cbounce.txt";
            i++;
        }
    }

    // read logo from txt
    string filename(logopath);
    vector<char> bytes;
    char byte = 0;
    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '" << filename << "'" << endl;
        return EXIT_FAILURE;
    }
    while (input_file.get(byte)) {
        bytes.push_back(byte);
    }
    if (filename == "_cbounce.txt") bytes.pop_back(); // remove figlet's trailing newline
    for (const auto &i : bytes) {
        if (i == '\n') {
            logo_rows++;
        }
        else {
            logo_total++;
        }
    }
    logo_total++;
    logo_rows++;
    logo_columns = logo_total/logo_rows;
    char amogus[logo_total];
    int k = 0;
    for (const auto &i : bytes) {
        if (i != '\n') {
            amogus[k] = i;
            k++;
        }
    }
    input_file.close();
    if (logopath == "_cbounce.txt") remove("_cbounce.txt");

    int velx = speed*2;
    int vely = speed;
    int _x, _y;
    int row,col;
    getmaxyx(stdscr,row,col);

    bool quit = false;
    while (!quit) {

        // clock
        timeout(delay);

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
        for (int i = 0; i < logo_rows; i++) {
            for (int j = 0; j < logo_columns; j++) {
                mvaddch(posy+_y, posx+_x, ' ');
                _x++;
            }
            _x = 0;
            _y++;
        }

        // move amogus
        posx += velx;
        posy += vely;

        // render amogus
        _x = 0;
        _y = 0;
        for (int i = 0; i < logo_rows; i++) {
            for (int j = 0; j < logo_columns; j++) {
                char sus = amogus[i*logo_columns + j];
                mvaddch(posy+_y, posx+_x, sus);
                _x++;
            }
            _x = 0;
            _y++;
        }

        // check amogus collision
        if (posx+logo_columns >= col || posx <= 0) velx *= -1;
        if (posy+logo_rows >= row || posy <= 0) vely *= -1;

        // refresh screen
        wrefresh(stdscr);
    }
    
    endwin();

    return 0;
}

