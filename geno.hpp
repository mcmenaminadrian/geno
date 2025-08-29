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


    public:
    Geneworld(const unsigned int iPop=10000000u, const double iProp=0.02, const double nFert=2.3,
        const double nRFert=1.9, const double pFert=0.7, const double pRFert=2.3,
        const double badYearRate = 0.15):
        initialPopulation(iPop), initialRecessiveProportion(iProp), normalFertility(nFert),
        normalRecessiveFertility(nRFert), panicFertility(pFert), panicRecessiveFertility(pRFert),
        badYearRate(badYearRate){};
    
    void buildworld();

    void generate();

    unsigned int getCurrentGeneration() {return currentGeneration;}
    
};