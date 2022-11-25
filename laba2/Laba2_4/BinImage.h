#pragma once
#include <iostream>

template<typename T>
class BinImage {
private:
    T** _matrix;
    int _height, _width;
public:
    BinImage(int height, int width) : _height(height), _width(width) {
        _matrix = new T* [height];
        for (int i = 0; i < height; ++i) {
            _matrix[i] = new T[width];
        }
        for (int i = 0; i < height; ++i) {
            std::fill_n(_matrix[i], width, 0);
        }
    }
    BinImage(const BinImage& image) : BinImage(image._height, image._width) {
        for (int i = 0; i < _height; ++i) {
            for (int j = 0; j < _width; ++j) {
                _matrix[i][j] = image._matrix[i][j];
            }
        }
    }
    ~BinImage() {
        for (int i = 0; i < _height; ++i) {
            delete[] _matrix[i];
        } delete[] _matrix;
    }

    int get_height() const { return _height; }
    int get_width() const { return _width; }

    T get_pixel_value(int x, int y) const {
        if (x < 0 || x >= _height || y < 0 || y >= _width) throw std::out_of_range("error!");
        return _matrix[x][y];
    }

    // void print_standart() const; 
    static void rprint_standart(const BinImage<T>&image, int x = 0, int y = 0) {
        if (x < image._height) {
            if (y < image._width) {
                if (image._matrix[x][y] == 1) { std::cout << "1"; }
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

    BinImage<T> operator!() {
        BinImage<T> res(_height, _width);
        for (int i = 0; i < _height; ++i) {
            for (int j = 0; j < _width; ++j) {
                res._matrix[i][j] = !_matrix[i][j];
            }
        }
        return res;
    }

    BinImage<T> operator+(const BinImage<T>&image) {
        if (image._height != _height || image._width != _width) throw std::out_of_range("the main parameters of the image are not equal!");
        BinImage<T> new_image(_height, _width);
        for (int i = 0; i < _height; ++i) {
            for (int j = 0; j < _width; ++j) {
                new_image._matrix[i][j] = _matrix[i][j] || image._matrix[i][j];
            }
        } return new_image;
    }
    BinImage<T> operator*(const BinImage<T>&image) {
        if (image._height != _height || image._width != _width) throw std::out_of_range("the main parameters of the image are not equal!");
        BinImage<T> new_image(_height, _width);
        for (int i = 0; i < _height; ++i) {
            for (int j = 0; j < _width; ++j) {
                new_image._matrix[i][j] = _matrix[i][j] && image._matrix[i][j];
            }
        } return new_image;
    }

    BinImage<T> operator+(T value) {
        BinImage<T> new_image(_height, _width);

        for (int i = 0; i < _height; ++i)
            for (int j = 0; j < _width; ++j)
                new_image._matrix[i][j] = value || _matrix[i][j];

        return new_image;
    }
    BinImage<T> operator*(T value) {
        BinImage<T> new_image(_height, _width);

        for (int i = 0; i < _height; ++i)
            for (int j = 0; j < _width; ++j)
                new_image._matrix[i][j] = value && _matrix[i][j];

        return new_image;
    }

    BinImage<T>& operator=(const BinImage<T>& image) {
        if (this != &image) { 
            for (int i = 0; i < _height; ++i) {
                delete[] _matrix[i];
            }
            delete[] _matrix;

            _matrix = new T* [image._height];
            for (int i = 0; i < image._height; ++i) {
                _matrix[i] = new T[image._width];
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

    double fill_rate() const {
        if (_height == 0 || _width == 0) throw std::out_of_range("error! height or width = 0!");
        int count = 0, size = _height * _width;
        for (int i = 0; i < _height; ++i) {
            for (int j = 0; j < _width; ++j) {
                if (_matrix[i][j] == 1)
                    ++count;
            }
        } return (double)count / (double)size;
    }

    friend std::ostream& operator<<(std::ostream & os, const BinImage<T>&image) {
        if (image._height == 0 || image._width == 0 || image._height < 0 || image._width < 0) throw std::out_of_range("invalid height or width");
        for (int i = 0; i < image._height; ++i) {
            for (int j = 0; j < image._width; ++j) {
                if (image._matrix[i][j] == 1) { os << "1"; }
                else os << ".";
            }
            os << std::endl;
        } return os;
    }

    T operator()(int x, int y) const {
        if (x < 0 || x >= _height || y < 0 || y >= _width) throw std::out_of_range("error!");
        return _matrix[x][y];
    }

   T& operator()(int x, int y) {
        if (x < 0 || x >= _height || y < 0 || y >= _width) throw std::out_of_range("error!");
        return _matrix[x][y];
    }

    // void draw_rectangle(int x_1, int y_1, int x_2, int y_2) const;
    void rdraw_rectangle(int x_1, int y_1, int x_2, int y_2, int i = 0, int j = 0) const {
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
};

