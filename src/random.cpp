#include "random.hpp"

std::random_device rdevice;
std::mt19937_64 rng::rng(rdevice());
