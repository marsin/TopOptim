#include "genomecollection.h"

GenomeCollection::GenomeCollection()
{
}

void GenomeCollection::insert(const std::vector<int> &p_genome, float p_fitness)
{
    std::vector<short unsigned int> l_temp(p_genome.begin(),p_genome.end());
    GenomeWithResult l_genome(std::move(l_temp), p_fitness);
    m_genomes.insert(l_genome);
}

void GenomeCollection::insert(const GA1DArrayAlleleGenome<int> &p_genome, float p_fitness)
{
    m_genomes.insert(GenomeWithResult(buildIntVector(p_genome), p_fitness));
}

bool GenomeCollection::isInCollection(std::vector<int> p_genome)
{
    return m_genomes.count(GenomeWithResult(std::vector<short unsigned int>(p_genome.begin(),p_genome.end()), 0)) > 0;
}

std::vector<short unsigned> GenomeCollection::buildIntVector(const GA1DArrayAlleleGenome<int> &p_genome)
{
    std::vector<short unsigned int> l_genome;
    for (unsigned int i = 0; i < p_genome.size(); ++i)
    {
        l_genome.push_back(p_genome[i]);
    }
    return l_genome;
}

bool GenomeCollection::isInCollection(const GA1DArrayAlleleGenome<int> &p_genome)
{
    return m_genomes.count(GenomeWithResult(buildIntVector(p_genome), 0)) > 0;
}

float GenomeCollection::getFitnessForGenome(const GA1DArrayAlleleGenome<int> &p_genome)
{
    GenomeWithResult p_result = *m_genomes.find(GenomeWithResult(buildIntVector(p_genome), 0.0));
    return p_result.value;
}
