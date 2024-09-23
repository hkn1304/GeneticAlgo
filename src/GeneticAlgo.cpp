#include "GeneticAlgo.h"
#include <vector>
#include <map>
#include <functional>
#include <random> // For random number generator
#include <ctime>
#include <cstdlib>
#include <stdexcept> // For std::runtime_error

using namespace std;

vector<double> GeneticAlgo::generate_random_numbers(double lower_bound, double upper_bound, int num_numbers) {
    vector<double> numbers;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> distr(lower_bound, upper_bound);

    for (int i = 0; i < num_numbers; ++i) {
        numbers.push_back(distr(gen));
    }
    return numbers;
};

vector<double> GeneticAlgo::getpopulation(int index) const{ 
    if (index > population.size() ){
        throw "Out of bounds";
    }
    else {
        cout << "Population " << index << ": ";
        vector<double>::const_iterator iter;
            for (iter = population[index].begin(); iter !=population[index].end();iter++ ) {
                cout << *iter << " ";
            }
        return population[index];
         }
};

void GeneticAlgo::setpopulation(int index, int nind){ 
    vector<vector<double>>::iterator iterPop = population.begin();
    advance(iterPop,index);
    vector<double>::iterator iter = iterPop->begin();
    advance(iter,nind);
    vector<double> temp = generate_random_numbers(low_bound, up_bound, 1);
    *iter = temp.front();
};


vector<double> GeneticAlgo::setpopulationUser(int index){ 
    if (index > population.size() ){
        throw "Out of bounds";
    }
    else {
        cout << "Population " << index << ": ";
        vector<double>::iterator iter;
            for (iter = population[index].begin(); iter !=population[index].end();iter++ ) {
                int ind = iter - population[index].begin();
                cin >> *iter ;
            }
        return population[index];
         }
};

void GeneticAlgo::printpopulation()const{ 
    vector<vector<double>>::const_iterator iterPop;
    for (iterPop = population.begin(); iterPop != population.end();iterPop++){
        int index = distance(population.begin(), iterPop);
        cout << "Population " << index << ": ";
        vector<double>::const_iterator iter;
            for (iter = iterPop->begin(); iter != iterPop->end();iter++ ) {
                cout << *iter << " ";
            }
            cout << endl;
    }
    
};

void GeneticAlgo::printpopulation(int index, int nind)const{ 
    vector<vector<double>>::const_iterator iterPop = population.begin();
    advance(iterPop,index);

    vector<double>::const_iterator iter = iterPop->begin();
    advance(iter,nind);
    cout << *iter << " ";
};

void GeneticAlgo::printnextgen()const{ 
    vector<vector<double>>::const_iterator iterPop;
    for (iterPop = nextgen.begin(); iterPop != nextgen.end();iterPop++){
        int index = distance(nextgen.begin(), iterPop);
        cout << "Next Gen: " << index << ": ";
        vector<double>::const_iterator iter;
            for (iter = iterPop->begin(); iter != iterPop->end();iter++ ) {
                //int ind = distance(iterPop->begin(), iter);
                cout << *iter << " ";
            }
            cout << endl;
    }
    
};

void GeneticAlgo::mutation(){
    // Seed random number generator
    srand(static_cast<unsigned>(time(nullptr)));

    double rateMutation= getMutationRate();
    int number_mutation= static_cast<int>(rateMutation*dim_population*num_population);
    
    try
    {
        if (number_mutation < 1){
            throw runtime_error("No mutation happened, less than 1");
        }
            for (int i=0; i < number_mutation; i++ ) {
                int index = rand() % num_population;
                cout << index << " ";
                int nind = rand() % dim_population;
                cout << nind << " ";
                //printpopulation(index,nind); // Before Mutation
                setpopulation(index, nind);
                //printpopulation(index,nind); // After Mutation
                cout << endl;
            }
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    // printpopulation();
};

void GeneticAlgo::crossover(){
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> distPop(0, num_population - 1);
    uniform_int_distribution<> distDim(0, dim_population - 1);

    double rateCrossover= getCrossoverRate();
    int number_crossover= static_cast<int>(rateCrossover*dim_population*num_population);

        try
    {
        if (number_crossover < 1){
            throw runtime_error("No Crossover happened, less than 1");
        }

        for (int i=0; i < number_crossover; i++ ) {

        // Create a random number from uniform distribution
        int index = distPop(gen), nind = distDim(gen);
        cout << index << " "; cout << nind << " ";
        int index2 = distPop(gen), nind2 = distDim(gen);
        cout << index2 << " "; cout << nind2 << " ";

        //printpopulation(index,nind); //printpopulation(index2,nind2); // Before Mutation
        swap(population[index][nind],population[index2][nind2]);
        //printpopulation(index,nind); printpopulation(index2,nind2); // After Mutation
        cout << endl;
    }
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
};


void GeneticAlgo::selectElite(){

    int number_elite= static_cast<int>(percent_elite*num_population);
    int i=0;

    std::multimap<double, std::vector<double>, std::greater<double>>::iterator iterMap;
    nextgen.clear();  // Clear the previous nextgen data to avoid appending

    // Ensure that nextgen has the same number of individuals as population_score
    for (iterMap = population_score.begin(); iterMap != population_score.end() && i < num_population; iterMap++, i++) {
        if (i < number_elite) {
            // Add elite individuals to nextgen
            nextgen.push_back(iterMap->second);
        } else {
            // Generate new individuals to fill the remaining population
            nextgen.push_back(generate_random_numbers(low_bound, up_bound, dim_population));
        }
    }
    printnextgen();
};


