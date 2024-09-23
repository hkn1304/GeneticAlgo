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
        int num_population;
        int dim_population;
        double low_bound;
        double up_bound;
        double mutation_rate;
        double crossover_rate;
        double percent_elite;
        double tolerance;
        vector<vector<double>> population;
        vector<vector<double>> nextgen;
        std::multimap<double, std::vector<double>, std::greater<double>> population_score;

        void createPopulationArray(int size, int dimension,double low_bound, double up_bound, double mutation_rate, double crossover_rate, double percentElite, double tol)
        {
            num_population = size;
            dim_population = dimension;
            this->low_bound = low_bound;
            this->up_bound= up_bound;
            this->mutation_rate=mutation_rate;
            this->crossover_rate=crossover_rate;
            this->percent_elite=percentElite;
            this->tolerance = tol;
            population.resize(size);
            for (int i=0; i < size; i++){
                population[i] = generate_random_numbers(low_bound,up_bound,dim_population);
                //cout << "Population " << i << ": ";
            }
            printpopulation();
            cout << endl;
        }

    public:
        GeneticAlgo(int num_population, int dim_population, double lower_bound, double upper_bound, double rateMutation, double rateCross, double percentElite, double tol){
            createPopulationArray(num_population, dim_population,lower_bound, upper_bound,rateMutation,rateCross,percentElite, tol);
            
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
        void printnextgen()const;
        vector<double> setpopulationUser (int );
        void mutation();
        void crossover();
        void selectElite();

        template <typename FitnessFuncCallback> void fitness_func(FitnessFuncCallback fit_func)
        {
            
            // Iterate over each individual in the population
            for (auto& individual : this->population) {
                // Apply the fitness function ( here max_func ) to each individual
                double fitness = fit_func(individual);
                // Insert the fitness score and the corresponding individual into the multimap
                population_score.insert(std::make_pair(fitness, individual));
            }

        };

        template <typename FitnessFuncCallback>
        void evolve(int max_generations, FitnessFuncCallback fit_func) {
    
            double previous_best_fitness = std::numeric_limits<double>::max();  // Initialize with a large value
            double current_best_fitness = 0.0;

            for (int generation = 0; generation < max_generations; ++generation) {
                // Evaluate fitness and sort population
                population_score.clear();
                fitness_func(fit_func);

                // Get the best fitness from the current generation
                current_best_fitness = population_score.begin()->first;  // Highest fitness

                // Check convergence: if the difference is smaller than tolerance
                if (std::abs(previous_best_fitness - current_best_fitness) < tolerance) {
                    std::cout << "Converged at generation " << generation << " with best fitness = " << current_best_fitness << std::endl;
                    break;  // Stop the loop when convergence criteria are met
                }

                // Perform genetic operations

                crossover();
                mutation();
                selectElite();

                // Replace old population with new one
                population = nextgen;

                // Optional: Check for convergence criteria
                std::cout << "Generation " << generation << ": Best fitness = " << population_score.begin()->first << std::endl;
                
                // Update the previous best fitness for the next generation
                previous_best_fitness = current_best_fitness;

            }
        };

        ~GeneticAlgo()
        { };
};

#endif