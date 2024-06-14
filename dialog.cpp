#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QPixmap fondo(":/images/background.jpg");
    QSize size = this->size();
    fondo = fondo.scaled(size,Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, fondo);
    this->setPalette(palette);
    this->setFocus();

    timerInicio = new QTimer();
    animacionPlaneta = new QTimer();
    titulo = new QLabel("Space Travel",this);
    titulo->setFont(QFont("Ravie",40));
    titulo->setGeometry(170,50,this->width(),200);
    titulo->show();

    begin = new QLabel("Press any key to continue",this);
    begin->setVisible(false);
    begin->setFont(QFont("MS Gothic",20));
    begin->setAlignment(Qt::AlignCenter);
    begin->setGeometry(10,480,this->width(),200);


    connect(timerInicio,SIGNAL(timeout()),this,SLOT(animacionInicio()));
    timerInicio->start(300);
    mouseCount = 0;


}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
        canvas = new QPainter(this);
        dibujarFiguraMapeada();
        canvas->end();


}

void Dialog::keyPressEvent(QKeyEvent *evento)
{
    if(evento->key() == Qt::Key_Escape)
        this->close();

    if(mouseCount==0){
        mouseCount++;
    }

    QDialog::keyPressEvent(evento);
}

void Dialog::mousePressEvent(QMouseEvent *evento)
{
    if(evento->button() == Qt::LeftButton){
        mouseCount++;
        if(mouseCount == 1){
            titulo->clear();
            begin->clear();
            trasladar(0,-450);
            opcionesPlanetas();
        }

    }
    if(evento->button() == Qt::RightButton){
        regresarMenu();
    }
}

void Dialog::asignarfigura()
{
    figPropia[0][0] =  60;  figPropia[0][1] =  10;  figPropia[0][2] = 1;
    figPropia[1][0] =  70;  figPropia[1][1] =  20;  figPropia[1][2] = 1;
    figPropia[2][0] =  70;  figPropia[2][1] =  30;  figPropia[2][2] = 1;
    figPropia[3][0] =  80;  figPropia[3][1] =  30;  figPropia[3][2] = 1;
    figPropia[4][0] =  80;  figPropia[4][1] =  40;  figPropia[4][2] = 1;
    figPropia[5][0] =  90;  figPropia[5][1] =  40;  figPropia[5][2] = 1;
    figPropia[6][0] =  90;  figPropia[6][1] =  30;  figPropia[6][2] = 1;
    figPropia[7][0] =  100; figPropia[7][1] =  30;  figPropia[7][2] = 1;
    figPropia[8][0] =  110; figPropia[8][1] =  20;  figPropia[8][2] = 1;
    figPropia[9][0] =  100; figPropia[9][1] =  50;  figPropia[9][2] = 1;
    figPropia[10][0] = 70;  figPropia[10][1] = 80;  figPropia[10][2] = 1;
    figPropia[11][0] = 60;  figPropia[11][1] = 100; figPropia[11][2] = 1;
    figPropia[12][0] = 50;  figPropia[12][1] = 80;  figPropia[12][2] = 1;
    figPropia[13][0] = 20;  figPropia[13][1] = 50;  figPropia[13][2] = 1;
    figPropia[14][0] = 10;  figPropia[14][1] = 20;  figPropia[14][2] = 1;
    figPropia[15][0] = 20;  figPropia[15][1] = 30;  figPropia[15][2] = 1;
    figPropia[16][0] = 30;  figPropia[16][1] = 30;  figPropia[16][2] = 1;
    figPropia[17][0] = 30;  figPropia[17][1] = 40;  figPropia[17][2] = 1;
    figPropia[18][0] = 40;  figPropia[18][1] = 40;  figPropia[18][2] = 1;
    figPropia[19][0] = 40;  figPropia[19][1] = 30;  figPropia[19][2] = 1;
    figPropia[20][0] = 50;  figPropia[20][1] = 30;  figPropia[20][2] = 1;
    figPropia[21][0] = 50;  figPropia[21][1] = 20;  figPropia[21][2] = 1;
    figPropia[22][0] = 60;  figPropia[22][1] = 10;  figPropia[22][2] = 1;

    for(int r = 0; r<23; r++){
        for (int c = 0; c < 3; c++) {
            figPropiaAux[r][c] = figPropia[r][c];
        }
    }

    //DEFINIMOS O ESTABLECEMOS EL ANCHO DEL AREA DE DIBUJO
    ancho = this->size().width();
    largo = this->size().height();
    centroX = ancho/2;
    centroY = largo/2;
    TX = TY = 0;
    SX = SY = 1;
}


