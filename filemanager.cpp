#include <filemanager.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <errorCodes.h>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <QDir>
#include <QFile>

using namespace boost;
using std::string;

namespace fm {

CmModelp FileManager::OpenModelFile(const std::string &path, int &error)
{
  error = ERR_NO_ERROR;
  CmModelp model;
  CmPartp part = CmPartp();
  std::ifstream file;
  const char* temp = path.c_str();
  elemType reading = other;
  file.open(temp,std::ifstream::in);
  if(!file)
  {
    error = ERR_OPEN_FILE;
    return CmModelp();
  }
  while(file.good())
  {
    std::string line;
    std::vector< std::string > sequence;
    std::getline(file,line);
    if(algorithm::find_first(line,"//"))
    {
      continue;
    }
    if(algorithm::contains(line,"#Model:"))
    {
      algorithm::split(sequence,line,algorithm::is_any_of(":"));
      model = CmModelp(new CmModel(sequence[1]));
    }
    else if(boost::algorithm::contains(line,"##Part:"))
    {
      algorithm::split(sequence,line,algorithm::is_any_of(":"));
      part = CmPartp(new CmPart(sequence[1]));
    }
    else if(boost::algorithm::contains(line,"###Faces:"))
    {
      reading = faceType;
      continue;
    }
    else if(boost::algorithm::contains(line,"###Vertices:"))
    {
      reading = verticeType;
      continue;
    }
    else if(boost::algorithm::contains(line,"###Load:"))
    {
      continue;
    }
    else if(boost::algorithm::contains(line,"###BC:"))
    {
      continue;
    }
    else if(boost::algorithm::contains(line,"####LVerticesIndexList:"))
    {
      algorithm::split(sequence,line,algorithm::is_any_of(":"));
      algorithm::split(sequence,sequence[1],algorithm::is_any_of(" "));
      for(size_t it=0;it < sequence.size();it++)
      {
        if(!sequence[it].empty())
          part->AddLoadForVertex(atoi(sequence[it].c_str()),error);
      }
      continue;
    }
    else if(boost::algorithm::contains(line,"####BVerticesIndexList:"))
    {
      algorithm::split(sequence,line,algorithm::is_any_of(":"));
      algorithm::split(sequence,sequence[1],algorithm::is_any_of(" "));
      for(size_t it=0;it < sequence.size();it++)
      {
        if(!sequence[it].empty())
          part->AddBCForVertex(atoi(sequence[it].c_str()),error);
      }
      continue;
    }
    else if(reading == faceType)
    {
      algorithm::split(sequence,line,algorithm::is_any_of(" "));
      unsigned int num = atoi(sequence[0].c_str());
      std::vector<unsigned int> vertices;
      for(size_t it=1;it < sequence.size();it++)
      {
        algorithm::erase_all(sequence[it],"(");
        algorithm::erase_all(sequence[it],",");
        algorithm::erase_all(sequence[it],")");
        vertices.push_back(atoi(sequence[it].c_str()));
      }
      CmFacep face = CmFacep(new CmFace(num,vertices,error));
      face->SetMaterialIndex(1);
      if(error == ERR_NO_ERROR)
        part->AddFace(face);
    }
    else if(reading == verticeType)
    {
      algorithm::split(sequence,line,algorithm::is_any_of(" "));
      if(sequence.size() == 4)
      {
        std::vector<unsigned int> vertices;
        for(size_t it=1;it < sequence.size();it++)
        {
          algorithm::erase_all(sequence[it],"(");
          algorithm::erase_all(sequence[it],",");
          algorithm::erase_all(sequence[it],")");
          vertices.push_back(atoi(sequence[it].c_str()));
        }
        vertexp overtex = vertexp(new vertex(atoi(sequence[0].c_str()),
                                  atof(sequence[1].c_str()),
            atof(sequence[2].c_str()),
            atof(sequence[3].c_str())));
        part->AddVertex(overtex);
      }
    }
    else if(boost::algorithm::contains(line,"#Genome Collection"))
    {
        break;
    }
  }
  part->SetNumOfHoles(0);
  part->SetupNeighbors();
  model->AddPart(part);
  return model;
}

void FileManager::SaveTextToFile(const std::string &text, const std::string &fileName, int &error)
{
  std::ofstream file;
  file.open(fileName.c_str());
  if(file.is_open())
  {
    file << std::endl;
    file << text;
    file.close();
    error = ERR_NO_ERROR;
  }
  else
  {
    error = ERR_OPEN_FILE;
  }
}

void FileManager::SaveGenomeToFile(const GA1DArrayAlleleGenome<int> p_genome,
                                   const std::string &p_fileName,
                                   const std::string p_comment)
{
  std::ofstream genomeFile;
  genomeFile.open(p_fileName.c_str(), std::ios_base::app);
  if(genomeFile.is_open())
  {
    genomeFile << std::endl;
    for(unsigned int it = 0; it < p_genome.length();it++)
    {
      genomeFile << p_genome.gene(it);
      genomeFile << " ";
    }
    if(not p_comment.empty())
    {
        genomeFile << std::endl << "#" << p_comment;
    }
    genomeFile.close();
  }
}

void FileManager::SaveGenomeToFile(const std::vector<int> p_genome,
                                   const std::string &p_fileName,
                                   const std::string p_comment)
{
  std::ofstream genomeFile;
  genomeFile.open(p_fileName.c_str(), std::ios_base::app);
  if(genomeFile.is_open())
  {
    genomeFile << std::endl;
    for(auto it : p_genome)
    {
      genomeFile << it;
      genomeFile << " ";
    }
    if(not p_comment.empty())
    {
        genomeFile << std::endl << "#" << p_comment;
    }
    genomeFile.close();
  }
}

std::vector<int> FileManager::OpenGenomeFile(const std::string &p_path, int *p_error)
{
  std::ifstream file;
  std::vector<int> l_genome{};
  const char* temp = p_path.c_str();
  file.open(temp,std::ifstream::in);
  if(!file)
  {
    *p_error = ERR_OPEN_FILE;
    file.close();
    return l_genome;
  }
  while(file.good())
  {
    std::string line;
    std::vector< std::string > sequence;
    std::getline(file,line);
    algorithm::split(sequence,line,algorithm::is_any_of(" "));
    for(const std::string &l_str : sequence)
    {
      if(l_str == "1" or l_str == "0")
      {
        l_genome.push_back(atoi(l_str.c_str()));
      }
    }
  }
  file.close();
  *p_error = ERR_NO_ERROR;
  return l_genome;
}

void FileManager::DeleteAnyFile(const std::string &p_path)
{
  std::remove(p_path.c_str());
}

void FileManager::CreateFolder(const std::string &p_path)
{
  QDir qdir("");
  qdir.mkpath(p_path.c_str());
}

void FileManager::CopyFileAndReplace(const std::string &p_source, const std::string &p_destination)
{
  DeleteAnyFile(p_destination);
  QFile::copy(p_source.c_str(), p_destination.c_str());
}

void FileManager::SaveConfigurationsToFile(const configurations &p_config, const std::string &p_destination)
{
  string l_text = string("Configurations:\n") +
      string("Path to Abaqus: ") + p_config.abaqusBatPath + string("\n") +
      string("Path to model file: ") + p_config.caeFilePath + string("\n") +
      string("Run for genome script path: ") + p_config.runForGenomeScriptPath + string("\n") +
      string("Open model script path: ") + p_config.openModelScriptPath + string("\n") +
      string("Convergence percentage: ") + std::to_string(p_config.convergencePercentage) + string("\n") +
      string("Crossover probability: ") + std::to_string(p_config.crossoverProbability) + string("\n") +
      string("Elitism: ") + std::to_string(p_config.elitism) + string("\n") +
      string("Flush Frequency: ") + std::to_string(p_config.flushFrequency) + string("\n") +
      string("Generations To Convergence: ") + std::to_string(p_config.generationsToConvergence) + string("\n") +
      string("Mesh Size: ") + std::to_string(p_config.meshSize) + string("\n") +
      string("Migration Number: ") + std::to_string(p_config.migrationNumber) + string("\n") +
      string("Migration Percentage: ") + std::to_string(p_config.migrationPercentage) + string("\n") +
      string("Mutation Probability: ") + std::to_string(p_config.mutationProbability) + string("\n") +
      string("numberOfBest: ") + std::to_string(p_config.numberOfBest) + string("\n") +
      string("numberOfGenerations: ") + std::to_string(p_config.numberOfGenerations) + string("\n") +
      string("numberOfOffsprings: ") + std::to_string(p_config.numberOfOffsprings) + string("\n") +
      string("numberOfPopulations: ") + std::to_string(p_config.numberOfPopulations) + string("\n") +
      string("optimizationNetSize: ") + std::to_string(p_config.optimizationNetSize) + string("\n") +
      string("populationSize: ") + std::to_string(p_config.populationSize) + string("\n") +
      string("recordDiversity: ") + std::to_string(p_config.recordDiversity) + string("\n") +
      string("replacementNumber: ") + std::to_string(p_config.replacementNumber) + string("\n") +
      string("replacementPercentage: ") + std::to_string(p_config.replacementPercentage) + string("\n") +
      string("scoreFrequency: ") + std::to_string(p_config.scoreFrequency) + string("\n") +
      string("selectedOptimizationDebugLevel: ") + std::to_string(p_config.selectedOptimizationDebugLevel) + string("\n") +
      string("connectivityAnalysis: ") + std::to_string(p_config.connectivityAnalysis) + string("\n") +
      string("recordVideo: ") + std::to_string(p_config.recordVideo) + string("\n") +
      string("fpsForRecordings: ") + std::to_string(p_config.fpsForRecordings) + string("\n") +
      string("intervalBetweenSnapshot: ") + std::to_string(p_config.intervalBetweenSnapshot) + string("\n");
  int error = 0;
  SaveTextToFile(l_text, p_destination, error);
}

void FileManager::AppendToGenomeCollector(const configurations &p_config, const std::string &p_text, const std::string p_comment)
{
    std::ofstream l_out;
    l_out.open(p_config.projectName + g_collectionExt, std::ios_base::app);
    if(l_out.is_open())
    {
        l_out << std::endl << p_text;
        if(not p_comment.empty())
        {
            l_out << std::endl << "#" << p_comment;
        }
        l_out.close();
    }
}

void FileManager::AppendToGenomeCollector(const configurations &p_config, const GA1DArrayAlleleGenome<int> &p_genome, const std::string p_comment)
{
    SaveGenomeToFile(p_genome, p_config.projectName + g_collectionExt, p_comment);
}

void FileManager::AppendToGenomeCollector(const configurations &p_config,const std::vector<int> &p_genome, const std::string p_comment)
{
    SaveGenomeToFile(p_genome, p_config.projectName + g_collectionExt, p_comment);
}

std::vector<std::vector<int> > FileManager::OpenGenomeCollectionFile(const std::string &p_path, int p_error)
{
    std::ifstream file;
    std::vector<std::vector<int>> l_collection{};
    file.open(p_path.c_str(),std::ifstream::in);
    if(!file)
    {
      p_error = ERR_OPEN_FILE;
      file.close();
      return l_collection;
    }
    bool isCollection = false;
    while(file.good())
    {
      std::string line;
      std::getline(file,line);
      if(boost::algorithm::contains(line,"#Genome Collection"))
      {
          isCollection = true;
      }
      if(isCollection)
      {
          if((*line.begin()) != '#')
          {
              std::vector<int> l_genome{};
              std::vector< std::string > sequence;
              algorithm::split(sequence,line,algorithm::is_any_of(" "));
              for(const std::string &l_str : sequence)
              {
                if(l_str == "1" or l_str == "0")
                {
                  l_genome.push_back(atoi(l_str.c_str()));
                }
              }
              if(!l_genome.empty())
              {
                l_collection.push_back(l_genome);
              }
          }
      }
    }
    file.close();
    p_error = ERR_NO_ERROR;
    return l_collection;
}


}
