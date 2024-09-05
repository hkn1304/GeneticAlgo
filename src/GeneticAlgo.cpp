#include "GeneticAlgo.h"
#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>

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
                //int ind = distance(iterPop->begin(), iter);
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

void GeneticAlgo::mutation(){
        // Seed random number generator
    srand(static_cast<unsigned>(time(nullptr)));

    double rateMutation= getMutationRate();
    // int number_mutation= static_cast<int>(rateMutation*dim_population*num_population);
        int number_mutation= rateMutation*dim_population*num_population;
    for (int i=0; i < number_mutation; i++ ) {
        int index = rand() % num_population;
        cout << index << " ";
        int nind = rand() % dim_population;
        cout << nind << " ";
        printpopulation(index,nind);
        setpopulation(index, nind);
        printpopulation(index,nind);
        cout << endl;
    }
    // printpopulation();
};
