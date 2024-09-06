#ifndef GENETICALGO_H
#define GENETICALGO_H
#include <iostream>
#include <vector>
using namespace std;
//const double DEFAULT_SCORE =0.0;

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
        // std::mt19937 gen;


        void createPopulationArray(int size, int dimension,double low_bound, double up_bound, double mutation_rate, double crossover_rate)
        {
            num_population = size;
            dim_population = dimension;
            this->low_bound = low_bound;
            this->up_bound= up_bound;
            this->mutation_rate=mutation_rate;
            this->crossover_rate=crossover_rate;
            population.resize(size);
            for (int i=0; i < size; i++){
                population[i] = generate_random_numbers(low_bound,up_bound,dim_population);
                //cout << "Population " << i << ": ";
            }
            printpopulation();
            cout << endl;
        }

    public:
        GeneticAlgo(int num_population, int dim_population, double lower_bound, double upper_bound, double rateMutation, double rateCross){
            //vector<double> init_values= generate_random_numbers(lower_bound , upper_bound , num_population);
            createPopulationArray(num_population, dim_population,lower_bound, upper_bound,rateMutation,rateCross);
        }

        vector<double> getpopulation (int ) const;
        double getMutationRate () const{ return mutation_rate; };
        double getCrossoverRate () const{ return crossover_rate; };
        vector<double> generate_random_numbers(double , double , int); 
        void setpopulation (int, int);
        void printpopulation()const;
        void printpopulation(int index, int nind)const;
        vector<double> setpopulationUser (int );
        void mutation();
        void crossover();

        ~GeneticAlgo()
        { }
};



#endif