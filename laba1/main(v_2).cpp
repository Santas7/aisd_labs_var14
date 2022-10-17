// л/р номер 1 вариант 6 (2)
// Панюшкин Андрей Михайлович


#include <iostream>
#include <Windows.h>


class BinImage {
private:
    bool** _matrix;
    size_t _height, _width;
public:

    // получение значения высоты избражения
    size_t get_height_value() const { return _height; }

    // получение значения ширины избражения
    size_t get_width_value() const { return _width; }

    // изменение значения высоты избражения
    void set_height_value(size_t height) { _height = height; }

    // изменение значения ширины избражения
    void set_width_value(size_t width) { _width = width; }

    // выделение динамической памяти под матрицу Height X Width
    void new_memory() {
        _matrix = new bool* [_height];
        for (int i = 0; i < _height; ++i) {
            _matrix[i] = new bool[_width];
        }
    }

    // конструктор по-умолчанию
    BinImage(size_t height, size_t width) : _height(height), _width(width)
    {
        new_memory();
    }

    // изменить значение пикселя с координатами (x, y)
    void set_pixel_value(size_t x, size_t y, bool value) {
        try {
            if (x < 0 || x > _height || y < 0 || y > _width) throw std::out_of_range("Invalid x or y!");
            _matrix[x][y] = value;
        }
        catch (const std::string& msg_error) {
            std::cout << msg_error << "\n";
        }
    }

    // получение значения пикселя с координатами (x, y)
    bool get_pixel_value(size_t x, size_t y) {
        try {
            if (x < 0 || x > _height || y < 0 || y > _width) throw std::out_of_range("Invalid x or y!");
            return _matrix[x][y];
        }
        catch (const std::string& msg_error) {
            std::cout << msg_error << "\n";
        }
    }

    // отрисовка изображения в консоль
    void print_image() {
        try {
            for (int i = 0; i < _height; i++) {
                for (int j = 0; j < _width; j++) {
                    if (_matrix[i][j] == true) {
                        std::cout << "1";
                    }
                    else {
                        std::cout << "0";
                    }
                }
                std::cout << std::endl;
            }
        }
        catch (const std::string& msg_error) {
            std::cout << msg_error << "\n";
        }
    }

    // operator+
    BinImage operator+(const BinImage& image) {
        try {
            if (image._height != _height || image._width != _width) throw std::out_of_range("Error! height1 != height2 or width1 != width2!");
            BinImage new_image(_height, _width);
            for (int i = 0; i < _height; ++i) {
                for (int j = 0; j < _width; ++j) {
                    new_image.set_pixel_value(i, j, _matrix[i][j] || image._matrix[i][j]);
                }
            }
            return new_image;
        }
        catch (const std::string& msg_error) {
            std::cout << msg_error << "\n";
        }
        return *this;
    }

    // operator*
    BinImage operator*(const BinImage& image) {
        try {
            if (image._height != _height || image._width != _width) throw std::out_of_range("Error! height1 != height2 or width1 != width2!");
            BinImage new_image(_height, _width);
            for (int i = 0; i < _height; ++i) {
                for (int j = 0; j < _width; ++j) {
                    new_image.set_pixel_value(i, j, _matrix[i][j] && image._matrix[i][j]);
                }
            }
            return new_image;
        }
        catch (const std::string& msg_error) {
            std::cout << msg_error << "\n";
        }
        return *this;
    }

    // комутативность operator+
    friend BinImage operator+(const BinImage& image_1, const BinImage& image_2) {
        try {
            if (image_1._height != image_2._height || image_1._width != image_2._width) throw std::out_of_range("Error! height1 != height2 or width1 != width2!");
            BinImage new_image(image_1._height, image_2._width);
            for (int i = 0; i < image_1._height; ++i) {
                for (int j = 0; j < image_1._width; ++j) {
                    new_image.set_pixel_value(i, j, image_1._matrix[i][j] || image_2._matrix[i][j]);
                }
            }
            return new_image;
        }
        catch (const std::string& msg_error) {
            std::cout << msg_error << "\n";
        }
        return image_1;
    }

    // комутативность operator*
    friend BinImage operator*(const BinImage& image_1, const BinImage& image_2) {
        try {
            if (image_1._height != image_2._height || image_1._width != image_2._width) throw std::out_of_range("Error! height1 != height2 or width1 != width2!");
            BinImage new_image(image_1._height, image_2._width);
            for (int i = 0; i < image_1._height; ++i) {
                for (int j = 0; j < image_1._width; ++j) {
                    new_image.set_pixel_value(i, j, image_1._matrix[i][j] && image_2._matrix[i][j]);
                }
            }
            return new_image;
        }
        catch (const std::string& msg_error) {
            std::cout << msg_error << "\n";
        }
        return image_1;
    }

    // operator=
    BinImage& operator=(const BinImage& image) {
        try {
            if (this == &image) throw std::out_of_range("Error! Object1 == Object2!");
            else {
                for (int i = 0; i < _height; ++i) {
                    delete[] _matrix[i];
                }
                delete[] _matrix;
                new_memory();
                _height = image._height;
                _width = image._width;
            }
            return *this;
        }
        catch (const std::string& msg_error) {
            std::cout << msg_error << "\n";
        }
    }

    // инвертирование значений
    BinImage operator!() {
        try {
            BinImage new_image(_height, _width);
            for (int i = 0; i < _height; ++i) {
                for (int j = 0; j < _width; ++j) {
                    new_image.set_pixel_value(i, j, !_matrix[i][j]);
                }
            }
            return new_image;
        }
        catch (const std::string& msg_error) {
            std::cout << msg_error << "\n";
            return { 0, 0 };
        }
    }

    // отрисовка прямоугольника
    void draw_rectangle(size_t x_1, size_t y_1, size_t x_2, size_t y_2) { // (x1, y1) - координата верхней левой точки и (x2, y2) - координата нижней правой точки
        try {
            for (int i = x_1; i <= x_2; ++i) {
                for (int j = y_1; j <= y_2; ++j) {
                    if ((j > y_1 && j < y_2) && (i > x_1 && i < x_2)) _matrix[i][j] = false;
                    else _matrix[i][j] = true; 
                }
            }
        }
        catch (const std::string& msg_error) {
            std::cout << msg_error << "\n";
        }
    }

    // коэфициент заполняемости изображения
    double fill_rate() {
        try {
            if (_height == 0 || _width == 0) throw std::out_of_range("Error! Height = 0 or Width = 0!");
            size_t count = 0;
            for (int i = 0; i < _height; i++) {
                for (int j = 0; j < _width; j++) {
                    if (_matrix[i][j] == true) ++count;
                }
            } return (double)(count / (_height * _width));
        }
        catch (const std::string& msg_error) {
            std::cout << msg_error << "\n";
        }
        return 0;
    }

    // диструктор
    ~BinImage() {
        delete[] _matrix;
    }
};

int main()
{
    // SetConsoleOutputCP(CP_UTF8);
    BinImage a(100, 100), b(100, 100);

    a.draw_rectangle(1, 1, 20, 20);
    b.draw_rectangle(10, 10, 20, 30);
    
    a.print_image();
    b.print_image();
    //BinImage c = a + b;
   // c.print_image();
    return 0;
}
