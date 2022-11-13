/*
 * MainWindow.h
 *
 *  Created on: Nov 8, 2022
 *      Author: amyznikov
 */

#pragma once
#ifndef __MainWindow_h__
#define __MainWindow_h__

#include <gui/qindigo/QIndigoFocuserWidget.h>

class MainWindow :
    public QMainWindow
{
  Q_OBJECT;
public:
  typedef MainWindow ThisClass;
  typedef QMainWindow Base;

  MainWindow(QWidget * parent = Q_NULLPTR);
  ~MainWindow();

protected slots:
  void init();

protected:
  QIndigoFocuserWidget * focuserWidget_ = Q_NULLPTR;
  QIndigoClient indigoClient_;
};

#endif /* __MainWindow_h__ */
