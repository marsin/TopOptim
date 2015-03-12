#ifndef OPTIMALIZATIONGAL_H
#define OPTIMALIZATIONGAL_H

#include <ioptimalizationmanager.h>
#include <FitnessComparators.h>

class fitness : public GaFitnessOperation
{
public:
    fitness(){}
};



class CmOptimalizationGAL : public ImOptimalizationManager
{
public:
    CmOptimalizationGAL();
};

#endif // OPTIMALIZATIONGAL_H
