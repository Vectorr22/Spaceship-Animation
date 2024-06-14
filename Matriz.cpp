#include "Matriz.h"
#include <assert.h>
#include <QtCore>
//Constructor
Matrix::Matrix(int nr, int nc, float valor){
    ren = nr;
    col = nc;
    Mat = new float*[ren];
    assert(Mat);

    for (int i = 0; i < ren; ++i) {
        Mat[i] = new float [col];
        assert(Mat[i]);
    }
    for (int i = 0; i < ren; ++i) {
        for (int j = 0; j < col; ++j) {
            Mat[i][j]= valor;
        }
    }
}

Matrix::Matrix(float nr, float nc, float **m){
    ren = nr;
    col = nc;
    Mat = new float*[ren];
    assert(Mat);

    for (int i = 0; i < ren; ++i) {
        Mat[i] = new float [col];
        assert(Mat[i]);
    }
    for (int i = 0; i < ren; ++i) {
        for (int j = 0; j < col; ++j) {
            Mat[i][j]= m[i][j];
        }
    }
}

Matrix::Matrix(Matrix &m){
    this->ren = m.numRen();
    this->col = m.numCol();
    this->Mat = new float *[ren];
    assert(Mat);

    for (int i = 0; i < ren; ++i) {
        Mat[i] = new float [col];
        assert(Mat[i]);
    }
    for (int i = 0; i < ren; ++i) {
        for (int j = 0; j < col; ++j) {
            Mat[i][j]= m.GET(i,j);
        }
    }
}

Matrix::~Matrix(){
    for (int i = 0; i < ren; ++i) {
        delete [] Mat[i];
    }
    delete[]Mat;
}

void Matrix::inicializar(int R, int C){
    ren = R;
    col = C;
    Mat = new float*[ren];
    for (int i = 0; i < ren; ++i) {
        Mat[i] = new float [col];
        assert(Mat[i]);
    }
    for (int i = 0; i < ren; ++i) {
        for (int j = 0; j < col; ++j) {
            Mat[i][j]= 0;
        }
    }
}
Matrix &Matrix::operator*(const Matrix &m1){
    Matrix * result = new Matrix(ren, col, 0);
    assert(result);
    for (int i = 0; i < ren; ++i) {
        for (int j = 0; j < col; ++j) {
            for (int k = 0; k < col; ++k) {
                result->Mat[i][j] += Mat[i][k] * m1.Mat[k][j];
            }
        }
    }
    return *result;
}

Matrix &Matrix::operator=(Matrix &m){
    for (int i = 0; i < ren; ++i) {
        delete[] Mat[i];
    }
    delete []Mat;

    this->ren = m.numRen();
    this->col = m.numCol();
    this->Mat = new float *[ren];
    assert(Mat);

    for (int i = 0; i < ren; ++i) {
        Mat[i] = new float [col];
        assert(Mat[i]);
    }
    for (int i = 0; i < ren; ++i) {
        for (int j = 0; j < col; ++j) {
            //Mat[i][j]= m.GET(i,j);
            Mat[i][j]= m.Mat[i][j];
        }
    }
    return *this;
}

Matrix &Matrix::asignar(Matrix m)
{
   for(int i = 0; i<m.numRen();i++) {
       for(int j = 0; j<m.numCol();j++) {
            this->Mat[i][j]= m.GET(i,j);
       }
   }
   return *this;
}

Matrix &Matrix::identidad()
{
    for(int i = 0; i<ren;i++) {
        for(int j = 0; j<col;j++) {
            if(i==j)
             this->Mat[i][i]= 1;
            else
              Mat[i][j]=0;
        }
    }
    return *this;
}

//------TRANSFORMACIONES------
Matrix &Matrix::traslacion(Matrix f, Matrix id, int tx, int ty)
{
    id.identidad();
    id.SET(2,0,tx);
    id.SET(2,1,ty);
    //f*=id;
    //this REPRESENTA A FigRes
    this->asignar(f*id);
    return *this; //this = puntero
}

Matrix &Matrix::escalacion(Matrix fig, Matrix id, float Sx, float Sy)
{
    id.identidad();
    id.SET(0,0,Sx);
    id.SET(1,1,Sy);

    fig*=id;
    this->asignar(fig);
    return *this;
}

Matrix &Matrix::escalacionPuntoFijo(Matrix fig, Matrix id, float sx, float sy, int pFx, int pFy)
{
    id.identidad();
    double traslacionX = pFx * (1-sx);
    double traslacionY = pFy*(1-sy);
    id.SET(0,0,sx);
    id.SET(1,1,sy);
    id.SET(2,0,traslacionX);
    id.SET(2,1,traslacionY);
    fig*=id;
    this->asignar(fig);
    return *this;
}

Matrix &Matrix::rotacion(Matrix fig, Matrix id, float radianes)
{
    id.identidad();
    double grados = radianes * (M_PI/180.0);
    id.SET(0,0,cos(grados));
    id.SET(0,1,sin(grados));
    id.SET(1,0,-sin(grados));
    id.SET(1,1,cos(grados));

    fig*=id;
    this->asignar(fig);
    return *this;
}

Matrix &Matrix::rotacionPuntoFijo(Matrix fig, Matrix id, float angulo, int pFx, int pFy)
{
    id.identidad();
    double grados = angulo * (M_PI/180.0);
    double ren2_0 = pFx * (1-cos(grados)) + pFy * sin(grados);
    float ren2_1 = pFy * (1-cos(grados)) - pFx * sin(grados);

    id.SET(0,0,cos(grados));
    id.SET(0,1,sin(grados));
    id.SET(1,0,-sin(grados));
    id.SET(1,1,cos(grados));
    id.SET(2,0,ren2_0);
    id.SET(2,1,ren2_1);

    fig*=id;
    this->asignar(fig);
    return *this;
}

Matrix Matrix::operator*(float val){
    Matrix temp;
    temp.inicializar(ren,col);
    for (int i = 0; i < ren; ++i) {
        for (int j = 0; j < col; ++j) {
            temp.SET(i,j,Mat[i][j] * val);
        }
    }
    return temp;
}
Matrix &Matrix::operator*=(Matrix &mat2){
    Matrix aux;
    aux.inicializar(ren,col);
    for (int i = 0; i < ren; i++) {
        for (int j = 0; j < mat2.numCol(); j++) {
            float suma = 0;
            for (int k = 0; k < col; ++k) {
                suma+=floor(Mat[i][k]*mat2.GET(k,j)+0.5);
                aux.SET(i,j,suma);
            }
        }
    }
    asignar(aux);
    return *this;
}


