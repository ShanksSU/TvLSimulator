#include "simulation.h"
#include "constants.h"
#include <iostream>
#include <random>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <conio.h>

double Gaussian_noise(double mean, double stddev) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(mean, stddev);
    return dist(gen);
}

void csv_writefile_2d(const std::vector<std::vector<std::string>>& matrix_2d, const std::vector<std::string>& title) {
    std::string file_name = Path;
    std::ofstream file_writer(file_name, std::ios_base::out);

    if (!file_writer) {
        std::cout << "無法打開文件：" << file_name << std::endl;
        return;
    }

    for (unsigned int t = 0; t < title.size(); t++) {
        file_writer << title[t];
        if (t != title.size() - 1) {
            file_writer << ",";
        }
    }
    file_writer << std::endl;

    for (const auto& row : matrix_2d) {
        for (unsigned int j = 0; j < row.size(); j++) {
            file_writer << row[j];
            if (j != row.size() - 1) {
                file_writer << ",";
            }
        }
        file_writer << std::endl;
    }

    file_writer.close();
    std::cout << "寫入完成" << std::endl;
}

template<typename T>
std::string to_string(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

std::vector<std::string> Person::title = { "id", "wealth", "talent", "lucky_cnt", "unlucky_cnt" };

Person::Person() : id(""), talent(Gaussian_noise(M_T, SD_T)), capital(C_0), lucky_cnt(P_L), unlucky_cnt(P_E) {
    person_arr = { to_string(capital), to_string(talent), to_string(lucky_cnt), to_string(unlucky_cnt) };
}

void Person::processEvents(Person& person) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::poisson_distribution<> d(0.5);

    int freq = d(gen);
    for (int i = 0; i < freq; i++) {
        std::uniform_int_distribution<int> dis_int(0, 1);
        std::uniform_real_distribution<double> dis_double(0, 1);

        bool lucky = dis_int(gen);
        if (lucky) {
            if (dis_double(gen) < person.talent) {
                person.capital *= 2;
            }
            person.lucky_cnt++;
        }
        else {
            person.capital /= 2;
            person.unlucky_cnt++;
        }
    }
}

std::vector<std::string> Person::dataArr(const Person& person) {
    return { person.id, to_string(person.capital), to_string(person.talent), to_string(person.lucky_cnt), to_string(person.unlucky_cnt) };
}

void runSimulation() {
    std::vector<Person> population(N);
    for (int i = 0; i < N; i++) {
        population[i].id = "A" + to_string(i);
    }

    std::vector<std::vector<std::string>> data;

    for (int i = 0; i < T_; i++) {
        for (int j = 0; j < N; j++) {
            Person::processEvents(population[j]);
        }
    }

    for (const auto& person : population) {
        data.push_back(Person::dataArr(person));
    }

    csv_writefile_2d(data, Person::title);
}

void runSimulationLoop() {
    int k_cut = 1;
    printf_s("開始運行\n\n");
    while (1) {
        if (_kbhit()) {
            int ch = _getch();
            if (ch == 32) {
                system("cls");
                printf_s("開始運行\n\n第 %d 次\n", k_cut);
                runSimulation();
                k_cut++;
            }
            if (ch == 27) { break; }
        }
    }
}

