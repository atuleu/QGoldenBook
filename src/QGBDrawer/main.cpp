/**
 * \file main.cpp
 *
 *  \date 18 sept. 2010
 *  \author akay
 */

#include <QApplication>
#include "MainWindow.h"


int main (int argc, char ** argv){
  QApplication appli(argc,argv);

  MainWindow window;
  window.show();
  return appli.exec();


}
