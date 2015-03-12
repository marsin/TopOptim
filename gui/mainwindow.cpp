#include <gui/mainwindow.h>
#include <ui_mainwindow.h>
#include <QAction>
#include <errorCodes.h>
#include <filemanager.h>
#include <QFileDialog>
#include <QtCore>
#include <stdlib.h>
#include <QtWidgets>
#include <QtConcurrent/QtConcurrentRun>
#include <configurationwindow.h>
#include <optimalizationwindow.h>
#include <optimalizationmanager.h>
#include <optimconfigwindow.h>
#include <model.h>

MainWindowOpt::MainWindowOpt(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  m_optManager(std::make_shared<CmOptimalizationManager>())
{
  connect(&mRenderTimer, SIGNAL(timeout()), this, SLOT(actionPrintModel()));
  mRenderTimer.start(500);
  ui->setupUi(this);
  ui->actionConfiguration->setDisabled(true);
  fm::FileManager::DeleteAnyFile("temp.genome");
}

MainWindowOpt::~MainWindowOpt()
{
  m_optManager->quit();
  delete ui;
}

void MainWindowOpt::SetModel(const CmModelp &model)
{
  m_model = model;  
  ui->modelView->init(m_model, m_configurations);
  if(m_setted)
  {
    ui->modelView->updateGeometry();
    ui->modelView->update();
    ui->modelView->updateGL();
  }
  else
  {
    m_setted = true;
  }
}

void MainWindowOpt::actionPrintModel()
{
  if(m_setted)
  {
    //ui->modelView->init(m_model);
  }
}


void MainWindowOpt::on_actionQuit_triggered()
{
  this->close();

}

void MainWindowOpt::on_actionOpen_triggered()
{
  int error = ERR_NO_ERROR;
  QString supportedFiles("*.cae");
  supportedFiles = tr("Abaqus Model Database (") + supportedFiles + tr(")");
  QString fileName = QFileDialog::getOpenFileName(this,tr("Open project file"),"",supportedFiles);
  m_configurations.caeFilePath = fileName.toStdString();
  fileName = fileName.replace("/", "\\").section("\\", -1).section(".", 0, 0);
  m_configurations.projectName = fileName.toStdString();
  ConfigurationWindow confWin(m_configurations);
  confWin.exec();
  m_configurations = confWin.getConfig();
  std::string confJson = "{\"Config\":{";
  confJson += "\"ModelPath\":\"" + m_configurations.caeFilePath + "\",";
  confJson += "\"NetSize\":" + QString::number(m_configurations.optimizationNetSize).toStdString() + ",";
  confJson += "\"MeshSize\":" + QString::number(m_configurations.meshSize).toStdString() + "";
  confJson += "}}";
  fm::FileManager::SaveTextToFile(confJson,"temp.conf",error);
  std::string l_command = m_configurations.abaqusBatPath + " cae noGUI=" + m_configurations.openModelScriptPath;
  QProcess exec;
  exec.start(l_command.c_str());
    if(exec.state() > 0)
    {
      std::cerr << "Command started:";
      std::cerr << l_command;
    }
    else
    {
      std::cerr << "Command fail to start:";
      std::cerr << l_command;
      return;
    }
    exec.waitForFinished();
    int exitcode = exec.exitCode();
    std::cerr << "Abaqus script exited with code: "<<exitcode;
    if(exitcode == 0)
    {
      fm::FileManager::CopyFileAndReplace("temp.model", m_configurations.projectName + fm::g_collectionExt);
      SetModel(fm::FileManager::OpenModelFile("temp.model",error));
      ui->actionConfiguration->setEnabled(true);
    }
}

void MainWindowOpt::on_actionConfiguration_triggered()
{
  OptimConfigWindow l_configWindow(m_configurations);
  l_configWindow.exec();
  m_configurations = l_configWindow.getConfig();
  fm::FileManager::SaveConfigurationsToFile(m_configurations, "configuration.log");
  m_optManager->setupOptimalization(m_model->Parts()[0], m_configurations);
  m_optManager->start();
  ui->modelView->setUpdateFaces(true, m_configurations);
}

void MainWindowOpt::updateModel()
{
//  ui->modelView->updateFaces(m_genome);
}

void MainWindowOpt::on_actionOpen_collection_triggered()
{
    int error = 0;
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open project file"),"","*.*");
    SetModel(fm::FileManager::OpenModelFile(fileName.toStdString(), error));
    std::vector<std::vector<int>> l_collection = fm::FileManager::OpenGenomeCollectionFile(fileName.toStdString(), error);
    ui->actionConfiguration->setEnabled(true);
    ui->horizontalSlider->setMaximum(l_collection.size() - 1);
    ui->horizontalSlider->setEnabled(true);
    ui->spinBox->setMaximum(l_collection.size() - 1);
    ui->spinBox->setEnabled(true);
    std::cout << "collection size: " << l_collection.size() << std::endl;
    ui->modelView->setUpdateFaces(true, m_configurations);
    ui->modelView->setModeCollectionViewer(true, l_collection);
}

void MainWindowOpt::on_horizontalSlider_valueChanged(int value)
{
    m_collectionPos = value;
    ui->spinBox->setValue(m_collectionPos);
    ui->modelView->setCollectionPosition(m_collectionPos);
}

void MainWindowOpt::on_spinBox_valueChanged(int arg1)
{
    m_collectionPos = arg1;
    ui->horizontalSlider->setValue(m_collectionPos);
    ui->modelView->setCollectionPosition(m_collectionPos);
}
