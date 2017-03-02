#include <agent/MyAgent.h>
#include <cstdlib>
#include <grid/grid.h>
#include <iostream>

using namespace std;

vector<int> goForward(char dir, int x, int y) {
    vector<int> next;
    switch(dir) {
        case 'n':
            next.push_back(x);
            next.push_back(y + 1);
            break;
        case 'e':
            next.push_back(x + 1);
            next.push_back(y);
            break;
        case 's':
            next.push_back(x);
            next.push_back(y - 1);
            break;
        case 'w':
            next.push_back(x - 1);
            next.push_back(y);
            break;
    }
    return next;
}

char turnRight(char dir) {
    char newDir;
    switch(dir) {
        case 'n': newDir = 'e'; break;
        case 'e': newDir = 's'; break;
        case 's': newDir = 'w'; break;
        case 'w': newDir = 'n'; break;
    }
    return newDir;
}

bool isMember(int new_x, int new_y, vector<int> not_x, vector<int> not_y) {
    bool found = false;
    for(int a = 0; a < not_x.size(); a++) {
        if(new_x == not_x.at(a) && new_y == not_y.at(a)) {
            found = true;
            break;
        }
    }
    return found;
}

bool isForwardFree(char dir, int width, int height, int x, int y, vector<int> not_x, vector<int> not_y) {
    int new_x = x;
    int new_y = y;
    bool forward = true;
    switch(dir) {
        case 'n':
            new_y = y + 1;
            if(isMember(new_x, new_y, not_x, not_y)) {
                forward = false;
            }
            break;
        case 'e':
            new_x = x + 1;
            if(isMember(new_x, new_y, not_x, not_y)) {
                forward = false;
            }
            break;
        case 's':
            new_y = y - 1;
            if(isMember(new_x, new_y, not_x, not_y)) {
                forward = false;
            }
            break;
        case 'w':
            new_x = x - 1;
            if(isMember(new_x, new_y, not_x, not_y)) {
                forward = false;
            }
            break;
    }
    return forward;
}

vector<char> findPath(int id, int width, int height) {
    vector<char> path;
    vector<int> path_x;
    vector<int> path_y;
    vector<int> not_x;
    vector<int> not_y;
    
    int total_area = width * height;
    int one_area = (width * height) / 4;
    int limit_x = width / 2;
    int limit_y = height / 2;
    
    /**
    if(one_area % 1 != 0) {
        cout << "width x height can't be divided by 4!!" << endl;
    }
     **/
    
    // Not allowed points:
    for(int x = -1; x < width + 1; x++) {
        for(int y = -1; y < height + 1; y++) {
            if(x < 0 || x >= width || y < 0 || y >= height) {
                not_x.push_back(x);
                not_y.push_back(y);
            } else {
                switch (id) {
                    case 0:
                        if (x >= limit_x || y >= limit_y) {
                            not_x.push_back(x);
                            not_y.push_back(y);
                        }
                        break;
                    case 1:
                        if (x < limit_x || y >= limit_y) {
                            not_x.push_back(x);
                            not_y.push_back(y);
                        }
                        break;
                    case 2:
                        if (x < limit_x || y < limit_y) {
                            not_x.push_back(x);
                            not_y.push_back(y);
                        }
                        break;
                    case 3:
                        if (x >= limit_x || y < limit_y) {
                            not_x.push_back(x);
                            not_y.push_back(y);
                        }
                        break;
                }
            }
        }
    }
    
    char dir;
    switch(id) {
        case 0: 
            dir = 'n';
            path_x.push_back(0);
            path_y.push_back(0);
            not_x.push_back(0);
            not_y.push_back(0);
            break;
        case 1: 
            dir = 'w';
            path_x.push_back(9);
            path_y.push_back(0);
            not_x.push_back(9);
            not_y.push_back(0);
            break;
        case 2: 
            dir = 's';
            path_x.push_back(9);
            path_y.push_back(9);
            not_x.push_back(9);
            not_y.push_back(9);
            break;
        case 3: 
            dir = 'e';
            path_x.push_back(0);
            path_y.push_back(9);
            not_x.push_back(0);
            not_y.push_back(9);
            break;
    }
    
    vector<int> next;
    
    for(int a = 0; a < (one_area - 1); a++) {
        if (!isForwardFree(dir, width, height, path_x.at(a), path_y.at(a), not_x, not_y)) {
            dir = turnRight(dir);
        }
        next = goForward(dir, path_x.at(a), path_y.at(a));
        path_x.push_back(next.at(0));
        path_y.push_back(next.at(1));
        not_x.push_back(next.at(0));
        not_y.push_back(next.at(1));
        path.push_back(dir);
        //cout << "x: " << path_x.at(a) << ", y: " << path_y.at(a) << ", dir: " << dir << endl;
    }
    
    return path;
}

vector<int> setPrevious(int id) {
    
}

