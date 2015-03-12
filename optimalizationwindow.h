#ifndef OPTIMALIZATIONWINDOW_H
#define OPTIMALIZATIONWINDOW_H
#include <configurations.h>
#include <QDialog>

class OptimalizationWindow : public QDialog
{
  Q_OBJECT
public:
  OptimalizationWindow(const configurations& config);
  ~OptimalizationWindow();
  configurations getConfig(){return m_config;}
public slots:
  void saveAndClose();
private:
  configurations m_config{};
};

#endif // OPTIMALIZATIONWINDOW_H
