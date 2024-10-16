#ifndef SIMULATED_ANNEALING_HEADER_12647_H
#define SIMULATED_ANNEALING_HEADER_12647_H

#define SIMULATED_ANNEALING_DISABLE_SHOWCRATES 1
#define SIMULATED_ANNEALING_DISABLE_SHOWITRNUM 2

#include <algorithm>
#include <iostream>
#include <queue>
#include <random>
#include <set>
#include <utility>
#include <vector>

#include "random.hpp"

namespace sa {

using content = std::priority_queue<long long, std::vector<long long>, std::greater<>>;

class box {
	content items;
	long long fullness{};

	/* Troca uma caixa com a outra. */
	friend void swap(box &one, box &two) {
		using std::swap;

		swap(one.items, two.items);
		swap(one.fullness, two.fullness);
	}

	/* Remove o menor item da caixa. */
	void pop() {
		fullness -= items.top();
		items.pop();
	}

	public:

	box() = default;

	/*
	 * Inicialia uma caixa a partir de um conjunto de items e da soma total
	 * dos items.
	 */
	box(content items, long long fullness):
	    items(std::move(items)), fullness(fullness) {}

	/* Adiciona um item a caixa. */
	void add_item(long long item) {
		fullness += item;
		items.push(item);
	}

	/* Limpa a caixa. */
	void clear() {
		while (!items.empty()) {
			items.pop();
		}
		fullness = 0;
	}

	/*
	 * Verifica se é possível move o menor item da caixa atual para a
	 * caixa "other" sem violar as restrições de capacidade.
	 */
	auto swappable10(box &other, int capacity) -> bool {
		return items.top() + other.fullness <= capacity;
	}

	/*
	 * Move o menor item da caixa atual para a caixa "other".
	 */
	void swap10(box &other) {
		other.add_item(items.top());
		pop(); 
	}

	/*
	 * Verifica se é possivel realizar "swap11" com a caixa "other" sem
	 * violar as restrições de capacidade, também verificando se ambos os menores
	 * items são os mesmos.
	 */
	auto swappable11(box &other, int capacity) -> bool {
		long long choice1 = items.top();
		long long choice2 = other.items.top();
		return choice1 != choice2 &&
		       choice1 + other.fullness - choice2 <= capacity &&
		       choice2 + fullness - choice1 <= capacity;
	}

	/*
	 * Troca o menor item da caixa atual com o menor item da caixa
	 * "other"
	 */
	void swap11(box &other) {
		long long choice1 = items.top();
		long long choice2 = other.items.top();

		pop();
		other.pop();
		add_item(choice2);
		other.add_item(choice1);
	}

	/* Imprime todos os items da caixa junto com um identificador. */
	void print(int ind) {
		std::cout << "Caixa " << ind << ":";
		content tmp;
		while (!items.empty()) {
			std::cout << ' ' << items.top();
			items.pop();
		}
		std::cout << '\n';
	}

	/* Retorna um booleano indicando se a caixa está vazia. */
	[[nodiscard]] auto empty() const -> bool {
		return fullness == 0;
	}
};

class solution {
	std::vector<box> boxes;
	long long fitness;
	int capacity;
	int iterations;
	int iteration;

	/* 
	 * Função para trocar duas soluções.
	 * Overload da função std::swap.
	 */
	friend void swap(solution &one, solution &two) {
		using std::swap;

		swap(one.boxes, two.boxes);
		swap(one.capacity, two.capacity);
		swap(one.fitness, two.fitness);
		swap(one.iterations, two.iterations);
		swap(one.iteration, two.iteration);
	}

	/*
	 * Função para usar o swap10 ou swap11 aleatoriamente quando
	 * possível.
	 */
	void random_swap(int choice, std::vector<int> &sequence10, std::vector<int> &sequence11) {
		typedef void (box::*swap)(box&);
		swap swaps[2] = {
			&box::swap10,
			&box::swap11
		};
		std::vector<int>* sequences[2] = {
			&sequence10,
			&sequence11
		};

		int now = rng::random_double<0, 1>() > 0.3 ? 0 : 1;

		if (sequences[now]->empty()) {
			now ^= 1;
			if (sequences[now]->empty()) {
				return;
			}
		}

		std::uniform_int_distribution<> dist(0, (int)sequences[now]->size() - 1);
		(boxes[choice].*swaps[now])(boxes[(*sequences[now])[dist(rng::rng)]]);
	}