bwi_gridworld::Agent* MyAgent::clone(int id) {
    //return new RandomAgent(); //random agents don't use ids because they all do the same thing
    MyAgent *a = new MyAgent();
    a->id = id;
    a->counter = 0;
    a->path = findPath(id, bwi_gridworld::Grid::width, bwi_gridworld::Grid::height);
    /**
    switch(id) {
        case 0: {
            char my_chars[] = {'n', 'n', 'n', 'n', 'n', 'e', 'e', 'e', 'e', 'e', 's', 's', 's', 's', 's', 'w', 'w', 'w', 'w', 
                               'n', 'n', 'n', 'n', 'e', 'e', 'e', 's', 's', 's', 'w', 'w', 'n', 'n', 'e', 's'};
            vector<char> path_set(my_chars, my_chars + sizeof(my_chars) / sizeof(char));
            a->path = path_set;
            a->steps = 36;
        }
            break;
        case 1: {
        
            char my_chars1[] = {'w', 'w', 'w', 'n', 'e', 'e', 'e', 'n', 'w', 'w', 'w', 'n', 'e', 'e', 'e', 'n', 'w', 'w', 'w',
                                'n', 'e', 'e', 'e', 'n', 'w', 'w', 'w', 'w'};
            vector<char> path_set1(my_chars1, my_chars1 + sizeof(my_chars1) / sizeof(char));
            a->path = path_set1;
            a->steps = 29;
        }
            break;
        case 2: {
            char my_chars2[] = {'s', 's', 'w', 'n', 'n', 'w', 's', 's', 'w', 'n', 'n', 'w', 's', 's', 'w', 'n', 'n', 'w', 's', 's'};
            vector<char> path_set2(my_chars2, my_chars2 + sizeof(my_chars2) / sizeof(char));
            a->path = path_set2;
            a->steps = 21;
        }
            break;
        case 3: {
            char my_chars3[] = {'e', 'e', 's', 'w', 'w', 's', 's', 'e', 'n', 'e', 's', 'e', 'e'};
            vector<char> path_set3(my_chars3, my_chars3 + sizeof(my_chars3) / sizeof(char));
            a->path = path_set3;
            a->steps = 14;
        }
            break;
    }
     **/
    a->steps=25;
    a->start = true;
    a->backward = false;
    
    return a;
}

char takeNextStep(int id, int x, int y, int limitx, int limity, char previous_dir, int on, int end) {
    char dir;
    
    return dir;
}

char opposite(char dir) {
    char newDir;
    switch(dir) {
        case 'n': newDir = 's'; break;
        case 'e': newDir = 'w'; break;
        case 's': newDir = 'n'; break;
        case 'w': newDir = 'e'; break;
    }
    return newDir;
}

void printGrid(int x, int y, int width, int height) {
    
    cout << "--------------------------------" << endl;
    for(int a = height-1; a >= 0; a--) {
        for(int b = 0; b < width; b++) {
            if(b == 0) {
                cout << "|";
            }
            if(x == b && y == a) {
                cout << " A ";
            } else {
                cout << " * ";
            }
            
            if(b == width-1) {
                cout << "|";
            }
        }
        cout << endl;
    }
    cout << "--------------------------------" << endl;
    cout << "current pose: " << x << ", " << y << endl;
    int done;
}

char MyAgent::nextAction(const bwi_gridworld::Pos& currentPos) {
    int x = currentPos.x;
    int y = currentPos.y;
    int width = bwi_gridworld::Grid::width;
    int height = bwi_gridworld::Grid::height;
    int one_area = (width * height) / 4;
    char dir;
    bool override = false;
    
    
    if(!start && (abs(x - previous.at(0)) > 1 || abs(y - previous.at(1)) > 1)) {
        //cout << "RESET" << endl;
        counter = 0;
        start = true;
        backward = false;
    }
        /**
    else if (!start && previous.at(0) == x && previous.at(1) == y) {
        //cout << "MOVE DENIED" << endl;
        counter = previousCounter;
        if(counter == -1) {
            backward = true;
        } else if(counter == (steps - 1)) {
            backward = false;
        }
    } else {
        start = false;
    }
    **/
    if(id == 1) {
        //printGrid(x, y, 10, 10);
    }
    
    /**
    //cout << "--------------" << endl;
    //cout << "ID: " << id << ", x: " << x << ", y: " << y << endl;
    
     **/

    if (counter == (steps - 1) && !backward) {
        backward = true;
        override = true;
        previousCounter = counter;
        counter--;
        dir = opposite(path.at(counter));
        //cout << "Direction: " << dir << ", counter: " << counter << endl;
        counter--;
        //return dir;
    } else if (counter == -1 && backward) {
        backward = false;
        override = true;
        previousCounter = counter;
        counter++;
        dir = path.at(counter);
        //cout << "Direction: " << dir << ", counter: " << counter << endl;
        counter++;
        //return dir;
    }

    if (!override) {
        if (!backward) {
            dir = path.at(counter);
            //cout << "Direction: " << dir << ", counter: " << counter << endl;
            previousCounter = counter;
            counter++;
        } else {
            dir = opposite(path.at(counter));
            //cout << "Direction: " << dir << ", counter: " << counter << endl;
            previousCounter = counter;
            counter--;
        }
    }
    
    if(id == 3) {
        //cout << "next dir: " << dir << endl;
    }
    previous.clear();
    previous.push_back(x);
    previous.push_back(y);
    
    switch(id) {
        case 0:
            //dir = 's';
            break;
        case 1:
            //dir = 's';
            break;
        case 2:
            //dir = 'n';
            break;
        case 3:
            //dir = 'n';
            break;
    }
    
    return dir;
}

