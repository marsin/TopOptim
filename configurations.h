#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H
#include <string>

enum optimizationDebugLevel{noDebug, bestFromGeneration, fullDebug};

struct configurations
{
  configurations();
  std::string caeFilePath = "G:\\Temp\\rectangle02\\rectangle02.cae";
  std::string abaqusBatPath = "J:\\SIMULIA\\Abaqus\\Commands\\abaqus.bat";
  std::string openModelScriptPath = "D:\\Python_for_Abaqus\\openmodel.py";
  std::string runForGenomeScriptPath = "D:\\Python_for_Abaqus\\runforgenome.py";
  float optimizationNetSize = 2;
  float meshSize = 1;
  optimizationDebugLevel selectedOptimizationDebugLevel = fullDebug;
  bool recordVideo = false;
  double fpsForRecordings = 4.0;
  int intervalBetweenSnapshot = 1;
  std::string projectName = "genomeCollection";
  bool shutdownWhenDone = false;

  //Optimization parameters
  // most of values are default as described in
  // http://lancet.mit.edu/galib-2.4/API.html
  int populationSize = 100;
  float crossoverProbability = 0.95;
  float mutationProbability = 0.01;
  int numberOfGenerations = 400;
  int numberOfPopulations = 30;
  int numberOfOffsprings = 2;
  float migrationPercentage = 0.1;
  int migrationNumber = 5;
  float convergencePercentage = 0.25; // zbieżność
  int generationsToConvergence = 20; // pokolenia do przeprowadzenia zbieżności
  float replacementPercentage = 0.0;
  int replacementNumber = 5;
  int numberOfBest = 5;
  int scoreFrequency = 1;
  int flushFrequency = 0;
  bool elitism = true;
  bool recordDiversity = false;
  bool connectivityAnalysis = true;

};

#endif // CONFIGURATIONS_H