	public:
	solution() = default;

	/* Inicializa uma solução a partir da outra. */
	solution(const solution &other, int itr): boxes(other.boxes), fitness(other.fitness), 
	                                          capacity(other.capacity), iteration(itr) {}

	/* Gera a solução inicial a partir dos items disponíveis. */
	solution(const std::vector<long long> &items, int capacity):
	         capacity(capacity), iteration(0) {
		std::multiset<long long> its; // Items ordenados.
		for (auto i : items) {
			its.insert(i);
		}

		long long cap = capacity; // Capacidade restante da caixa atual.
		box tmp; // Caixa atual.

		while (!its.empty()) {
			auto itr = its.upper_bound(cap);
			if (itr == its.begin()) { // Caixa está cheia, cria-se outra.
	        		cap = capacity;
	        		cap -= *its.begin();
	        		itr = its.begin();
	        		this->boxes.emplace_back(tmp);
	        		tmp.clear();
			} else { // Caixa consegue colocar outro elemento.
				itr--;
				cap -= *itr;
			}
			tmp.add_item(*itr);
			its.erase(itr);
		}

		if (!tmp.empty()) {
			this->boxes.emplace_back(tmp);
		}
		fitness = (int)this->boxes.size();
	}

	/* Muda a solução atual para um de seus vizinhos. */
	void setneighbor() {
		int choice = std::uniform_int_distribution<>(0, (int)boxes.size() - 1)(rng::rng);
		std::vector<int> sequence10; // Possíveis candidatos para swap10
		std::vector<int> sequence11; // Possíveis candidatos para swap11

		sequence10.reserve(boxes.size());
		sequence11.reserve(boxes.size());

		for (size_t i = 0; i < (size_t)choice; i++) {
			if (boxes[choice].swappable10(boxes[i], capacity)) {
				sequence10.push_back((int)i);
			}
			if (boxes[choice].swappable11(boxes[i], capacity)) {
				sequence11.push_back((int)i);
			}
		}
		for (size_t i = choice + 1; i < boxes.size(); i++) {
			if (boxes[choice].swappable10(boxes[i], capacity)) {
				sequence10.push_back((int)i);
			}
			if (boxes[choice].swappable11(boxes[i], capacity)) {
				sequence11.push_back((int)i);
			}
		}

		random_swap(choice, sequence10, sequence11);
		if (boxes[choice].empty()) {
			/* 
			 * Caixa agora está vazia, é possível remove-la.
			 */
			swap(boxes[choice], boxes[boxes.size() - 1]);
			boxes.pop_back();
			fitness = (int)boxes.size();
		}
	}

	/*
	 * Imprime todas as informações da solução:
	 * 	- Número de caixas
	 * 	- Items em cada caixa
	 * 	- Iteração onde foi encontrada a solução
	 * 	- Iterações totais ate o fim do algoritmo
	 */
	void print_sol(char flags = 0) {
		if(!(flags & SIMULATED_ANNEALING_DISABLE_SHOWITRNUM)){
			std::cout << "Iteração da solução: " << iteration << '\n';
			std::cout << "Número de iterações calculadas: " << iterations << '\n';
		}
		std::cout << "Número de caixas: " << fitness << '\n';

		if(!(flags & SIMULATED_ANNEALING_DISABLE_SHOWCRATES)){
			for (size_t i = 0; i < boxes.size(); i++) {
				boxes[i].print((int)i + 1);
			}
		}
	}

	/* Pôe o número de iterações totais para a solução. */
	void setiterations(int itr) {
		iterations = itr;
	}

	/*
	 * Declaração do algoritmo, sua implementação está no arquivo
	 * sa.cpp.
	 */
	static auto simulated_annealing(int capacity, const std::vector<long long> &items,
	                                double alpha, double temp,
	                                double temp_min) -> solution;
};

} // namespace sa

#endif
