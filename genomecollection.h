#pragma once
#include <set>
#include <vector>
#include <ga/GA1DArrayGenome.h>

struct GenomeWithResult
{
    bool operator< (const GenomeWithResult &p_right) const
    {
        return this->genome < p_right.genome;
    }
    GenomeWithResult(const std::vector<unsigned short int> &p_genome, float p_value) :
        genome(p_genome),
        value(p_value) {}

    std::vector<unsigned short int> genome;
    float value;
};

class GenomeCollection
{
public:
    GenomeCollection();
    void insert(const std::vector<int> &p_genome, float p_fitness);
    void insert(const GA1DArrayAlleleGenome<int> &p_genome, float p_fitness);
    bool isInCollection(std::vector<int> p_genome);
    bool isInCollection(const GA1DArrayAlleleGenome<int> &p_genome);
    float getFitnessForGenome(const GA1DArrayAlleleGenome<int> &p_genome);
private:
    std::vector<unsigned short> buildIntVector(const GA1DArrayAlleleGenome<int> &p_genome);
    std::set<GenomeWithResult> m_genomes{};
};
