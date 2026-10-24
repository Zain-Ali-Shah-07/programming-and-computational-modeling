#include <string>

class Column {
    public:
    std::string name;
    double value;
};

class Row {
    public:
    Column *columns;
};

class DB {
    public:
    Row *rows;
    size_t numRows;
    size_t numColumns;

    void print() const;
};
