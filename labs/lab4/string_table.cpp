#include "string_table.h"

StringTable::StringTable(size_t rows, size_t cols)
{
    cells_=new string[rows*cols];
    nrows_=rows;
    ncols_=cols;
}

StringTable::~StringTable()
{
    delete[] cells_;
}

size_t StringTable::size_rows()
{
    return nrows_;
}
size_t StringTable::size_columns()
{
    return ncols_;
}

string & StringTable::at(int rowIndex, int colIndex)
{
    return cells_[colIndex+rowIndex*ncols_];
}

void StringTable::print()
{
    for(int i=0;i<nrows_;i++)
    {
        for(int j=0;j<ncols_;j++)
        {
            cout<<cells_[i*ncols_+j]<<", ";

        }
        cout<<endl;
    }
    cout<<endl;
}