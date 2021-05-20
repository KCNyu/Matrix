#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
using namespace std;


class Matrix
{
private:
    int num_rows;
    int num_cols;
    double *M;

public:
    Matrix(int n,int m);
    // размера n на m из 0.0
    Matrix(double);
    // 1 на 1 с этим элементом
    Matrix(double*,int m);
    // матрица-строка из массива длины m
    Matrix(int n,double*);
    // матрица-столбец из массива длины n
    Matrix(char*);
    // из строкового представления
    // "{{1, 0, 0}, {0, 1, 0.5}}" обозначает матрицу 2 на 3
    ~Matrix();
    // Освободить память
    void Init(int,int);
    // инициализировать память
    void swaps(int i,int j);
    // Поменять местами строку i и строку j
    int rows() const;
    // число строк
    int columns() const;
    // число столбцов
    double get(int i,int j) const;
    // возвращать значение элементу [i][j].
    void set(int i,int j,double val);
    // присвоить значение элементу [i][j].
    double determinant();
    // определитель
    Matrix solve();
    // решить любым способом неоднородную систему из n линейных
    // алгебраических уравнений с n неизвестными, представленную матрицей размера n на (n+1).
    // Вернуть решение в виде матрицы 1 на n.
    // Выбросить исключение в случае неразрешимости системы (опять же, с учетом EPS)
    // обязательно запишите какой-нибудь тест в таком виде: x = (A|b).solve(); if( A*x != b ) { error( "solve" ); }
    Matrix inverse();
	// обратная матрица
    const static double EPS;
    // погрешность
    static Matrix identity(int n);
    // возвращает единичную матрицу размера n
    static Matrix diagonal(double* vals, int n);
    // возвращает диагональную матрицу размера n с заданными элементами по главной диагонали
    class Row{
    public:
        int cols;
        double *r;
        Row(int row, int cols, double *p);
        double& operator[](int i);
    };
    // Эффективная реализация индексирования – обеспечение возможности присваивания m[i][j] = вещественное_значение
    Matrix(Row row);
    // матрица-строка из массива строк
    Row operator[](int i);
    // i-я строка в виде новой матрицы, если такая строка есть –1-й приоритет
    // j-й столбец в виде новой матрицы, если такой столбец есть – 2-й приоритет, – иначе ошибка
    Matrix operator-();
    // -matrix унарный минус, применить ко всем элементам
    Matrix operator*(const int scalar);
    // matrix * scalar
    Matrix& operator*=(const int scalar);
    // matrix*=scalar – умножение матрицы на скаляр
    Matrix& operator*=(const Matrix&);
    // matrix *= matrix
    Matrix& operator+=(const Matrix&);
    // matrix += matrix
    Matrix& operator-=(const Matrix&);
    // matrix -= matrix
    friend ostream& operator<<(ostream&,const Matrix&);
    // перегрузка операции << – вывод матрицы, в привычном двумерном виде
    friend Matrix operator+(const Matrix&,const Matrix&);
    // matrix + matrix
    friend Matrix operator-(const Matrix&,const Matrix&);
    // matrix - matrix
    friend Matrix operator*(const Matrix&,const Matrix&);
    // matrix * matrix
    friend bool operator==(const Matrix&,const Matrix&);
    // точность сравнения задана статической константой matrix::EPS
    friend bool operator!=(const Matrix&,const Matrix&);
    // matrix != matrix
    friend Matrix operator|(const Matrix&,const Matrix&);
    // конкатенировать (приписать) матрицы вертикально (вторую справа от первой)
    friend Matrix operator/(const Matrix&,const Matrix&);
    // конкатенировать (приписать) матрицы горизонтально (вторую под первой)
};

#endif /* MATRIX_H */
