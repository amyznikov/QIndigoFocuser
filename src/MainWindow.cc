/*
 * MainWindow.cc
 *
 *  Created on: Nov 8, 2022
 *      Author: amyznikov
 */

#include "MainWindow.h"

MainWindow::MainWindow(QWidget * parent) :
  Base(parent),
  indigoClient_("QIndigoFocuser", this)
{
  setWindowTitle("QIndigoFocuser");

  setCentralWidget(focuserWidget_ =
      new QIndigoFocuserWidget(this));

  focuserWidget_->setIndigoClient(
      &indigoClient_);

  QMetaObject::invokeMethod(this,
      "init",
      Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
  indigoClient_.stop();
}

void MainWindow::init()
{
  indigo_result status;

  if( (status = indigoClient_.start()) != INDIGO_OK ) {
    QMessageBox::critical(this, "ERROR",
        "indigoClient_.start() fails");
  }
  else if( (status = indigoClient_.load_driver("indigo_focuser_focusdreampro")) ) {
    QMessageBox::critical(this, "ERROR",
        "indigoClient_.loadIndigoDriver(indigo_focuser_focusdreampro) fails");
  }

}
