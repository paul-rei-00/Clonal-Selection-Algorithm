#include "Cell.h"
#include <ctime>
#include <algorithm>
#include <iostream>

Cell::Cell(std::initializer_list<int> cell)
	: data(cell),
	  cell_size(cell.size())
{}

Cell::Cell(size_t size)
	: data(size),
	  cell_size(size)
{
	for (int i = 0; i < size; i++)
		this->data[i] = rand() % 2;
}

size_t Cell::size() const
{
	return this->data.size();
}

Cell* Cell::copy()
{
	Cell* copy = new Cell(0);
	copy->data = this->data;
	copy->cell_size = this->cell_size;
	return copy;
}

void Cell::mutate(double p_mut) {
	int amount = ceil(this->cell_size * p_mut);
	std::vector<int> idxs(amount, -1);
	int i = 0;
	while (i != amount)
	{
		int bit = rand() % amount;
		if (std::find(idxs.begin(), idxs.end(), bit) != idxs.end())
		{
			continue;
		}
		else
		{
			idxs[i++] = bit;
			(this->data[bit] == 1) ? this->data[bit] = 0 : this->data[bit] = 1;
		}
	}
}

size_t Cell::affinity(Cell & first, Cell & seccond)
{
	// Hamming distance
	size_t affinity = 0;
	for (int i = 0; i < first.cell_size; i++)
		if (first.data[i] != seccond.data[i])
			affinity++;
	return affinity;
}

void Cell::print_cell(Cell & cell, size_t size, size_t width)
{
	for (size_t i = 0; i < size; i++)
		(i % width) ? std::cout << cell.data[i] << ' ' : std::cout << std::endl << cell.data[i] << ' ';
}

