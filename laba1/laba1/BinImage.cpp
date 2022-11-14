#include "BinImage.h"

/* конструктор с параметрами */
BinImage::BinImage(int height, int width) : _height(height), _width(width) {
    _matrix = new bool* [height];
    for (int i = 0; i < height; ++i) {
        _matrix[i] = new bool[width];
    }
    for (int i = 0; i < height; ++i) {
        std::fill_n(_matrix[i], width, false); // 1 - начальный элемент цикла (for); 2 - до какого индекса будет идти цикл; 3 - значение которое присваивается элементам
    }
}

/* конструктор копирования*/
BinImage::BinImage(const BinImage& image) : BinImage(image._height, image._width) {
    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            _matrix[i][j] = image._matrix[i][j];
        }
    }
}

/* деструктор */
BinImage::~BinImage() {
    for (int i = 0; i < _height; ++i) {
        delete[] _matrix[i];
    } delete[] _matrix;
}

int BinImage::get_height() const { return _height; } // получение значения высоты
int BinImage::get_width() const { return _width; } // получение значения ширины

/* установка значения пикселю с (x, y) */
void BinImage::set_pixel_value(int x, int y, bool value)
{
    if (x < 0 || x >= _height || y < 0 || y >= _width) throw std::out_of_range("error!");
    _matrix[x][y] = value;
}

/* получение значения пикселя с (x, y) */
bool BinImage::get_pixel_value(int x, int y) const {
    if (x < 0 || x >= _height || y < 0 || y >= _width) throw std::out_of_range("error!");
    return _matrix[x][y];
}


BinImage BinImage::operator!() {
    BinImage res(_height, _width);
    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            res.set_pixel_value(i, j, !_matrix[i][j]);
        }
    }
    return res;
}

/* вывод изображения */
void BinImage::print_standart() const {
    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            if (_matrix[i][j] == true) { std::cout << "1"; }
            else { std::cout << "."; }
        }
        std::cout << std::endl;
    }
}

/* рекурсивный вывод изображения */
void BinImage::rprint_standart(const BinImage& image, int x, int y) const {
    if (x < image._height) {
        if (y < image._width) {
            if (image._matrix[x][y] == true) { std::cout << "1"; }
            else { std::cout << "."; }
            rprint_standart(image, x, ++y);
        }
        else {
            std::cout << "\n";
            rprint_standart(image, ++x, 0);
        }
    }
    else {
        return;
    }
} 

/* оператор + */
BinImage BinImage::operator+(const BinImage& image) {
    if (image._height != _height || image._width != _width) throw std::out_of_range("the main parameters of the image are not equal!");
    BinImage new_image(_height, _width);
    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            new_image.set_pixel_value(i, j, _matrix[i][j] || image._matrix[i][j]);
        }
    } return new_image;

}

/* comut_оператор + 
BinImage operator+(const BinImage& image_1, const BinImage& image_2) {
    if (image_1._height != image_2._height || image_1._width != image_2._width) throw std::out_of_range("the main parameters of the image are not equal!");
    BinImage new_image(image_1._height, image_1._width);
    for (int i = 0; i < image_1._height; ++i) {
        for (int j = 0; j < image_2._width; ++j) {
            new_image.set_pixel_value(i, j, image_1._matrix[i][j] || image_2._matrix[i][j]);
        }

    } return new_image;
}*/

/* оператор = */
BinImage& BinImage::operator=(const BinImage& image) {
    if (this != &image) { // если текущий не равен передоваемому то ...
        for (int i = 0; i < _height; ++i) {
            delete[] _matrix[i];
        } 
        delete[] _matrix;

        _matrix = new bool* [image._height];
        for (int i = 0; i < image._height; ++i) {
            _matrix[i] = new bool[image._width];
        }

        for (int i = 0; i < image._height; ++i) {
            for (int j = 0; j < image._width; ++j) {
                _matrix[i][j] = image._matrix[i][j];
            }
        }

        _height = image._height;
        _width = image._width;
    }
    return *this;
}


/* отрисовка прямоугольника */
void BinImage::draw_rectangle(int x_1, int y_1, int x_2, int y_2) const { // (x1, y1) - координата верхней левой точки и (x2, y2) - координата нижней правой точки
    for (int i = x_1; i <= x_2; ++i) {
        for (int j = y_1; j <= y_2; ++j) {
           _matrix[i][j] = 1;
        }
    }
}

