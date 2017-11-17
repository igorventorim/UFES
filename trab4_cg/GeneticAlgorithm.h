#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <vector>
#include <list>
#include "NPC.h"


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
        double evaluate(vector<int>,NPC*);
        void mutation(vector<int>&);
        void crossover(int,int,vector<int>&);
        int getFitness(NPC* npc);
    public:
        GeneticAlgorithm(void);
        GeneticAlgorithm(int,int,int,int,double,double);
        void run(list<NPC*>);
        void initFullPopulation(void);
        void modifyRun(list<NPC*>);

};

#endif