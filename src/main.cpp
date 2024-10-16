#include <iostream>
#include <vector>

#include "sa.hpp"

#ifndef TEMP
#define TEMP 1000
#endif

#ifndef ALPHA
#define ALPHA 0.999
#endif

#ifndef TEMP_MIN
#define TEMP_MIN 10
#endif

/*
 * Função main.
 * Usada apenas para ler os items, a capacidade máxima e
 * imprimir os dados da melhor solução encontrada.
 */

int main(int argc, char *argv[])
{
	char flags = 0;
	for(int i = 1; i < argc; i++){
		if(argv[i][0] == '-'){
			int j = 1;
			while(argv[i][j] != '\0'){
				if(argv[i][j] == 'i') flags |= SIMULATED_ANNEALING_DISABLE_SHOWITRNUM;
				else if(argv[i][j] == 'c') flags |= SIMULATED_ANNEALING_DISABLE_SHOWCRATES;
				j++;
			}
		}
	}

	int number_of_items = 0;
	int capacity = 0;
	std::cin >> number_of_items >> capacity;

	std::vector<long long> items(number_of_items);
	for (auto &i : items) {
		std::cin >> i;
	}

	sa::solution act = sa::solution::simulated_annealing(capacity, items,
	                                                     ALPHA, TEMP, TEMP_MIN);

	act.print_sol(flags);
}
