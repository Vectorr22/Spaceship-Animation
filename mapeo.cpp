#include "mapeo.h"


Mapeo::Mapeo()
{

}

void Mapeo::ventana(float wx1, float wy1, float wx2, float wy2)
{
    xWmin = wx1;
    yWmin = wy1;
    xWmax = wx2;
    yWmax = wy2;
}

void Mapeo::puerto(int pvx1, int pvy1, int pvx2, int pvy2)
{
     xPVmin = pvx1;
     yPVmin = pvy1;
     xPVmax = pvx2;
     yPVmax = pvy2;
}
    // REFERENCIA EN C/C++ &, EN LA DIRECCION DE LA
// VARIABLE LOCAL SE PASA SU REFERENCIA Y LO QUE
// SE CALCULE EN EL METODO QUEDA ASIGNADO EN
// DICHA VARIABLE
//                                                              v ^
void Mapeo::mapear(int xW, int yW, int &xP, int &yP, int L, int M)
{
    float sX, sY;
    sX = ( xPVmax - xPVmin ) / ( xWmax - xWmin );
    //cout << "Escalación en X: " << sX << endl;

    sY = ( yPVmax - yPVmin ) / ( yWmax - yWmin );
    //cout << "Escalación en Y: " << sY << endl;

    xP = (int) ( round (sX * (xW - xWmin) + xPVmin + L) );
    yP = (int) ( round (sY * (yWmin - yW) - yPVmin + M) );


}







