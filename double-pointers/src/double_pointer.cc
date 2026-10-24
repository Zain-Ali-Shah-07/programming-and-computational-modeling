#include <iostream>
#include "../include/double_pointer.h"

using namespace std;
#include "double_pointer.h"

void DB::print() const {
    for (size_t i = 0; i < numRows; ++i) {
        const Row& row = rows[i];

        for (size_t j = 0; j < numColumns; ++j) {
            const Column& col = row.columns[j];

            std::cout << col.name << ": " << col.value;

            if (j < numColumns - 1) {
                std::cout << ", ";
            }
        }

        std::cout << std::endl;
    }
}