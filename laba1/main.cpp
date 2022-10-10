// variant 6(2)
// created by Panyshkin Andrey 
// group 6213

#include <iostream>
#include "Graphics.h"
#include <conio.h>
#include <windows.h>

using namespace std;

struct coordinates {
    int x, y;
};

class BinImage {
private:
    size_t _height, _width;
public:

    void set_height(size_t new_height) { _height = new_height; }
    void set_width(size_t new_width) { _width = new_width; }

    size_t get_height() const { return _height; }
    size_t get_width() const { return _width; }

    BinImage(size_t height = 200, size_t width = 200) : _height(height), _width(width)
    { 
    }

};

class Point {
private:
    coordinates* _data;
    size_t _size;
    size_t _capacity;
public:

    void clear_image(Graphics& g, size_t height, size_t width) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                g.DrawSquare(i, j, 1, { 255, 255, 255 });
            }
        }
    }

    void draw(Graphics& g, int index) {
        for (int i = _data[index].x; i <= _data[index + 1].x; ++i) {
            for (int j = _data[index].y; j <= _data[index + 1].y; ++j) {
                if ((j > _data[index].y && j < _data[index + 1].y) && (i > _data[index].x && i < _data[index + 1].x)) {
                    g.DrawSquare(i, j, 1, { 255, 255, 255 });
                    cout << "0" << endl;
                }
                else {
                    g.DrawSquare(i, j, 1, { 0, 0, 0 });
                    cout << "1" << endl;
                }
            }
        }
    }

    Point operator()(size_t x, size_t y) {
        Point* obj = new Point();
        obj->set_data(x, y);
        return *obj;
    }

    Point& operator+(const Point& obj) {
        return *this;
    }

    Point& operator*(const Point& obj) {
        return *this;
    }

    bool operator+() {
        // ...
    }

    bool operator*() {
        // ...
    }

    Point& operator!() {

    }

    void inversion(Graphics& g, size_t height, size_t width) {
        clear_image(g, height, width);
        for (int i = 0; i < _size; i += 2) {
            size_t tmp = _data[i + 1].x;
            _data[i + 1].x = _data[i + 1].y; 
            _data[i + 1].y = tmp;
            draw(g, i);
        } 
    }

    size_t fill_rate(size_t S) {
        //     x2y2 + ... + xnyn = N
        // K = ---------------------- * 100%
        //      height * width = S
        if (_size == 0) throw "Error! size == 0!";
        size_t K, N = 0;
        for (int i = 0; i < _size; i += 2) {
            N += (_data[i + 1].x * _data[i + 1].y);
        }
        K = (N * 100) / S;
        return K; 
    }

    void set_data(size_t x, size_t y) {
        if (_size == _capacity) {
            _capacity += 10;
            auto tmp = new coordinates[_capacity];
            move(_data, _data + _size, tmp);
            delete[] _data;
            _data = tmp;
            ++_size;
            _data[_size - 1].x = x;
            _data[_size - 1].y = y;
        }
        else {
            ++_size;
            _data[_size - 1].x = x;
            _data[_size - 1].y = y;
        }
    }

    size_t get_x(size_t index) { return _data[index].x; }
    size_t get_y(size_t index) { return _data[index].y; }

    size_t get_size() { return _size; }
    size_t set_size(size_t new_size) { _size = new_size; }

    Point(const Point& src) {
        _size = src._size;
        _capacity = src._capacity;
        _data = new coordinates[_capacity];
        for (int i = 0; i < _size; ++i) {
            _data[i] = src._data[i];
        }
    }

    Point(size_t capacity = 10) : _size(0), _capacity(capacity)
    {
        _data = new coordinates[_capacity];
    }
    ~Point() 
    {
        delete _data;
    }
};

int Menu() {
    int key = _getch();
    if (key == 49 || key == 50 || key == 51 || key == 52 || key == 53 || key == 54 || key == 55 || key == 8)
        return key;
    return 0;
}


int main() {

    int index = 0;
    BinImage picture;
    while (true) {
        int height, width;
        cout << "Set the parameters of the binary image!" << endl;
        cout << "Height: "; cin >> height;
        cout << "Width: "; cin >> width;
        if (height > 0 || width > 0) { 
            picture.set_height(height); 
            picture.set_width(width); 
            break; 
        }
        else {
            cout << "Error!" << endl;
        }
    }

    Graphics g{ picture.get_height(), picture.get_width() };

    system("cls");
    cout << "[1] Add rectangle"
        << endl << "[2] Summa"
        << endl << "[3] Summa_Bool"
        << endl << "[4] Mul"
        << endl << "[5] Mul_Bool"
        << endl << "[6] Invertation (!)"
        << endl << "[7] Fill rate"
        << endl << "[BackSpace] Exit"
        << endl << "-->";

    Point* data = new Point();
    while (true) {
        int commandKey = Menu();
        if (commandKey == 8)
            break;
        switch (commandKey) {
        case '1':
            system("cls");
            int x_1, y_1, x_2, y_2;
            // first 
            cout << "<--First-->" << endl;
            cout << "X: "; cin >> x_1;
            cout << "Y: "; cin >> y_1;
            data->set_data(x_1, y_1);
           // Data* obj = new Data();
           // obj(1, 2)

            // second
            cout << "<--Second-->" << endl;
            cout << "X: "; cin >> x_2;
            cout << "Y: "; cin >> y_2;
            data->set_data(x_2, y_2);

            cout << "(" << data->get_x(index) << "; " << data->get_y(index) << ")" << endl;
            cout << "(" << data->get_x(index+1) << "; " << data->get_y(index+1) << ")" << endl;

            data->draw(g, index);
            index += 2;
            cout << "[0]Back-->";
            break;
        case '6':
            system("cls");
            cout << "...." << endl;
            data->inversion(g, picture.get_height(), picture.get_width());
            cout << "Okey... [100%]" << endl << "[0]Back-->";
            break;
        case '7':
            system("cls");
            cout << "...." << endl;
            try {
                size_t result = data->fill_rate(picture.get_height() * picture.get_width());
                cout << result << endl << "[0]Back-->";
            }
            catch (const char* msg) {
                cout << msg << endl << "[0]Back-->";
            }
            break;
        case 0:
            system("cls");
            cout << "[1] Add rectangle"
                << endl << "[2] Summa"
                << endl << "[3] Summa_Bool"
                << endl << "[4] Mul"
                << endl << "[5] Mul_Bool"
                << endl << "[6] Invertation (!)"
                << endl << "[7] Fill rate"
                << endl << "[BackSpace] Exit"
                << endl << "-->";
            break;
        default:
            system("cls");
            cout << "Error!" << endl;
            break;
        }
        //delete data;
    }
    system("pause");
    return 0;
}
