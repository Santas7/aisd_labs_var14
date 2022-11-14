// л/р номер 1 вариант 6 (2)
// Панюшкин Андрей Михайлович
#include <iostream>
#include <conio.h>
#include "BinImage.h"


void rprogress_bar(int i = 0) {
    if (i == 101) { system("color 2"); return ; }
    else {
        system("cls"); system("color 6");
        std::cout << ".............................................................. " << i << " %" << std::endl;
        rprogress_bar(++i);
    }
}
void text_for_menu() {
    std::cout << "[1] Drawing of rectangle"
        << std::endl << "[2] Invertion image (!)"
        << std::endl << "[3] Output image" 
        << std::endl << "[4] Adding another image to the image (+)" // Добавление другого изображения к изображению (+)
        << std::endl << "[5] Intersection of two images (*)" // Пересечение двух изображений (*)
        << std::endl << "[6] Adding an image to a Boolean value" // Умножение изображения на булевое значение
        << std::endl << "[7] Multiplying an image by a Boolean value" // Сложение изображения на булевое значение
        << std::endl << "[8] Fill ratio"
        << std::endl << "[9] Get value by (x, y)"
        << std::endl << "[BackSpace] Clean the image"
        << std::endl << "[Esc] Back"
        << std::endl << "-->";
}
int get_key() {
    int key = _getch();
    if (key == 27 || key == 49 || key == 50 || key == 51 || key == 52 || key == 53 || key == 54 || key == 55 || key == 56 || key == 57 || key == 8)
        return key;
    return 0;
}
int get_key2() {
    int key = _getch();
    if (key == 27 || key == 49 || key == 50 || key == 51 || key == 52 || key == 53 || key == 54 || key == 55 || key == 56 || key == 57 ||  key == 8)
        return key;
    return 0;
}
BinImage set_size_images(const std::string& type_image = "first") {
    int height, width;
    while (true) {
        std::cout << "Please enter the size " << type_image << " picture.." << std::endl << "Height--> "; std::cin >> height;
        std::cout << "Width--> "; std::cin >> width;
        if (width < 0 || height < 0) {
            std::cout << "Try again! ";
        }
        else {
            std::cout << "Okey.." << std::endl;
            break;
        }
    }
    return BinImage(height, width);
}
void menu() {
    BinImage image_1 = set_size_images("first"), image_2 = set_size_images("second");
    system("cls");

    std::cout << "[1] First image" << std::endl << "[2] Second image" << std::endl << "[Backspace] Exit" << std::endl << "--> "; 
    while (true) {
        int x_1, y_1, x_2, y_2;
        int commandKey = get_key2();
        if (commandKey == 8) {
            system("cls");
            std::cout << "Bye... waiting for you again...)";
            break;
        }
        switch (commandKey) {
        // первое изображение 
        case '1': 
        {
            system("cls");
            text_for_menu();
            while (true) {
                int commandKey = get_key();
                if (commandKey == 27) {
                    system("cls");
                    std::cout << "[1] First image" << std::endl << "[2] Second image" << std::endl << "[Backspace] Exit" << std::endl << "--> "; break;
                }
                switch (commandKey) {
                case '1':
                    system("cls");
                    try {
                        std::cout << "First point.." << std::endl << "X--> "; 
                        std::cin >> x_1;
                        std::cout << "Y--> "; 
                        std::cin >> y_1;
                        std::cout << "Second point.." << std::endl << "X--> "; 
                        std::cin >> x_2;
                        std::cout << "Y--> "; 
                        std::cin >> y_2;
                        if (x_1 < 0 || y_1 < 0) {
                            image_1.rdraw_rectangle(x_1, y_1, x_2, y_2, 0, 0);
                        }
                        else {
                            image_1.rdraw_rectangle(x_1, y_1, x_2, y_2, x_1, y_1);
                        }
                        std::cout << "Okey.." << std::endl;
                    }
                    catch (const std::out_of_range& err) {
                        std::cerr << err.what() << std::endl;
                    }
                    std::cout << "[0] Back--> ";
                    break;
                case '2':
                    system("cls");
                    // rprogress_bar();
                    image_1 = !image_1;
                    std::cout << "Okey.." << std::endl << "[0] Back--> ";
                    break;
                case '3':
                    system("cls");
                    // rprogress_bar();
                    // image_1.print_standart();
                    image_1.rprint_standart(image_1);
                    std::cout << "[0] Back--> ";
                    break;
                case '4':
                    system("cls");
                    // rprogress_bar();
                    try {
                        image_1 = image_1 + image_2;
                    }
                    catch (const std::out_of_range& err) {
                        std::cerr << err.what() << std::endl;
                    }
                    std::cout << "Okey.." << std::endl << "[0] Back--> ";
                    break;

                case '5':
                    system("cls");
                    // rprogress_bar();
                    try {
                        image_1 = image_1 * image_2;
                    }
                    catch (const std::out_of_range& err) {
                        std::cerr << err.what() << std::endl;
                    }
                    std::cout << "Okey.." << std::endl << "[0] Back--> ";
                    break;
                case '6':
                    system("cls");
                    // rprogress_bar();
                    try {
                        bool value;
                        std::cout << "Enter a boolean value--> "; std::cin >> value;
                        image_1 = image_1 + value;
                        // std::cout << image_1 << std::endl;
                    }
                    catch (const std::out_of_range& err) {
                        std::cerr << err.what() << std::endl;
                    }
                    std::cout << "Okey.." << std::endl << "[0] Back--> ";
                    break;
                case '7':
                    system("cls");
                    // rprogress_bar();
                    try {
                        bool value;
                        std::cout << "Enter a boolean value--> "; std::cin >> value;
                        image_1 = image_1 * value;
                    }
                    catch (const std::out_of_range& err) {
                        std::cerr << err.what() << std::endl;
                    }
                    std::cout << "Okey.." << std::endl << "[0] Back--> ";
                    break;
                case '8':
                    system("cls");
                    // rprogress_bar();
                    try {
                        std::cout << "Fill rate = " << image_1.fill_rate();
                    }
                    catch (const std::out_of_range& err) {
                        std::cerr << err.what() << std::endl;
                    }
                    std::cout << std::endl << "Okey.." << std::endl << "[0] Back--> ";
                    break;
                case '9':
                    system("cls");
                    // rprogress_bar();
                    try {
                        std::cout << "X: "; std::cin >> x_1;
                        std::cout << "Y: "; std::cin >> y_1;
                        std::cout << image_1(x_1, y_1) << std::endl;
                    }
                    catch (const std::out_of_range& err) {
                        std::cerr << err.what() << std::endl;
                    }
                    std::cout << std::endl << "Okey.." << std::endl << "[0] Back--> ";
                    break;
                case 8:
                    system("cls");
                    // rprogress_bar();
                    image_1.clean_the_image();
                    std::cout << "The image space has been successfully cleared and is ready for further use!" 
                        << std::endl << "[0] Back--> ";
                    break;
                case 0:
                    system("cls");
                    system("color 7");
                    text_for_menu();
                    break;
                default:
                    system("cls");
                    std::cout << "Error!" << std::endl;
                    break;
                }
            }
            break;
        }
        // второе изображение
        case '2': 
        {
            system("cls");
            text_for_menu();
            while (true) {
                int commandKey = get_key();
                if (commandKey == 27) {
                    system("cls");
                    std::cout << "[1] First image" << std::endl << "[2] Second image" << std::endl << "[Backspace] Exit" << std::endl << "--> "; break;
                }
                switch (commandKey) {
                case '1':
                    system("cls");
                    try {
                        std::cout << "First point.." << std::endl << "X--> "; 
                        std::cin >> x_1;
                        std::cout << "Y--> "; 
                        std::cin >> y_1;
                        std::cout << "Second point.." << std::endl << "X--> "; 
                        std::cin >> x_2;
                        std::cout << "Y--> "; 
                        std::cin >> y_2;
                        if (x_1 < 0 || y_1 < 0) {
                            image_2.rdraw_rectangle(x_1, y_1, x_2, y_2, 0, 0);
                        }
                        else {
                            image_2.rdraw_rectangle(x_1, y_1, x_2, y_2, x_1, y_1);
                        }
                        std::cout << "Okey.." << std::endl;
                    }
                    catch (const std::out_of_range& err) {
                        std::cerr << err.what() << std::endl;
                    }
                    std::cout << "[0] Back--> ";
                    break;
                case '2':
                    system("cls");
                    rprogress_bar();
                    image_2 = !image_2;
                    std::cout << "Okey.." << std::endl << "[0] Back--> ";
                    break;
                case '3':
                    system("cls");
                    rprogress_bar();
                    // image_2.print_standart();
                    image_2.rprint_standart(image_1);
                    std::cout << "[0] Back--> ";
                    break;
                case '4':
                    system("cls");
                    rprogress_bar();
                    try {
                        image_2 = image_2 + image_1;
                    }
                    catch (const std::out_of_range& err) {
                        std::cerr << err.what() << std::endl;
                    }
                    std::cout << "Okey.." << std::endl << "[0] Back--> ";
                    break;
                case '5':
                    system("cls");
                    rprogress_bar();
                    try {
                        image_2 = image_2 * image_1;
                    }
                    catch (const std::out_of_range& err) {
                        std::cerr << err.what() << std::endl;
                    }
                    std::cout << "Okey.." << std::endl << "[0] Back--> ";
                    break;
                case '6':
                    system("cls");
                    rprogress_bar();
                    try {
                        bool value;
                        std::cout << "Enter a boolean value--> "; std::cin >> value;
                        image_2 = image_2 + value;
                    }
                    catch (const std::out_of_range& err) {
                        std::cerr << err.what() << std::endl;
                    }
                    std::cout << "Okey.." << std::endl << "[0] Back--> ";
                    break;
                case '7':
                    system("cls");
                    rprogress_bar();
                    try {
                        bool value;
                        std::cout << "Enter a boolean value--> "; std::cin >> value;
                        image_2 = image_2 * value;
                    }
                    catch (const std::out_of_range& err) {
                        std::cerr << err.what() << std::endl;
                    }
                    std::cout << "Okey.." << std::endl << "[0] Back--> ";
                    break;
                case '8':
                    system("cls");
                    rprogress_bar();
                    std::cout << "Fill rate = "
                        << image_2.fill_rate()
                        << std::endl << "Okey.."
                        << std::endl << "[0] Back--> ";
                    break;
                case '9':
                    system("cls");
                    // rprogress_bar();
                    try {
                        std::cout << "X: "; std::cin >> x_1;
                        std::cout << "Y: "; std::cin >> y_1;
                        std::cout << image_2(x_1, y_1) << std::endl;
                    }
                    catch (const std::out_of_range& err) {
                        std::cerr << err.what() << std::endl;
                    }
                    std::cout << std::endl << "Okey.." << std::endl << "[0] Back--> ";
                    break;
                case 8:
                    system("cls");
                    rprogress_bar();
                    try {
                        std::cout << "Fill rate = " << image_2.fill_rate();
                    }
                    catch (const std::out_of_range& err) {
                        std::cerr << err.what() << std::endl;
                    }
                    std::cout << std::endl << "Okey.." << std::endl << "[0] Back--> ";
                    break;
                case 0:
                    system("cls");
                    system("color 7");
                    text_for_menu();
                    break;
                default:
                    system("cls");
                    std::cout << "Error!" << std::endl;
                    break;
                }
            }
            break;
        }
        case 0:
            system("cls");
            std::cout << "[1] First image" << std::endl << "[2] Second image" << std::endl << "[Backspace] Exit" << std::endl << "--> "; break;
        default:
            system("cls");
            std::cout << "Error!" << std::endl;
            break;
        }
    }
}
int main() {
    menu();
    return 0;
}