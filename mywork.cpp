#include <iostream>
#include "geesespotter_lib.h"

char *createBoard(std::size_t xdim, std::size_t ydim);
void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim);
void hideBoard(char *board, std::size_t xdim, std::size_t ydim);
void cleanBoard(char *board);
void printBoard(char *board, std::size_t xdim, std::size_t ydim);
int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc);
int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc);
bool isGameWon(char *board, std::size_t xdim, std::size_t ydim);


char *createBoard(std::size_t xdim, std::size_t ydim) {
	std::size_t capacity{xdim * ydim};
	char *a_board{new char[capacity]};
	for (std::size_t index{0}; index < capacity; ++index) {
		a_board[index] = 0;
	}
	return a_board;
}

void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim) {
	char count{0};
	if ( (xdim == 1) && (ydim == 1) ) {
		return;
	}
	else if ( ((xdim == 1) && (ydim == 2)) || ((xdim == 2) && (ydim == 1)) ) {
		if (board[0] == board[1]) {
			return;
		}
		else {
			if (board[0] == 9) {
				board[1] = 1;
			}
			else {
				board[0] = 1;
			}
		}
	}
	else if ( (xdim == 1) || (ydim == 1) )  {
		std::size_t capacity {xdim*ydim};
		if (board[1] == 9) {
			board[0] = 1;
		}
		if (board[capacity - 2] == 9) {
			board[capacity - 1] = 1;
		}
		for (std::size_t index{1}; index < (capacity - 1); ++index) {
			count = 0;
			if (board[index - 1] == 9) {
				++count;
			}
			if (board[index + 1] == 9) {
				++count;
			}
			board[index] = count;
		}
	}
	else {
		for (std::size_t index{0}; index < xdim*ydim; ++index) {
			count = 0;
			if (board[index] == 9) {
				count = 9;
			}
			//top left corner
			else if (index == 0) {
				if (board[index + 1] == 9) {
					++count;
				}
				if (board[index + xdim] == 9) {
					++count;
				}
				if (board[index + xdim + 1] == 9) {
					++count;
				}
			}
			//top row
			else if (((index < (xdim - 1)) && (index - 1 >= 0)) && ((index + xdim - 1) < (ydim*xdim))) {
				if (board[index - 1] == 9) {
					++count;
				}
				if (board[index + 1] == 9) {
					++count;
				}
				if (board[index + xdim - 1] == 9) {
					++count;
				}
				if (board[index + xdim] == 9) {
					++count;
				}
				if (board[index + xdim + 1] == 9) {
					++count;
				}
			}
			//top right corner
			else if (index == xdim - 1) {
				if (board[index - 1] == 9) {
					++count;
				}
				if (board[index + xdim - 1] == 9) {
					++count;
				}
				if (board[index + xdim] == 9) {
					++count;
				}
			}
			//bottom left corner
			else if (index == ((ydim - 1)*xdim)) {
				if (board[index - xdim] == 9) {
					++count;
				}
				if (board[index - xdim + 1] == 9) {
					++count;
				}
				if (board[index + 1] == 9) {
					++count;
				}
			}
			//bottom row
			else if ((index < (xdim*ydim - 1)) && (index > (ydim - 1)*xdim)) {
				if (board[index - xdim - 1] == 9) {
					++count;
				}
				if (board[index - xdim] == 9) {
					++count;
				}
				if (board[index - xdim + 1] == 9) {
					++count;
				}
				if (board[index - 1] == 9) {
					++count;
				}
				if (board[index + 1] == 9) {
					++count;
				}
			}
			//bottom right corner
			else if (index == ((xdim*ydim) - 1)) {
				if (board[index - xdim - 1] == 9) {
					++count;
				}
				if (board[index - xdim] == 9) {
					++count;
				}
				if (board[index - 1] == 9) {
					++count;
				}
			}
			//left column
			else if ( ((((index - xdim)%xdim) == 0) && (index - xdim >= 0)) && ((index + xdim) < (xdim*ydim))) {
				if (board[index - xdim] == 9) {
					++count;
				}
				if (board[index - xdim + 1] == 9) {
					++count;
				}
				if (board[index + 1] == 9) {
					++count;
				}
				if (board[index + xdim] == 9) {
					++count;
				}
				if (board[index + xdim + 1] == 9) {
					++count;
				}
			}
			//right column
			else if (((index - xdim + 1)%xdim == 0 && (index - xdim) > 0) && (index + xdim - 1) < xdim*ydim) {
				if (board[index - xdim - 1] == 9) {
					++count;
				}
				if (board[index - xdim] == 9) {
					++count;
				}
				if (board[index - 1] == 9) {
					++count;
				}
				if (board[index + xdim - 1] == 9) {
					++count;
				}
				if (board[index + xdim] == 9) {
					++count;
				}
			}
			//general solution
			else {
				if (board[index - xdim - 1] == 9) {
					++count;
				}
				if (board[index - xdim] == 9) {
					++count;
				}
				if (board[index - xdim + 1] == 9) {
					++count;
				}
				if (board[index - 1] == 9) {
					++count;
				}
				if (board[index + 1] == 9) {
					++count;
				}
				if (board[index + xdim - 1] == 9) {
					++count;
				}
				if (board[index + xdim] == 9) {
					++count;
				}
				if (board[index + xdim + 1] == 9) {
					++count;
				}
			}

			board[index] = count;
		}
	}
}

