#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QTextStream>
#include <QDebug>

// Инициализирует новый экземпляр класса MainWindow
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setWindowIcon(QIcon(QString::fromLatin1(":/resources/icon.png")));
    ui->setupUi(this);

    // создаем combo box и добавляем его в toolBar
    comboBox = new QComboBox();
    connect(comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(DataBaseUpdate(QString)));
    comboBox->setEnabled(false);
    comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    ui->mainToolBar->addWidget(comboBox);
}

// Очищает текущий экземпляр класса MainWindow
MainWindow::~MainWindow()
{
    delete ui;
}

// очищает модели
void MainWindow::clearModels()
{
    comboBox->clear();
    if (_sqlTableModel != nullptr)
    {
        if (db.isOpen())    // если в прошлый Open открывалась база
        {
            _sqlTableModel->clear();
            _sqlTableModel = nullptr;
            db.close();
        }
    }
    if (_customModel != nullptr)
    {
        _customModel->clear();
        _customModel = nullptr;
    }
}

// Обновляет интерфейс
void MainWindow::UpdateUI(bool openType)
{
    comboBox->setEnabled(openType);
}

// Выход из приложения
void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

// Открывает CSV файл
void MainWindow::on_actionOpen_CSV_triggered()
{
    // получаем имя файла из диалога
    QString name = QFileDialog::getOpenFileName(this,
                tr("Open file"),
                QString(), QString(QString::fromLatin1("CSV (*.csv)")));

    // открываем CSV файл
    if (openCSVFile(name))
    {
        // обновляем интерфейс
        UpdateUI(false);
    }
}

// Открывает CSV файл
bool MainWindow::openCSVFile(const QString& fileName)
{
    QFile file{fileName};
    // если нет имени файла
    if (fileName.isEmpty())
    {
        // выходим
        return false;
    }
    // если не смогли открыть файл
    if (!file.open(QIODevice::ReadOnly))
    {
        // выходим
        return false;
    }
     clearModels();

    QApplication::setOverrideCursor(Qt::WaitCursor);

    // считываем имя колонок
    QString column_names = file.readLine();
    column_names.remove( QRegExp("\r") );
    column_names.remove( QRegExp("\n") );
    QStringList names = column_names.split(";");

    // создаем табличную модель для отображения
    _customModel = new CustomTableModel(this, names);

    // загружаем данные
    QString data = file.readAll();
    data.remove( QRegExp("\r") ); //remove all ocurrences of CR (Carriage Return)
    QString temp;
    QChar character;
    QTextStream textStream(&data);

    // пока не дойдем до конца данных
    while (!textStream.atEnd()) {
        // получаем символ
        textStream >> character;
        if (character == CSV_DIVIDER || character == '\n') {
            if(temp.count("\"")%2 != 0)
            {
                temp.append(character);
                continue;
            }
            temp = DeleteExtraSymbols(temp);
            standardItemList.append(temp);
            if (character != QChar(CSV_DIVIDER)) {
                _customModel->appendRow(standardItemList);
                standardItemList.clear();
            }
            temp.clear();
        } else if (textStream.atEnd()) {
            temp.append(character);
            temp = DeleteExtraSymbols(temp);
            standardItemList.append(temp);
            _customModel->appendRow(standardItemList);
            standardItemList.clear();
            temp.clear();
        } else {
            temp.append(character);
        }
    }

    QApplication::restoreOverrideCursor();

    // определяем типы считанных данных
    _customModel->DetermineColumnsTypes();
    // устанавливаем модель в просмотрщик таблиц
    ui->tableView->setModel(_customModel);

    return true;
}

// Удаляет лишние спец символы
QString MainWindow::DeleteExtraSymbols(QString temp)
{
    if (temp.startsWith( QChar('\"')) && temp.endsWith( QChar('\"') ) ) {
         temp.remove( QRegExp("^\"") );
         temp.remove( QRegExp("\"$") );
    }
    temp.replace("\"\"", "\"");
    return temp;
}

