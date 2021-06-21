#include <iostream>
//#include "function.h"

using namespace std;

class Matrix
{
    friend std::ostream &operator<<(std::ostream &, const Matrix &);
    friend std::istream &operator>>(std::istream &, Matrix &);
public:
    Matrix(int s = 5);

    Matrix(const Matrix &);// copy constructor

    ~Matrix() {
        delete [] matrix;
        delete [] buf;
    }

    Matrix &operator=(const Matrix &a);

    Matrix &clockwise90(){
        int tmp[size*size];
        int num = 0;
        for(int i=0;i<this->size;i++){
            for(int j = 0;j<this->size;j++){
                tmp[num] = this->matrix[i][j];
                num++;
            }
        }
        num=0;
        for(int i=size-1; i>=0; i--){
            for(int j=0; j<size; j++){
                matrix[j][i] = tmp[num];
                num++;
            }
        }
        return *this;
    }
private:
    int **matrix;
    int *buf;   // 2D matrix stored in 1D raster scan order
    int size;
}; //end class Matrix

ostream &operator << (std::ostream &out, const Matrix &m){
    //cout << "print" << endl;

    for(int i = 0; i < m.size; i++){
        for(int j = 0; j < m.size; j++){
            if(j == m.size - 1)
                out << m.matrix[i][j];
            else
                out << m.matrix[i][j] << " ";
        }
        cout << endl;
    }
    return out;
}

istream &operator >> (std::istream &read, Matrix &m){
    //cout << "reading" << endl;
    for(int i = 0; i < m.size; i++)
        for(int j = 0; j < m.size; j++)
            read >> m.matrix[i][j];

    return read;
}

Matrix::Matrix(int s){
    size = s;

    buf = new int[size*size];
    for(int i = 0; i < size*size; i++)
        buf[i] = 0;

    matrix = new int*[size];
    for(int i = 0; i < size; i++)
        matrix[i] = new int[size];

    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            matrix[i][j] = 0;
}

Matrix::Matrix(const Matrix &m){
    //cout << "copy" << endl;
    size = m.size;
    buf = m.buf;
    *this = m;
}

Matrix& Matrix::operator = (const Matrix &m){
    //cout << "assign" << endl;
}

int main()
{
    int matrix_size;
    cin>>matrix_size;

    Matrix a(matrix_size);
    cin>>a;
    //cout << "read complete" << endl;
    //cout << endl << a << endl;

    cout<<endl;
    cout<<a.clockwise90().clockwise90()<<endl;
    //cout << "clock wise done" << endl;
    cout<<a<<endl;
    //cout << "ouput done" << endl;

    return 0;
} // end main
