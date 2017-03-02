#include <agent/MyAgent.h>
#include <cstdlib>
#include <grid/grid.h>
#include <iostream>

using namespace std;

bwi_gridworld::Agent* MyAgent::clone(double id) {
    //return new RandomAgent(); //random agents don't use ids because they all do the same thing
    MyAgent *a = new MyAgent();
    a->id = id;
    a->counter = 0;
    a->begCount = 0;
    int id1 = id;
    switch(id1) {
        case 0: {
            char my_chars[] = {'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 
                               'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e',
                               's', 's', 's', 's', 's', 's', 's', 's', 's',
                               'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w',};
            vector<char> path_set(my_chars, my_chars + sizeof(my_chars) / sizeof(char));
            a->path = path_set;
            a->steps = 36;
        }
            break;
        case 1: {
            char beg1[] = {'n', 'w'};
            vector<char> path_beg1(beg1, beg1 + sizeof(beg1) / sizeof(char));
            a->beg = path_beg1;
            char my_chars1[] = {'w', 'w', 'w', 'w', 'w', 'w', 'w',
                               'n', 'n', 'n', 'n', 'n', 'n', 'n',
                               'e', 'e', 'e', 'e', 'e', 'e', 'e',
                               's', 's', 's', 's', 's', 's', 's'};
            vector<char> path_set1(my_chars1, my_chars1 + sizeof(my_chars1) / sizeof(char));
            a->path = path_set1;
            a->steps = 28;
        }
            break;
        case 2: {
            char beg2[] = {'s', 's', 'w', 'w'};
            vector<char> path_beg2(beg2, beg2 + sizeof(beg2) / sizeof(char));
            a->beg = path_beg2;
            char my_chars2[] = { 's', 's', 's', 's', 's',
                                 'w', 'w', 'w', 'w', 'w',
                                 'n', 'n', 'n', 'n', 'n',
                                 'e', 'e', 'e', 'e', 'e',};
            vector<char> path_set2(my_chars2, my_chars2 + sizeof(my_chars2) / sizeof(char));
            a->path = path_set2;
            a->steps = 20;
        }
            break;
        case 3: {
            char beg3[] = {'e', 'e', 'e', 's', 's', 's'};
            vector<char> path_beg3(beg3, beg3 + sizeof(beg3) / sizeof(char));
            a->beg = path_beg3;
            char my_chars3[] = { 'e', 'e', 'e',
                                 's', 's', 's',
                                 'w', 'w', 'w',
                                 'n', 'n', 'n'};
            vector<char> path_set3(my_chars3, my_chars3 + sizeof(my_chars3) / sizeof(char));
            a->path = path_set3;
            a->steps = 12;
        }
            break;
    }
    return a;
}

char MyAgent::nextAction(const bwi_gridworld::Pos& currentPos) {
    int x = currentPos.x;
    int y = currentPos.y;
    int width = bwi_gridworld::Grid::width;
    int height = bwi_gridworld::Grid::height;
    char dir;
    int id1 = id;
    switch(id1) {
        case 0:
            return 's';
            break;
        case 1:
            //return 's';
            break;
        case 2:
            return 'n';
            break;
        case 3:
            return 'n';
            break;
    }
    
    
    if(id == 1) {
        int debug = 0;
        debug += 1;
    }
    
    if(!previous.empty()) {
        if ((abs(x - previous.at(0)) > 1 || abs(y - previous.at(1)) > 1)) {
            //cout << "RESET" << endl;
            counter = 0;
            begCount = 0;
        }
        else if (previous.at(0) == x && previous.at(1) == y) {
            //cout << "MOVE DENIED" << endl;
            counter = previousCounter;
            begCount = previousBegCount;
        }
         
    
    }
    
    if(id != 0) {
        if(begCount != beg.size()) {
            dir = beg.at(begCount);
            previousBegCount = begCount;
            begCount++;
            previous.clear();
            previous.push_back(x);
            previous.push_back(y);
            return dir;
        } else {
            previousBegCount = begCount;
        }
    }
    
    if(counter == steps) {
        counter = 0;
    }
    
    dir = path.at(counter);
    previousCounter = counter;
    counter++;

    previous.clear();
    previous.push_back(x);
    previous.push_back(y);
    
    return dir;
}

void MyAgent::eventFound(const bwi_gridworld::Pos &currentPos) {
}
