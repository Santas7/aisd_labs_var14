#include <iostream>


class BinImage {
private:
    bool** _matrix;
    int _height, _width;
public:
    BinImage(int height, int width); // Конструктор с параметрами 
    BinImage(const BinImage& image); // Конструктор копирования 
    ~BinImage(); // Деструктор

    int get_height() const;  
    int get_width() const; 

    void set_pixel_value(int x, int y, bool value); // изменение значения пикселя по (x, y) 
    bool get_pixel_value(int x, int y) const;  // получение значения пикселя по (x, y) 

    void print_standart() const; // вывести картинку  
    static void rprint_standart(const BinImage& image, int x = 0, int y = 0); // рекурсивный вывод изображения

    BinImage operator!(); // инвертирование !

    void clean_the_image(); // очистка изображения

    BinImage operator+(const BinImage& image); // оператор+ 
    BinImage operator*(const BinImage& image); // оператор* 

    // friend BinImage operator+(const BinImage& image_1, const BinImage& image_2); // коммутативный оператор+ 
    // friend BinImage operator*(const BinImage& image_1, const BinImage& image_2); // коммутативный оператор* 
    BinImage operator+(bool value); // оператор + на булевое значение
    BinImage operator*(bool value); // оператор * на булевое значение

    BinImage& operator=(const BinImage& image); // оператор = 

    double fill_rate() const; // коэфициент заполняемости изображения

    friend std::ostream& operator<<(std::ostream& os, const BinImage& image); // оператор <<
    friend std::istream& operator>>(std::istream& os, BinImage& image); // оператор >> 

    bool operator()(int x, int y) const; // оператор () const для получения значения по (x, y)
    bool& operator()(int x, int y); // оператор () для получения значения по (x, y)

    void draw_rectangle(int x_1, int y_1, int x_2, int y_2) const; // отрисовка прямоугольника 
    void rdraw_rectangle(int x_1, int y_1, int x_2, int y_2, int i = 0, int j = 0) const; // рекурсивная отрисовка прямоугольника 
};

