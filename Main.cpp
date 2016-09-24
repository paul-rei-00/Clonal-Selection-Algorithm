#include "Antigene.h"
#include "Antibody.h"
#include <iostream>
#include <array>
#include <ctime>
#include <map>


namespace ClonAlg {
	size_t CELL_SIZE = 12;
	int gen = 330; // how many generations algorithm will pass
	constexpr size_t M = 3; // size of a set of antigenes
	constexpr size_t N = 6; // size of a set of antibodies
	double beta = 1.0;
	double p_mutmax = 0.6; // 60% of the cell will mutate
	size_t Abm_begin = 0; // range in set of antibodies, it shows where is a memory cells (from Abm_begin to Abm_end)
	size_t Abm_end = M;
	size_t Abr_begin = M; // range in set of antibodies, it shows where is a remaining cells (from Arm_begin to Arm_end)
	size_t Abr_end = N;
}

int main() {
	using namespace ClonAlg;
	srand(time(NULL));

	std::array<Antigene*, M> Ag;
	std::array<Antibody*, N> Ab;

	Ag[0] = new Antigene { 0,1,0,0,1,0,0,1,0,0,1,0 }; // 1
	Ag[1] = new Antigene { 1,0,1,1,0,1,1,1,1,0,0,1 }; // 4
	Ag[2] = new Antigene { 1,1,1,0,0,1,0,0,1,0,0,1 }; // 7
	
	for (int i = 0; i < N; i++)
		Ab[i] = new Antibody(CELL_SIZE);


	std::cout << "Generations: " << gen << std::endl;
	while (gen != 0)
	{
		for (int z = 0; z < M; z++)
		{
			// Affinity between antibody and antigene
			std::multimap<int, int> aff;
			for (int i = 0; i < N; i++)
				aff.insert(std::pair<int, int>(Cell::affinity(*Ab[i], *Ag[z]), i));

			int amount = 6; // how many antibodies need to select with the lowest affinity

			// Selection
			auto it = aff.begin();
			while (amount != 0) {
				it++;
				amount--;
			}
			aff.erase(it, aff.end());
			//std::multimap<int, int> abn = aff;

			// Clonning
			std::vector<int> c_amount(aff.size());
			int _i = 0;
			for (auto it = aff.begin(); it != aff.end(); it++)
				c_amount[_i++] = (beta * N) / (it->second + 1);
			
			int Nc = 0; // sum of the all clones
			for (int i = 0; i < c_amount.size(); i++)
				Nc += c_amount[i];

			std::vector<Antibody*> C(Nc);
			std::vector<int> C_indexes(Nc);
			int x = 0;
			it = aff.begin();
			for (int i = 0; i < aff.size(); i++)
			{
				while (c_amount[i] != 0)
				{
					C[x] = Ab[it->second]->copy();
					C_indexes[x++] = it->second + 1;
					c_amount[i]--;
				}
				it++;
			}

			// Mutation of all clones
			for (int i = 0; i < Nc; i++) {
				double p_mut = p_mutmax * ((beta * C_indexes[i]) / N);
				C[i]->mutate(p_mut);
			}

			// Affinity between antibody and antigene
			std::multimap<int, int> aff_star;
			for (int i = 0; i < Nc; i++)
				aff_star.insert(std::pair<int, int>(Cell::affinity(*C[i], *Ag[z]), i));
			
			// Replacing antibody with its best clone
			if (aff_star.begin()->first < Cell::affinity(*Ab[z], *Ag[z]))
				Ab[z] = C[aff_star.begin()->second]->copy();
			
			// Editing of remaining population
			for (int i = Abr_begin; i < Abr_end; i++)
			{
				delete Ab[i];
				Ab[i] = new Antibody(CELL_SIZE);
			}
		}
		--gen;
	}

	std::cout << "\nMemory cell #1:";
	Cell::print_cell(*Ab[0], CELL_SIZE, 3);
	std::cout << "\n\nMemory cell #2:";
	Cell::print_cell(*Ab[1], CELL_SIZE, 3);
	std::cout << "\n\nMemory cell #3:";
	Cell::print_cell(*Ab[2], CELL_SIZE, 3);
	std::cout << std::endl;

	return 0;
}

