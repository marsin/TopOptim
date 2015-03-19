#include <optimalizationmanager.h>
#include <filemanager.h>
#include <errorCodes.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <QProcess>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <fstream>
#include <QtConcurrent/QtConcurrentRun>
#include <genomecollection.h>

std::string itos(long n){
  std::stringstream stream;
  stream <<n;
  return stream.str();
}

float objective1D(GAGenome &);

/* ----------------------------------------------------------------------------
   Operator definitions
---------------------------------------------------------------------------- */
// The random initializer sets the elements of the array based on the alleles
// set.  We choose randomly the allele for each element.
template <class ARRAY_TYPE> void
GA1DArrayAlleleGenome<ARRAY_TYPE>::UniformInitializerWithConectivityAnalisis(GAGenome & c)
{
  int error;
  GA1DArrayAlleleGenome<ARRAY_TYPE> &child=
    DYN_CAST(GA1DArrayAlleleGenome<ARRAY_TYPE> &, c);
  GAUserData l_userData = *(GAUserData*)child.userData();
  CmPartp part = l_userData.part;
  child.resize(GAGenome::ANY_SIZE); // let chrom resize if it can
  std::set<unsigned int> LoadsSet = part->GetAllLoadsIndex();
  std::set<unsigned int> BCsSet = part->GetAllBCsIndex();

  bool isGenomeOk = false;
  while(!isGenomeOk)
  {
    for(int i=child.length()-1; i>=0; i--)
      child.gene(i, child.alleleset(i).allele());
    for(std::set<unsigned int>::iterator it=LoadsSet.begin();
        it != LoadsSet.end(); ++it  )
    {
      if(child.gene(*it) == 0)
      {
        child.gene(*it,1);
      }
    }
    for(std::set<unsigned int>::iterator it=BCsSet.begin();
        it != BCsSet.end(); ++it  )
    {
      if(child.gene(*it) == 0)
      {
        child.gene(*it,1);
      }
    }
    std::vector<CmGroupp> groups;
    std::set<unsigned int> toCheck;
    for(unsigned int i = 0; i<(part)->Faces().size();i++)
    {
      toCheck.insert(i);
    }
    {
      std::vector<CmFacep> faces = (part)->Faces();
      std::set<unsigned int>::iterator cIt;
      unsigned int groupIndex = 0;
      std::set<unsigned int> saved;
      while(toCheck.size()>0)
      {
        cIt = toCheck.begin();
        CmGroupp group = CmGroupp(new CmGroup());
        if(child.gene(*cIt)>0)
        {
          group->AddMember(*cIt);
          std::set<unsigned int> neighbors = faces[*cIt]->GetNeighbors();
          toCheck.erase(cIt);
          toCheck.insert(saved.begin(),saved.end());
          CheckNeighbors(neighbors,group,faces,child,toCheck);
          if(group->GetMembers().size()>1 || group->GetNeighbors().size()>0)
          {
            group->SetIndex(groupIndex);
            groups.push_back(group);
            groupIndex++;
          }
        }
        else
        {
          saved.insert(*cIt);
          toCheck.erase(cIt);
        }
      }
    }


    std::set<std::pair<unsigned int,unsigned int> >connectedGroups;
    for(std::vector<CmGroupp>::iterator git=groups.begin();git!=groups.end();git++)
    {
      for(std::vector<CmGroupp>::iterator git2=groups.begin();git2!=groups.end();git2++)
      {
        //        if(!(connectedGroups.find(std::make_pair<unsigned int,unsigned int>((*git)->GetIndex(),(*git2)->GetIndex())) != connectedGroups.end()))
        {
          if((*git)->GetIndex() != (*git2)->GetIndex())
          {
            std::set<unsigned int> neighbors = ((*git)->GetNeighbors());
            std::set<unsigned int> neighbors2 = ((*git2)->GetNeighbors());
            for(std::set<unsigned int>::iterator nit=neighbors.begin();nit!=neighbors.end();nit++)
            {
              if(neighbors2.find(*nit) != neighbors2.end())
              {
                int temp=*nit;
                child.gene(*nit,1);
                //(*git)->RemoveNeighbor(*nit);
                //(*git2)->RemoveNeighbor(*nit);

                //                    connectedGroups.insert(std::make_pair<unsigned int,unsigned int>((*git)->GetIndex(),(*git2)->GetIndex()));
                //                    connectedGroups.insert(std::make_pair<unsigned int,unsigned int>((*git2)->GetIndex(),(*git)->GetIndex()));
                break;
              }
            }
          }
        }
      }
    }
    groups.clear();
    toCheck.clear();
    for(unsigned int i = 0; i<(part)->Faces().size();i++)
    {
      toCheck.insert(i);
    }
    {
      std::vector<CmFacep> faces = (part)->Faces();
      std::set<unsigned int>::iterator cIt;
      unsigned int groupIndex = 0;
      while(toCheck.size()>0)
      {
        cIt = toCheck.begin();
        CmGroupp group = CmGroupp(new CmGroup());
        group->AddMember(*cIt);
        std::set<unsigned int> neighbors = faces[*cIt]->GetNeighbors();
        toCheck.erase(cIt);


        CheckNeighbors(neighbors,group,faces,child,toCheck);
        if(group->GetMembers().size() > 1 or group->GetNeighbors().size() > 0)
        {
          unsigned int contains = 0;
          for(std::set<unsigned int>::iterator lit = LoadsSet.begin();
              lit != LoadsSet.end(); ++lit  )
          {
            if(group->MembersContians(*lit))
            {
              contains++;
            }
          }
          for(std::set<unsigned int>::iterator bit=BCsSet.begin();
              bit != BCsSet.end(); ++bit  )
          {
            if(group->MembersContians(*bit))
            {
              contains++;
            }
          }
          if(contains > 0)
          {
            group->SetIndex(groupIndex);
            groups.push_back(group);
            groupIndex++;
          }
          else
          {
            std::set<unsigned int> members = group->GetMembers();
            for(std::set<unsigned int>::iterator grit=members.begin();grit!=members.end();grit++)
            {
              child.gene(*grit,0);
            }
          }
        }
      }
    }
    int numOfGroups = groups.size();
    if (numOfGroups == 1)
    {
      isGenomeOk = true;
    }
  }
}