void Dialog::dibujarFiguraMapeada()
{
    QPen pen(QColor(0,200,0),3);
    canvas->setPen(pen);
    //ANTIALIAS, para simular lineas sin escalonamiento
    canvas->setRenderHint(QPainter::Antialiasing,true);
    //Dibujar 4 cuadrantes
    //canvas->drawLine(0,centroY,ancho,centroY);
    //canvas->drawLine(centroX,0,centroX,size().height());

    //COMPLETAR CODIGO 1:1 VENTANA = PUERTO
    Mapeo dibujo;
    dibujo.ventana(0,0,ancho,largo);
    dibujo.puerto(0,0,ancho,largo);
    int L = centroX;
    int M = centroY;
    QPen pen2(QColor(255,0,0),3);
    canvas->setPen(pen2);
    int x1,y1;

    QVector<QPoint> puntosFigura;
    canvas->setPen(QColor(102,131,217));
    for (int i = 0; i < 23; i++)
    {
        dibujo.mapear(figPropia[i][0], figPropia[i][1], x1, y1, L, M);
        puntosFigura.append(QPoint(x1, y1));
    }

    // Dibuja el relleno de la figura
    canvas->setBrush(QBrush(QColor(65,215,145))); // Color de relleno
    canvas->drawPolygon(puntosFigura);
}

void Dialog::trasladar(int tX, int tY)
{
    Matrix fig, id, figRes;
    fig.inicializar(23,3);
    figRes.inicializar(23,3);
    id.inicializar(3,3);
    //Asignar los puntos de la figura
    for (int i = 0; i < fig.numRen(); ++i) {
        for (int j = 0; j < fig.numCol(); ++j) {
             fig.SET(i,j,figPropia[i][j]);
        }
    }
    figRes.traslacion(fig,id,tX,tY);
    for (int r = 0; r < figRes.numRen(); r++) {
        for (int c = 0; c < figRes.numCol(); c++) {
             figPropia[r][c] = figRes.GET(r,c);
        }
    }
    update();
}

void Dialog::escalar(double SX, double SY)
{
    Matrix fig, id, figRes;
    fig.inicializar(23,3);
    figRes.inicializar(23,3);
    id.inicializar(3,3);
    //Asignar los puntos de la figura
    for (int i = 0; i < fig.numRen(); ++i) {
        for (int j = 0; j < fig.numCol(); ++j) {
             fig.SET(i,j,figPropia[i][j]);
        }
    }

    figRes.escalacion(fig,id,SX,SY);

    for (int r = 0; r < figRes.numRen(); r++) {
        for (int c = 0; c < figRes.numCol(); c++) {
             figPropia[r][c] = figRes.GET(r,c);
        }
    }

    update();
}

void Dialog::escalacionPuntoFijo(float sx, float sy, int pFx, int pFy)
{
    Matrix fig, id, figRes;
    fig.inicializar(23,3);
    figRes.inicializar(23,3);
    id.inicializar(3,3);
    //Asignar los puntos de la figura
    for (int i = 0; i < fig.numRen(); ++i) {
        for (int j = 0; j < fig.numCol(); ++j) {
             fig.SET(i,j,figPropia[i][j]);
        }
    }

    figRes.escalacionPuntoFijo(fig,id,sx,sy,pFx,pFy);

    for (int r = 0; r < figRes.numRen(); r++) {
        for (int c = 0; c < figRes.numCol(); c++) {
             figPropia[r][c] = figRes.GET(r,c);
        }
    }

    update();
}

void Dialog::rotar(double angulo)
{
    Matrix fig, id, figRes;
    fig.inicializar(23,3);
    figRes.inicializar(23,3);
    id.inicializar(3,3);
    //Asignar los puntos de la figura
    for (int i = 0; i < fig.numRen(); ++i) {
        for (int j = 0; j < fig.numCol(); ++j) {
             fig.SET(i,j,figPropia[i][j]);
        }
    }

    figRes.rotacion(fig,id,angulo);

    for (int r = 0; r < figRes.numRen(); r++) {
        for (int c = 0; c < figRes.numCol(); c++) {
             figPropia[r][c] = figRes.GET(r,c);
        }
    }

    update();
}

