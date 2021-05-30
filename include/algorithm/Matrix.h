#pragma once
#include <algorithm>
#include <array>

#include <QString>
#include <QDebug>

class Matrix4X4 {
    constexpr static int matrixSize = 4;

    class Line {
    public:
        using Element = int;
    private:
        std::array<Element, matrixSize> line;
        using Iterator = std::array<Element, matrixSize>::iterator;
        using ConstIterator = std::array<Element, matrixSize>::const_iterator;

    public:
        Line(const std::initializer_list<Element>& init)
        {
            assert(init.size() == matrixSize);
            int i = 0;
            for(const auto& el : init)
            {
                line.at(i) = el;
                ++i;
            }
        }
        Line() = default;

        void ChangeAt(const int& index, const Element& value) { line[index] = value; }
        Element at(const int& index) const { return line.at(index); }

        int size() const { return line.size(); }

        Iterator begin() { return line.begin(); }
        Iterator end() { return line.end(); }
        ConstIterator cbegin() const { return line.cbegin(); }
        ConstIterator cend() const { return line.cend(); }

        void shift(const int& offset)
        {
            auto tmp = line;
            for(int i{0}; i < matrixSize; ++i)
                line[(offset+i)%matrixSize] = tmp[i];

            qDebug() << "shift";
            for(const auto& v : line)
                qDebug("%s", QString::number(v, 16).toStdString().c_str());
        }

        void shiftUp()
        {
            auto tmp = line.front();
            std::transform(std::next(line.cbegin()), line.cend(), line.begin(), [](const Line::Element& line){ return line; });
            line.back() = tmp;
//            qDebug() << "shift";
//            for(const auto& v : line)
//                qDebug("%s", QString::number(v, 16).toStdString().c_str());
        }

        void Print() const
        {
            qDebug("%s %s %s %s", QString::number(line.at(0), 16).toStdString().c_str(),
                   QString::number(line.at(1), 16).toStdString().c_str(),
                   QString::number(line.at(2), 16).toStdString().c_str(),
                   QString::number(line.at(3), 16).toStdString().c_str());
        }

    private:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = Element;
        using difference_type = std::ptrdiff_t;
        using pointer = Element*;
        using reference = Element&;
    }; // Line

    struct Index
    {
        int row;
        int column;
        Index()
            : row{0},
              column{0}
        {}

        Index(int _row, int _column)
            : row{_row},
              column{_column}
        {}

        Index(const std::initializer_list<int>& indexs)
            : row{*indexs.begin()},
              column{*std::prev(indexs.end())}
        {}
    }; // Index

    std::array<Line, matrixSize> m_state;

    friend Line operator* (const Line& lhs, const Line& rhs)
    {
        auto GMul = [](Line::Element a, Line::Element b)
        {
            Line::Element p = 0;

            while (a && b)
            {
                if (b & 1)
                    p ^= a;

                if (a & 0x80)
                    a = (a << 1) ^ 0x11b;
                else
                    a <<= 1;
                b >>= 1;
            }

            return p;
        };

        Line result;
        std::transform(lhs.cbegin(), lhs.cend(), rhs.cbegin(), result.begin(),
                       [&](const Line::Element& lhsValue, const Line::Element& rhsValue)
        {
//            qDebug() << "GMul" << lhsValue << rhsValue << QString::number(GMul(lhsValue,rhsValue), 16);
            return GMul(lhsValue,rhsValue);
        });

        return result;
    }

    friend Line operator^ (const Line& lhs, const Line& rhs)
    {
//        qDebug() << "lhs";
//        lhs.Print();
//        qDebug() << "rhs";
//        rhs.Print();
        Line result;
        std::transform(lhs.cbegin(), lhs.cend(), rhs.cbegin(), result.begin(),
                       [&](const Line::Element& lhsValue, const Line::Element& rhsValue)
        {
//            qDebug("%i(%s) ^ %i(%s) = %i(%s)", lhsValue, QString::number(lhsValue, 16).toStdString().c_str(),
//                   rhsValue, QString::number(rhsValue, 16).toStdString().c_str(),
//                   (lhsValue^rhsValue), QString::number((lhsValue^rhsValue), 16).toStdString().c_str());
            return lhsValue^rhsValue;
        });

        return result;
    }

