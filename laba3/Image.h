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

    /*static void rprint_standart(const Image<T>& image, int x = 0, int y = 0) {
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
    }*/

    Image<T> operator!() const{
        Image<T> res(_height, _width);

        T val1;

        auto iterator_1 = _matrix.begin();
        auto iterator_2 = res._matrix.begin();

        for (int i = 0; i < _height * _width; ++i, ++iterator_1) {
            if (*iterator_1 != 0) { val1 = *iterator_1; break; }
        }

        iterator_1 = _matrix.begin();

        for (int i = 0; i < _height * _width; ++i, ++iterator_1, ++iterator_2) {
            if (*iterator_1 == 0) { *iterator_2 = val1; }
            else { *iterator_2 = 0; }
        } return res;
    }

    Image<T> operator+(const Image<T>& image) const{
        if (image._height != _height || image._width != _width) throw std::out_of_range("the main parameters of the image are not equal!");
        Image<T> new_image(_height, _width);
        // auto iterator_1 = _matrix.begin();
        auto iterator_2 = image._matrix.begin();
        auto iterator_3 = new_image._matrix.begin();
        for (auto iterator_1 = _matrix.begin(); iterator_1 != _matrix.end(); ++iterator_1, ++iterator_2, ++iterator_3) {
            *iterator_3 = *iterator_1 + *iterator_2;
        } return new_image;
    }

    Image<T> operator*(const Image<T>& image) const{
        if (image._height != _height || image._width != _width) throw std::out_of_range("the main parameters of the image are not equal!");
        Image<T> new_image(_height, _width);
        // auto iterator_1 = _matrix.begin();
        auto iterator_2 = image._matrix.begin();
        auto iterator_3 = new_image._matrix.begin();
        for (auto iterator_1 = _matrix.begin(); iterator_1 != _matrix.end(); ++iterator_1, ++iterator_2, ++iterator_3) {
            *iterator_3 = *iterator_1 * *iterator_2;
        } return new_image;
    }

    Image<T> operator+(T value) const{
        Image<T> new_image(_height, _width);
        // auto iterator_1 = _matrix.begin();
        auto iterator_2 = new_image._matrix.begin();
        for (auto iterator_1 = _matrix.begin(); iterator_1 != _matrix.end(); ++iterator_1, ++iterator_2) {
            *iterator_2 = *iterator_1 + value;
        } return new_image;
    }

    Image<T> operator*(T value) const{
        Image<T> new_image(_height, _width);
        // auto iterator_1 = _matrix.begin();
        auto iterator_2 = new_image._matrix.begin();
        for (auto iterator_1 = _matrix.begin(); iterator_1 != _matrix.end(); ++iterator_1, ++iterator_2) {
            *iterator_2 = *iterator_1 * value;
        } return new_image;
    }

    Image<T>& operator=(const Image<T>& image) = default;

    double fill_rate() const {
        if (_height == 0 || _width == 0) throw std::out_of_range("error! height or width = 0!");
        int count = 0, size = _height * _width;
        // auto iterator = _matrix.begin();
        for (auto iterator = _matrix.begin(); iterator != _matrix.end(); ++iterator) {
            if (*iterator)
                ++count;
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

    auto operator()(int x, int y) ->  typename std::vector<T>::reference {
        if (x < 0 || x >= _height || y < 0 || y >= _width) throw std::out_of_range("error!");
        return _matrix[x * _width + y];
    }

    static void rdraw_rectangle(Image<T>& image, int x_1, int y_1, int x_2, int y_2, int i = 0, int j = 0, T value = 1) {
        if (i <= x_2 && i < image._height) {
            if (j <= y_2 && j < image._width) {
                image(i, j) = value;
                rdraw_rectangle(image, x_1, y_1, x_2, y_2, i, ++j, value);
            }
            else {
                rdraw_rectangle(image, x_1, y_1, x_2, y_2, ++i, y_1, value);
            }
        }

    }
};
