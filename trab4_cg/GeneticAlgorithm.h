#ifndef _GENETICALGORITHM_H_
#define _GENETICALGORITHM_H_
#include <vector>
#include "NPC.h"
#include <list>

using namespace std;

class GeneticAlgorithm
{
    private:
        int chromosome_size;
        int population_size;
        int tournament_size;
        int generations;
        double mutation_prob;
        double crossover_prob;
        vector <vector<int>> population;
        void initPopulation(void);
        void showPopulation(void);
        int evaluate(vector<int>,NPC*);
        void mutation(vector<int>&);
        void crossover(int,int,vector<int>&);
        int getFitness(NPC* npc);
    public:
        GeneticAlgorithm(void);
        GeneticAlgorithm(int,int,int,int,double,double);
        void run(list<NPC*>);

};

#endif