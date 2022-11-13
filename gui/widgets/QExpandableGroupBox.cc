/*
 * QExpandableGroupBox.cc
 *
 *  Created on: Mar 29, 2022
 *      Author: amyznikov
 */

#include "QExpandableGroupBox.h"
//#include <core/debug.h>

#define __STYLE_TEXT(x) #x

static constexpr char chkbox_style[] =
  __STYLE_TEXT(

      QCheckBox {
        spacing: 15px;
      }
      QCheckBox::indicator {
        width: 13px;
        height: 13px;
      }
      QCheckBox::indicator:unchecked {
        image: url(:/gui/icons/double-arrow-right.png);
      }
      QCheckBox::indicator:checked {
        image: url(:/gui/icons/double-arrow-up.png);
      }
  );

#undef __STYLE_TEXT

QExpandableGroupBox::QExpandableGroupBox(const QString & title, QWidget * view, int stretch, Qt::Alignment alignment, QWidget * parent) :
    Base(parent),
    view_(view)
{
  Q_INIT_RESOURCE(gui_resources);

  QVBoxLayout * frameLayout;

  layout_ = new QVBoxLayout(this);

  chkBox_ = new QCheckBox(title, this);
  chkBox_->setStyleSheet(chkbox_style);
  layout_->addWidget(chkBox_, 0, Qt::AlignTop);

  frame_ = new QGroupBox(this);
  frame_->setCheckable(false);

  frameLayout = new QVBoxLayout(frame_);
  frameLayout->addWidget(view_);

  frame_->setVisible(false);

  QObject::connect(chkBox_, &QCheckBox::stateChanged,
      [this, stretch, alignment](int state) {

        if ( state == Qt::Checked ) {
          frame_->setVisible(true);
          layout_->addWidget(frame_, stretch, alignment);
        }
        else {
          frame_->setVisible(false);
          layout_->removeWidget(frame_);
        }
      });

}

QWidget * QExpandableGroupBox::view() const
{
  return view_;
}

QCheckBox * QExpandableGroupBox::checkbox() const
{
  return chkBox_;
}

QVBoxLayout * QExpandableGroupBox::boxlayout() const
{
  return layout_;
}

void QExpandableGroupBox::expand()
{
  chkBox_->setChecked(true);
}

void QExpandableGroupBox::collapse()
{
  chkBox_->setChecked(false);
}

void QExpandableGroupBox::toggle()
{
  chkBox_->toggle();
}

