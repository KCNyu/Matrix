/*================================================================
* Filename:main.cpp
* Author: KCN_yu
* Createtime:Sat 12 Dec 2020 01:22:47 AM CST
================================================================*/

#include "Matrix.h"

int main(int argc, char *argv[])
{
    Matrix m1(2,5);
    cout << m1 << endl;
    Matrix m2 = Matrix::identity(10);
    cout << m2 << endl;


    double vals[] = {1.01,1.02,1.03};
    Matrix m4 = Matrix::diagonal(vals,3);
    cout << m4 << endl;

    char s[] = "{{1.234, 1.567, 1.6789, 1.088},{2, 3, 1, 2.612},{3, 2, 1, 4},{4.08, 1, 1.92, 3}}";
    Matrix m3(s);
    cout << m3 << endl;
    Matrix m5 = m3[0];
    cout << m5 << endl;
    m3[0][0] = 100;
    cout << m3 << endl;

    cout << m5 << endl;
    // Значение первого элемента не изменится, потому что m5 - новая матрица и не имеет ничего общего с m3
    Matrix m6 = -m3;
    cout << m6 << endl;

    Matrix m7 = m3*2;
    cout << m7 << endl;

    m7 *= 3;
    cout << m7 << endl;

    Matrix m8 = m6+m7;
    cout << m8 << endl;

    m8 += m6;
    cout << m8 << endl;

    m8 -= m6;
    cout << m8 << endl;

    Matrix m9 = m8 - m3*5;
    cout << m9 << endl;

    m6 *= m3;
    cout << m6 << endl;

    char s1[] = "{{1,2,3},{4,5,6}}";
    Matrix m10(s1);
    cout << m10 << endl;

    char s2[] = "{{1,2},{2,3},{3,4}}";
    Matrix m11(s2);
    cout << m11 << endl;
    m10 *= m11;
    cout << m10 << endl;
    try{
        Matrix m12 = m10 * m11;
        cout << m12 << endl;
    }
    catch(const char* s){
        cout << s << endl;
    }
    char s3[] = "{{0, 0, 2},{2, -1, 3},{3, 1, 2}}";
    Matrix m13(s3);
    cout << m13 << endl;
    char s4[] = "{{-4},{7},{18}}";
    Matrix m14(s4);
    cout << m14 << endl;
    Matrix x = (m13|m14).solve();
    cout << x << endl;
    Matrix f = m13*x;
    cout << f << endl;
    if(m13*x == m14) cout << "Right!" << endl;
    // обязательно запишите какой-нибудь тест в таком виде: x = (A|b).solve(); if( A*x != b ) { error( "solve" ); }
    Matrix m15 = m13.inverse();
    cout << m15 << endl;
    cout << (m13*m15) << endl;
    return 0;
}

