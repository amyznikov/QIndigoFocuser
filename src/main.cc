/*
 * main.cc
 *
 *  Created on September 5, 2019
 *      Author: amyznikov
 */
#include "MainWindow.h"

#define MY_COMPANY  "amyznikov"
#define MY_APP      "QIndigoFocuser"

int main(int argc, char *argv[])
{
  indigo_result status;

  indigo_main_argv = (const char**)argv;
  indigo_main_argc = argc;


  /* This shall be set only before connecting */
  indigo_use_host_suffix = true;

  indigo_log_levels log_level =
      INDIGO_LOG_ERROR;

  for( int i = 1; i < argc; ++i ) {

    if ( strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--enable-info") == 0 ) {
      if ( log_level < INDIGO_LOG_INFO ) {
        log_level = INDIGO_LOG_INFO;
      }
      continue;
    }
    if ( strcmp(argv[i], "-vv") == 0 || strcmp(argv[i], "--enable-debug") == 0 ) {
      if ( log_level < INDIGO_LOG_DEBUG ) {
        log_level = INDIGO_LOG_DEBUG;
      }
      continue;
    }
    if ( strcmp(argv[i], "-vvv") == 0 || strcmp(argv[i], "--enable-trace") == 0 ) {
      if ( log_level < INDIGO_LOG_TRACE ) {
        log_level = INDIGO_LOG_TRACE;
      }
      continue;
    }

    if( (strcmp(argv[i], "-T") == 0 || strcmp(argv[i], "--master-token")) == 0 ) {
      if( ++i >= argc ) {
        fprintf(stderr, "Command line error: master_token expected after %s\n", argv[i - 1]);
        return 1;
      }

      indigo_set_master_token(indigo_string_to_token(argv[i]));
      continue;
    }

    if( ( strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--acl-file")) ) {
      if( ++i >= argc ) {
        fprintf(stderr, "Command line error: file with device tokens expected after %s\n", argv[i - 1]);
        return 1;
      }

      indigo_load_device_tokens_from_file(argv[i]);
      continue;
    }
  }

  indigo_set_log_level(log_level);


  QApplication app(argc, argv);

  Q_INIT_RESOURCE(app_resources);

  app.setOrganizationName(MY_COMPANY);
  app.setApplicationName(MY_APP);
  app.setWindowIcon(QIcon(":/icons/focus.png"));

  //  QFont font("SansSerif", 16, QFont::Medium);
  //  font.setStyleHint(QFont::SansSerif);
  //  QFont font("System", 16, QFont::Medium);
  //  font.setStyleHint(QFont::System);
  //  app.setFont(font);


  QVersionNumber running_version =
      QVersionNumber::fromString(QString(qVersion()));

  QVersionNumber threshod_version(5, 13, 0);
  QString qss_resource(":qdarkstyle/style.qss");

  if (running_version >= threshod_version) {
    qss_resource = ":qdarkstyle/style-5.13.qss";
  }

  QFile f(qss_resource);
  f.open(QFile::ReadOnly | QFile::Text);
  QTextStream ts(&f);
  app.setStyleSheet(ts.readAll());
  f.close();



  MainWindow mainWindow;

  mainWindow.show();
  mainWindow.activateWindow();
  mainWindow.raise();

  return app.exec();
}

