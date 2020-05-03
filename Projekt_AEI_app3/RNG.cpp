#include "RNG.h"
#include <random>
#include <chrono>

std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
std::uniform_real_distribution<double> distribution(0.0, 1.0);


double RNG::rand() {
	return distribution(generator);
}

double RNG::rand(const double min, const double max) {
	return rand() * (max - min) + min;
}