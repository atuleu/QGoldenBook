/**
 * \file QGBSettings.cpp
 *
 *  \date 21 sept. 2010
 *  \author akay
 */
#include <iostream>
#include "QGBSettings.h"
#include <QSettings>
QGBSettings::QGBSettings()
: QWidget()
, Ui::QGBSettings(){
  this->setupUi(this);
}

QGBSettings::~QGBSettings() {
}
QGBSettings * QGBSettings::d_instance(NULL);
QGBSettings * QGBSettings::instance(){
  if(!d_instance)
    std::cerr<<"Warning you did not initialize the settings ! "
      <<"call QGBSettings::initialize() first !"<<std::endl;

  return d_instance;
}

void QGBSettings::initialize(const QCoreApplication & appli){
  appli.setOrganizationName("Satellite");
  appli.setOrganizationDomain("satellite.epfl.ch");
  appli.setApplicationName("QGoldenBook");

  d_instance = new QGBSettings();
}

void QGBSettings::on_doneButton_clicked(){
  on_applyButton_clicked();
  this->hide();
}

void QGBSettings::on_applyButton_clicked(){
  saveToSettings();
}

//  void QGBSettings::on_portEdit_valueChanged(){
//
//  }
//  void QGBSettings::on_serverEdit_editingFinished(){
//  }


void QGBSettings::saveToSettings(){
  QSettings settings;
  settings.setValue("server",serverEdit->text());
  settings.setValue("port",portEdit->value());
}

void QGBSettings::loadFromSettings(){
  QSettings settings;
  serverEdit->setText(settings.value("server","127.0.0.1").toString());
  portEdit->setValue(settings.value("port",6666).toInt());
}
