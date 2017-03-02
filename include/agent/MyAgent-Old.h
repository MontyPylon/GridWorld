#ifndef MyAgent_h__guard
#define MyAgent_h__guard


#include <grid/Agent.h>

using namespace std;

struct MyAgent : public bwi_gridworld::Agent {

    int id;
    vector<char> path;
    bool backward;
    vector<int> previous;
    bool start;
    int previousCounter;
    int steps;
    
    
    int counter;
    
    char nextAction(const bwi_gridworld::Pos &currentPos);
    void eventFound(const bwi_gridworld::Pos &currentPos);
    bwi_gridworld::Agent *clone(int id);

};


#endif

