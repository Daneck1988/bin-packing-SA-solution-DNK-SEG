#include "sa.hpp"
#include <cmath>

/*
 * Implementação do algoritmo de SA.
 */

auto sa::solution::simulated_annealing(int capacity, const std::vector<long long> &items,
                                       const double alpha, double temp,
                                       const double temp_min)->sa::solution
{
	sa::solution best(items, capacity);
	sa::solution prev = best;

	int iteration = 0;

	while (temp > temp_min) {
		iteration++;
		sa::solution neighbor(prev, iteration);
		neighbor.setneighbor();

		long long diff = neighbor.fitness - prev.fitness;
		if (diff < 0 || rng::random_double<0, 1>() / temp < 0.05) {
			swap(prev, neighbor);
		}

		temp *= alpha;

		if (prev.fitness < best.fitness) {
			best = prev;
		}
	}

	best.setiterations(iteration);
	return best;
}
