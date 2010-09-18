/**
 * \file main.cpp
 *
 *  \date 18 sept. 2010
 *  \author akay
 */

#include <QApplication>
#include "tabletcanvas.h"


int main (int argc, char ** argv){
  QApplication appli(argc,argv);
  TabletCanvas canvas;
  canvas.show();
  return appli.exec();


}
