#include <vector>

#ifndef CELL_H
#define CELL_H

class Cell
{
	std::vector<int> data;
	size_t cell_size;
public:
	Cell(const std::initializer_list<int> cell);
	Cell(size_t size);
	Cell() = delete;

	size_t size() const;
	virtual Cell* copy();
	void mutate(double p_mut);
	static size_t affinity(Cell& first, Cell& seccond);
	static void print_cell(Cell & cell, size_t size, size_t width);
};

#endif

