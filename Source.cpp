#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <random>
#include <chrono>
#include <random>
#include <fstream>
#include <sstream>
#include <math.h>
#include <unordered_map>
#include <map>
using namespace std;

/*
	模擬的條件如下：
		・模擬一個世界，其中1000人遇到500個事件
		・天賦為正態分佈，範圍在0和1之間
		・資產起始值均為10
		・進行80次迭代，年齡範圍在20到60之間
		・代理人遇到的事件有50%的機率是幸運或是不幸
			※幸運事件根據天賦決定是否使資產翻倍
			※不幸事件無視天賦資產减半


	求一個事件遇到特定期望值的概率 -> 泊松分佈
		由於 500 個事件在 1000 人中移動，因此期望值為 0.5，故相遇的次數是根據λ=0.5 的泊松分佈確定的
*/

#define N 1000		//人數
#define P_E 0.75	//不幸事件概率
#define P_L 0.5		//幸運事件概率
#define C_0 10.		//初始資本
#define T_ 80		//迭代次數
#define M_T 0.6		//期望值
#define SD_T 0.1	//標準差

//高斯正態分佈		mean:期望值， stddev:標準差
double Gaussian_noise(double mean, double stddev) {
	//從epoch（1970年1月1日00:00:00 UTC）開始經過的納秒數，unsigned類型會截斷這個值
	//long long seed = std::chrono::system_clock::now().time_since_epoch().count();
	//default_random_engine generator(seed);
	random_device rd;
	mt19937 gen(rd());
	normal_distribution<double> dist(mean, stddev);
	return dist(gen);
}

//寫入 csv文件
void csv_writefile_2d(vector<vector<string>>& matrix_2d, vector<string> title) {
	string file_name = "E:\\TvsL\\cpp_write.csv";
	ofstream file_writer(file_name, ios_base::out);

	fstream file;
	file.open(file_name);
	if (file.fail()) {
		cout << "開啟失敗";
		exit(1);
	}

	//標題寫入
	for (unsigned int t = 0; t < title.size(); t++) {
		file << title[t];
		if (t != title.size() - 1) {
			file << ",";
		}
	}
	file << endl;

	for (unsigned int i = 0; i < matrix_2d.size(); i++) {
		for (unsigned int j = 0; j < matrix_2d[i].size(); j++) {
			file << matrix_2d[i][j];
			if (j != matrix_2d[i].size() - 1) {
				file << ",";
			}
		}
		file << endl;
	}
	file.close();
	cout << "寫入完成" << endl;
}

//轉換string
template<typename T>
string toString(const T& t) {
	ostringstream oss;
	oss << t;
	return oss.str();
}

class Human {
public:
	Human() {
		id = "";
		talent = Gaussian_noise(M_T, SD_T);
		capital = C_0;
		lucky_cnt = P_L;
		unlucky_cnt = P_E;
	}

	static void possion(Human& man);
	static vector<string> data_arr(Human man);
	static string put_data(Human man);

	string id = "";
	double talent = 0.;
	double capital = 0.;
	double lucky_cnt = 0.;
	double unlucky_cnt = 0.;
	vector<string> Human_arr = { {toString(capital)}, toString(talent), toString(lucky_cnt), toString(unlucky_cnt) };
	vector<string> title = { "id", "wealth", "talent", "lucky_cnt", "unlucky_cnt" };
}H;

void Human::possion(Human& man) {
	random_device rd;
	mt19937 gen(rd());
	poisson_distribution<> d(0.5);	//泊松分布
	int freq = d(gen);

	for (int i = 0; i < freq; i++) {
		uniform_int_distribution<int> dis_int(0, 1);		//離散型均勻分布 生成隨機整數
		uniform_real_distribution<double> dis_double(0, 1);	//連續型均勻分布 生成隨機浮點數
		bool lucky = dis_int(gen);
		if (lucky) {
			if (dis_double(gen) < man.talent) {		//std::rand() / (RAND_MAX + 1.0), dis_double(gen)
				man.capital *= 2;
			}
			man.lucky_cnt++;
		}
		else {	
			man.capital /= 2;
			man.unlucky_cnt++;
		}
	}
}

vector<string> Human::data_arr(Human man) {
	return {	toString(man.id),
				toString(man.capital),
				toString(man.talent),
				toString(man.lucky_cnt),
				toString(man.unlucky_cnt)
	};
}

string Human::put_data(Human man) {
	return toString(man.capital) + "\t" + toString(man.talent) + "\t" + toString(man.lucky_cnt) + "\t" + toString(man.unlucky_cnt);
}

void run_simulation() {
	Human HP[N];
	vector<vector<string>> population;
	for (int i = 0; i < N; i++) {
		//cout << Human::put_data(HP[i]) << endl;
		//population.push_back({ toString(HP[i].talent) });
		HP[i].id = "A" + toString(i);
	}

	for (int j = 0; j < T_; j++) {
		for (auto& man : HP) {
			Human::possion(man);
		}
		//cout << Human::put_data(HP[j]) << endl;
	}

	for (auto man : HP) {
		/*cout << Human::put_data(man) << endl;*/
		population.push_back(Human::data_arr(man));
	}
	csv_writefile_2d(population, H.title);
}

void code_test();
void run_S() {
	int ch = 0;
	int k_cut = 1;
	printf_s("開始運行\n\n");
	while (1) {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 32) {
				system("cls");
				printf_s("開始運行\n\n");
				printf_s("第 %d 次\n", k_cut);
				run_simulation();
				//code_test();
				k_cut++;
			}
			if (ch == 27) { break; }
		}
	}
}

void code_test() {
	mt19937 gen(unsigned int(std::chrono::system_clock::now().time_since_epoch().count()));
	poisson_distribution<> d(0.5);	//泊松分布
	uniform_real_distribution<> dis_int(0., 1.);
	unordered_map<double, int> cut;
	for (int i = 0; i < 1000; i++) {
		cut[dis_int(gen)]++;
	}

	for (auto& m : cut) {
		cout << m.first << "\t" << m.second << endl;
	}
}

int main() {
	run_S();
	//code_test();

	return 0;
}