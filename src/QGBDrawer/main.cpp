/**
 * \file main.cpp
 *
 *  \date 18 sept. 2010
 *  \author akay
 */

#include <QApplication>
#include "MainWindow.h"


#include <libQGBBase/settings/QGBSettings.h>

int main (int argc, char ** argv){
  QApplication appli(argc,argv);

  QGBSettings::initialize(appli);

  MainWindow window;
  window.show();
  return appli.exec();


}
