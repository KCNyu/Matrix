/*================================================================
* Filename:Matrix.cpp
* Author: KCN_yu
* Createtime:Fri 11 Dec 2020 07:10:49 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <iomanip>
#include <cstring>
#include "Matrix.h"
#include "Mystack.h"

using namespace std;

const double Matrix::EPS = 0.0000000001;

void Matrix::Init(int n, int m){
    num_rows = n;
    num_cols = m;
    M = new double[num_rows*num_cols];
}
void Matrix::set(int i, int j, double val){
    if(i >= num_rows || j >= num_cols) throw "out of index!\n";
    M[i*num_cols+j] = val;
}
void Matrix::swaps(int i, int j){
    if(i >= num_rows || j >= num_rows) throw "out of index!\n";
    for(int k = 0; k < num_cols; k++){
        double t = get(i,k);
        set(i,k,get(j,k));
        set(j,k,t);
    }
}
double Matrix::get(int i, int j) const{
    if(i >= num_rows || j >= num_cols) throw "out of index!\n";
    return M[num_cols*i+j];
}
int Matrix::rows() const{
    return num_rows;
}
int Matrix::columns() const{
    return num_cols;
}
double Matrix::determinant(){
    if(num_rows != num_cols) throw "Not a square matrix!\n";
    Matrix tmp(num_rows,num_cols);
    for(int i = 0; i < num_rows*num_cols; i++) tmp.M[i] = M[i];
    for(int i = 0; i < num_rows-1; i++){
        for(int j = i+1; j < num_rows; j++){
            if(tmp.get(i,i) < EPS && tmp.get(i,i) > -1*EPS){
                for(int m = i+1; m < num_rows; m++){
                    if(tmp.get(m,i) < EPS && tmp.get(m,i) > -1*EPS) continue;
                    else tmp.swaps(i,m);
                }
            }
            double temp = tmp.get(j,i)/tmp.get(i,i);
            for(int k = 0; k < num_cols; k++){
                tmp.set(j,k,tmp.get(j,k)-tmp.get(i,k)*temp);
            }
        }
    }
    double det = 1;
    for(int i = 0; i < num_rows; i++) det *= tmp.get(i,i);
    return det;
}
Matrix::Matrix(int n, int m){
    Init(n,m);
    for(int i = 0; i < num_rows; i++)
        for(int j = 0; j < num_cols; j++)
            set(i,j,0);
}
Matrix::Matrix(double elem){
    Init(1,1);
    set(0,0,elem);
}
Matrix::Matrix(double* row, int m){
    Init(1,m);
    for(int i = 0; i < num_cols; i++) set(0,i,row[i]);
}
Matrix::Matrix(int n, double* col){
    Init(n,1);
    for(int i = 0; i < num_rows; i++) set(i,0,col[i]);
}
Matrix::Matrix(char* s){
    int count = 0;
    int count_pair = 0;
    double* mat = new double[MAX];
    if(s != nullptr){
        Mystack st;
        char num[MAX];
        int j = 0;
        int len = strlen(s);
        if(s[0] != '{' || s[len-1] != '}') throw "Illegal bracket pairing!\n";
        for(int i = 1; i < len-1; i++){
            char tmp = s[i];
            if(!(tmp == '{' || tmp == '}'|| tmp == '.' || tmp == ','|| (tmp >= '0'&& tmp <= '9') || tmp == ' ' || tmp == '-'))
                throw "Illegal identifier!\n";
            if(tmp == '{'){
                st.push(tmp);
                continue;
            }
            else if(tmp == '-' ||(tmp >= '0' && tmp <= '9') || tmp == '.'){
                num[j++] = tmp;
                continue;
            }
            else if((tmp == ',' && s[i-1] != '}') || (tmp == '}' && s[i+1] == ',') || i == static_cast<int>(strlen(s))-2){
                num[j] = '\0';
                mat[count++] = atof(num);
                j = 0;
            }
            if(tmp == '}'){
                if(st.empty()) throw "Illegal bracket pairing!\n";
                st.pop();
                count_pair++;
            }
        }
        if(!st.empty()) throw "Illegal bracket pairing!\n";
    }
    else throw "NULL!\n";
    Init(count_pair,count/count_pair);
    for(int m = 0; m < num_rows; m++)
        for(int n = 0; n < num_cols; n++)
            set(m,n,mat[m*num_cols+n]);
    delete []mat;
}
Matrix::Matrix(Matrix::Row row){
    Init(1,row.cols);
    for(int i = 0; i < num_cols; i++) M[i] = row.r[i];
}
Matrix::~Matrix(){
    delete []M;
}
Matrix Matrix::identity(int n){
    Matrix ident(n,n);
    for(int i = 0; i < n; i++) ident.set(i,i,1);
    return ident;
}
Matrix Matrix::diagonal(double* vals, int n){
    Matrix diag(n,n);
    for(int i = 0; i < n; i++) diag.set(i,i,vals[i]);
    return diag;
}
Matrix Matrix::solve(){
    for(int i = 0; i < num_rows-1; i++){
        for(int j = i+1; j < num_rows; j++){
            if(get(i,i) < EPS && get(i,i) > -1*EPS){
                bool flag = true;
                for(int m = i+1; m < num_rows; m++){
                    if(get(m,i) < EPS && get(m,i) > -1*EPS) continue;
                    else{
                        swaps(i,m);
                        flag = false;
                    }
                }
                if(flag) throw "There is no finite number solution!\n";
            }
            double temp = get(j,i)/get(i,i);
            for(int k = 0; k < num_cols; k++){
                set(j,k,get(j,k)-get(i,k)*temp);
            }
        }
    }
    for(int i = 0; i < num_rows; i++){
        double first = get(i,i);
        for(int j = i; j < num_cols; j++){
            set(i,j,get(i,j)/first);
        }
    }
    for(int i = num_rows-1; i > 0; i--){
        for(int j = 0; j <= i-1; j++){
            double temp = get(j,i)/get(i,i);
            for(int k = i; k < num_cols; k++){
                set(j,k,get(j,k)-get(i,k)*temp);
            }
        }
    }
    Matrix res(num_rows,1);
    for(int i = 0; i < num_rows; i++) res.set(i,0,get(i,num_cols-1));
    return res;
}
Matrix Matrix::inverse(){
    if(num_rows != num_cols) throw "Not a square matrix!\n";
    Matrix tmp(num_rows,num_cols);
    Matrix obratno = identity(num_rows);
    for(int i = 0; i < num_rows*num_cols; i++) tmp.M[i] = M[i];
    for(int i = 0; i < num_rows-1; i++){
        for(int j = i+1; j < num_rows; j++){
            if(tmp.get(i,i) < EPS && tmp.get(i,i) > -1*EPS){
                bool flag = true;
                for(int m = i+1; m < num_rows; m++){
                    if(tmp.get(m,i) < EPS && tmp.get(m,i) > -1*EPS) continue;
                    else{
                        tmp.swaps(i,m);
                        obratno.swaps(i,m);
                        flag = false;
                    }
                }
                if(flag) throw "Doesn't have result!\n";
            }
            double temp = tmp.get(j,i)/tmp.get(i,i);
            for(int k = 0; k < num_cols; k++){
                tmp.set(j,k,tmp.get(j,k)-tmp.get(i,k)*temp);
                obratno.set(j,k,obratno.get(j,k)-obratno.get(i,k)*temp);
            }
        }
    }
    for(int i = 0; i < num_rows; i++){
        double first = tmp.get(i,i);
        for(int j = 0; j < num_cols; j++){
            tmp.set(i,j,tmp.get(i,j)/first);
            obratno.set(i,j,obratno.get(i,j)/first);
        }
    }
    for(int i = num_rows-1; i > 0; i--){
        for(int j = 0; j <= i-1; j++){
            double temp = tmp.get(j,i)/tmp.get(i,i);
            for(int k = 0; k < num_cols; k++){
                tmp.set(j,k,tmp.get(j,k)-tmp.get(i,k)*temp);
                obratno.set(j,k,obratno.get(j,k)-obratno.get(i,k)*temp);
            }
        }
    }
    return obratno;
}
Matrix::Row::Row(int row, int cols, double *p){
    r = new double[cols];
    r = p+row*cols;
    this->cols = cols;
}
double& Matrix::Row::operator[](int i){
    return r[i];
}
Matrix::Row Matrix::operator[](int i){
    return Row(i,num_cols,M);
}
Matrix Matrix::operator-(){
    Matrix res(num_rows,num_cols);
    for(int i = 0; i < num_rows; i++)
        for(int j = 0; j < num_rows; j++)
            res.set(i,j,-get(i,j));
    return res;
}
Matrix Matrix::operator*(const int scalar){
    Matrix res(num_rows,num_cols);
    for(int i = 0; i < num_rows; i++)
        for(int j = 0; j < num_rows; j++)
            res.set(i,j,scalar*get(i,j));
    return res;
}
Matrix& Matrix::operator*=(const int scalar){
    for(int i = 0; i < num_rows; i++)
        for(int j = 0; j < num_rows; j++)
            set(i,j,scalar*get(i,j));
    return *this;
}
Matrix& Matrix::operator*=(const Matrix& m){
    if(columns() != m.rows()) throw "Can't mult due to ros/columns!\n";
    double* tmp = new double[num_rows*m.num_cols];
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < m.num_cols; j++){
            double sum = 0;
            for(int k = 0; k < num_cols; k++) sum += get(i,k)*m.get(k,j);
            tmp[i*m.num_cols+j] = sum;
        }
    }
    num_cols = m.columns();
    for(int i = 0; i < num_rows; i++)
        for(int j = 0; j < num_cols; j++)
            set(i,j,tmp[i*num_cols+j]);
    delete []tmp;
    return *this;
}
Matrix& Matrix::operator+=(const Matrix& m){
    if(rows() != m.rows() || columns() != m.columns()) throw "Don't the same ros/columns!\n";
    for(int i = 0; i < num_rows; i++)
        for(int j = 0; j < num_cols; j++)
            set(i,j,get(i,j)+m.get(i,j));
    return *this;
}
Matrix& Matrix::operator-=(const Matrix& m){
    if(rows() != m.rows() || columns() != m.columns()) throw "Don't the same ros/columns!\n";
    for(int i = 0; i < num_rows; i++)
        for(int j = 0; j < num_cols; j++)
            set(i,j,get(i,j)-m.get(i,j));
    return *this;
}
ostream& operator<<(ostream& os,const Matrix& m){
    for(int i = 0; i < m.rows(); i++){
        for(int j = 0; j < m.columns(); j++){
            cout.width(12);
            cout.precision(6);
            os << m.get(i,j) << " ";
        }
        os << endl;
    }
    os << endl;
    return os;
}
Matrix operator+(const Matrix& m1,const Matrix& m2){
    if(m1.rows() != m2.rows() || m1.columns() != m2.columns()) throw "Don't the same rows/columns!\n";
    Matrix res(m1.rows(),m2.columns());
    for(int i = 0; i < res.rows(); i++)
        for(int j = 0; j < res.columns(); j++)
            res.set(i,j,m1.get(i,j)+m2.get(i,j));
    return res;
}
Matrix operator-(const Matrix& m1,const Matrix& m2){
    if(m1.rows() != m2.rows() || m1.columns() != m2.columns()) throw "Don't the same rows/columns!\n";
    Matrix res(m1.rows(),m2.columns());
    for(int i = 0; i < res.rows(); i++)
        for(int j = 0; j < res.columns(); j++)
            res.set(i,j,m1.get(i,j)-m2.get(i,j));
    return res;
}
Matrix operator*(const Matrix& m1,const Matrix& m2){
    if(m1.columns() != m2.rows()) throw "Can't mult due to rows/columns!\n";
    Matrix res(m1.rows(),m2.columns());
    for(int i = 0; i < m1.rows(); i++){
        for(int j = 0; j < m2.columns(); j++){
            double sum = 0;
            for(int k = 0; k < m1.columns(); k++) sum += m1.get(i,k)*m2.get(k,j);
            res.set(i,j,sum);
        }
    }
    return res;
}
Matrix operator|(const Matrix& m1,const Matrix& m2){
    if(m1.rows() != m2.rows()) throw "Can't add due to rows!\n";
    Matrix res(m1.rows(),m1.columns()+m2.columns());
    for(int i = 0; i < res.rows(); i++)
        for(int j = 0; j < res.columns(); j++){
            if(j < m1.columns()) res.set(i,j,m1.get(i,j));
            else res.set(i,j,m2.get(i,j-m1.columns()));
        }
    return res;
}
Matrix operator/(const Matrix& m1,const Matrix& m2){
    if(m1.columns() != m2.columns()) throw "Can't add due to columns!\n";
    Matrix res(m1.rows()+m2.rows(),m1.columns());
    for(int i = 0; i < res.rows(); i++)
        for(int j = 0; j < res.columns(); j++){
            if(i < m1.rows()) res.set(i,j,m1.get(i,j));
            else res.set(i,j,m2.get(i-m1.rows(),j));
        }
    return res;
}
bool operator==(const Matrix& m1,const Matrix& m2){
    if(m1.rows() != m2.rows() || m1.columns() != m2.columns()) throw "Don't the same rows/columns!\n";
    double diff = 0;
    for(int i = 0; i < m1.rows()*m1.columns(); i++) diff += (m1.M[i]-m2.M[i]);
    return (diff <= Matrix::EPS && diff >= -Matrix::EPS);
}
bool operator!=(const Matrix& m1,const Matrix& m2){
    if(m1.rows() != m2.rows() || m1.columns() != m2.columns()) throw "Don't the same rows/columns!\n";
    double diff = 0;
    for(int i = 0; i < m1.rows()*m1.columns(); i++) diff += (m1.M[i]-m2.M[i]);
    return !(diff <= Matrix::EPS && diff >= -Matrix::EPS);
}
