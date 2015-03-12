#ifndef OPTIMCONFIGWINDOW_H
#define OPTIMCONFIGWINDOW_H

#include <QtWidgets>
#include <QDialog>
#include <configurations.h>
#include <memory>
QT_BEGIN_NAMESPACE
class QListWidget;
class QListWidgetItem;
class QStackedWidget;
QT_END_NAMESPACE

class OptimConfigWindow : public QDialog
{
  Q_OBJECT
public:
  explicit OptimConfigWindow(const configurations& p_config);
  ~OptimConfigWindow();
  configurations getConfig(){return m_config;}

signals:
public slots:
  void saveConf();
private:
  configurations m_config{};
  QTextEdit *numberOfPopulationsTextEdit;
  QTextEdit *numberOfGenerationsTextEdit;
  QTextEdit *crossoverProbabilityTextEdit;
  QTextEdit *mutationProbabilityTextEdit;
  QTextEdit *populationSizeTextEdit;
  QTextEdit *convergencePercentageTextEdit;
  QTextEdit *flushFrequencyTextEdit;
  QTextEdit *generationsToConvergenceTextEdit;
  QTextEdit *migrationNumberTextEdit;
  QTextEdit *migrationPercentageTextEdit;
  QTextEdit *numberOfBestTextEdit;
  QTextEdit *numberOfOffspringsTextEdit;
  QTextEdit *replacementNumberTextEdit;
  QTextEdit *replacementPercentageTextEdit;
  QTextEdit *scoreFrequencyTextEdit;
  QComboBox *debugLevelDropDown;
  QCheckBox *elitismCheckBox;
  QCheckBox *recordDiversityCheckBox;
  QCheckBox *connAnalysisCheckBox;
  QCheckBox *recordVideoCheckBox;
  QCheckBox *shutdownWhenDoneCheckBox;
  QTextEdit *fpsForRecordingsTextEdit;
  QTextEdit *intervalBetweenSnapshotTextEdit;
};

#endif
