#include <iostream>
#include <iomanip>

#include <chrono>
#include <utility>
#include <algorithm>

#include <vector>
#include <list>
#include <map>
#include <string>

class Timer { //meranie vypoctoveho casu pomocou STL <chrono>
public:
	static std::chrono::time_point<std::chrono::high_resolution_clock> t_start;
	static std::chrono::time_point<std::chrono::high_resolution_clock> t_end;

	static void start() { t_start = std::chrono::high_resolution_clock::now(); }
	static void end(std::string s) { t_end = std::chrono::high_resolution_clock::now(); print(s); }
	static void print(std::string s) {
		std::cout << std::fixed << std::setprecision(2) << s
			<< std::chrono::duration<double, std::milli>(t_end - t_start).count()
			<< " ms\n";
	}
};

std::chrono::time_point<std::chrono::high_resolution_clock> Timer::t_start = std::chrono::high_resolution_clock::now();
std::chrono::time_point<std::chrono::high_resolution_clock> Timer::t_end = std::chrono::high_resolution_clock::now();

template<class T>
void printVectorData(T* data, int size) {
	for (int i = 0; i < size; i++)
	{
		std::cout << data[i] << std::endl;
	}
}

template<class T>
class myVector {
	private:
		T* data;
		size_t size;
	public:
		enum exceptions {out_of_range};

		myVector() : data(nullptr), size(0) {}
		myVector(size_t n, T def) : size(n) {
			data = new T[n];
			for (size_t i = 0; i < size; i++) {
				data[i] = def;
			}
		}
		~myVector() { delete[] data; }

		void resize(size_t n) {
			T* newData = new T[n];
			for (size_t i = 0; i < std::min(size, n); i++) {
				newData[i] = data[i];
			}
			delete[] data;
			data = newData;
			size = n;
		}

		T& operator[](size_t i) {
			return data[i];
		}

		T& at(size_t i) {
			if (i < 0 || i >= size) {
				throw out_of_range;
			}
			return data[i];
		}

		T& begin() {
			return data[0];		
		}

		T& end() {
			return data[size - 1];
		}
		
		void clear() {
			delete [] data;
			data = nullptr;
			size = 0;
		}
		

		void printAll() {
			for (size_t i = 0; i < size; i++) {
				std::cout << data[i] << ", ";
			}
			std::cout << std::endl;
		}
};


int main() {
	
	// myVector<int> v(12, 3);
	// v.printAll();
	// v.resize(5, 0);
	// v.printAll();
	// v.resize(15, 0);
	// v.printAll();
	// v[1] = 12;
	// v.printAll();
	// v.at(5) = 3;
	// v.printAll();
	// std::cout << v.begin();
	// v.printAll();
	// v.end() = 5;
	// std::cout << v.end();
	// v.printAll();

	size_t n = 250000;

	std::vector<int> v(n, 0);
	myVector<int> mv(n, 0);

	Timer::start();
	for (int i = 0; i < n; i++) {
		v[i] = i;
	}
	Timer::end("STD resize time:");

	Timer::start();
	for (int i = 0; i < n; i++) {
		mv[i] = i;
	}
	Timer::end("Custom resize time:");
	
	mv.at(-1);

	mv.printAll();
	return 0;
}

