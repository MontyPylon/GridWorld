#ifndef MyAgent_h__guard
#define MyAgent_h__guard


#include <grid/Agent.h>

using namespace std;

struct MyAgent : public bwi_gridworld::Agent {

    int id;
    vector<char> path;
    vector<char> beg;
    vector<int> previous;
    int begCount;
    int steps;
    int counter;
    int previousCounter;
    int previousBegCount;
    
    char nextAction(const bwi_gridworld::Pos &currentPos);
    void eventFound(const bwi_gridworld::Pos &currentPos);
    bwi_gridworld::Agent *clone(double id);

};


#endif

