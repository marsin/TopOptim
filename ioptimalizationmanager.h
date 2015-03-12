#ifndef IOPTIMALIZATIONMANAGER_H
#define IOPTIMALIZATIONMANAGER_H
#include <model.h>
#include <configurations.h>
#include <QThread>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

class ImOptimalizationManager : public QThread
{
Q_OBJECT
public:
  virtual void setupOptimalization(const CmPartp &part, const configurations &conf) = 0;
  virtual void run() = 0;
  virtual std::vector<int> getGenome() = 0;
};


#endif // IOPTIMALIZATIONMANAGER_H
