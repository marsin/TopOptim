#ifndef CONFIGURATIONWINDOW_H
#define CONFIGURATIONWINDOW_H

#include <QtWidgets>
#include <QDialog>
#include <configurations.h>
#include <ui_configurationwindow.h>
QT_BEGIN_NAMESPACE
class QListWidget;
class QListWidgetItem;
class QStackedWidget;
QT_END_NAMESPACE


class ConfigurationWindow : public QDialog
{
  Q_OBJECT
public:
  explicit ConfigurationWindow(const configurations& config);
  ~ConfigurationWindow();

  configurations getConfig(){return m_config;}
signals:
  
public slots:
  void saveConf();
private:

  configurations m_config{};
  QTextEdit *caeFilePathTextEdit;
  QTextEdit *abaqusBatPathTextEdit;
  QTextEdit *openModelScriptPathTextEdit;
  QTextEdit *runForGenomeScriptPathTextEdit;
  QTextEdit *optimizationNetSizeTextEdit;
  QTextEdit *meshSizeTextEdit;
  QListWidget *contentsWidget;
  QStackedWidget *pagesWidget;
};

#endif // CONFIGURATIONWINDOW_H
