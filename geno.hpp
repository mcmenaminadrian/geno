// geno.h
// model recessive genes

#include <iostream>
#include <vector>
#include "creature.hpp"

class Geneworld
{
    private:
    const unsigned int initialPopulation;
    unsigned int currentPopulation;
    const double initialRecessiveProportion;
    double currentRecessiveProportion;
    double currentRecessivePairs;
    unsigned int currentGeneration;
    const double normalFertility;
    const double normalRecessiveFertility;
    const double panicFertility;
    const double panicRecessiveFertility;
    const double badYearRate;

    std::vector<Creature> organisms;

    void mixUpCreatures();
    std::pair<std::vector<Creature>, std::vector<Creature>> pickLuckyGenes(const int totalPicks);


    public:
    Geneworld(const unsigned int iPop=10000000u, const double iProp=0.02, const double nFert=2.1,
        const double nRFert=0.9, const double pFert=0.3, const double pRFert=2.5,
        const double badYearRate = 0.15):
        initialPopulation(iPop), initialRecessiveProportion(iProp), normalFertility(nFert),
        normalRecessiveFertility(nRFert), panicFertility(pFert), panicRecessiveFertility(pRFert),
        badYearRate(badYearRate){};
    
    void buildworld();

    void generate();

    unsigned int getCurrentGeneration() {return currentGeneration;}
    
};