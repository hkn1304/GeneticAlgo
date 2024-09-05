#include <iostream>
#include <random> 
#include "GeneticAlgo.h"

using namespace std;

int main(){

GeneticAlgo genalg(20, 5, 10.0, 100.0, 0.05, 0.05);
//genalg.printpopulation();
cout << endl;
//genalg.getpopulation(3);
// cout << endl;
// genalg.printpopulation();

// cout << endl;
// genalg.setpopulation(2,4);
// cout << endl;
// genalg.getpopulation(2);

genalg.mutation();
genalg.printpopulation();
//cout << "Random number between " ;//<< lower_bound << "and " <<upper_bound << ": " << random_number <<"\n";

    return 0;
}