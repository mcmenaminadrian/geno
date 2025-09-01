#include <iostream>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <algorithm>
#include <random>
#include <utility>
#include "geno.hpp"

using namespace std;

double randFactor()
{
    return double(rand())/RAND_MAX;
}

void Geneworld::mixUpCreatures()
{
    random_device rd;
    mt19937 generator(rd());
    shuffle(organisms.begin(), organisms.end(), generator);
}

pair<vector<Creature>, vector<Creature>> Geneworld::dividePopulation(const int totalPicks) const
{
    vector<Creature> picksFirst;
    vector<Creature> picksSecond;
    auto firstParent = organisms.begin();
    auto secondParent = organisms.rbegin();
    picksFirst = vector<Creature>(firstParent, firstParent + totalPicks);
    picksSecond = vector<Creature>(secondParent, secondParent + totalPicks);
    return pair(picksFirst, picksSecond);
}

vector<Creature> Geneworld::createClonables(const pair<vector<Creature>, vector<Creature>>& dividedPopulation) const
{
    vector<Creature> newCreatures;
    auto pfElement = dividedPopulation.first.begin();
    auto psElement = dividedPopulation.second.begin();
    for (auto j = 0; j < dividedPopulation.first.size(); j++) {
        uint aOrB = rand()%2;
        uint bOrA = rand()%2;
        newCreatures.push_back(Creature(aOrB < 1? (*pfElement).getAState(): (*pfElement).getBState(),
            bOrA < 1 ? (*psElement).getAState() : (*psElement).getBState()));
        pfElement++;
        psElement++;
    }
    return newCreatures;
}

void Geneworld::countClones(const vector<Creature>& clonableCreatures) const
{
    auto fRParents = 0u;
    auto pRParents = 0u;
    for (auto critter: clonableCreatures) {
        if (critter.isFullyRecessive())
        { fRParents++; }
        else if (critter.isPartiallyRecessive())
        { pRParents++; }
    }
    cout << "Total to be cloned..." << clonableCreatures.size() << "\n";
    cout << "Of which, fully recessive... " << fRParents << "\n";
    cout << "Partially recessive...       " << pRParents << "\n";
    cout << "No recessive genes...        " << clonableCreatures.size() - (fRParents + pRParents) << endl;
}


void Geneworld::buildworld()
{
    // build the initial world of creatures
    srand(time(0));
    cout << "Creating initial genetic distribution---" << "\n";
    for (auto i = 0u; i < initialPopulation; ++i) {
        double firstStrand = randFactor();
        double secondStrand = randFactor();
        organisms.push_back(Creature(firstStrand < initialRecessiveProportion, secondStrand < initialRecessiveProportion));
    }
    cout << "\n";
    cout << "Now counting population..." << "\n";
    cout << "Total population is: " << organisms.size() << "\n";
    auto fullyRecessed = 0u;
    auto partiallyRecessed = 0u;
    for (auto critter : organisms) {
        fullyRecessed += critter.isFullyRecessive() == true;
        partiallyRecessed += critter.isPartiallyRecessive() == true;
    }
    cout << "Fully recessive:     " << fullyRecessed << "\n";
    cout << double(fullyRecessed) / organisms.size() << " - share of population" << "\n";
    cout << "Partially recessive: " << partiallyRecessed << "\n";
    cout <<  double(partiallyRecessed) / organisms.size() << " - share of population" << "\n";
    cout << "Press enter move to the next generation" << "\n";
    cin.get();
    currentGeneration = 1u;
}

