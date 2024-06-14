#ifndef MATRIZ_H
#define MATRIZ_H
#include <QDebug>

#endif // MATRIZ_H

class Matrix {
    int col, ren;
    float **Mat;

public:
    //Constructor default
    Matrix(int nr = 4, int nc = 4, float valor = 0);
    //Constructor
    Matrix(float nr, float nc, float **m);
    //Constructor copia
    Matrix (Matrix &);
    //Destructor
    ~Matrix();
    //Definir metodos
    void SET(int r, int c, float val){
        Mat[r][c]=val;
    }
    float GET(int r, int c){
        return Mat[r][c];
    }
    int numCol(){return col;}
    int numRen(){return ren;}
    void inicializar(int, int);

    //SOBRECARGA DE OPERADORES
    Matrix &operator *(const Matrix  &m1);
    Matrix &operator *=(Matrix  &mat2);
    Matrix &operator =(Matrix  &);
    Matrix operator *(float);//Multiplicar por un escalar
    Matrix &asignar(Matrix);
    Matrix &identidad();//Permite inicializar la matriz base

    //Transformaciones
    //FigRes            Fig     id      tx  ty
    Matrix &traslacion(Matrix, Matrix, int, int);
    Matrix &escalacion(Matrix, Matrix, float, float);
    Matrix &escalacionPuntoFijo(Matrix fig, Matrix id, float sx,float sy,int pFx,int pFy);
    Matrix &rotacion(Matrix fig, Matrix id, float);
    Matrix &rotacionPuntoFijo(Matrix fig, Matrix id,float angulo, int pFx, int pFy);




};
