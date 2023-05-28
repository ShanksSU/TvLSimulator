#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <string>

class Person {
public:
    Person();
    static void processEvents(Person& person);
    static std::vector<std::string> dataArr(const Person& person);

    std::string id;
    double talent;
    double capital;
    double lucky_cnt;
    double unlucky_cnt;
    std::vector<std::string> person_arr;
    static std::vector<std::string> title;
};

void runSimulation();
void runSimulationLoop();

#endif  // SIMULATION_H
