/**
 * \file QGBSettings.h
 *
 *  \date 21 sept. 2010
 *  \author akay
 */

#ifndef LIBAMARSI_QUAD_QGBSETTINGS_H_
#define LIBAMARSI_QUAD_QGBSETTINGS_H_

#include <QWidget>

#include "../ui_Settings.h"
/**
 *
 */
class QGBSettings : public QWidget, public Ui::QGBSettings{
  Q_OBJECT
public :
  virtual ~QGBSettings();

  static QGBSettings * instance();

  static void initialize(const QCoreApplication & appli);

public slots :
  void on_doneButton_clicked();
  void on_applyButton_clicked();
//  void on_portEdit_valueChanged();
//  void on_serverEdit_editingFinished();
private :
  QGBSettings();
  void loadFromSettings();
  void saveToSettings();
private :
  static QGBSettings *d_instance;
  QString d_ipAdress;
  unsigned int d_port;

};

#endif // LIBAMARSI_QUAD_QGBSETTINGS_H_
