#include <iostream>


class BinImage {
private:
    bool** _matrix;
    int _height, _width;
public:
    BinImage(int height, int width); // ����������� � ����������� 
    BinImage(const BinImage& image); // ����������� ����������� 
    ~BinImage(); // ����������

    int get_height() const;  
    int get_width() const; 

    void set_pixel_value(int x, int y, bool value); // ��������� �������� ������� �� (x, y) 
    bool get_pixel_value(int x, int y) const;  // ��������� �������� ������� �� (x, y) 

    void print_standart() const; // ������� ��������  
    static void rprint_standart(const BinImage& image, int x = 0, int y = 0); // ����������� ����� �����������

    BinImage operator!(); // �������������� !

    void clean_the_image(); // ������� �����������

    BinImage operator+(const BinImage& image); // ��������+ 
    BinImage operator*(const BinImage& image); // ��������* 

    // friend BinImage operator+(const BinImage& image_1, const BinImage& image_2); // ������������� ��������+ 
    // friend BinImage operator*(const BinImage& image_1, const BinImage& image_2); // ������������� ��������* 
    BinImage operator+(bool value); // �������� + �� ������� ��������
    BinImage operator*(bool value); // �������� * �� ������� ��������

    BinImage& operator=(const BinImage& image); // �������� = 

    double fill_rate() const; // ���������� ������������� �����������

    friend std::ostream& operator<<(std::ostream& os, const BinImage& image); // �������� <<
    friend std::istream& operator>>(std::istream& os, BinImage& image); // �������� >> 

    bool operator()(int x, int y) const; // �������� () const ��� ��������� �������� �� (x, y)
    bool& operator()(int x, int y); // �������� () ��� ��������� �������� �� (x, y)

    void draw_rectangle(int x_1, int y_1, int x_2, int y_2) const; // ��������� �������������� 
    void rdraw_rectangle(int x_1, int y_1, int x_2, int y_2, int i = 0, int j = 0) const; // ����������� ��������� �������������� 
};

