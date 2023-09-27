#include <iostream>
using namespace std;
#include <vector>
#include <queue>
#include <unordered_map>

#ifndef JUG_H
#define JUG_H

struct State{
  int a;
  int b;
  string action;
  int cost;
  bool operator>(const State& s) const { //defines two comparison operator overloads that allow you to compare two State objects
        return cost > s.cost;
  }

  bool operator<(const State& s) const {
          return cost > s.cost;
  }
};

class Jug {
    public:
        Jug(int,int,int,int,int,int,int,int,int);
        ~Jug();

        //solve is used to check input and find the solution if one exists
        //returns -1 if invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string &solution);
    private:
      int Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA;
      vector <State> steps;
      void nextOperation(priority_queue<State, vector<State>, greater<State>> &, vector <vector <int> > &, int, int, string, int, State, vector <vector<State>> &);

};
#endif