void hideBoard(char *board, std::size_t xdim, std::size_t ydim) {
	for (std::size_t index{0}; index < (xdim*ydim); ++index) {
		board[index] |= hiddenBit();
	}
}

void cleanBoard(char *board) {
	delete[] board;
	board = nullptr;
}

void printBoard(char *board, std::size_t xdim, std::size_t ydim) {
	if ( (xdim > xdim_max()) || (ydim > ydim_max()) ) {
		return;
	}
	std::size_t index{0};
	for (std::size_t y{0}; y < ydim; ++y) {
		for (std::size_t x{0}; x < xdim; ++x) {
			index = ((y*xdim) + x);
			if (board[index] & markedBit()) {
				std::cout << "M";
			} else if (board[index] & hiddenBit()) {
				std::cout << "*";
			} else {
				std::cout << board[index] + 0;
			}
		}
		std::cout << std::endl;
	}
}

int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc) {
	std::size_t index{(yloc*xdim) + xloc};
	if (board[index] == (board[index] & valueMask())) {
		return 2;
	} else if ((board[index] & markedBit()) == markedBit()) {
		return 1;
	} else if ((board[index] & 0x09) == 0x09) {
		board[index] &= valueMask();
		return 9;
	} else {
		board[index] &= valueMask();
		if (board[index] == 0x00) {
			if ( (xdim == 1) && (ydim == 1) ) {
				return 0;
			}
			else if ( ((xdim == 1) && (ydim == 2)) || ((xdim == 2) && (ydim == 1)) ) {
				if (index == 1) {
					if (!(board[index - 1] & markedBit())) {
						board[index - 1] &= valueMask();
					}
					return 0;
				}
				else {
					if (!(board[index + 1] & markedBit())) {
						board[index + 1] &= valueMask();
					}
					return 0;
				}
			}
			else if ( (xdim == 1) || (ydim == 1) )  {
				std::size_t capacity{xdim*ydim};
				if (index == 0) {
					if (!(board[index + 1] & markedBit())) {
						board[index + 1] &= valueMask();
					}
					return 0;
				}
				else if (index == (capacity - 1)) {
					if (!(board[capacity - 2] & markedBit())) {
						board[capacity - 2] &= valueMask();
					}
					return 0;
				}
				else {
					if (!(board[index - 1] & markedBit())) {
						board[index - 1] &= valueMask();
					}
					if (!(board[index + 1] & markedBit())) {
						board[index + 1] &= valueMask();
					}
					return 0;
				}
			}
			else {
				//top left corner
				if (index == 0) {
					if (!(board[index + 1] & markedBit())) {
						board[index + 1] &= valueMask();
					}
					if (!(board[index + xdim] & markedBit())) {
						board[index + xdim] &= valueMask();
					}
					if (!(board[index + xdim + 1] & markedBit())) {
						board[index + xdim + 1] &= valueMask();
					}
					return 0;
				}
				//top row
				else if (((index < (xdim - 1)) && (index - 1 >= 0)) && ((index + xdim - 1) < (ydim*xdim))) {
					if (!(board[index - 1] & markedBit())) {
						board[index - 1] &= valueMask();
					}
					if (!(board[index + 1] & markedBit())) {
						board[index + 1] &= valueMask();
					}
					if (!(board[index + xdim - 1] & markedBit())) {
						board[index + xdim - 1] &= valueMask();
					}
					if (!(board[index + xdim] & markedBit())) {
						board[index + xdim] &= valueMask();
					}
					if (!(board[index + xdim + 1] & markedBit())) {
						board[index + xdim + 1] &= valueMask();
					}
					return 0;
				}
				//top right corner
				else if (index == xdim - 1) {
					if (!(board[index - 1] & markedBit())) {
						board[index - 1] &= valueMask();
					}
					if (!(board[index + xdim - 1] & markedBit())) {
						board[index + xdim - 1] &= valueMask();
					}
					if (!(board[index + xdim] & markedBit())) {
						board[index + xdim] &= valueMask();
					}
					return 0;
				}
				//bottom left corner
				else if (index == ((ydim - 1)*xdim)) {
					if (!(board[index - xdim] & markedBit())) {
						board[index - xdim] &= valueMask();
					}
					if (!(board[index - xdim + 1] & markedBit())) {
						board[index - xdim + 1] &= valueMask();
					}
					if (!(board[index + 1] & markedBit())) {
						board[index + 1] &= valueMask();
					}
					return 0;
				}
				//bottom row
				else if ((index < (xdim*ydim - 1)) && (index > (ydim - 1)*xdim)) {
					if (!(board[index - xdim - 1] & markedBit())) {
						board[index - xdim - 1] &= valueMask();
					}
					if (!(board[index - xdim] & markedBit())) {
						board[index - xdim] &= valueMask();
					}
					if (!(board[index - xdim + 1] & markedBit())) {
						board[index - xdim + 1] &= valueMask();
					}
					if (!(board[index - 1] & markedBit())) {
						board[index - 1] &= valueMask();
					}
					if (!(board[index + 1] & markedBit())) {
						board[index + 1] &= valueMask();
					}
					return 0;
				}
				//bottom right corner
				else if (index == ((xdim*ydim) - 1)) {
					if (!(board[index - xdim - 1] & markedBit())) {
						board[index - xdim - 1] &= valueMask();
					}
					if (!(board[index - xdim] & markedBit())) {
						board[index - xdim] &= valueMask();
					}
					if (!(board[index - 1] & markedBit())) {
						board[index - 1] &= valueMask();
					}
					return 0;
				}
				//left column
				else if ( ((((index - xdim)%xdim) == 0) && (index - xdim >= 0)) && ((index + xdim) < (xdim*ydim))) {
					if (!(board[index - xdim] & markedBit())) {
						board[index - xdim] &= valueMask();
					}
					if (!(board[index - xdim + 1] & markedBit())) {
						board[index - xdim + 1] &= valueMask();
					}
					if (!(board[index + 1] & markedBit())) {
						board[index + 1] &= valueMask();
					}
					if (!(board[index + xdim] & markedBit())) {
						board[index + xdim] &= valueMask();
					}
					if (!(board[index + xdim + 1] & markedBit())) {
						board[index + xdim + 1] &= valueMask();
					}
					return 0;
				}
				//right column
				else if (((index - xdim + 1)%xdim == 0 && (index - xdim) > 0) && (index + xdim - 1) < xdim*ydim) {
					if (!(board[index - xdim - 1] & markedBit())) {
						board[index - xdim - 1] &= valueMask();
					}
					if (!(board[index - xdim] & markedBit())) {
						board[index - xdim] &= valueMask();
					}
					if (!(board[index - 1] & markedBit())) {
						board[index - 1] &= valueMask();
					}
					if (!(board[index + xdim - 1] & markedBit())) {
						board[index + xdim - 1] &= valueMask();
					}
					if (!(board[index + xdim] & markedBit())) {
						board[index + xdim] &= valueMask();
					}
					return 0;
				}
				//general solution
				else {
					if (!(board[index - xdim - 1] & markedBit())) {
						board[index - xdim - 1] &= valueMask();
					}
					if (!(board[index - xdim] & markedBit())) {
						board[index - xdim] &= valueMask();
					}
					if (!(board[index - xdim + 1] & markedBit())) {
						board[index - xdim + 1] &= valueMask();
					}
					if (!(board[index - 1] & markedBit())) {
						board[index - 1] &= valueMask();
					}
					if (!(board[index + 1] & markedBit())) {
						board[index + 1] &= valueMask();
					}
					if (!(board[index + xdim - 1] & markedBit())) {
						board[index + xdim - 1] &= valueMask();
					}
					if (!(board[index + xdim] & markedBit())) {
						board[index + xdim] &= valueMask();
					}
					if (!(board[index + xdim + 1] & markedBit())) {
						board[index + xdim + 1] &= valueMask();
					}
					return 0;
				}
			}
		}
		return 0;
	}
}

int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc) {
	std::size_t index{(yloc*xdim) + xloc + readSizeT()};
	if (board[index] == (board[index] & valueMask())) {
		return 2;
	} else {
		board[index] ^= markedBit();
		return 0;
	}
}

bool isGameWon(char *board, std::size_t xdim, std::size_t ydim) {
	bool result{false};
	int num_geese{0};
	int count_true{0};
	for (std::size_t index{0}; index < (xdim*ydim); ++index) {
		if ((board[index] & valueMask()) == 0x09) {
			++num_geese;
			if (board[index] == (board[index] & valueMask())) {
				result = false;
				break;
			}
		}
		else {
			if (board[index] != (board[index] & valueMask())) {
				result = false;
				break;
			}
			else {
				++count_true;
			}
		}
	}
	if ( (num_geese == (xdim * ydim)) || ((num_geese + count_true) == (xdim*ydim))) {
		result = true;
	}
	return result;
}
