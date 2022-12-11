#pragma once
#include <iostream>
#include <vector>

template<typename T>
class BinImage {
private:
    std::vector<T> _matrix;
    int _height, _width;
public:
    BinImage(int height, int width) : _height(height), _width(width) {
        _matrix.resize(height * width);
        std::fill_n(begin(), height * width, 0);
    }

    BinImage(const BinImage& image) = default;
    ~BinImage() = default;

    int get_height() const { return _height; }
    int get_width() const { return _width; }

    auto begin() { return _matrix.begin(); }
    auto end() { return _matrix.end(); }

    static void rprint_standart(const BinImage<T>& image, int x = 0, int y = 0) {
        if (x < image._height) {
            if (y < image._width) {
                if (image._matrix[x*image._width +y] == 1) { std::cout << "1"; }
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

        T val1;

        for (auto& i : _matrix)
            for (auto& j : i)
                if (_matrix[i * _width + j] != 0) { val1 = _matrix[i * _width + j]; break; }

        for (auto& i : _matrix) {
            for (auto& j : i) {
                if (_matrix[i * _width + j] == 0) { res._matrix[i * _width + j] = val1; }
                else { res._matrix[i * _width + j] = 0; }
                
            }
        } return res;
    }

    BinImage<T> operator+(const BinImage<T>& image) {
        if (image._height != _height || image._width != _width) throw std::out_of_range("the main parameters of the image are not equal!");
        BinImage<T> new_image(_height, _width);
        for (auto& i : new_image._matrix) {
            for (auto& j : i) {
                new_image._matrix[i * _width + j] = _matrix[i * _width + j] + image._matrix[i * _width + j];
            }
        } return new_image;
    }
    BinImage<T> operator*(const BinImage<T>& image) {
        if (image._height != _height || image._width != _width) throw std::out_of_range("the main parameters of the image are not equal!");
        BinImage<T> new_image(_height, _width);
        for (auto& i : new_image._matrix) {
            for (auto& j : i) {
                new_image._matrix[i * _width + j] = _matrix[i * _width + j] * image._matrix[i * _width + j];
            }
        } return new_image;
    }

    BinImage<T> operator+(T value) {
        BinImage<T> new_image(_height, _width);

        for (auto& i : new_image._matrix) {
            for (auto& j : i) {
                new_image._matrix[i * _width + j] = value + _matrix[i * _width + j];
            }
        }
        return new_image;
    }
    BinImage<T> operator*(T value) {
        BinImage<T> new_image(_height, _width);
        for (auto& i : new_image._matrix) {
            for (auto& j : i) {
                new_image._matrix[i * _width + j] = value * _matrix[i * _width + j];
            }    
        }
        return new_image;
    }

    BinImage<T>& operator=(const BinImage<T>& image) = default;

    double fill_rate() const {
        if (_height == 0 || _width == 0) throw std::out_of_range("error! height or width = 0!");
        int count = 0, size = _height * _width;
        for (auto& i : _matrix) {
            for (auto& j : i) {
                if (_matrix[i * _width + j])
                    ++count;
            }
        } return (double)count / (double)size;
    }

    friend std::ostream& operator<<(std::ostream & os, const BinImage<T>& image) {
        if (image._height == 0 || image._width == 0 || image._height < 0 || image._width < 0) throw std::out_of_range("invalid height or width");
        for (auto& i : image._matrix) {
            for (auto& j : i) {
                os << image._matrix[i * image._width + j] << " ";
            }
            os << std::endl;
        } return os;
    }

    T operator()(int x, int y) const {
        if (x < 0 || x >= _height || y < 0 || y >= _width) throw std::out_of_range("error!");
        return _matrix[x * _width + y];
    }

    T& operator()(int x, int y) {
        if (x < 0 || x >= _height || y < 0 || y >= _width) throw std::out_of_range("error!");
        return _matrix[x * _width + y];
    }
    static void rdraw_rectangle(BinImage<T> image, int x_1, int y_1, int x_2, int y_2, int i = 0, int j = 0, T value = 1) {
        if (i <= x_2 && i < image._height) {
            if (j <= y_2 && j < image._width) {
                image._matrix[i * image._width + j] = value;
                rdraw_rectangle(image, x_1, y_1, x_2, y_2, i, ++j, value);
            }
            else {
                rdraw_rectangle(image, x_1, y_1, x_2, y_2, ++i, y_1, value);
            }
        }
    }
};