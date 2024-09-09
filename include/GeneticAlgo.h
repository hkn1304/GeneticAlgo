#ifndef GENETICALGO_H
#define GENETICALGO_H
#include <iostream>
#include <vector>
#include <functional>
#include <limits>
#include <map>
#include <algorithm>
using namespace std;

class GeneticAlgo
{
    private:
        int num_generations;
        int num_chromosomes;
        vector<vector<double>> population;
        int num_population;
        int dim_population;
        double low_bound;
        double up_bound;
        double mutation_rate;
        double crossover_rate;
        double percent_elite;
        // std::mt19937 gen;


        void createPopulationArray(int size, int dimension,double low_bound, double up_bound, double mutation_rate, double crossover_rate, double percentElite)
        {
            num_population = size;
            dim_population = dimension;
            this->low_bound = low_bound;
            this->up_bound= up_bound;
            this->mutation_rate=mutation_rate;
            this->crossover_rate=crossover_rate;
            this->percent_elite=percentElite;
            population.resize(size);
            for (int i=0; i < size; i++){
                population[i] = generate_random_numbers(low_bound,up_bound,dim_population);
                //cout << "Population " << i << ": ";
            }
            printpopulation();
            cout << endl;
        }

    public:
        GeneticAlgo(int num_population, int dim_population, double lower_bound, double upper_bound, double rateMutation, double rateCross, double percentElite){
            createPopulationArray(num_population, dim_population,lower_bound, upper_bound,rateMutation,rateCross,percentElite);
            
        }


        vector<double> getpopulation (int ) const;
        vector<vector<double>> getpopulation ( ) const { return population; };
        double getMutationRate () const{ return mutation_rate; };
        double getCrossoverRate () const{ return crossover_rate; };
        int getNumberElite () {return static_cast<int>(percent_elite*num_population); };
        vector<double> generate_random_numbers(double , double , int); 
        void setpopulation (int, int);
        void printpopulation()const;
        void printpopulation(int index, int nind)const;
        vector<double> setpopulationUser (int );
        void mutation();
        void crossover();

        template <typename FitnessFuncCallback> void fitness_func(FitnessFuncCallback fit_func)
        {
            //double score;
            int numElite = getNumberElite();
            cout << numElite <<endl;
            int ind = 0;
            
            // Map creation with score & population pairs
            std::multimap<double, std::vector<double>, std::greater<double>> population_score;
            
            // Iterate over each individual in the population
            for (auto& individual : this->population) {
                // Apply the fitness function ( here max_func ) to each individual
                double fitness = fit_func(individual);
                // Insert the fitness score and the corresponding individual into the multimap
                population_score.insert(std::make_pair(fitness, individual));
            }

            // print the scores and population for debugging
            for (const auto& entry : population_score) {
                double score = entry.first;
                const std::vector<double>& individual = entry.second;
                std::cout << "Fitness: " << score << std::endl;
            }

        };

        ~GeneticAlgo()
        { }
};



#endif