template <class ARRAY_TYPE> void
GA1DArrayAlleleGenome<ARRAY_TYPE>::UniformInitializerWithConectivityAnalisis_2(GAGenome &p_genome)
{
  GA1DArrayAlleleGenome<ARRAY_TYPE> &l_children =
    DYN_CAST(GA1DArrayAlleleGenome<ARRAY_TYPE> &, p_genome);
  GAUserData l_userData = *(GAUserData*)l_children.userData();
  CmPartp l_part = l_userData.part;
  l_children.resize(GAGenome::ANY_SIZE); // let chrom resize if it can
  std::set<unsigned int> l_loadsSet = l_part->GetAllLoadsIndex();
  std::set<unsigned int> l_bcsSet = l_part->GetAllBCsIndex();

  bool l_isGenomeOk = false;
  while(!l_isGenomeOk)
  {
    for(int i = l_children.length() - 1; i >= 0; --i)
    {
      l_children.gene(i, l_children.alleleset(i).allele());
    }

    for(unsigned int l_faceUnderLoad : l_loadsSet)
    {
      l_children.gene(l_faceUnderLoad, 1);
    }

    for(unsigned int l_faceUnderBC : l_bcsSet)
    {
      l_children.gene(l_faceUnderBC, 1);
    }

    unsigned int l_firstLoadPosition = *l_loadsSet.begin();
    CmGroupp l_group{boost::make_shared<CmGroup>()};
    l_group->AddMember(l_firstLoadPosition);
    std::vector<CmFacep> l_faces = l_part->Faces();
    std::set<unsigned int> l_toCheck = l_faces[l_firstLoadPosition]->GetNeighbors();
    std::set<unsigned int> l_checked;
    while(l_toCheck.size() != 0)
    {
      unsigned int l_tmp = *l_toCheck.begin();
      if(l_children.gene(l_tmp) == 1)
      {
        l_group->AddMember(l_tmp);
        std::set<unsigned int> l_neighbors = l_faces[l_tmp]->GetNeighbors();
        for(unsigned int l_neighbor : l_neighbors)
        {
          if(l_checked.count(l_neighbor) == 0)
          {
            l_toCheck.insert(l_neighbor);
          }
        }
      }
      l_checked.insert(l_tmp);
      l_toCheck.erase(l_tmp);
    }
    l_isGenomeOk = true;
    for(unsigned int l_faceUnderLoad : l_loadsSet)
    {
      if(!l_group->MembersContians(l_faceUnderLoad))
      {
        l_isGenomeOk = false;
      }
    }

    for(unsigned int l_faceUnderBC : l_bcsSet)
    {
      if(!l_group->MembersContians(l_faceUnderBC))
      {
        l_isGenomeOk = false;
      }
    }
  }
}

