#pragma once
#include <iostream>
#include <vector>

template<typename T>
class Image {
private:
    std::vector<T> _matrix;
    int _height, _width;
public:
    Image(int height, int width) : _height(height), _width(width) {
        _matrix.resize(height * width);
        std::fill_n(begin(), height * width, 0);
    }
    Image(const Image& image) = default;
    ~Image() = default;

    int get_height() const { return _height; }
    int get_width() const { return _width; }

    auto begin() { return _matrix.begin(); }
    auto end() { return _matrix.end(); }

    Image<T> operator!() {
        Image<T> res(_height, _width);

        T val1;

        auto iterator_1 = _matrix.begin();
        auto iterator_2 = res._matrix.begin();

        for (int i = 0; i < _height; ++i)
            for (int j = 0; j < _width; ++j, ++iterator_1)
                if (*iterator_1 != 0) { val1 = *iterator_1; break; }

        iterator_1 = _matrix.begin();

        for (int i = 0; i < _height; ++i) {
            for (int j = 0; j < _width; ++j, ++iterator_1, ++iterator_2) {
                if (*iterator_1 == 0) { *iterator_2 = val1; }
                else { *iterator_2 = 0; }
                
            }
        } return res;
    }

    Image<T> operator+(const Image<T>& image) {
        if (image._height != _height || image._width != _width) throw std::out_of_range("the main parameters of the image are not equal!");
        Image<T> new_image(_height, _width);
        auto iterator_1 = _matrix.begin();
        auto iterator_2 = image._matrix.begin();
        auto iterator_3 = new_image._matrix.begin();
        for (int i = 0; i < new_image._height; ++i) {
            for (int j = 0; j < new_image._width; ++j, ++iterator_1, ++iterator_2, ++iterator_3) {
                *iterator_3 = *iterator_1 + *iterator_2;
            }
        } return new_image;
    }
    Image<T> operator*(const Image<T>& image) {
        if (image._height != _height || image._width != _width) throw std::out_of_range("the main parameters of the image are not equal!");
        Image<T> new_image(_height, _width);
        auto iterator_1 = _matrix.begin();
        auto iterator_2 = image._matrix.begin();
        auto iterator_3 = new_image._matrix.begin();
        for (int i = 0; i < new_image._height; ++i) {
            for (int j = 0; j < new_image._width; ++j, ++iterator_1, ++iterator_2, ++iterator_3) {
                *iterator_3 = *iterator_1 * *iterator_2;
            }
        } return new_image;
    }

    Image<T> operator+(T value) {
        Image<T> new_image(_height, _width);
        auto iterator_1 = _matrix.begin();
        auto iterator_2 = new_image._matrix.begin();
        for (int i = 0; i < new_image._height; ++i) {
            for (int j = 0; j < new_image._width; ++j, ++iterator_1, ++iterator_2) {
                *iterator_2 = *iterator_1 + value;
            }
        } return new_image;
    }

    Image<T> operator*(T value) {
        Image<T> new_image(_height, _width);
        auto iterator_1 = _matrix.begin();
        auto iterator_2 = new_image._matrix.begin();
        for (int i = 0; i < new_image._height; ++i) {
            for (int j = 0; j < new_image._width; ++j, ++iterator_1, ++iterator_2) {
                *iterator_2 = *iterator_1 * value;
            }
        } return new_image;
    }

    Image<T>& operator=(const Image<T>& image) = default;

    double fill_rate() const {
        if (_height == 0 || _width == 0) throw std::out_of_range("error! height or width = 0!");
        int count = 0, size = _height * _width;
        auto iterator = _matrix.begin();
        for (int i = 0; i < _height; ++i) {
            for (int j = 0; j < _width; ++j, ++iterator) {
                if (*iterator)
                    ++count;
            }
        } return (double)count / (double)size;
    }

    friend std::ostream& operator<<(std::ostream & os, const Image<T>& image) {
        if (image._height == 0 || image._width == 0 || image._height < 0 || image._width < 0) throw std::out_of_range("invalid height or width");
        auto iterator = image._matrix.begin();
        for (int i = 0; i < image._height; ++i) {
            for (int j = 0; j < image._width; ++j, ++iterator) {
                os << *iterator << " ";
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

    void rdraw_rectangle(int x_1, int y_1, int x_2, int y_2, int i = 0, int j = 0, T value = 1) {
        if (i <= x_2 && i < _height) {
            if (j <= y_2 && j < _width) {
                _matrix[i * _width + j] = value;
                rdraw_rectangle(x_1, y_1, x_2, y_2, i, ++j, value);
            }
            else {
                rdraw_rectangle(x_1, y_1, x_2, y_2, ++i, y_1, value);
            }
        }
    }
};