/* рекурсивная отрисовка прямоугольника */
void BinImage::rdraw_rectangle(int x_1, int y_1, int x_2, int y_2, int i, int j) {
    // if (x_1 > 0 || y_1 > 0 || x_2 > 0 || y_2 > 0 || x_1 >= _height || y_1 >= _width || x_2 >= _height || y_2 >= _width) throw std::out_of_range("Try again... X > 0 and Y > 0 or X >= HEIGHT or Y >= WIDTH!");
    if (i <= x_2 && i < _height) {
        if (j <= y_2 && j < _width) {
            _matrix[i][j] = 1;
            rdraw_rectangle(x_1, y_1, x_2, y_2, i, ++j);
        }
        else {
            rdraw_rectangle(x_1, y_1, x_2, y_2, ++i, y_1);
        }
    }
}

/* оператор * */
BinImage BinImage::operator*(const BinImage& image) {
    if (image._height != _height || image._width != _width) throw std::out_of_range("the main parameters of the image are not equal!");
    BinImage new_image(_height, _width);
    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            new_image.set_pixel_value(i, j, _matrix[i][j] && image._matrix[i][j]);
        }
    } return new_image;
}


/* оператор * булевое значение */
BinImage BinImage::operator+(bool value) {
    BinImage new_image(_height, _width);

    for (int i = 0; i < _height; ++i)
        for (int j = 0; j < _width; ++j)
            new_image._matrix[i][j] = value || _matrix[i][j];

    return new_image;
}

/* оператор * булевое значение */
BinImage BinImage::operator*(bool value) {
    BinImage new_image(_height, _width);

    for (int i = 0; i < _height; ++i)
        for (int j = 0; j < _width; ++j)
            new_image._matrix[i][j] = value && _matrix[i][j];

    return new_image;
}

/* comut_оператор
BinImage operator*(const BinImage& image_1, const BinImage& image_2) {
    if (image_1._height != image_2._height || image_1._width != image_2._width) throw std::out_of_range("the main parameters of the image are not equal!");
    BinImage new_image(image_1._height, image_1._width);
    for (int i = 0; i < image_1._height; ++i) {
        for (int j = 0; j < image_1._width; ++j) {
            new_image.set_pixel_value(i, j, image_1._matrix[i][j] && image_2._matrix[i][j]);
        }
    } return new_image;
}*/

/* коэф.заполнения */
double BinImage::fill_rate() const{
    if (_height == 0 || _width == 0) throw std::out_of_range("error! height or width = 0!");
    int count = 0, size = _height * _width;
    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            if (_matrix[i][j] == true)
                ++count;
        }
    } return (double)count / (double)size;
}

/* очистка изображения */
void BinImage::clean_the_image() const {
    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            _matrix[i][j] = false;
        }
    }
}


// оператор <<
std::ostream& operator<<(std::ostream& os, const BinImage& image) {
    if (image._height == 0 || image._width == 0 || image._height < 0 || image._width < 0) throw std::out_of_range("invalid height or width");
    for (int i = 0; i < image._height; ++i) {
        for (int j = 0; j < image._width; ++j) {
            if (image._matrix[i][j] == true) { os << "1"; }
            else os << ".";
        } 
        os << std::endl;
    } return os;
}

// оператор >>
std::istream& operator>>(std::istream& os, BinImage& image) {
    if (image._height == 0 || image._width == 0 || image._height < 0 || image._width < 0) throw std::out_of_range("invalid height or width");
    for (int i = 0; i < image._height; ++i) {
        for (int j = 0; j < image._width; ++j) {
            os >> image._matrix[i][j];
        }
    } return os;
}

// константный
bool BinImage::operator()(int x, int y) const {
    if (x < 0 || x >= _height || y < 0 || y >= _width) throw std::out_of_range("error!");
    return _matrix[x][y];
}

bool& BinImage::operator()(int x, int y){
    if (x < 0 || x >= _height || y < 0 || y >= _width) throw std::out_of_range("error!");
    return _matrix[x][y];
}