    using iterator_category = std::random_access_iterator_tag;
    using value_type = Line;
    using difference_type = std::ptrdiff_t;
    using pointer = Line*;
    using reference = Line&;

    using Iterator = std::array<Line, matrixSize>::iterator;
    using ConstIterator = std::array<Line, matrixSize>::const_iterator;


public:
    using Line = Line;

    Matrix4X4() = default;
    Matrix4X4(const QString& str)
    {
        assert(str.size() == 16);
        Line tmp;
        int i {1};
        for(const auto& c : str.toLatin1())
        {
            tmp.ChangeAt((i-1) % matrixSize, static_cast<int>(c));
//            qDebug() << "el" << c << static_cast<int>(c);
            if( i != 0 && i % matrixSize == 0)
            {
//                qDebug() << "tmp" << tmp.at(0) << tmp.at(1) << tmp.at(2) << tmp.at(3);
                ChangeColumn(tmp, (i-1) / matrixSize);
                tmp = {};
            }
            ++i;
        }
    }

    Matrix4X4(const std::initializer_list<std::initializer_list<int>>& table)
    {
        int i = 0;
        for(const auto& row : table)
        {
            m_state.at(i) = row;
            ++i;
        }
    }

    void Print()
    {
        for(const auto& v : m_state)
            qDebug("%s %s %s %s", QString::number(v.at(0), 16).toStdString().c_str(),
                                  QString::number(v.at(1), 16).toStdString().c_str(),
                                  QString::number(v.at(2), 16).toStdString().c_str(),
                                  QString::number(v.at(3), 16).toStdString().c_str());
    }

    Line GetRow(const int& index) const { return m_state.at(index); }
    Line GetColumn(int index) const
    {
//        Print();
        Line column;
        for(int i {0}; i < rows(); ++i)
        {
//            qDebug() << "column";
//            m_state.at(i).Print();
            column.ChangeAt(i, m_state.at(i).at(index));
        }

//        qDebug() << "GetColumn";
//        column.Print();

        return column;
    }

    void ChangeRow(const Line& row, const int& index)
    {
        m_state.at(index) = row;
    }

    void ChangeColumn(const Line& column, const int& index)
    {
        for(int i {0}; i < rows(); ++i)
            m_state.at(i).ChangeAt(index, column.at(i));
    }

    friend Matrix4X4 operator* (const Matrix4X4& lhs, const Matrix4X4& rhs)
    {
        Matrix4X4 result;
        for(int i{0}; i < lhs.columns(); ++i)
            result.ChangeColumn(lhs.GetColumn(i) * rhs.GetColumn(i), i);

        return result;
    }

    friend Matrix4X4 operator^(const Matrix4X4& lhs, const Matrix4X4& rhs)
    {
        Matrix4X4 result;
        for(int i{0}; i < lhs.rows(); ++i)
            result.ChangeRow(lhs.GetRow(i) ^ rhs.GetRow(i), i);

        return result;
    }

    void ChangeAt(const Line::Element& el, const Index& index)
    {
        m_state[index.row].ChangeAt(index.column, el);
//        qDebug() << "ChangeAt" << el << index.row << index.column;
    }

    Line::Element at(const Index& index) const
    {
        return m_state.at(index.row).at(index.column);
    }

    constexpr int rows() const { return matrixSize; }
    constexpr int columns() const { return matrixSize; }

    void rowShift(const int& index, const int& offset)
    {
        m_state.at(index).shift(offset);
    }

    Line& at(int index) { return m_state.at(index); }

    Line& back() { return m_state.back(); }
    Line& front() { return m_state. front(); }

    Iterator begin() { return m_state.begin(); }
    Iterator end() { return m_state.end(); }
    ConstIterator cbegin() const { return m_state.cbegin(); }
    ConstIterator cend() const { return m_state.cend(); }
};
