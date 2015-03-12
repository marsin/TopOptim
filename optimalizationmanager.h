#ifndef OPTIMALIZATIONMANAGER_H
#define OPTIMALIZATIONMANAGER_H

#include <ga/ga.h>
#include <ga/GAGenome.h>
#include <ga/GAAllele.h>
#include <ga/GABaseGA.h>
#include <ga/GASStateGA.h>
#include <ga/GAScaling.h>
#include <ga/ga.h>
#include <ga/GA2DArrayGenome.h>
#include <group.h>
#include <QMutex>
#include <ioptimalizationmanager.h>

static int s_generationCounter = 0;
static long int s_processedGenomeCounter = 0;

struct GAUserData
{
  GAUserData(const configurations &p_config, const CmPartp &p_part)
    : config(p_config),
      part(p_part) {}

  configurations config;
  CmPartp part;
};


static void CheckNeighbors(const std::set<unsigned int> &neighbors, CmGroupp &grupa,
                    const std::vector<CmFacep> &faces, const GA1DArrayAlleleGenome<int> &genome,
                    std::set<unsigned int> &set, int searchMatIndex);

void static PerformConnectivityAnalysis(const GA1DArrayAlleleGenome<int> &p_genome, const CmPartp& p_part, GA1DArrayAlleleGenome<int> &p_genomeOut);

class CmOptimalizationManager : public ImOptimalizationManager
{
Q_OBJECT
public:
  CmOptimalizationManager();
  void setupOptimalization(const CmPartp &part, const configurations &conf);
  void run();
  std::vector<int> getGenome();
private:
  //float objective1D(GAGenome & c);
  void Init();

  CmPartp m_part{};
  configurations m_conf{};
  QMutex mutex{};
  std::vector<int> m_genome{};
};
typedef boost::shared_ptr<CmOptimalizationManager> CmOptimalizationManagerp;

#endif // OPTIMALIZATIONMANAGER_H
