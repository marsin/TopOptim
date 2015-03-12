#include "optimconfigwindow.h"
#include <memory>

OptimConfigWindow::OptimConfigWindow(const configurations &p_config) :
  m_config(p_config)
{
  QGroupBox *configGroup = new QGroupBox(tr("Configuration"));


  QLabel *numberOfPopulationsLabel = new QLabel(tr("Number of populations:"));
  numberOfPopulationsTextEdit = new QTextEdit(QString::number(p_config.numberOfPopulations));
  numberOfPopulationsTextEdit->setFixedHeight(25);
  QHBoxLayout *numberOfPopulationsLayout = new QHBoxLayout;
  numberOfPopulationsLayout->addWidget(numberOfPopulationsLabel);
  numberOfPopulationsLayout->addWidget(numberOfPopulationsTextEdit);

  QLabel *numberOfGenerationsLabel = new QLabel(tr("Number of generations:"));
  numberOfGenerationsTextEdit = new QTextEdit(QString::number(p_config.numberOfGenerations));
  numberOfGenerationsTextEdit->setFixedHeight(25);
  QHBoxLayout *numberOfGenerationsLayout = new QHBoxLayout;
  numberOfGenerationsLayout->addWidget(numberOfGenerationsLabel);
  numberOfGenerationsLayout->addWidget(numberOfGenerationsTextEdit);

  QLabel *crossoverProbabilityLabel = new QLabel(tr("Crossover probability:"));
  crossoverProbabilityTextEdit = new QTextEdit(QString::number(p_config.crossoverProbability));
  crossoverProbabilityTextEdit->setFixedHeight(25);
  QHBoxLayout *crossoverProbabilityLayout = new QHBoxLayout;
  crossoverProbabilityLayout->addWidget(crossoverProbabilityLabel);
  crossoverProbabilityLayout->addWidget(crossoverProbabilityTextEdit);

  QLabel *mutationProbabilityLabel = new QLabel(tr("Mutation probability:"));
  mutationProbabilityTextEdit = new QTextEdit(QString::number(p_config.mutationProbability));
  mutationProbabilityTextEdit->setFixedHeight(25);
  QHBoxLayout *mutationProbabilityLayout = new QHBoxLayout;
  mutationProbabilityLayout->addWidget(mutationProbabilityLabel);
  mutationProbabilityLayout->addWidget(mutationProbabilityTextEdit);

  QLabel *populationSizeLabel = new QLabel(tr("Population size:"));
  populationSizeTextEdit = new QTextEdit(QString::number(p_config.populationSize));
  populationSizeTextEdit->setFixedHeight(25);
  QHBoxLayout *populationSizeLayout = new QHBoxLayout;
  populationSizeLayout->addWidget(populationSizeLabel);
  populationSizeLayout->addWidget(populationSizeTextEdit);

  QLabel *convergencePercentageLabel = new QLabel(tr("Convergence percentage:"));
  convergencePercentageTextEdit = new QTextEdit(QString::number(p_config.convergencePercentage));
  convergencePercentageTextEdit->setFixedHeight(25);
  QHBoxLayout *convergencePercentageLayout = new QHBoxLayout;
  convergencePercentageLayout->addWidget(convergencePercentageLabel);
  convergencePercentageLayout->addWidget(convergencePercentageTextEdit);

  QLabel *flushFrequencyLabel = new QLabel(tr("Flush frequency:"));
  flushFrequencyTextEdit = new QTextEdit(QString::number(p_config.flushFrequency));
  flushFrequencyTextEdit->setFixedHeight(25);
  QHBoxLayout *flushFrequencyLayout = new QHBoxLayout;
  flushFrequencyLayout->addWidget(flushFrequencyLabel);
  flushFrequencyLayout->addWidget(flushFrequencyTextEdit);

  QLabel *generationsToConvergenceLabel = new QLabel(tr("Generations to convergence:"));
  generationsToConvergenceTextEdit = new QTextEdit(QString::number(p_config.generationsToConvergence));
  generationsToConvergenceTextEdit->setFixedHeight(25);
  QHBoxLayout *generationsToConvergenceLayout = new QHBoxLayout;
  generationsToConvergenceLayout->addWidget(generationsToConvergenceLabel);
  generationsToConvergenceLayout->addWidget(generationsToConvergenceTextEdit);

  QLabel *migrationNumberLabel = new QLabel(tr("Migration number:"));
  migrationNumberTextEdit = new QTextEdit(QString::number(p_config.migrationNumber));
  migrationNumberTextEdit->setFixedHeight(25);
  QHBoxLayout *migrationNumberLayout = new QHBoxLayout;
  migrationNumberLayout->addWidget(migrationNumberLabel);
  migrationNumberLayout->addWidget(migrationNumberTextEdit);

//  QLabel *migrationPercentageLabel = new QLabel(tr("Migration percentage:"));
//  migrationPercentageTextEdit = new QTextEdit(QString::number(p_config.migrationPercentage));
//  migrationPercentageTextEdit->setFixedHeight(25);
//  QHBoxLayout *migrationPercentageLayout = new QHBoxLayout;
//  migrationPercentageLayout->addWidget(migrationPercentageLabel);
//  migrationPercentageLayout->addWidget(migrationPercentageTextEdit);

  QLabel *numberOfBestLabel = new QLabel(tr("Number of selected best solutions:"));
  numberOfBestTextEdit = new QTextEdit(QString::number(p_config.numberOfBest));
  numberOfBestTextEdit->setFixedHeight(25);
  QHBoxLayout *numberOfBestLayout = new QHBoxLayout;
  numberOfBestLayout->addWidget(numberOfBestLabel);
  numberOfBestLayout->addWidget(numberOfBestTextEdit);

  QLabel *numberOfOffspringsLabel = new QLabel(tr("Number of offsprings:"));
  numberOfOffspringsTextEdit = new QTextEdit(QString::number(p_config.numberOfOffsprings));
  numberOfOffspringsTextEdit->setFixedHeight(25);
  QHBoxLayout *numberOfOffspringsLayout = new QHBoxLayout;
  numberOfOffspringsLayout->addWidget(numberOfOffspringsLabel);
  numberOfOffspringsLayout->addWidget(numberOfOffspringsTextEdit);

  QLabel *replacementNumberLabel = new QLabel(tr("Replacement number:"));
  replacementNumberTextEdit = new QTextEdit(QString::number(p_config.replacementNumber));
  replacementNumberTextEdit->setFixedHeight(25);
  QHBoxLayout *replacementNumberLayout = new QHBoxLayout;
  replacementNumberLayout->addWidget(replacementNumberLabel);
  replacementNumberLayout->addWidget(replacementNumberTextEdit);

  QLabel *replacementPercentageLabel = new QLabel(tr("Replacement percentage:"));
  replacementPercentageTextEdit = new QTextEdit(QString::number(p_config.replacementPercentage));
  replacementPercentageTextEdit->setFixedHeight(25);
  QHBoxLayout *replacementPercentageLayout = new QHBoxLayout;
  replacementPercentageLayout->addWidget(replacementPercentageLabel);
  replacementPercentageLayout->addWidget(replacementPercentageTextEdit);

  QLabel *scoreFrequencyLabel = new QLabel(tr("Score frequency:"));
  scoreFrequencyTextEdit = new QTextEdit(QString::number(p_config.scoreFrequency));
  scoreFrequencyTextEdit->setFixedHeight(25);
  QHBoxLayout *scoreFrequencyLayout = new QHBoxLayout;
  scoreFrequencyLayout->addWidget(scoreFrequencyLabel);
  scoreFrequencyLayout->addWidget(scoreFrequencyTextEdit);

  QLabel *debugLevelLabel = new QLabel(tr("Optimization debug level:"));
  debugLevelDropDown = new QComboBox();
  debugLevelDropDown->setFixedHeight(25);
  debugLevelDropDown->addItems(QStringList{"No debug", "Best for generation", "Full debug"});
  debugLevelDropDown->setCurrentIndex(p_config.selectedOptimizationDebugLevel);
  QHBoxLayout *debugLevelLayout = new QHBoxLayout;
  debugLevelLayout->addWidget(debugLevelLabel);
  debugLevelLayout->addWidget(debugLevelDropDown);

  QLabel *elitismLabel = new QLabel(tr("Elitism:"));
  elitismCheckBox = new QCheckBox();
  elitismCheckBox->setChecked(m_config.elitism);
  elitismCheckBox->setFixedHeight(25);
  QHBoxLayout *elitismLayout = new QHBoxLayout();
  elitismLayout->addWidget(elitismLabel);
  elitismLayout->addWidget(elitismCheckBox);

  QLabel *recordDiversityLabel = new QLabel(tr("Record diversity:"));
  recordDiversityCheckBox = new QCheckBox();
  recordDiversityCheckBox->setChecked(m_config.recordDiversity);
  recordDiversityCheckBox->setFixedHeight(25);
  QHBoxLayout *recordDiversityLayout = new QHBoxLayout();
  recordDiversityLayout->addWidget(recordDiversityLabel);
  recordDiversityLayout->addWidget(recordDiversityCheckBox);

  QLabel *connAnalysisLabel = new QLabel(tr("Connectivity analysis:"));
  connAnalysisCheckBox = new QCheckBox();
  connAnalysisCheckBox->setChecked(m_config.connectivityAnalysis);
  connAnalysisCheckBox->setFixedHeight(25);
  QHBoxLayout *connAnalysisLayout = new QHBoxLayout();
  connAnalysisLayout->addWidget(connAnalysisLabel);
  connAnalysisLayout->addWidget(connAnalysisCheckBox);

  QLabel *recordVideoLabel = new QLabel(tr("Record video of GA process:"));
  recordVideoCheckBox = new QCheckBox();
  recordVideoCheckBox->setChecked(m_config.recordVideo);
  recordVideoCheckBox->setFixedHeight(25);
  QHBoxLayout *recordVideoLayout = new QHBoxLayout();
  recordVideoLayout->addWidget(recordVideoLabel);
  recordVideoLayout->addWidget(recordVideoCheckBox);

  QLabel *shutdownWhenDoneLabel = new QLabel(tr("Shutdown Computer after optimization:"));
  shutdownWhenDoneCheckBox = new QCheckBox();
  shutdownWhenDoneCheckBox->setChecked(m_config.shutdownWhenDone);
  shutdownWhenDoneCheckBox->setFixedHeight(25);
  QHBoxLayout *shutdownWhenDoneLayout = new QHBoxLayout();
  shutdownWhenDoneLayout->addWidget(shutdownWhenDoneLabel);
  shutdownWhenDoneLayout->addWidget(shutdownWhenDoneCheckBox);

  QLabel *fpsForRecordingsLabel = new QLabel(tr("FPS of recording:"));
  fpsForRecordingsTextEdit = new QTextEdit(QString::number(p_config.fpsForRecordings));
  fpsForRecordingsTextEdit->setFixedHeight(25);
  QHBoxLayout *fpsForRecordingsLayout = new QHBoxLayout;
  fpsForRecordingsLayout->addWidget(fpsForRecordingsLabel);
  fpsForRecordingsLayout->addWidget(fpsForRecordingsTextEdit);

  QLabel *intervalBetweenSnapshotLabel = new QLabel(tr("Interval between snapshots:"));
  intervalBetweenSnapshotTextEdit = new QTextEdit(QString::number(p_config.intervalBetweenSnapshot));
  intervalBetweenSnapshotTextEdit->setFixedHeight(25);
  QHBoxLayout *intervalBetweenSnapshotLayout = new QHBoxLayout;
  intervalBetweenSnapshotLayout->addWidget(intervalBetweenSnapshotLabel);
  intervalBetweenSnapshotLayout->addWidget(intervalBetweenSnapshotTextEdit);


  QVBoxLayout *configLayout = new QVBoxLayout;
  configLayout->addLayout(numberOfPopulationsLayout);
  configLayout->addLayout(numberOfGenerationsLayout);
  configLayout->addLayout(crossoverProbabilityLayout);
  configLayout->addLayout(mutationProbabilityLayout);
  configLayout->addLayout(populationSizeLayout);
  configLayout->addLayout(convergencePercentageLayout);
  configLayout->addLayout(flushFrequencyLayout);
  configLayout->addLayout(generationsToConvergenceLayout);
  configLayout->addLayout(migrationNumberLayout);
//  configLayout->addLayout(migrationPercentageLayout);
  configLayout->addLayout(numberOfOffspringsLayout);
  configLayout->addLayout(numberOfBestLayout);
  configLayout->addLayout(replacementNumberLayout);
  configLayout->addLayout(replacementPercentageLayout);
  configLayout->addLayout(scoreFrequencyLayout);
  configLayout->addLayout(debugLevelLayout);
  configLayout->addLayout(elitismLayout);
  configLayout->addLayout(recordDiversityLayout);
  configLayout->addLayout(connAnalysisLayout);
  configLayout->addLayout(recordVideoLayout);
  configLayout->addLayout(shutdownWhenDoneLayout);
  configLayout->addLayout(fpsForRecordingsLayout);
  configLayout->addLayout(intervalBetweenSnapshotLayout);
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

OptimConfigWindow::~OptimConfigWindow()
{
}

void OptimConfigWindow::saveConf()
{
  m_config.numberOfPopulations = numberOfPopulationsTextEdit->toPlainText().toFloat();
  m_config.numberOfGenerations = numberOfGenerationsTextEdit->toPlainText().toFloat();
  m_config.convergencePercentage = convergencePercentageTextEdit->toPlainText().toFloat();
  m_config.crossoverProbability = crossoverProbabilityTextEdit->toPlainText().toFloat();
  m_config.elitism = elitismCheckBox->isChecked();
  m_config.flushFrequency = flushFrequencyTextEdit->toPlainText().toInt();
  m_config.generationsToConvergence = generationsToConvergenceTextEdit->toPlainText().toInt();
  m_config.migrationNumber = migrationNumberTextEdit->toPlainText().toInt();
//  m_config.migrationPercentage = migrationPercentageTextEdit->toPlainText().toFloat();
  m_config.mutationProbability = mutationProbabilityTextEdit->toPlainText().toFloat();
  m_config.numberOfBest = numberOfBestTextEdit->toPlainText().toInt();
  m_config.numberOfGenerations = numberOfGenerationsTextEdit->toPlainText().toInt();
  m_config.numberOfOffsprings = numberOfOffspringsTextEdit->toPlainText().toInt();
  m_config.numberOfPopulations = numberOfPopulationsTextEdit->toPlainText().toInt();
  m_config.populationSize = populationSizeTextEdit->toPlainText().toInt();
  m_config.recordDiversity = recordDiversityCheckBox->isChecked();
  m_config.recordVideo = recordVideoCheckBox->isChecked();
  m_config.shutdownWhenDone = shutdownWhenDoneCheckBox->isChecked();
  m_config.replacementNumber = replacementNumberTextEdit->toPlainText().toInt();
  m_config.replacementPercentage = replacementPercentageTextEdit->toPlainText().toFloat();
  m_config.scoreFrequency = scoreFrequencyTextEdit->toPlainText().toInt();
  m_config.selectedOptimizationDebugLevel =
      static_cast<optimizationDebugLevel>(debugLevelDropDown->currentIndex());
  m_config.fpsForRecordings = fpsForRecordingsTextEdit->toPlainText().toDouble();
  m_config.intervalBetweenSnapshot = intervalBetweenSnapshotTextEdit->toPlainText().toInt();
  close();
}



