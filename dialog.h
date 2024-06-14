#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtGui>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include "mapeo.h"
#include "Matriz.h"
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QLabel>
#include <QVBoxLayout>
#include <QRect>
#include <QDebug>
#include <QRect>
#include <QPixmap>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void paintEvent(QPaintEvent * event);
    void keyPressEvent(QKeyEvent *evento);
    void mousePressEvent(QMouseEvent *evento);
    void asignarfigura();
    void dibujarFiguraMapeada();
    //Transformaciones 2D
    void trasladar(int tX, int tY);
    void escalar(double SX, double SY);
    void escalacionPuntoFijo(float sx,float sy,int pFx,int pFy);
    void rotar(double angulo);
    void rotarFijo(double angulo, double pFx, double pFy);
    void opcionesPlanetas();
    void eliminarOpciones();
    void regresarMenu();

public slots:
    void animacionInicio();
    void mostrarPlaneta1();
    void mostrarPlaneta2();
    void mostrarPlaneta3();
    void mostrarPlaneta4();
    void animacionLuna();
    void animacionMarte();
    void animacionJupiter();
    void animacionTierra();


private:
    Ui::Dialog *ui;
    QPainter *canvas;
    float figPropia[23][3];
    float figPropiaAux[23][3];
    int ancho,largo;
    int centroX,centroY;
    int TX,TY;
    float SX,SY;
    float pFx, pFy;
    QTimer *timerInicio;
    QTimer *animacionPlaneta;
    QLabel *titulo;
    QLabel *begin;
    QLabel *opcionPlaneta;
    QPushButton *planeta1;
    QPushButton *planeta2;
    QPushButton *planeta3;
    QPushButton *planeta4;
    int mouseCount;



};
#endif // DIALOG_H
