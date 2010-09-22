/**
 * \file main.cpp
 *
 *  \date 22 sept. 2010
 *  \author akay
 */

#include <QApplication>
#include "QGBViewerMainWindow.h"


int main(int argc, char ** argv){
  QApplication appli(argc,argv);



  QGBViewerMainWindow main;

  main.show();

  return appli.exec();
}