void Dialog::rotarFijo(double angulo, double pFx, double pFy)
{
    Matrix fig, id, figRes;
    fig.inicializar(23,3);
    figRes.inicializar(23,3);
    id.inicializar(3,3);
    //Asignar los puntos de la figura
    for (int i = 0; i < fig.numRen(); ++i) {
        for (int j = 0; j < fig.numCol(); ++j) {
             fig.SET(i,j,figPropia[i][j]);
        }
    }

    figRes.rotacionPuntoFijo(fig,id,angulo,pFx,pFy);

    for (int r = 0; r < figRes.numRen(); r++) {
        for (int c = 0; c < figRes.numCol(); c++) {
             figPropia[r][c] = figRes.GET(r,c);
        }
    }

    update();
}

void Dialog::opcionesPlanetas()
{

    opcionPlaneta = new QLabel("Choose a planet to visit!",this);
    opcionPlaneta->setFont(QFont("Ravie",30));
    opcionPlaneta->setAlignment(Qt::AlignCenter);
    opcionPlaneta->setGeometry(10,50,this->width(),200);
    opcionPlaneta->show();

    planeta1 = new QPushButton("MOON",this);
    planeta1->setFont(QFont("Ravie",25));
    planeta1->setGeometry(40,260,331,101);
    planeta1->setStyleSheet("background-color: rgb(109, 67, 200);");
    planeta1->show();

    planeta2 = new QPushButton("MARS",this);
    planeta2->setFont(QFont("Ravie",25));
    planeta2->setGeometry(430,260,331,101);
    planeta2->setStyleSheet("background-color: rgb(109, 67, 200);");
    planeta2->show();

    planeta3 = new QPushButton("JUPITER",this);
    planeta3->setFont(QFont("Ravie",25));
    planeta3->setGeometry(40,420,331,101);
    planeta3->setStyleSheet("background-color: rgb(109, 67, 200);");
    planeta3->show();

    planeta4 = new QPushButton("EARTH",this);
    planeta4->setFont(QFont("Ravie",25));
    planeta4->setGeometry(430,420,331,101);
    planeta4->setStyleSheet("background-color: rgb(109, 67, 200);");
    planeta4->show();

    connect(planeta1,SIGNAL(clicked()),this,SLOT(mostrarPlaneta1()));
    connect(planeta2,SIGNAL(clicked()),this,SLOT(mostrarPlaneta2()));
    connect(planeta3,SIGNAL(clicked()),this,SLOT(mostrarPlaneta3()));
    connect(planeta4,SIGNAL(clicked()),this,SLOT(mostrarPlaneta4()));

}

void Dialog::eliminarOpciones()
{

    /*disconnect(planeta1,SIGNAL(clicked()),this,SLOT(mostrarPlaneta1()));
    disconnect(planeta2,SIGNAL(clicked()),this,SLOT(mostrarPlaneta2()));
    disconnect(planeta3,SIGNAL(clicked()),this,SLOT(mostrarPlaneta3()));
    disconnect(planeta4,SIGNAL(clicked()),this,SLOT(mostrarPlaneta4()));*/


    opcionPlaneta->clear();

    delete planeta1;
    planeta1 = nullptr;

    delete planeta2;
    planeta2 = nullptr;

    delete planeta3;
    planeta3 = nullptr;

    delete planeta4;
    planeta4 = nullptr;



}

void Dialog::regresarMenu()
{
    QPixmap fondo(":/images/background.jpg");
    QSize size = this->size();
    fondo = fondo.scaled(size,Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, fondo);
    this->setPalette(palette);
    opcionesPlanetas();

}

void Dialog::animacionInicio()
{
    static int ciclo =0;
    pFx = figPropia[0][0];
    pFy = figPropia[0][1];
    if(ciclo==0){
        asignarfigura();
        rotar(90);
        trasladar(450,-200);
    }
    if(ciclo>0 && ciclo<8){
        trasladar(-100,0);

    }if(ciclo==8){
        rotarFijo(-90,figPropia[0][0],figPropia[0][1]);
        trasladar(0,100);
    }
    if(ciclo==9){
        trasladar(0,100);
        rotarFijo(-90,figPropia[0][0],figPropia[0][1]);
    }
    if(ciclo>9 && ciclo<15){
        trasladar(100,0);
    }
    if(ciclo==15){
        rotarFijo(-90,figPropia[0][0],figPropia[0][1]);
        trasladar(0,-100);
    }
    if(ciclo==16){
        trasladar(0,-100);
        rotarFijo(-90,figPropia[0][0],figPropia[0][1]);
    }
    if(ciclo>16 && ciclo<19){
        trasladar(-100,0);
    }
    if(ciclo==19){
        trasladar(-50,0);
        rotarFijo(-90,figPropia[0][0],figPropia[0][1]);
    }
    if(ciclo>19 && ciclo<21){
        trasladar(0,100);
    }
    if(ciclo==21){
        timerInicio->stop();
        begin->show();
    }
    ciclo++;
    update();




}

