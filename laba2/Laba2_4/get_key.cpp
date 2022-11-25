#include "get_key.h"
#include <conio.h>

int get_key() {
    int key = _getch();
    if (key == 27 || key == 49 || key == 50 || key == 51 || key == 52 || key == 53 || key == 54 || key == 55 || key == 56 || key == 57 || key == 8)
        return key;
    return 0;
}
int get_key2() {
    int key = _getch();
    if (key == 27 || key == 49 || key == 50 || key == 51 || key == 52 || key == 53 || key == 54 || key == 55 || key == 56 || key == 57 || key == 8)
        return key;
    return 0;
}