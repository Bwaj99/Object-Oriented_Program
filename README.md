This project is an implementation of a problem-solving algorithm for a variation of the classic "Jug Problem" using C++. The Jug Problem involves two jugs, Jug A and Jug B, with different capacities, a target amount of liquid to measure, and various operations to perform on the jugs to achieve the desired target amount while minimizing costs. In this project, you have the following main components:
      - Jug Class (Jug.h and Jug.cpp):
    * The Jug class represents the problem. It is initialized with the capacities of Jug A and Jug B, the target amount to achieve, and the costs associated with various operations (filling, emptying, pouring from one jug to another).
    * The solve method in this class attempts to find a solution to the Jug Problem. It checks if the input parameters are valid and then uses an algorithm to search for a solution while minimizing costs. The solution is stored in a string variable.
      -	State Struct (Jug.h):
    * The State struct represents the state of the problem at a particular point in time. It includes the current amount of liquid in Jug A and Jug B, the action taken to reach this state, and the cost incurred to reach this state. This struct is used to keep track of the state transitions during the search for a solution.
    - Main Program (main.cpp):
    * In the main function, you create instances of the Jug class and provide different sets of input parameters to simulate different instances of the Jug Problem.
    * For each instance, you call the solve method to find a solution. If a valid solution is found, it prints the sequence of actions taken to reach the solution and the total cost.
Overall, this project aims to solve the Jug Problem instances with different sets of parameters (capacities, costs) and output the solution steps along with the associated cost. It uses a search algorithm to explore the state space of the problem efficiently, keeping track of the minimum cost paths to reach the target amount of liquid in the jugs.
