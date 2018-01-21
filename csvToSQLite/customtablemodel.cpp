#include "customtablemodel.h"
#include <QString>
#include <QDebug>

// Инициализирует новый экземпляр класса CustomTableModel
CustomTableModel::CustomTableModel(QObject * parent, QStringList& column_names)
    : QAbstractTableModel(parent)
{
    QStringList* types = new QStringList();
    for(int i = 0; i < column_names.size(); ++i)
    {
        types->append("string");
    }
    InitCustomTableModel(column_names, *types);
}

// Инициализирует поля класса CustomTableModel
void CustomTableModel::InitCustomTableModel(QStringList& column_names, QStringList& types)
{
    m_column_names = column_names;

    QList<QPair<QString,int>> t_types;
    for(int i = 0; i < types.size(); ++i){
        QPair<QString, int> type;
        type.first = types[i];
        if (type.first.contains("int", Qt::CaseInsensitive))
                type.second = HEADER_INT;
        if (type.first.contains("string", Qt::CaseInsensitive))
                type.second = HEADER_STRING;
        if (type.first.contains("float", Qt::CaseInsensitive))
                type.second = HEADER_FLOAT;
        t_types.push_back(type);
    }
    m_types = t_types;
}


// Очищает текущий экземпляр класса CustomTableModel
CustomTableModel::~CustomTableModel()
{
    clear();
}


// записывает новые данные введенные пользователем
bool CustomTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    // если индекс корректный
    // и роль - изменяемый, или отображаемы, или CheckState
    if (index.isValid() && (role == Qt::EditRole || role == Qt::DisplayRole || role== Qt::CheckStateRole ))
    {
        QStringList &record = m_data[index.row()];
        // определяем соответствие между столбцами и полями структуры
        switch(m_types[index.column()].second) {
        case HEADER_INT:
            record[index.column()] = value.toString();
            break;
        case HEADER_STRING:
            record[index.column()] = value.toString();
            break;
        case HEADER_FLOAT:
            record[index.column()] = value.toString();
            break;
        default:
            return false;
        }

        // испускаем сигнал, что данные изменены.
        emit(dataChanged(index, index));
        // возвращаем значение, что данные изменены успешно
        return true;
    }
    // возвращаем значение, что данные не изменены
    return false;
}

// возвращает количество строк в таблице
int CustomTableModel::rowCount(const QModelIndex &rcParent) const
{
    return m_data.size();
}

// возвращает количество колонок в таблице
int CustomTableModel::columnCount(const QModelIndex &rcParent) const
{
    return m_column_names.size();
}

// выводит данные на экран таблицы
QVariant CustomTableModel::data(const QModelIndex &index, int role) const
{
    // если индекс корректный
    if (index.isValid())
        if (index.row() < rowCount() && index.column() < columnCount())
        {
            // получаем запись ячейки таблицы
            const QString &record = m_data[index.row()][index.column()];
            // если роль - отображаемый, или изменяемый
            if (role == Qt::DisplayRole || role == Qt::EditRole)
            {
                // определяем соответствие между столбцами и полями структуры
                switch(m_types[index.column()].second) {
                case HEADER_INT:
                    return record.toInt();
                case HEADER_STRING:
                    return record;
                case HEADER_FLOAT:
                    return record.toFloat();
                }
                return record;
            }
            return QString();
        }
    return QString();
}

// отображает заголовки колонок
QVariant CustomTableModel::headerData(int nSection,
                                  Qt::Orientation nOrientation,
                                  int nRole) const
{
    if (nRole == Qt::DisplayRole && nOrientation == Qt::Horizontal)
    {
        return m_column_names[nSection];
    }
    return QVariant();
}

// устанавливает флаги для соответсвующей ячейки
Qt::ItemFlags CustomTableModel::flags(const QModelIndex &rcIndex) const
{

    if (!rcIndex.isValid())
        return Qt::ItemIsEnabled;

    Qt::ItemFlags result = QAbstractTableModel::flags(rcIndex);

    result |= Qt::ItemIsDragEnabled;
    result |= Qt::ItemIsEditable;
    return result;
}

// добавляет строку в таблицу
bool CustomTableModel::appendRow(QStringList data)
{
    if (data.size() != m_column_names.size())
        return false;
    m_data.push_back(data);
    return true;
}

// возвращает данные таблицы
QList<QStringList>* CustomTableModel::getData()
{
    return &m_data;
}

// возвращает имена колонок
QStringList* CustomTableModel::getColNames()
{
    return &m_column_names;
}

// определяет типы колонок по их содержимому
void CustomTableModel::DetermineColumnsTypes()
{
    // если список данных пуст
    if (m_data.isEmpty() || m_data.size() == 0)
        return;

    m_types.clear();
    // для всех колонок
    for (int i = 0; i < m_data[0].size(); ++i)
    {
        QPair<QString, int> type;
        // если колонка типа int
        if (CheckIntType(i))
        {
            type.first = "int";
            type.second = HEADER_INT;
            m_types.append(type);
        }
        // если колонка типа real (float)
        else if (CheckRealType(i))
        {
            type.first = "float";
            type.second = HEADER_FLOAT;
            m_types.append(type);
        }
        // если колонка типа string
        else
        {
            type.first = "string";
            type.second = HEADER_STRING;
            m_types.append(type);
        }

    }

}

// проверяет, является ли колонка типа INT
bool CustomTableModel::CheckIntType(int indexColumn)
{
    // для всех колонок
    for (int i = 0; i < m_data.size(); ++i)
    {
        bool check = true;
        int temp = m_data[i][indexColumn].toInt(&check);
        // если не смогли привести значение к типу int
        // и строка не пустая
        if (!check && !(m_data[i][indexColumn].isEmpty()))
        {
            // то значит колонка не является типа integer
           return false;
        }
    }

    return true;
}

// проверяет, является ли колонка типа REAL
bool CustomTableModel::CheckRealType(int indexColumn)
{
    // для всех колонок
    for (int i = 0; i < m_data.size(); ++i)
    {
        bool check = true;
        int temp = m_data[i][indexColumn].toFloat(&check);
        // если не смогли привести значение к типу float
        // и строка не пустая
        if (!check && !(m_data[i][indexColumn].isEmpty()))
        {
            // то значит колонка не является типа float
           return false;
        }
    }

    return true;
}

// очищает таблицу
void CustomTableModel::clear()
{
    m_data.clear();
    m_column_names.clear();
    m_types.clear();
}

// возвращает значение, показывающее, что таблица пуста
bool CustomTableModel::IsEmpty()
{
    return m_data.empty();
}
