#include "gui/mainwindow.h"
#include <QApplication>
#include <boost/any.hpp>

#include <QGLWidget>
#include <QtWidgets>
#include "filemanager.h"
#include "errorCodes.h"
#include "model.h"
#include "optimalizationmanager.h"
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  MainWindowOpt w{};

  w.show();

  QGLWidget *widget = new QGLWidget(QGLFormat(QGL::SampleBuffers));
  widget->makeCurrent();
  return a.exec();
}
