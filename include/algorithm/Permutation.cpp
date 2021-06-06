#include "Permutation.h"

using namespace Algorithm;

void Permutation::makePermutation(QString& text, const QStringList& permutation)
{
    QString temp;
    //        qDebug() << text;
    for(const auto& index : permutation)
    {
        temp += text[index.toInt()-1];
    }

    text = std::move(temp);
}

QString Permutation::makeEncode(const std::vector<QString>& table, const QStringList& permuationTable)
{
    QStringList resultTable = permuationTable;
    int i = 0;

    m_description.GetContentDetails() += TAB + "Після цього робимо перестановку столбців за ключем: \n";

    for(const auto& column : permuationTable)
    {
        int _column = column.toLongLong()-1;
        QString resStr = "";

        for(const auto& c : table)
            if(auto symbol = c.at(i); symbol != ' ')
                resStr += symbol;

        ++i;
        resultTable[_column] = resStr;

        m_description.GetContentDetails() += DOUBLE_TAB + resStr + " стає " + column + " сторокою\n";
    }

    m_description.GetContentDetails() += TAB + "Ітогова таблица:\n";

    for(const auto& row : resultTable)
        m_description.GetContentDetails() += DOUBLE_TAB + row + "\n";

    return resultTable.join(QString());
}

QString Permutation::makeDecode(const std::vector<QString>& table, const QStringList& permuationTable)
{
//            qDebug() << "table";
//            for(auto v : table)
//                qDebug() << v;

//            qDebug() << "end table";

    QString result = "";

    m_description.GetContentDetails() += TAB + "Після цього необхідно пройтись по кожному стовпцю та зробити перестановку за ключем:\n";

    for(int i{0}; i < table.at(0).size(); ++i)
    {
        QString tmp;
        for(const auto& row : table)
        {
            tmp += row[i];
        }

        m_description.GetContentDetails() += DOUBLE_TAB + "стовбець '" +  tmp + "' після перестановки: '";

        makePermutation(tmp, permuationTable);
        //            qDebug() << tmp;
        result += tmp;

        m_description.GetContentDetails() += tmp.simplified() + "'\n";
    }

    //        qDebug() << result.simplified();
    return result.simplified();
}

std::vector<QString> Permutation::makeEncodeTable(const QString& text, const int& size, const int& chanSize)
{
    QString default_value(chanSize, QChar(' '));
    std::vector<QString> table(size, default_value);

    m_description.GetContentDetails() += TAB + "Розбиваємо вхідний текст на частини, які дорівнюють довжині ключа("
                                         +  QString::number(chanSize) + "):\n";

    for(int i{0}, offset{0}; i < size; ++i)
    {
        if(offset + chanSize > text.size())
        {
            int rest = (offset + chanSize) - text.size();
            table.at(i) = text.mid(offset, chanSize) + QString(rest, QChar(' '));
            m_description.GetContentDetails() += DOUBLE_TAB + table.at(i) + "\n";
        } else {
            table.at(i) = (text.mid(offset, chanSize));
            offset += chanSize;
            m_description.GetContentDetails() += DOUBLE_TAB + table.at(i) + "\n";
        }
    }

    return table;
}

std::vector<QString> Permutation::makeDecodeTable(const QString& text, const int& keyLegth, const QStringList& key)
{
    int stringSize = 0;
    int startSpaceColumns = -1;

    if(int ratio = (text.size() / keyLegth); text.size() % keyLegth == 0)
    {
        stringSize = ratio;
    } else
    {
        stringSize = ratio + 1;
        startSpaceColumns = text.size() - (keyLegth * ratio);
    }

    m_description.GetContentDetails() += TAB + "Розбиваємо вхідний текст на частини, щоб кількість строк дорівнювала довжині ключа(" + QString::number(keyLegth) + "):\n";

    QString default_value(stringSize, QChar(' '));
    std::vector<QString> table(keyLegth, default_value);

    //        qDebug() << key;

    for(int i{0}, offset{0}; i < keyLegth; ++i)
    {
        //            qDebug() << "i" << i+1;
        if(startSpaceColumns != -1)
        {
            auto it = std::find(key.cbegin(), key.cend(), QString::number(i+1));
            //                qDebug() << "startSpaceColumns != -1" << (it == key.cend()) << "distance" << std::distance(key.cbegin(), it);
            if(startSpaceColumns <= std::distance(key.cbegin(), it))
            {
                table.at(i) = (text.mid(offset, stringSize-1)) + ' ';
                offset += stringSize-1;
                //                    qDebug() << "if" << table.at(i);
            } else
            {
                table.at(i) = (text.mid(offset, stringSize));
                offset += stringSize;
            }
        } else
        {
            table.at(i) = (text.mid(offset, stringSize));
            offset += stringSize;
        }

        m_description.GetContentDetails() += DOUBLE_TAB + table.at(i) + "\n";
        //            qDebug() << table.at(i);
    }

    return table;
}

bool Permutation::validateKey(QStringList key)
{
    std::sort(key.begin(), key.end());
    if(key.isEmpty() || key.back().toInt() != key.size()) return false;
    for(auto it = key.cbegin(); it != std::prev(key.cend()); ++it)
        if(it->toInt()+1 != std::next(it)->toInt())
            return false;

    return true;
}

ReturnType Permutation::encode(const QString& text, const QString& key)
{
    auto keyTable = key.split(QString(","));
    //        if(!validateKey(keyTable) || !Utils::validateString(text, ONLY_UKRAINIAN_LETTERS))
    //            return "";
    auto result = text;

    m_description.Clear();

    m_description.AddHeader(ENCODING);
    m_description.GetContentDetails() += "Вхідний текст: " + result + "\nКлюч: (";
    for(const auto& s : keyTable)
        m_description.GetContentDetails() += s + ",";
    m_description.GetContentDetails().back() = ')';
    m_description.GetContentDetails() += "\nЕтапи:\n";

    result.replace(QRegularExpression("\\s+"), QString());
    int size = text.size() %  keyTable.size() == 0 ? text.size() /  keyTable.size() : (text.size() /  keyTable.size()) + 1;

    result = makeEncode(makeEncodeTable(result, size, keyTable.size()), keyTable);

    m_description.GetContentDetails() += "В результаті отримуємо: " + result + "\n";

    m_description.AddContent();

    return {result, m_description};
}

ReturnType Permutation::decode(const QString& text, const QString& key)
{
    auto keyTable = key.split(QString(","));
    // TODO: add validation
    auto result = text;
    qDebug() << "text" << result;
    result.replace(QRegularExpression("\\s+"), QString());

    m_description.Clear();

    m_description.AddHeader(DECODING);
    m_description.GetContentDetails() += "Вхідний текст: " + result + "\nКлюч: (";
    for(const auto& s : keyTable)
        m_description.GetContentDetails() += s + ",";
    m_description.GetContentDetails().back() = ')';
    m_description.GetContentDetails() += "\nЕтапи:\n";

    result = makeDecode(makeDecodeTable(result, keyTable.size(), keyTable), keyTable);

    m_description.GetContentDetails() += "В результаті отримуємо: " + result + "\n";

    m_description.AddContent();

    return {result, m_description};
}

QString Permutation::generateKey()
{
    return "3,1,4,2,5";
}

Description::Description Permutation::m_description = Description::Description();
