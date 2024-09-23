#include <iostream>
#include <random> 
#include <vector> 
#include <algorithm> 
#include "GeneticAlgo.h"

using namespace std;

double max_func(const std::vector<double>& iterPop)
{
if (iterPop.empty() || iterPop.empty()) return 0; // Handle empty vectors appropriately
    return *std::max_element(iterPop.begin(), iterPop.end());
};

int main(){

GeneticAlgo genalg(10, 4, 10.0, 100.0, 0.05, 0.05, 0.20, 0.001);
genalg.evolve(100, max_func);
    return 0;
}

//genalg.printpopulation();
//cout << endl;
//genalg.getpopulation(3);
// cout << endl;
// genalg.printpopulation();

// cout << endl;
// genalg.setpopulation(2,4);
// cout << endl;
// genalg.getpopulation(2);

// Pass the arbitrary fitness function as functor via:
//genalg.fitness_func(max_func);

// genalg.mutation();
//genalg.printpopulation();
// genalg.selectElite();

// genalg.crossover();
// genalg.printpopulation();