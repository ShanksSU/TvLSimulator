# TvLSimulator
[![C++](https://img.shields.io/badge/support-C%2B%2B11%20or%20later-blue?style=flat&logo=cplusplus)](https://github.com/topics/cpp) 
[![CMake](https://img.shields.io/badge/support-v2.8.12%20or%20later-blue?style=flat&logo=cmake)](https://cmake.org/) 
## Introduction

In 2022, Alessandro Pluchino, Alessio Emanuele Biondo, and Andrea Rapisarda were awarded the Ig Nobel Prize for their research in the field of economics, which is a humorous parody of the Nobel Prize.

Their paper mathematically explained why success tends to be attributed more to luck than individual talent (Improbable Research, 2022).

By conducting simulations within the context of the "Talent vs. Luck" debate, the paper argues that luck plays a more significant role than talent. This lighthearted affirmation reveals unconventional factors that influence success and prompts contemplation on the interaction between luck and individual abilities.

The conditions of the simulation are as follows:
+ Building an agent-based model
+ Simulating a world where 1000 individuals encounter 500 events
+ Talent follows a normal distribution ranging from 0 to 1
+ Initial asset values are set at 10
+ Conducting 80 iterations with an age range between 20 and 60
+ Events encountered by agents have a 50% chance of being lucky or unlucky
+ + Lucky events double assets based on talent
+ + Unlucky events halve assets regardless of talent

## Project Structure
```
.
├── CMakeLists.txt
├── lib
│   ├── constants.h
│   ├── simulation.cpp
│   └── simulation.h
└── main.cpp
```

## Objective

Build an agent-based model using C++ to implement the model and visualize it in R for analysis.

## References

<b>Environment:</b><br>
gcc version 11.3.0<br>
g++ version 11.3.0<br>
R version 4.2.3<br>
<br>
<b>Reference:</b><br>
Pluchino, A., Biondo, A. E., & Rapisarda, A. (2018). Talent vs. Luck: The Role of Randomness in Success and Failure. <i>Advances in Complex Systems</i>.
https://arxiv.org/abs/1802.07068