/**
char MyAgent::nextAction(const bwi_gridworld::Pos& currentPos) {
    int x = currentPos.x;
    int y = currentPos.y;
    int width = bwi_gridworld::Grid::width;
    int height = bwi_gridworld::Grid::height;
    int one_area = (width * height) / 4;
    char dir;
    bool override = false;


    if(!start && (abs(x - previous.at(0)) > 1 || abs(y - previous.at(1)) > 1)) {
        //cout << "RESET" << endl;
        counter = 0;
        start = true;
        backward = false;
    }
    else if (!start && previous.at(0) == x && previous.at(1) == y) {
        //cout << "MOVE DENIED" << endl;
        counter = previousCounter;
        if(counter == -1) {
            backward = true;
        } else if(counter == (steps - 1)) {
            backward = false;
        }
    } else {
        start = false;
    }

    if(id == 1) {
        //printGrid(x, y, 10, 10);
    }

    /**
    //cout << "--------------" << endl;
    //cout << "ID: " << id << ", x: " << x << ", y: " << y << endl;
    
     

    if (counter == (steps - 1) && !backward) {
        backward = true;
        override = true;
        previousCounter = counter;
        counter--;
        dir = opposite(path.at(counter));
        //cout << "Direction: " << dir << ", counter: " << counter << endl;
        counter--;
        //return dir;
    } else if (counter == -1 && backward) {
        backward = false;
        override = true;
        previousCounter = counter;
        counter++;
        dir = path.at(counter);
        //cout << "Direction: " << dir << ", counter: " << counter << endl;
        counter++;
        //return dir;
    }

    if (!override) {
        if (!backward) {
            dir = path.at(counter);
            //cout << "Direction: " << dir << ", counter: " << counter << endl;
            previousCounter = counter;
            counter++;
        } else {
            dir = opposite(path.at(counter));
            //cout << "Direction: " << dir << ", counter: " << counter << endl;
            previousCounter = counter;
            counter--;
        }
    }

    if(id == 3) {
        //cout << "next dir: " << dir << endl;
    }
    previous.clear();
    previous.push_back(x);
    previous.push_back(y);

    switch(id) {
        case 0:
            //dir = 's';
            break;
        case 1:
            //dir = 's';
            break;
        case 2:
            //dir = 'n';
            break;
        case 3:
            //dir = 'n';
            break;
    }

    return dir;
}
**/


/**
char MyAgent::nextAction(const bwi_gridworld::Pos& currentPos) {
    int x = currentPos.x;
    int y = currentPos.y;
    int width = bwi_gridworld::Grid::width;
    int height = bwi_gridworld::Grid::height;
    int one_area = (width * height) / 4;
    char dir;
    bool override = false;

    if(id == 3) {
        cout << "x: " << x << ", y: " << y << endl;
        if (!start && previous.at(0) == x && previous.at(1) == y) {
            cout << "MOVE DENIED" << endl;
            counter = previousCounter;
            if(counter == -1) {
                backward = true;
            } else if(counter == 24) {
                backward = false;
            }
        } else {
            start = false;
        }

        if (counter == (one_area - 1) && !backward) {
            backward = true;
            override = true;
            previousCounter = counter;
            counter--;
            dir = opposite(path.at(counter));
            cout << "Direction: " << dir << ", counter: " << counter << endl;
            counter--;
            //return dir;
        } else if (counter == -1 && backward) {
            backward = false;
            override = true;
            previousCounter = counter;
            counter++;
            dir = path.at(counter);
            cout << "Direction: " << dir << ", counter: " << counter << endl;
            counter++;
            //return dir;
        }

        if (!override) {
            if (!backward) {
                dir = path.at(counter);
                cout << "Direction: " << dir << ", counter: " << counter << endl;
                previousCounter = counter;
                counter++;
            } else {
                dir = opposite(path.at(counter));
                cout << "Direction: " << dir << ", counter: " << counter << endl;
                previousCounter = counter;
                counter--;
            }
        }
        if(x == 0 && y == 9 && dir == 'n') {
            int wtf = 0;
        }
        previous.clear();
        previous.push_back(x);
        previous.push_back(y);
        return dir;
    } else {
        return 'n';
    }
}
**/
void MyAgent::eventFound(const bwi_gridworld::Pos &currentPos) {
    //cout << "Found an event at: " << currentPos.x << ", " << currentPos.y << endl;
    //if(id == 1) {
        //cout << "Found an event!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    //}
}
