# C Projects Example

Welcome to the **C Projects Example** repository! This collection contains various projects and code samples written in C, organized into categories for easier navigation. These projects cover essential programming concepts, algorithms, game implementations, and operating system topics, making this repository a valuable resource for learning C and exploring various programming techniques.

## Repository Structure

The repository is divided into three main categories:

- [**Algorithms**](#algorithms)
- [**Games**](#games)
- [**Operating System Concepts**](#operating-system-concepts)

Each folder contains projects demonstrating specific C programming techniques and computer science principles. See below for details on each category and the projects included.

---

### Algorithms

The **Algorithms** folder contains implementations of foundational algorithms. These projects highlight basic data manipulation, mathematical sequences, and functional programming techniques.

#### Projects:

1. **String Operations** (`StringOperations.c`)
   - Implements essential string operations, such as calculating length, comparing, and sorting strings.
   - **Usage**:
     ```bash
     gcc StringOperations.c -o string_operations
     ./string_operations
     ```

2. **Fibonacci Sequence** (`Fibonacci.c`)
   - Recursive approach for calculating the Fibonacci sequence. Demonstrates basic recursion.
   - **Usage**:
     ```bash
     gcc Fibonacci.c -o fibonacci
     ./fibonacci
     ```

3. **Deck of Cards** (`DeckOfCards.c`)
   - Simulates a deck of cards with functions to fill, shuffle, and print the deck, showcasing struct manipulation.
   - **Usage**:
     ```bash
     gcc DeckOfCards.c -o deck_of_cards
     ./deck_of_cards
     ```

4. **Map and Fold Operations** (`MapAndFold.c`)
   - Demonstrates higher-order functions like `map` and `fold`, applying functional programming techniques to an array.
   - **Usage**:
     ```bash
     gcc MapAndFold.c -o map_fold
     ./map_fold
     ```

---

### Games

The **Games** folder features simple C-based games that incorporate semaphores and threading to manage concurrency, player actions, and game flow. These examples are both fun and educational, showing how synchronization can be applied in game development.

#### Projects:

1. **Tic Tac Toe Game** (`TicTacToe_Game.c`)
   - A two-player Tic Tac Toe game using semaphores for player synchronization.
   - **Usage**:
     ```bash
     gcc TicTacToe_Game.c -o tictactoe -lpthread
     ./tictacttoe
     ```

2. **Rock Paper Scissors Game** (`RockPaperScissors_Game.c`)
   - A multi-round Rock Paper Scissors game where semaphores manage each player's moves.
   - **Usage**:
     ```bash
     gcc RockPaperScissors_Game.c -o rps -lpthread
     ./rps <number_of_rounds>
     ```

3. **Magic Square Game** (`MagicSquareGame.c`)
   - A game based on a 3x3 grid where players attempt to achieve a sum of 15. Semaphore-based synchronization is used for player turns.
   - **Usage**:
     ```bash
     gcc MagicSquareGame.c -o magic_square -lpthread
     ./magic_square
     ```

---

### Operating System Concepts

The **Operating System Concepts** folder provides projects that illustrate essential OS principles, including synchronization mechanisms, deadlock prevention, and resource management. These projects are ideal for exploring how operating systems handle concurrency, mutual exclusion, and process synchronization.

#### Projects:

1. **Process Scheduler Simulation** (`ProcessScheduler_Simulation.c`)
   - Simulates a process scheduler using queues and semaphores to manage process execution.
   - **Usage**:
     ```bash
     gcc ProcessScheduler_Simulation.c -o process_scheduler -lpthread
     ./process_scheduler
     ```

2. **Banker's Algorithm** (`BankersAlgorithm.c`)
   - Implements the Banker's Algorithm to prevent deadlock by ensuring the system is in a safe state during resource allocation.
   - **Usage**:
     ```bash
     gcc BankersAlgorithm.c -o bankers -lpthread
     ./bankers
     ```

3. **Deadlock Detection Simulation** (`DeadlockDetectionSimulation.c`)
   - Simulates deadlock detection by monitoring resource requests and determining if the system is deadlock-free.
   - **Usage**:
     ```bash
     gcc DeadlockDetectionSimulation.c -o deadlock_detection -lpthread
     ./deadlock_detection
     ```

4. **Readers-Writers Problem** (`ReadersWriters.c`)
   - Solves the Readers-Writers problem with semaphores and mutexes to manage concurrent access to shared resources.
   - **Usage**:
     ```bash
     gcc ReadersWriters.c -o readers_writers -lpthread
     ./readers_writers
     ```

5. **Dining Philosophers Problem (Mutex-based)** (`DiningPhilosophers_Mutex.c`)
   - Uses mutexes to manage philosopher states in the Dining Philosophers problem, ensuring starvation prevention.
   - **Usage**:
     ```bash
     gcc DiningPhilosophers_Mutex.c -o dining_philosophers_mutex -lpthread
     ./dining_philosophers_mutex
     ```

6. **Dining Philosophers Problem (Semaphore-based)** (`DiningPhilosophers_Semaphores.c`)
   - Alternative Dining Philosophers solution using semaphores to handle deadlock and starvation.
   - **Usage**:
     ```bash
     gcc DiningPhilosophers_Semaphores.c -o dining_philosophers_semaphores -lpthread
     ./dining_philosophers_semaphores
     ```

7. **Test-and-Set Lock** (`TAS_Lock.c`)
   - Demonstrates a Test-and-Set lock for mutual exclusion in concurrent threads.
   - **Usage**:
     ```bash
     gcc TAS_Lock.c -o tas -lpthread
     ./tas
     ```

8. **Peterson’s Algorithm** (`PetersonAlgorithm.c`)
   - Implements Peterson’s Algorithm for mutual exclusion between two threads.
   - **Usage**:
     ```bash
     gcc PetersonAlgorithm.c -o peterson -lpthread
     ./peterson
     ```

---

## Getting Started

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/SudeCat/C-Projects-Example.git
   cd C-Projects-Example
2. **Compile and Run**:
   Navigate to the relevant folder, compile the file using gcc, and execute it according to the instructions provided for each project.

4. **Explore and Learn**:
   Each project demonstrates specific programming principles and techniques. Use these examples to study algorithms, practice C programming, or explore operating system concepts.

Contributing

Contributions are welcome! If you have improvements, suggestions, or new projects to add, feel free to fork the repository and create a pull request.
