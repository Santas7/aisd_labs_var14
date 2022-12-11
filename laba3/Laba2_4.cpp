// л/р номер 2 вариант 6 (2)
// Панюшкин Андрей Михайлович
#include <iostream>
#include "BinImage.h"
#include "get_key.h"


void text_for_menu() {
    std::cout << "[1] Drawing of rectangle"
        << std::endl << "[2] Invertion image (!)"
        << std::endl << "[3] Output image"
        << std::endl << "[4] Adding another image to the image (+)" // Добавление другого изображения к изображению (+)
        << std::endl << "[5] Intersection of two images (*)" // Пересечение двух изображений (*)
        << std::endl << "[6] Adding an image to a Boolean value" // Умножение изображения на булевое значение
        << std::endl << "[7] Multiplying an image by a Boolean value" // Сложение изображения на булевое значение
        << std::endl << "[8] Fill ratio"
        << std::endl << "[Esc] Back"
        << std::endl << "-->";
}


template<typename T>
void menu(BinImage<T> image_1, BinImage<T> image_2) {
    system("cls");

    std::cout << "[1] First image" << std::endl << "[2] Second image" << std::endl << "[Backspace] Exit" << std::endl << "--> ";
    while (true) {
        int x_1, y_1, x_2, y_2;
        T value;
        int command_key = get_key2();
        if (command_key == 8) {
            system("cls");
            std::cout << "Bye... waiting for you again...)";
            break;
        }
        switch (command_key) {
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
                        std::cout << "Value--> ";
                        std::cin >> value;
                        if (x_1 < 0 || y_1 < 0) {
                            image_1.rdraw_rectangle(image_1, x_1, y_1, x_2, y_2, 0, 0, value);
                        }
                        else {
                            image_1.rdraw_rectangle(image_1, x_1, y_1, x_2, y_2, x_1, y_1, value);
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
                    image_1 = !image_1;
                    std::cout << "Okey.." << std::endl << "[0] Back--> ";
                    break;
                case '3':
                    system("cls");
                    //std::cout << image_1 << std::endl;
                    std::cout << "[0] Back--> ";
                    break;
                case '4':
                    system("cls");
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
                    try {
                        std::cout << "Enter a value--> "; std::cin >> value;
                        image_1 = image_1 + value;
                    }
                    catch (const std::out_of_range& err) {
                        std::cerr << err.what() << std::endl;
                    }
                    std::cout << "Okey.." << std::endl << "[0] Back--> ";
                    break;
                case '7':
                    system("cls");
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
                    try {
                        std::cout << "Fill rate = " << image_1.fill_rate();
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
        // второе изображение
        case '2':
        {
            system("cls");
            text_for_menu();
            while (true) {
                int command_key = get_key();
                if (command_key == 27) {
                    system("cls");
                    std::cout << "[1] First image" << std::endl << "[2] Second image" << std::endl << "[Backspace] Exit" << std::endl << "--> "; break;
                }
                switch (command_key) {
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
                        std::cout << "Value--> ";
                        std::cin >> value;
                        if (x_1 < 0 || y_1 < 0) {
                            image_1.rdraw_rectangle(image_2, x_1, y_1, x_2, y_2, 0, 0, value);
                        }
                        else {
                            image_1.rdraw_rectangle(image_2, x_1, y_1, x_2, y_2, x_1, y_1, value);
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
                    image_2 = !image_2;
                    std::cout << "Okey.." << std::endl << "[0] Back--> ";
                    break;
                case '3':
                    system("cls");
                    //std::cout << image_2 << std::endl;
                    std::cout << "[0] Back--> ";
                    break;
                case '4':
                    system("cls");
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
                    try {
                        std::cout << "Enter a value--> "; std::cin >> value;
                        image_2 = image_2 + value;
                    }
                    catch (const std::out_of_range& err) {
                        std::cerr << err.what() << std::endl;
                    }
                    std::cout << "Okey.." << std::endl << "[0] Back--> ";
                    break;
                case '7':
                    system("cls");
                    try {
                        std::cout << "Enter a value--> "; std::cin >> value;
                        image_2 = image_2 * value;
                    }
                    catch (const std::out_of_range& err) {
                        std::cerr << err.what() << std::endl;
                    }
                    std::cout << "Okey.." << std::endl << "[0] Back--> ";
                    break;
                case '8':
                    system("cls");
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

int create_data_type() {
    int height, width;

    while (true) {
        std::cout << "Please enter the size picture.." << std::endl << "Height--> "; std::cin >> height;
        std::cout << "Width--> "; std::cin >> width;
        if (width < 0 || height < 0) {
            std::cout << "Try again! ";
        }
        else {
            std::cout << "Okey.." << std::endl;
            break;
        }
    }
    system("cls");
    std::cout << "[1] bool" << std::endl << "[2] char" << std::endl << "[3] short" << std::endl << "[4] float" << std::endl << "-->";
    while (true) {
        int command_key = get_key();
        if (command_key == 8) {
            system("cls");
            std::cout << "Bye... waiting for you again...)";
            break;
        }
        switch (command_key) {
            case '1':
            {
                system("cls");
                BinImage<bool> image_1(height, width), image_2(height, width);
                menu(image_1, image_2);
                break;
            }
            case '2':
            {
                system("cls");
                BinImage<char> image_1(height, width), image_2(height, width);
                menu(image_1, image_2);
                break;
            }
            case '3':
            {
                system("cls");
                BinImage<short> image_1(height, width), image_2(height, width);
                menu(image_1, image_2);
                break;
            }
            case '4':
            {
                system("cls");
                BinImage<float> image_1(height, width), image_2(height, width);
                menu(image_1, image_2);
                break;
            }
            case 0:
            {
                system("cls");
                std::cout << "[1] bool" << std::endl << "[2] char" << std::endl << "[3] short" << std::endl << "[4] float" << std::endl << "-->";
                break;
            }
            default:
            {
                system("cls");
                std::cout << "error!" << std::endl;
                break;
            }
        }
    }
    return 0;
}

int main() {
    create_data_type();
    return 0;
}