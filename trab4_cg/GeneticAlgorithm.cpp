#include "GeneticAlgorithm.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#define CHROMOSOME_SIZE 5
#define POPULATION_SIZE 32
#define TOURNAMENT_SIZE 5
#define GENERATIONS 50
#define MUTATION_PROB 0.4
#define CROSSOVER_PROB 0.9



GeneticAlgorithm::GeneticAlgorithm(void)
{
    chromosome_size = CHROMOSOME_SIZE;
    population_size = POPULATION_SIZE;
    tournament_size = TOURNAMENT_SIZE;
    generations = GENERATIONS;
    mutation_prob = MUTATION_PROB;
    crossover_prob = CROSSOVER_PROB;
}

GeneticAlgorithm::GeneticAlgorithm(int csize,int psize ,int tsize,int gen,double mprob,double cprob)
{
    chromosome_size = csize;
    population_size = psize;
    tournament_size = tsize;
    generations = gen;
    mutation_prob = mprob;
    crossover_prob = cprob;
}

void GeneticAlgorithm::initPopulation(void)
{

    for(int i = 0; i < population_size; i++)
    {
        vector<int> chromossome;
        for(int j = 0; j < chromosome_size; j++)
        {
            int num = rand() % 2;
            chromossome.push_back(num);
        }

        population.push_back(chromossome);
    }
}

void GeneticAlgorithm::showPopulation(void)
{
     for(int i = 0; i < population_size; i++)
    {
        for(int j = 0; j < chromosome_size; j++)
            cout << population[i][j] << " ";
        cout << endl;
    }
}


/* OVERRIDE: Your method evaluate*/
int GeneticAlgorithm::evaluate(vector<int> individuo, NPC* npc)
{
    int score = npc->movementEvaluate(individuo, chromosome_size);
    return score;
}

void GeneticAlgorithm::mutation(vector<int>& individuo)
{
    // GENERATION ELEMENT IN INTERVAL [0, CHROMOSOME_SIZE]
    int gene = rand() % chromosome_size;

    if(individuo[gene] == 0)
    {
        individuo[gene] = 1;
    }else
    {
        individuo[gene] = 0;
    }
}

void GeneticAlgorithm::crossover(int parents1_index,int parents2_index,vector<int>& son)
{
    int point = rand() % chromosome_size;

    for(int i = 0; i <= point; i++)
    {
        son.push_back(population[parents1_index][i]);
    }

    for(int i = point+1; i < chromosome_size; i++)
    {
        son.push_back(population[parents2_index][i]);
    }
}

int GeneticAlgorithm::getFitness(NPC* npc)
{
    int fitness_index = 0;
    int fitness_score = evaluate(population[0],npc);

    for( int i = 1; i < population_size; i++)
    {
        int score = evaluate(population[i],npc);
        if(score > fitness_score )
        {
            fitness_index = i;
            fitness_score = score;
        }
    }

    return fitness_index;
}

void GeneticAlgorithm::run(list<NPC*> npcs)
{

    for (std::list<NPC*>::iterator npc=npcs.begin(); npc != npcs.end(); ++npc)
    {
        srand(time(NULL));
        int fitness_index = -1;
        initPopulation();

        for(int i = 0; i < generations; i++)
        {
            for(int j = 0; j < tournament_size; j++)
            {
                double prob = ((double) rand() / ((double)RAND_MAX + 1));

                if(prob < crossover_prob)
                {
                    int parent1_index = rand() % population_size;
                    int parent2_index;

                    do
                    {
                        parent2_index = rand() % population_size;
                    }while(parent1_index == parent2_index);

                    vector<int> son;
                    crossover(parent1_index,parent2_index,son);
                    if(prob < mutation_prob)
                    {
                        mutation(son);
                    }

                    int score_parent1 = evaluate(population[parent1_index],(*npc));
                    int score_son = evaluate(son,(*npc));

                    if(score_son > score_parent1)
                    {
                        for(int k = 0; k < chromosome_size; k++)
                        {
                            population[parent1_index][k] = son[k];
                        }
                    }
                }
            }

            // cout << "Geracao " << i+1 << endl;
            // cout << "Melhor: ";
            fitness_index = getFitness((*npc));
            int fitness_score = evaluate(population[fitness_index],(*npc));

            // for(int j = 0; j < chromosome_size; j++)
            // {
                // cout << population[fitness_index][j] << " ";
            // }
            // cout << "\n Score: "<< fitness_score << "\n\n";
            // cout << "SCORE: " << fitness_score << endl;
        }

        (*npc)->moveNPC(population[fitness_index],chromosome_size);

    }



    // return population[fitness_index];

}