CmOptimalizationManager::CmOptimalizationManager()
{

}

void CmOptimalizationManager::setupOptimalization(const CmPartp &part, const configurations &conf)
{
  QMutexLocker locker(&mutex);
  m_part = part;
  m_conf = conf;
}

void CmOptimalizationManager::Init()
{
  unsigned int l_seed = 0;
  // TODO: make aset auto settable
  fm::FileManager::DeleteAnyFile(m_conf.projectName);
  int aset[] = {0,1,0,1};
  GAAlleleSet<int> alleles(2,aset);
  GAUserData l_userData(m_conf, m_part);
  GA1DArrayAlleleGenome<int> genome(m_part->Faces().size(), alleles, objective1D, &l_userData);
  //genome.initializer(GA1DArrayAlleleGenome<int>::UniformInitializerWithConectivityAnalisis);
  genome.initializer(GA1DArrayAlleleGenome<int>::UniformInitializerWithConectivityAnalisis_2);
  genome.mutator(GA1DArrayAlleleGenome<int>::FlipMutator);
  genome.crossover(GA1DArrayAlleleGenome<int>::OnePointCrossover);
//  genome.initializer(GA1DArrayAlleleGenome<int>::UniformInitializer);


//  if(m_conf.selectedOptimizationDebugLevel != optimizationDebugLevel::noDebug)
//  {
//    fm::FileManager::CreateFolder("TopOptimDebug");
//  }

  GASteadyStateGA ga(genome);

  GASigmaTruncationScaling trunc;
  ga.scaling(trunc);
  GATournamentSelector selector;
  ga.selector(selector);

  ga.set(gaNpMigration, m_conf.migrationPercentage);
  ga.convergence();
  ga.set(gaNpConvergence, m_conf.convergencePercentage);
  ga.set(gaNnConvergence, m_conf.generationsToConvergence);
  ga.set(gaNnReplacement, m_conf.replacementNumber);
  ga.set(gaNscoreFrequency, m_conf.scoreFrequency);
  ga.set(gaNflushFrequency, m_conf.flushFrequency);
  ga.set(gaNelitism, m_conf.elitism);
  ga.set(gaNrecordDiversity, m_conf.recordDiversity);
  ga.set(gaNnMigration, m_conf.migrationNumber);
  ga.populationSize(m_conf.populationSize);
  ga.pCrossover(m_conf.crossoverProbability);
  ga.pMutation(m_conf.mutationProbability);
  ga.nGenerations(m_conf.numberOfGenerations);
  ga.set(gaNnPopulations, m_conf.numberOfPopulations);
  ga.set(gaNnOffspring, m_conf.numberOfOffsprings);
  ga.pReplacement(m_conf.replacementPercentage);
  ga.nBestGenomes(m_conf.numberOfBest);
  ga.minimaxi(GAGeneticAlgorithm::MAXIMIZE);
  std::cout << "evolving...";
  //ga.evolve();
  //std::cout << ga.statistics() << std::endl;
  s_generationCounter = 1;
  fm::FileManager::AppendToGenomeCollector(m_conf, std::string("\n\n"));
  fm::FileManager::AppendToGenomeCollector(m_conf, "#Genome Collection\n");
  ga.initialize(l_seed);
  while(!ga.done())
  {
    ga.step();
    std::cout << "." << ga.generation(); std::cout.flush();
    GA1DArrayAlleleGenome<int> & bestGenome = (GA1DArrayAlleleGenome<int> &)ga.statistics().bestIndividual(0);
    std::cout << ".best.fitness: " << bestGenome.fitness(); std::cout.flush();
    std::cout << ".best.score: " << bestGenome.score(); std::cout.flush();
    fm::FileManager::AppendToGenomeCollector(m_conf, "#Generation number: " + std::to_string(s_generationCounter) + "\n" +
                                                     "#Best score: " + std::to_string(bestGenome.score()) + "\n");
    s_generationCounter += 1;
  }
  int best = ga.nBestGenomes();
  //GAStatistics statistics = ga.statistics();
  for(int i = 0; i < m_conf.numberOfBest; ++i)
  {
    GA1DArrayAlleleGenome<int> & bestGenome = (GA1DArrayAlleleGenome<int> &)ga.statistics().bestIndividual(i);
    fm::FileManager::SaveGenomeToFile(bestGenome, "final_" + itos(i));
  }

  std::cout << "Best Genome: " << best;
  std::cout << "done!!";
  if(m_conf.shutdownWhenDone)
  {
      std::cout << "Shuting down";
#ifdef _WIN32
      system("shutdown -s");
      system("shutdown /s");
#endif
#ifdef _UNIX
      system("shutdown -P now");
#endif
  }
}

