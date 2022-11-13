/*
 * QIndigoFocuserWidget.h
 *
 *  Created on: Nov 8, 2022
 *      Author: amyznikov
 */

#pragma once
#ifndef __QIndigoFocuserSettings_h__
#define __QIndigoFocuserSettings_h__

#include <gui/widgets/QSettingsWidget.h>
#include "QIndigoClient.h"

class QIndigoFocuserWidget:
    public QSettingsWidget
{
  Q_OBJECT;
public:
  typedef QIndigoFocuserWidget ThisClass;
  typedef QSettingsWidget Base;

  QIndigoFocuserWidget(QWidget * parent = Q_NULLPTR);
  ~QIndigoFocuserWidget();

  void setIndigoClient(QIndigoClient * client);
  QIndigoClient * indigoClient() const;

  bool isConnected() const;
  bool canMoveFocusNow() const;
  bool isMovingFocusNow() const;

signals:
  void focuserConnectionStateChanged();
  void focuserMoveDirectionChanged();
  void focuserPositionChanged();
  void focuserLimitsChanged();
  void focuserStepsChanged();
  void focuserSpeedChanged();
  void focuserTemperatureChanged();

protected:
  void onload(QSettings & settings) override;
  void onupdatecontrols() override;
  void updateCurrentDeviceProperties(const indigo_property * property, const QString & message);
  void abortCurrentMotion();
  void moveFocusToPosition(int target_pos);
  bool setMovingDirection(INDIGO_FOCUSER_MOVE_DIRECTION direction);
  void moveFocusInward(int steps);
  void moveFocusOutward(int steps);
  void enumerateCurrentDeviceProperties();

protected slots:
  void onIndigoClientAttach();
  void onIndigoClientDefineProperty(const indigo_device * device, const indigo_property * property, const QString & message);
  void onIndigoClientUpdateProperty(const indigo_device * device, const indigo_property * property, const QString & message);
  void onIndigoClientDeleteProperty(const indigo_device * device, const indigo_property * property, const QString & message);
  void onIndigoClientSendMessage(const indigo_device * device, const char * message);
  void onIndigoClientDetach();
  void onFocuserConnectionStateChanged();
  void onFocuserMoveDirectionChanged();
  void onFocuserPositionChanged();
  void onFocuserLimitsChanged();
  void onFocuserStepsChanged();
  void onFocuserSpeedChanged();
  void onFocuserTemperatureChanged();

  // FOCUSER SELECTION AND CONNECTION STATUS
protected:
  struct c_focuser_connection {
    INDIGO_CONNECTION_STATUS connection_status = INDIGO_CONNECTION_STATUS_UNKNOWN;
    indigo_property_state state = INDIGO_IDLE_STATE;
    bool defined = false;
  } focuser_connection;

  QComboBox * deviceSelector_ctl = Q_NULLPTR;
  QToolButton * connectDisconnect_ctl = Q_NULLPTR;
protected slots:
  void onDeviceSelectorCurrentIndexChanged(int);
  void onConnectDiconnectButtonClicked();

  // DEVICE PORTS
protected:


  // FOCUSER LIMITS
protected:
  struct c_focuser_limits {
    int min_value = 0;
    int max_value = 0;
    indigo_property_state state = INDIGO_IDLE_STATE;
    indigo_property_perm perm = INDIGO_RW_PERM;
    bool defined = false;
  } focuser_limits;

  QLineEditBox * focuserLimits_ctl = Q_NULLPTR;
  // QToolButton * focuserLimitsApply_ctl = Q_NULLPTR;

protected slots:
  void onApplyFocusLimitsClicked();


  // FOCUSER POSITION
protected:
  struct c_focuser_position {
    int value = 0;
    int min_value = 0;
    int max_value = 0;
    indigo_property_state state = INDIGO_IDLE_STATE;
    indigo_property_perm perm = INDIGO_RW_PERM;
    bool defined = false;
  } focuser_position;

  QSpinBox * focuserPosition_ctl = Q_NULLPTR;
  QToolButton * focuserPositionMoveToAbsolutePosition_ctl = Q_NULLPTR;
  QToolButton * focuserPositionMoveToMinPosition_ctl = Q_NULLPTR;
  QToolButton * focuserPositionMoveToMaxPosition_ctl = Q_NULLPTR;

protected slots:
  void onFocuserPositionMoveToAbsolutePositionClicked();
  void onFocuserPositionMoveToMinPositionClicked();
  void onFocuserPositionMoveToMaxPositionClicked();

  // FOCUSER RELATIVE MOTION
protected:
  struct c_focuser_direction {
    INDIGO_FOCUSER_MOVE_DIRECTION value = INDIGO_FOCUSER_MOVE_DIRECTION_UNKNOWN;
    indigo_property_state state = INDIGO_IDLE_STATE;
    bool defined = false;
  } focuser_direction;

  struct c_focuser_steps {
    int value = 0;
    int min_value = 0;
    int max_value = 0;
    indigo_property_state state = INDIGO_IDLE_STATE;
    indigo_property_perm perm = INDIGO_RW_PERM;
    bool defined = false;
  } focuser_steps;

  QSpinBox * focuserSteps_ctl = Q_NULLPTR;
  QToolButton * focuserStepsMoveInward_ctl = Q_NULLPTR;
  QToolButton * focuserStepsMoveInward4x_ctl = Q_NULLPTR;
  QToolButton * focuserStepsMoveOutward_ctl = Q_NULLPTR;
  QToolButton * focuserStepsMoveOutward4x_ctl = Q_NULLPTR;
protected slots:
  void onFocuserStepsMoveInwardClicked();
  void onFocuserStepsMoveInward4xClicked();
  void onFocuserStepsMoveOutwardClicked();
  void onFocuserStepsMoveOutward4xClicked();


  // FOCUSER SPEED
protected:
  struct focuser_speed {
    int value = 0;
    int min_value = 0;
    int max_value = 0;
    indigo_property_state state = INDIGO_IDLE_STATE;
    indigo_property_perm perm = INDIGO_RW_PERM;
    bool defined = false;
  } focuser_speed;

  QSpinBox * focuserSpeed_ctl = Q_NULLPTR;
protected slots:
  void onFocuserSpeedControlValueChanged(int value);



  // FOCUSER TEMPERATURE
protected:
  struct c_focuser_temperature {
    double value;
    bool defined = false;
  } focuser_temperature;

protected: // overrides
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mouseDoubleClickEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
#if QT_CONFIG(wheelevent)
  void wheelEvent(QWheelEvent *event) override;
#endif

protected:
  QIndigoClient * client_ = Q_NULLPTR;
  QString currentDeviceName_;
  QLabel * status_ctl = Q_NULLPTR;
  QLabel * temperature_ctl = Q_NULLPTR;
  std::mutex mtx_;


#if QT_CONFIG(wheelevent)
  int wheel_steps_  = 0;
  bool wheel_steps_acc_started_ = false;
  QCheckBox * enableMouse_ctl = Q_NULLPTR;
#endif

};

#endif /* __QIndigoFocuserSettings_h__ */
