/**
 * \file main.cpp
 *
 *  \date 22 sept. 2010
 *  \author akay
 */
#include <libQGBBase/settings/QGBSettings.h>

#include <QApplication>
#include "QGBViewerMainWindow.h"


int main(int argc, char ** argv){
  QApplication appli(argc,argv);

  QGBSettings::initialize(appli);

  QGBViewerMainWindow main;

  main.show();

  return appli.exec();
}