void CmOptimalizationManager::run()
{
  Init();
}

std::vector<int> CmOptimalizationManager::getGenome()
{
  QMutexLocker locker(&mutex);
  return m_genome;
}

void CheckNeighbors(const std::set<unsigned int> &neighbors, CmGroupp &grupa,
                    const std::vector<CmFacep> &faces, const GA1DArrayAlleleGenome<int> &genome,
                    std::set<unsigned int> &set, int searchMatIndex = -1)
{
  std::set<unsigned int>::iterator nIt;
  for(nIt=neighbors.begin();nIt!=neighbors.end();++nIt)
  {
    if(searchMatIndex == -1 && nIt != neighbors.end())
    {
      if(genome.gene(*nIt) > 0)
      {
        if(set.find(*nIt) != set.end())
        {
          grupa->AddMember(*nIt);
          std::set<unsigned int> neighbors = faces[*nIt]->GetNeighbors();
          set.erase(*nIt);
          CheckNeighbors(neighbors,grupa,faces,genome,set);
        }
      }
      else
      {
        grupa->AddNeighbor(*nIt);
      }
    }
    else
    {
      if(genome.gene(*nIt) == searchMatIndex)
      {
        if(set.find(*nIt) != set.end())
        {
          grupa->AddMember(*nIt);
          std::set<unsigned int> neighbors = faces[*nIt]->GetNeighbors();
          set.erase(*nIt);
          CheckNeighbors(neighbors,grupa,faces,genome,set);
        }
      }
      else
      {
        grupa->AddNeighbor(*nIt);
      }
    }
  }
}


