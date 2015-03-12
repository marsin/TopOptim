#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ui_mainwindow.h>
#include <model.h>
#include <configurations.h>
#include <ioptimalizationmanager.h>
namespace Ui {
  class MainWindow;
}

class MainWindowOpt : public QMainWindow, public Ui::MainWindow
{
  Q_OBJECT

public:
  explicit MainWindowOpt(QWidget *parent = 0);
  ~MainWindowOpt();
  void SetModel(const CmModelp &model);
private slots:
  void actionPrintModel();

  void on_actionQuit_triggered();

  void on_actionOpen_triggered();

  void on_actionConfiguration_triggered();

  void on_actionOpen_collection_triggered();

  void on_horizontalSlider_valueChanged(int value);

  void on_spinBox_valueChanged(int arg1);

private:

  void updateModel();
  QFuture<void> m_threatedUpdater;
  CmModelp m_model;
  std::vector<int> m_genome;
  Ui::MainWindow *ui;
  QMenu *fileMenu;
  QMenu *toolMenu;
  QAction *openFile;
  QTimer mRenderTimer;
  std::string m_appPath;
  std::string m_scriptPath;
  configurations m_configurations{};
  std::shared_ptr<ImOptimalizationManager> m_optManager;
  bool m_setted = false;
  int m_collectionPos = 0;
};

#endif // MAINWINDOW_H
