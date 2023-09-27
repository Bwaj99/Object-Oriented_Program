#include <iostream>
using namespace std;
#include "Jug.h"
#include <vector>
#include <unordered_map>
#include <algorithm>

const int INF = 1000000000;


Jug::Jug(int capacity_a,int capacity_b,int goal,int costfill_A,int costfill_B,int costempty_A,int costempty_B,int costpour_AB,int costpour_BA){
  Ca = capacity_a; //capacity of jug A
  Cb = capacity_b; //capacity of jug B
  N = goal; //goal or target amount 
  cfA = costfill_A; //cost of filling jug A
  cfB = costfill_B; //cost of filling jug B
  ceA = costempty_A; //cost of emptying jug A
  ceB = costempty_B; //cost of emptying jug B
  cpAB = costpour_AB; //cost of pouring from jug A to jug B
  cpBA = costpour_BA; //cost of pouring from jug B to jug A
}

Jug::~Jug(){
  
}

int Jug::solve(string &solution){ //checks if any of the input values are invalid
  if(N > Cb || Ca <= 0 || Cb <= 0 || Ca > Cb || cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 || cpAB < 0 || cpBA < 0 || Cb > 1000){
    solution = "";
    return -1; //input values are invalid and the function cannot proceed with the solution
  }

  
  vector <vector <State> > predecessor(Ca + 1, vector <State>(Cb + 1)); //used to store the predecessor state for each state
  int a = 0, b = 0, cost = 0; //amount of liquid in jugs A and B and the current cost

  vector <vector <int> > distance(Ca + 1, vector <int>(Cb + 1, INF)); //minimum distance or cost to reach each state 
  
    priority_queue<State, vector<State>, greater<State>> q; //keep track of the states to be explored

  q.push({a, b, "", cost});

  distance[a][b] = 0;

  
  
  while(!q.empty()){
    int size = q.size();
    for(int i = 0; i < size; ++i){
      State currentState = q.top(); //obtains the current size of the priority queue and retrieves the top element

      // cout << currentState.a << " " << currentState.b << " " << currentState.action << endl;
      
      q.pop(); //removed from the queue

      int currentA = currentState.a;
      int currentB = currentState.b;
      string action = currentState.action;
      int cost = currentState.cost;

      if(currentA == 0 and currentB == N){

        vector <string> path;
        while (currentState.action != "") {
            path.push_back(currentState.action);
            currentState = predecessor[currentState.a][currentState.b]; //trace back the steps from the goal state to the initial state
        }

        reverse(path.begin(), path.end()); //path vector is reversed to obtain the correct order of actions

        for(string x : path){
          solution += x;
          solution += "\n";
        }
        solution += "success " + to_string(cost);
        return 1;
      }

    //exploring different possible operations or transitions from the current state and enqueuing them into the priority queue
      nextOperation(q, distance, currentA, currentB, "fill A", cfA, currentState, predecessor);
      nextOperation(q, distance, currentA, currentB, "fill B", cfB, currentState, predecessor);
      nextOperation(q, distance, currentA, currentB, "empty A", ceA, currentState, predecessor);
      nextOperation(q, distance, currentA, currentB, "empty B", ceB, currentState, predecessor);
      nextOperation(q, distance, currentA, currentB, "pour A B", cpAB, currentState, predecessor);
      nextOperation(q, distance, currentA, currentB, "pour B A", cpBA, currentState, predecessor);
    }
  }
    solution = "";
    return 0;
  }
void Jug::nextOperation(priority_queue<State, vector<State>, greater<State>> &q, vector <vector <int>> &distance, int currentA, int currentB, string action, int cost, State previousState, vector <vector<State>> &predecessor){
  int newA;
  int newB; //represent the new amounts of liquid in jugs A and B after performing the given action
  if (action == "fill A"){
    newA = Ca;
    newB = currentB;
  }
  else if (action == "fill B"){
    newB = Cb;
    newA = currentA;
  }  
  else if (action == "empty A"){
    newA = 0;
    newB = currentB;
  }
  else if (action == "empty B"){
    newB = 0;
    newA = currentA;
  }
  else if (action == "pour A B"){
    int neededByB = Cb - currentB;
    int canProvideA = currentA;
    
    if(canProvideA >= neededByB){
      newA = currentA - neededByB;
      newB = Cb;
    }
    else{
      newA = 0;
      newB = currentB + canProvideA;
    }
  }
  else if (action == "pour B A"){
    int neededByA = Ca - currentA;
    int canProvideB = currentB;
    
    if(canProvideB >= neededByA){
      newB = currentB - neededByA;
      newA = Ca;
    }
    else{
      newB = 0;
      newA = currentA + canProvideB;
    }
  }

//checks if the new state represented by newA and newB has a higher cost (distance) than the current state (currentA and currentB) plus the cost of the current action (cost)
  if(distance[newA][newB] > distance[currentA][currentB] + cost){
 
      q.push({newA, newB, action, previousState.cost + cost});
      State s;
      s.a = newA;
      s.b = newB;
      s.cost = previousState.cost + cost;
      s.action = action;
      predecessor[newA][newB] = previousState;
      distance[newA][newB] = distance[currentA][currentB] + cost;
  }
//ensures that only the states with the lowest cost are added to the priority queue
}