// Открывает SQLite базу данных
void MainWindow::on_actionOpen_SQLite_Table_triggered()
{
    QString name = QFileDialog::getOpenFileName(this,
                tr("Open file"),
                QString(), QString(QString::fromLatin1("SQLite files(*.sqlite *.db)")));

    // открываем SQL базу данных
    if(openSql(name))
    {
        // обновляем интерфейс
        UpdateUI(true);
    }
    else
    {
        // обновляем интерфейс
        UpdateUI(false);
    }
}

// Открывает SQLite базу данных
bool MainWindow::openSql(const QString& fileName)
{
    // если нет имени файла
    if (fileName.isEmpty())
    {
        // выходим
        return false;
    }
    clearModels();

    // открываем базу данных
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileName);
    if(!db.open())
        return false;

    // создаем табличную модель для отображения
    _sqlTableModel = new QSqlTableModel(this);
    // всегда открываем первую таблицу в списке
    _sqlTableModel->setTable(db.tables()[0]);
    _sqlTableModel->select();

    // добавляем список таблиц в comboBox
    comboBox->addItems(db.tables());

    ui->tableView->setModel(_sqlTableModel);

    return true;
}

// Открывает таблицу выбранную в комбобоксе
void MainWindow::DataBaseUpdate(QString tableName)
{
    if(tableName.isEmpty() || tableName == "")
        return;

    _sqlTableModel->setTable(tableName);
    _sqlTableModel->select();
}

// Сохраняет в CSV файл
void MainWindow::on_actionSave_To_CSV_triggered()
{
    // выбираем куда сохранить
    QString fileName = QFileDialog::getSaveFileName(
                this,
                tr("Save CSV File"),
                QString(), QString::fromLatin1("CSV (*.csv)"));

    // если успешно сохранили
    saveCSVFile(fileName);

}

// Сохраняет в CSV файл
bool MainWindow::saveCSVFile(const QString& fileName)
{
    // если не выбрали
    if (fileName.isEmpty())
    {
        // ниче не делаем
        return false;
    }

    QList<QStringList>* data;
    QStringList* column_names;

    // показывает пуста ли сохраняемая таблица
    bool isTablesEmpty = true;
    // если csv таблица не пуста
    if (_customModel != nullptr)
        if (!(_customModel->IsEmpty()))
        {
            // показываем, что таблица не пуста
            isTablesEmpty = false;
            // получаем данные
            data = _customModel->getData();
            // получаем заголовки колонок
            column_names = _customModel->getColNames();
        }

    // если sql таблица не пуста
    if (_sqlTableModel != nullptr && isTablesEmpty)
        if (_sqlTableModel->rowCount() > 0)
        {
            // показываем, что таблица не пуста
            isTablesEmpty = false;

            // получаем заголовки колонок
            column_names = new QStringList();
            for (int j = 0; j < _sqlTableModel->columnCount(); ++j)
                column_names->append(_sqlTableModel->headerData(j, Qt::Horizontal).toString());

            // получаем данные
            QStringList* line = new QStringList();
            data = new QList<QStringList>();
            for (int i = 0; i < _sqlTableModel->rowCount(); ++i)
            {
                line->clear();

                for (int j = 0; j < _sqlTableModel->columnCount(); ++j)
                    line->append(_sqlTableModel->data(_sqlTableModel->index(i, j)).toString());

                data->append(*line);
            }
        }

    // если таблица пуста
    if (isTablesEmpty)
    {
        // возвращаем false
        return false;
    }

    // открываем файл для сохранения
    QFile file{fileName};
    file.open(QIODevice::WriteOnly);
    QString data_string {""};
    QTextStream stream{&file};

    // записываем имена колонок
    data_string = column_names->join(CSV_DIVIDER);
    data_string += ("\r\n");
    stream << data_string;
    data_string.clear();

    // записываем данные
    for(int i = 0; i < data->size(); ++i)
    {
        for(int j = 0; j <data->at(i).size(); ++j)
        {
            QString temp = data->at(i)[j];
            if (temp.contains('\"'))
            {
                temp.replace('\"', "\"\"");
            }
            if (temp.contains(CSV_DIVIDER))
            {
                data_string += "\"";
                temp += "\"";
            }
            data_string += temp;
            data_string += (CSV_DIVIDER);

        }
        data_string.remove(data_string.size()-1,1);
        data_string += ("\r\n");
        stream << data_string;
        data_string.clear();
    }
    stream << data_string;

    // закрываем файл
    file.close();

    // возвращаем true
    return true;
}