void Geneworld::generate()
{   
    unsigned seed = 0;
    bool goodYear = randFactor() > badYearRate;
    unsigned int totalPicks = organisms.size()/2;

    vector<Creature> newCreatures;
    unsigned int tenth = totalPicks/10u;
    if (tenth == 0) {
        cout << "The population has reached a level where the creatures can no longer breed." << endl;
        exit(EXIT_SUCCESS);
    }
    unsigned int done = 0u;
    if (goodYear) {
        cout << "This is a good year for the creatures.";
    } else {
        cout << "This is a crisis year for the creatures.";
    }
    cout << "\n";
    cout << "Randomly picking elements to mate" << "\n";
    mixUpCreatures();
    pair<vector<Creature>, vector<Creature>> dividedPopulation = dividePopulation(totalPicks);
    cout << "Matching" << "\n";
    newCreatures = createClonables(dividedPopulation);
    countClones(newCreatures);
    cout << "Breeding" << "\n";
    organisms.clear();
    if (goodYear) {
        for (auto critter: newCreatures) {
            if (critter.isFullyRecessive()){
                unsigned int rFertNormInt = (unsigned int) normalRecessiveFertility;
                unsigned int additionalFactor = 0u;
                if ((double) rFertNormInt < normalRecessiveFertility) {
                    double partProb = normalRecessiveFertility - rFertNormInt;
                    if (randFactor() <= partProb) {
                        additionalFactor = 1;
                    }
                }
                for (auto z = 0; z < rFertNormInt + additionalFactor; z++) {
                    organisms.push_back(critter);
                }
            } else {
                unsigned int rFertStdInt = (unsigned int) normalFertility;
                unsigned int additionalFactor = 0u;
                if ((double) rFertStdInt < normalFertility) {
                    double partProb = normalFertility - rFertStdInt;
                    if (randFactor() <= partProb) {
                        additionalFactor = 1;
                    }
                }
                for (auto z = 0; z < rFertStdInt + additionalFactor; z++) {
                    organisms.push_back(critter);
                }
            }
        }
    } else {
        for (auto critter: newCreatures) {
           if (critter.isFullyRecessive()) {
                unsigned int rFertPanicInt = (unsigned int) panicRecessiveFertility;
                unsigned int additionalFactor = 0u;
                if ((double) rFertPanicInt < panicRecessiveFertility) {
                    double partProb = panicRecessiveFertility - rFertPanicInt;
                    if (randFactor() <= partProb) {
                        additionalFactor = 1;
                    }
                }
                for (auto z = 0; z < rFertPanicInt + additionalFactor; z++) {
                    organisms.push_back(critter);
                }    
            } else {
                unsigned int pFertStdInt = (unsigned int) panicFertility;
                unsigned int additionalFactor = 0u;
                if ((double) pFertStdInt < panicFertility) {
                    double partProb = panicFertility - pFertStdInt;
                    if (randFactor() <= partProb) {
                        additionalFactor = 1;
                    }
                }
                for (auto z = 0; z < pFertStdInt + additionalFactor; z++) {
                    organisms.push_back(critter);
                }    
            }
        }
    }
    cout << "Now counting population..." << "\n";
    cout << "Total population is now: " << organisms.size() << "\n";
    auto fullyRecessed = 0u;
    auto partiallyRecessed = 0u;
    for (auto critter : organisms) {
        fullyRecessed += critter.isFullyRecessive() == true;
        partiallyRecessed += critter.isPartiallyRecessive() == true;
    }
    cout << "Fully recessive:     " << fullyRecessed << "\n";
    cout << double(fullyRecessed) / organisms.size() << " - share of population" << "\n";
    cout << "Partially recessive: " << partiallyRecessed << "\n";
    cout <<  double(partiallyRecessed) / organisms.size() << " - share of population" << "\n";
    cout << "No recessive genes:  " << organisms.size() - (fullyRecessed + partiallyRecessed) << "\n";
    cout << 1.0 - (double(fullyRecessed + partiallyRecessed) / organisms.size()) << " - share of population" << "\n";
    cout << "Total share of recessive genes..." << (double(fullyRecessed * 2.0) + partiallyRecessed) / (organisms.size() * 2) << "\n";
    cout << "------------------------------------------------------" << "\n";
    currentGeneration++;
    newCreatures.clear();
    cout << "\n" << endl;   
}


int main()
{
    Geneworld geneGenie;
    geneGenie.buildworld();
    while(1) {
        cout << "Now building generation: " << 
        geneGenie.getCurrentGeneration() + 1 << "\n";
        geneGenie.generate();
    }

}

