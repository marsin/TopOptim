
#include "configurationwindow.h"

ConfigurationWindow::ConfigurationWindow(const configurations &config) :
  m_config(config)
{
  QGroupBox *configGroup = new QGroupBox(tr("Configuration"));


  QLabel *serverLabel = new QLabel(tr("CAE file path:"));
  caeFilePathTextEdit = new QTextEdit(QString(config.caeFilePath.c_str()));
  caeFilePathTextEdit->setEnabled(false);
  caeFilePathTextEdit->setFixedHeight(25);
  QHBoxLayout *filePathLayout = new QHBoxLayout;
  filePathLayout->addWidget(serverLabel);
  filePathLayout->addWidget(caeFilePathTextEdit);

  QLabel *abaqusBatPathLabel = new QLabel(tr("Abaqus.bat path:"));
  abaqusBatPathTextEdit = new QTextEdit(QString(config.abaqusBatPath.c_str()));
  abaqusBatPathTextEdit->setFixedHeight(25);
  QHBoxLayout *abaqusBatPathLayout = new QHBoxLayout;
  abaqusBatPathLayout->addWidget(abaqusBatPathLabel);
  abaqusBatPathLayout->addWidget(abaqusBatPathTextEdit);

  QLabel *openModelScriptPathLabel = new QLabel(tr("Prepare model script path:"));
  openModelScriptPathTextEdit = new QTextEdit(QString(config.openModelScriptPath.c_str()));
  openModelScriptPathTextEdit->setFixedHeight(25);
  QHBoxLayout *openModelScriptPathLayout = new QHBoxLayout;
  openModelScriptPathLayout->addWidget(openModelScriptPathLabel);
  openModelScriptPathLayout->addWidget(openModelScriptPathTextEdit);

  QLabel *runForGenomeScriptPathLabel = new QLabel(tr("Run for genome script path:"));
  runForGenomeScriptPathTextEdit = new QTextEdit(QString(config.runForGenomeScriptPath.c_str()));
  runForGenomeScriptPathTextEdit->setFixedHeight(25);
  QHBoxLayout *runForGenomeScriptPathLayout = new QHBoxLayout;
  runForGenomeScriptPathLayout->addWidget(runForGenomeScriptPathLabel);
  runForGenomeScriptPathLayout->addWidget(runForGenomeScriptPathTextEdit);

  QLabel *netSizeLabel = new QLabel(tr("Optimization net size:"));
  optimizationNetSizeTextEdit = new QTextEdit(QString::number(config.optimizationNetSize));
  optimizationNetSizeTextEdit->setFixedHeight(25);
  QHBoxLayout *netSizeLayout = new QHBoxLayout;
  netSizeLayout->addWidget(netSizeLabel);
  netSizeLayout->setSpacing(1);
  netSizeLayout->addWidget(optimizationNetSizeTextEdit);

  QLabel *meshSizeLabel = new QLabel(tr("Mesh size:"));
  meshSizeTextEdit = new QTextEdit(QString::number(config.meshSize));
  meshSizeTextEdit->setFixedHeight(25);
  QHBoxLayout *meshSizeLayout = new QHBoxLayout;
  meshSizeLayout->addWidget(meshSizeLabel);
  meshSizeLayout->addWidget(meshSizeTextEdit);
  meshSizeLayout->setSizeConstraint(QLayout::SetMaximumSize);

  QVBoxLayout *configLayout = new QVBoxLayout;
  configLayout->addLayout(filePathLayout);
  configLayout->addLayout(abaqusBatPathLayout);
  configLayout->addLayout(openModelScriptPathLayout);
  configLayout->addLayout(runForGenomeScriptPathLayout);
  configLayout->addLayout(netSizeLayout);
  configLayout->addLayout(meshSizeLayout);
  configGroup->setLayout(configLayout);
  configGroup->adjustSize();

  QPushButton *saveButton = new QPushButton(tr("Continue"));
  connect(saveButton, SIGNAL(clicked()), this, SLOT(saveConf()));

  QHBoxLayout *buttonsLayout = new QHBoxLayout;
  buttonsLayout->addStretch(1);
  buttonsLayout->addWidget(saveButton);

  QHBoxLayout *horizontalLayout = new QHBoxLayout;
  horizontalLayout->addWidget(configGroup);


  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addLayout(horizontalLayout);
  mainLayout->setSpacing(1);
  mainLayout->addStretch(1);
  mainLayout->addLayout(buttonsLayout);
  mainLayout->setGeometry(QRect(10,10,500,300));
  setLayout(mainLayout);

  setWindowTitle(tr("Config Dialog"));
}

ConfigurationWindow::~ConfigurationWindow()
{
}

void ConfigurationWindow::saveConf()
{
  m_config.optimizationNetSize = optimizationNetSizeTextEdit->toPlainText().toFloat();
  m_config.meshSize = meshSizeTextEdit->toPlainText().toFloat();
  m_config.openModelScriptPath = openModelScriptPathTextEdit->toPlainText().toStdString();
  m_config.runForGenomeScriptPath = runForGenomeScriptPathTextEdit->toPlainText().toStdString();
  close();
}
