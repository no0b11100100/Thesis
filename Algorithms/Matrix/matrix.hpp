#pragma once

#include <QDebug>

#include <array>

namespace Matrix
{

enum class ShiftDirection
{
    Left,
    Right,
    Up,
    Down
};

enum class Rotation
{
    _90,
    _180,
    _270
};

template <class T, unsigned Rows, unsigned Columns>
class Matrix
{
    std::array<std::array<T, Rows>, Columns> m_matrix;

    using FindingResult = std::pair<bool, int>;

    template<class Line>
    FindingResult find(const Line& line, T item)
    {
        auto it = std::find(line.cbegin(), line.cend(), item);
        if(it == line.cend())
            return {false, -1};

        auto itemIndex = std::distance(line.cbegin(), it);
        return {true, itemIndex};
    }

public:
    Matrix() = default;

    Matrix(T defaultValue)
    {
        for(auto& row : m_matrix)
            for(auto& el : row)
                el = defaultValue;
    }

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

    auto begin() { return m_matrix.begin(); }
    auto end() { return m_matrix.end(); }

    auto cbegin() const { return m_matrix.cbegin(); }
    auto cend() const { return m_matrix.cend(); }

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

    void ChangeRow(int index, const std::array<T, Rows>& rowData)
    {
        assert(index >= 0 && index < Rows);
        assert(rowData.size() == Rows);

        m_matrix.at(index) = rowData;
    }

    void ChangeColumn(int index, const std::array<T, Columns>& columnData)
    {
        assert(index >= 0 && index < Columns);
        assert(columnData.size() == Columns);

        int i{0};
        for(const auto& item : columnData)
        {
            at(i, index) = item;
            ++i;
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

    FindingResult FindInRow(int index, T item) { return find(Row(index), item); }

    FindingResult FindInColumn(int index, T item) { return find(Column(index), item); }

    void PermutateRows(const std::initializer_list<int>& indexs)
    {
        assert(indexs.size() == Rows);
        auto tmp = m_matrix;
        auto it = m_matrix.begin();
        for(const auto& index : indexs)
        {
            *it = tmp.Row(index);
            ++it;
        }
    }

    void PermutateColumns(const std::initializer_list<int>& indexs)
    {
        assert(indexs.size() == Columns);
        auto tmp = m_matrix;
        int i{0};
        for(const auto& index : indexs)
        {
            ChangeColumn(i,tmp.Column(index));
            ++i;
        }
    }

    // TODO: make common function
    void ShiftRow(int index, ShiftDirection direction, int offset)
    {
        auto row = Row(index);

        if(direction == ShiftDirection::Left)
        {
            for(int i{offset}, j{0}; j < Rows; ++i, ++j)
            {
                if(i == Rows) i = 0;
                row.at(j) = m_matrix.at(index).at(i);
            }
        }
        else if(direction == ShiftDirection::Right)
        {
            for(int i{offset}, j{0}; j < Rows; ++i, ++j)
            {
                if(i == Rows) i = 0;
                row.at(i) = m_matrix.at(index).at(j);
            }
        }

        ChangeRow(index, row);
    }

    void ShiftColumn(int index, ShiftDirection direction, int offset)
    {
        auto column = Column(index);
        auto matrixColumn = column;
        if(direction == ShiftDirection::Up)
        {
            for(int i{offset}, j{0}; j < Columns; ++i, ++j)
            {
                if(i == Columns) i = 0;
                column.at(j) = matrixColumn.at(i);
            }
        }
        else if(direction == ShiftDirection::Down)
        {
            for(int i{0}, j{offset}; i < Columns; ++i, ++j)
            {
                if(j == Columns) j = 0;
                column.at(j) = matrixColumn.at(i);
            }
        }

        ChangeColumn(index, column);
    }

    void Rotate(Rotation rotation)
    {
        if(rotation == Rotation::_180)
        {
            for(auto& row : m_matrix)
                std::reverse(row.begin(), row.end());

            std::reverse(m_matrix.begin(), m_matrix.end());
        }
        else if(rotation == Rotation::_270)
        {
            auto tmp = m_matrix;

            int i{0};
            for(auto row : tmp)
            {
                std::reverse(row.begin(), row.end());
                ChangeColumn(i, row);
                ++i;
            }
        }
        else if(rotation == Rotation::_90)
        {
            auto tmp = m_matrix;

            int i{Columns-1};
            for(const auto row : tmp)
            {
                ChangeColumn(i, row);
                --i;
            }
        }

    }

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