void Dialog::mostrarPlaneta1()
{
    eliminarOpciones();
    QPixmap fondo(":/images/moon.jpg");
    QSize size = this->size();
    fondo = fondo.scaled(size,Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, fondo);
    this->setPalette(palette);
    connect(animacionPlaneta,SIGNAL(timeout()),this,SLOT(animacionLuna()));
    animacionPlaneta->start(300);
}

void Dialog::mostrarPlaneta2()
{
    eliminarOpciones();
    QPixmap fondo(":/images/mars.jpg");
    QSize size = this->size();
    fondo = fondo.scaled(size,Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, fondo);
    this->setPalette(palette);
    connect(animacionPlaneta,SIGNAL(timeout()),this,SLOT(animacionMarte()));
    animacionPlaneta->start(300);
}

void Dialog::mostrarPlaneta3()
{
    eliminarOpciones();
    QPixmap fondo(":/images/jupiter.jpg");
    QSize size = this->size();
    fondo = fondo.scaled(size,Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, fondo);
    this->setPalette(palette);
    connect(animacionPlaneta,SIGNAL(timeout()),this,SLOT(animacionJupiter()));
    animacionPlaneta->start(300);
}

void Dialog::mostrarPlaneta4()
{
    eliminarOpciones();
    QPixmap fondo(":/images/earth.jpg");
    QSize size = this->size();
    fondo = fondo.scaled(size,Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, fondo);
    this->setPalette(palette);
    connect(animacionPlaneta,SIGNAL(timeout()),this,SLOT(animacionTierra()));
    animacionPlaneta->start(300);
}

void Dialog::animacionLuna()
{
    static int contador=1;

    if(contador==1){
        escalacionPuntoFijo(0.5,0.5,figPropia[0][0],figPropia[0][1]);
        trasladar(0,200);
    }
    if(contador==2){
        rotarFijo(45,figPropia[0][0],figPropia[0][1]);
    }
    if(contador>2 && contador <18){
        rotarFijo(-45,30,10);
    }
    if(contador==18){
        rotarFijo(-45,figPropia[0][0],figPropia[0][1]);
    }
    if(contador>18 && contador<24){
        trasladar(-10,50);
        escalacionPuntoFijo(0.5,0.5,figPropia[0][0],figPropia[0][1]);
    }
    if(contador==24){
        animacionPlaneta->stop();
        disconnect(animacionPlaneta,SIGNAL(timeout()),this,SLOT(animacionLuna()));
        for(int r = 0; r<23; r++){
            for (int c = 0; c < 3; c++) {
                figPropia[r][c] = figPropiaAux[r][c];
            }
        }
        trasladar(-550,0);
    }

    contador++;

}

void Dialog::animacionMarte()
{
    static int contador=1;
    qDebug()<<contador;

    if(contador==1){
        escalacionPuntoFijo(0.5,0.5,figPropia[0][0],figPropia[0][1]);
        rotarFijo(-90,figPropia[0][0],figPropia[0][1]);
        trasladar(150,200);
    }
    if(contador>1 && contador<8){
        trasladar(100,0);
    }
    if(contador==8){
        rotarFijo(-90,figPropia[0][0],figPropia[0][1]);
        trasladar(-15,-100);
        escalacionPuntoFijo(1.5,1.5,figPropia[0][0],figPropia[0][1]);
    }
    if(contador==9){
        rotarFijo(-90,figPropia[0][0],figPropia[0][1]);
        trasladar(-15,-100);
    }
    if(contador>9 && contador<14){
        trasladar(-100,0);
    }
    if(contador==14){
        rotarFijo(-180,figPropia[0][0],figPropia[0][1]);
        trasladar(30,-100);
        //escalacionPuntoFijo(1.5,1.5,figPropia[0][0],figPropia[0][1]);
    }
    if(contador>14 && contador<19){
        trasladar(100,-30);
    }
    if(contador==19){
        rotarFijo(-90,figPropia[0][0],figPropia[0][1]);
        trasladar(0,100);
    }
    if(contador==20){
        trasladar(0,-200);
        animacionPlaneta->stop();
        disconnect(animacionPlaneta,SIGNAL(timeout()),this,SLOT(animacionMarte()));
        for(int r = 0; r<23; r++){
            for (int c = 0; c < 3; c++) {
                figPropia[r][c] = figPropiaAux[r][c];
            }
        }
        trasladar(-550,0);
    }

    contador++;
}

void Dialog::animacionJupiter()
{

}

void Dialog::animacionTierra()
{

}