// Сохраняет в SQLite
void MainWindow::on_actionSave_To_SQLite_triggered()
{
    // открываем диалог
    saveSqlDialog = new SaveToSqlDialog(this);
    int result = saveSqlDialog->exec();

    QString tableName;
    QSqlDatabase temp;
    // если нажали OK
    if (result == QDialog::Accepted)
    {
        // получаем базу данных, в которую будем сохранять и имя таблицы
        tableName = saveSqlDialog->GetDataToSave(temp);
        // получаем текущую модель
        QAbstractTableModel* currentModel = qobject_cast<QAbstractTableModel*>(ui->tableView->model());
        // создаем таблицу, и заполняем заголовок
        fillFromHeader(*currentModel, temp, tableName);
        // заполняем данные
        fillFromData(*currentModel, temp, tableName);

    }

        temp.close();
}

// создает таблицу и записывает заголовки
// если таблица существует, она будет перезаписана
void MainWindow::fillFromHeader(
        const QAbstractTableModel& model,
        QSqlDatabase& dataBaseToSave,
        QString tableName)
{
    QSqlQuery query(dataBaseToSave);
    QString str = "CREATE TABLE " + tableName + " (";

    for (int i = 0; i < model.columnCount(); i++)
    {
        QString columnName = model.headerData(i, Qt::Horizontal).toString();
        if (columnName.contains(' '))
        {
            columnName = '[' + columnName + ']';
        }
        str += columnName + " ";

        // если в модели есть данные, а не только заголовок. таблица - просто шапка без строк
        if (model.rowCount())
        {
            QString tmp = whatTypeOfAttribute(model.data(model.index(0, i)).toString()); // тип поля
            str += tmp;
            columnTypes.append(tmp);
        }
        // если модель пуста, то в базе все поля будут TEXT
        else
        {
            str += "TEXT";
            columnTypes.append("TEXT");
        }

        if (i != model.columnCount() - 1)
            str += ", ";
    }

    str += ");";
    query.exec(str);

    dataBaseToSave.commit();
}

// записывает данные в таблицу
void MainWindow::fillFromData(
        const QAbstractTableModel& model,
        QSqlDatabase& dataBaseToSave,
        QString tableName)
{
    QString str;
    QSqlQuery query(dataBaseToSave);

    dataBaseToSave.transaction();

    for (int i = 0; i < model.rowCount(); ++i)
    {
        str = "INSERT INTO " + tableName + " (";

        for (int j = 0; j < model.columnCount(); ++j)
        {
            QString columnName = model.headerData(j, Qt::Horizontal).toString();
            if (columnName.contains(' '))
            {
                columnName = '[' + columnName + ']';
            }
            str += columnName;

            if (j != model.columnCount() - 1)
                str += ", ";
        }

        str += ") VALUES (";

        for (int j = 0; j < model.columnCount(); j++)
        {
            if (columnTypes.at(j) == "TEXT")
                str += "\'" + model.data(model.index(i, j)).toString() + "\'"; // вставляем как строку, база сама преобразует
            else
                str += model.data(model.index(i, j)).toString(); // вставляем как строку, база сама преобразует

            if (j != model.columnCount() - 1)
                str += ", ";
        }

        str += ");";
        bool b = query.exec(str);
        qDebug() << b << "\n";
    }

    dataBaseToSave.commit();
}

// определяет тип атрибута
QString MainWindow::whatTypeOfAttribute(const QString& str) const
{
  QRegExp reg("^\\-?\\d+\\.+\\d+$");

  if (str.contains(reg))
    return "REAL";

  reg = QRegExp("^\\-?\\d+$");
  if (str.contains(reg))
    return "INTEGER";

  return "TEXT";
}
