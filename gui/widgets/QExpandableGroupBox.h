/*
 * QExpandableGroupBox.h
 *
 *  Created on: Mar 29, 2022
 *      Author: amyznikov
 */

#pragma once
#ifndef __QExpandableGroupBox_h__
#define __QExpandableGroupBox_h__

#include <QtWidgets/QtWidgets>


class QExpandableGroupBox:
    public QWidget
{
  Q_OBJECT;
public:
  typedef QExpandableGroupBox ThisClass;
  typedef QWidget Base;

  QExpandableGroupBox(const QString & title, QWidget * view, int stretch = 0, Qt::Alignment alignment = Qt::Alignment(),
      QWidget * parent = Q_NULLPTR);

  QWidget * view() const;
  QCheckBox * checkbox() const;
  QVBoxLayout * boxlayout() const;

  void expand();
  void collapse();
  void toggle();



protected:
  QWidget * view_ = Q_NULLPTR;
  QVBoxLayout * layout_ = Q_NULLPTR;
  QCheckBox * chkBox_ = Q_NULLPTR;
  QGroupBox * frame_ = Q_NULLPTR;
};

#endif /* __QExpandableGroupBox_h__ */