float objective1D(GAGenome & c)
{
  GA1DArrayAlleleGenome<int> & genome = (GA1DArrayAlleleGenome<int> &)c;
  GAUserData l_userData = *(GAUserData*)genome.userData();
  GA1DArrayAlleleGenome<int> l_genomeOut = genome;
  GenomeCollection l_genomeCollection{};
  float value=0.0;
  for(auto l_load : l_userData.part->GetAllLoadsIndex())
  {
      genome.gene(l_load, 1);
  }
  for(auto l_bc : l_userData.part->GetAllBCsIndex())
  {
      genome.gene(l_bc, 1);
  }
  if(l_userData.config.connectivityAnalysis)
  {
      PerformConnectivityAnalysis(genome, l_userData.part, l_genomeOut);
  }
  fm::FileManager::DeleteAnyFile("temp.genome");
  fm::FileManager::SaveGenomeToFile(l_genomeOut, "temp.genome");

  std::cerr << "generation: " << s_generationCounter << std::endl;

  if (not l_genomeCollection.isInCollection(l_genomeOut))
  {
      QProcess exec;
      std::string appPath = l_userData.config.abaqusBatPath;
      std::string scriptPath = l_userData.config.runForGenomeScriptPath;
      std::string command = appPath + " cae noGUI=" + scriptPath;
      exec.start(command.c_str());
      exec.waitForFinished();
      int exitcode = exec.exitCode();
      if (exitcode != 0)
      {
        std::cerr << "script failed";
        return 0;
      }
      std::ifstream resultFile;
      resultFile.open("temp.genomeResult");
      if(!resultFile)
      {
        std::cerr << "error opening file";
        return 0;
      }
      while(resultFile.good())
      {
        std::string line;
        std::getline(resultFile,line);
        value = atof(line.c_str());
        break;
      }
      l_genomeCollection.insert(l_genomeOut, value);
      std::cerr << l_genomeCollection.getFitnessForGenome(l_genomeOut);
  }
  s_processedGenomeCounter += 1;
  fm::FileManager::AppendToGenomeCollector(l_userData.config, l_genomeOut, " generation: " +
                                                                           std::to_string(s_generationCounter) +
                                                                           " : genome: " +
                                                                           std::to_string(s_processedGenomeCounter) +
                                                                           " ; fitness: " +
                                                                           std::to_string(value));
//  if(l_userData.config.selectedOptimizationDebugLevel == optimizationDebugLevel::fullDebug)
//  {
//    fm::FileManager::CopyFileAndReplace("temp.genome", "TopOptimDebug/genome_"
//                          + QString::number(s_generationCounter).toStdString() + "_"
//                          + QString::number(value).toStdString());
//  }

  std::cerr << value;
  return(value);
}


void PerformConnectivityAnalysis(const GA1DArrayAlleleGenome<int>& p_genome, const CmPartp& p_part, GA1DArrayAlleleGenome<int> &p_genomeOut)
{
    std::vector<CmGroupp> groups;
    std::set<unsigned int> toCheck;
    std::set<unsigned int> LoadsSet = p_part->GetAllLoadsIndex();
    std::set<unsigned int> BCsSet = p_part->GetAllBCsIndex();
    for(unsigned int i = 0; i < p_part->Faces().size(); ++i)
    {
      toCheck.insert(i);
    }
    {
      std::vector<CmFacep> faces = p_part->Faces();
      std::set<unsigned int>::iterator cIt;
      unsigned int groupIndex = 0;
      while(toCheck.size() > 0)
      {
        cIt = toCheck.begin();
        CmGroupp group = CmGroupp(new CmGroup());
        group->AddMember(*cIt);
        std::set<unsigned int> neighbors = faces[*cIt]->GetNeighbors();
        toCheck.erase(cIt);


        CheckNeighbors(neighbors,group,faces,p_genome,toCheck);
        if(group->GetMembers().size() > 1 or group->GetNeighbors().size() > 0)
        {
          unsigned int contains = 0;
          for(std::set<unsigned int>::iterator lit = LoadsSet.begin();
              lit != LoadsSet.end(); ++lit  )
          {
            if(group->MembersContians(*lit))
            {
              contains++;
            }
          }
          for(std::set<unsigned int>::iterator bit=BCsSet.begin();
              bit != BCsSet.end(); ++bit  )
          {
            if(group->MembersContians(*bit))
            {
              contains++;
            }
          }
          if(contains > 0)
          {
            group->SetIndex(groupIndex);
            groups.push_back(group);
            groupIndex++;
          }
          else
          {
            std::set<unsigned int> members = group->GetMembers();
            for(auto grit : members)
            {
              p_genomeOut[grit] = 0;
            }
          }
        }
      }
    }

}

