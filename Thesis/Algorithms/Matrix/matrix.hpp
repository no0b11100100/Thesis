#pragma once

#include <QDebug>

#include <array>

namespace Matrix
{

template <class T, unsigned Rows, unsigned Columns>
class Matrix
{
    std::array<std::array<T, Rows>, Columns> m_matrix;

    using FindingResult = std::pair<bool, int>;

    template<class Line>
    FindingResult find(const Line& line, T item)
    {
        auto it = std::find(line.cbegin(), line.cend(), item);
        bool status = it != line.cend();
        if(!status)
            return {status, -1};

        auto itemIndex = std::distance(line.cbegin(), it);
        return {status, itemIndex};
    }

public:
    Matrix() = default;

    Matrix(const std::initializer_list<std::initializer_list<T>>& matrix)
    {
        assert (matrix.size() == Rows);
        auto rowIt = m_matrix.begin();
        for(const auto& row : matrix)
        {
            assert(row.size() == Columns);
            auto columnIt = rowIt->begin();
            for(const auto& item : row)
            {
                *columnIt = item;
                ++columnIt;
            }
            ++rowIt;
        }
    }

    unsigned rows() const { return Rows; }

    unsigned columns() const { return Columns; }

    auto Column(int index) const
    {
        assert(index >= 0 && index < Columns);
        std::array<T, Rows> result;
        auto it = result.begin();

        for(const auto row : m_matrix)
        {
            *it = row.at(index);
            ++it;
        }

        return result;
    }

    auto Row(int index) const
    {
        assert(index >= 0 && index < Rows);
        return m_matrix.at(index);
    }

    void ChangeRow(int index, const std::initializer_list<T>& rowData)
    {
        assert(index >= 0 && index < Rows);
        assert(rowData < Rows);

        m_matrix.at(index) = rowData;
    }

    void ChangeColumn(int index, const std::initializer_list<T>& columnData)
    {
        assert(index >= 0 && index < Columns);
        assert(columnData < Columns);

        auto it = m_matrix.at(index).begin();
        for(const auto item : columnData)
        {
            *it = item;
            ++it;
        }
    }

    T at(int row, int column) const
    {
        assert(row >= 0 && row < Rows);
        assert(column >= 0 && column < Columns);

        return m_matrix.at(row).at(column);
    }

    T& at(int row, int column)
    {
        assert(row >= 0 && row < Rows);
        assert(column >= 0 && column < Columns);

        return m_matrix.at(row).at(column);
    }

    FindingResult findInRow(int index, T item) { return find(Row(index), item); }

    FindingResult findInColumn(int index, T item) { return find(Column(index), item); }

    friend Matrix operator^(const Matrix& lhs, const Matrix& rhs)
    {
        assert(lhs.rows() == rhs.rows());
        assert(lhs.columns() == rhs.columns());
        Matrix result;

        for(unsigned i {0}; i < lhs.rows(); ++i)
            for(unsigned j{0}; j < lhs.columns(); ++j)
                result.at(i,j) = (lhs.at(i,j)^rhs.at(i,j));

        return result;
    }

};


}
