
#include <widgetzeug/DataLinkWidget.h>

#include <QDebug>

#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFileSystemWatcher>
#include <QDirIterator>
#include <QCompleter>
#include <QStringListModel>
#include <QFileSystemModel>

#include "ui_DataLinkWidget.h"


namespace widgetzeug
{

class FileExistsValidator : public QValidator
{
public:
    FileExistsValidator(QObject * parent) : QValidator{parent}
    {
    }

    State validate(QString & input, int & pos) const override
    {
        const auto fileInfo = QFileInfo{input};

        if (fileInfo.exists() && fileInfo.isFile())
            return Acceptable;

        return Intermediate;
    }
};


DataLinkWidget::DataLinkWidget(QWidget * parent)
:   m_ui{new Ui_DataLinkWidget()}
,   m_watcher{ new QFileSystemWatcher{ this } }
{
    m_ui->setupUi(this);

    m_ui->fileNameComboBox->setValidator(new FileExistsValidator{ m_ui->fileNameComboBox });
    m_ui->fileNameComboBox->setCompleter(new QCompleter);

    //    connect(m_watcher, &QFileSystemWatcher::fileChanged, this, &DataLinkWidget::fileChanged);   

    // register every file change to prevent unnecassary fileChanged emits
    connect(this, &DataLinkWidget::fileChanged, [&](const QString & fileName) { 
        m_fileName = fileName; });
}

DataLinkWidget::~DataLinkWidget()
{
    delete m_watcher;
    delete m_ui;
}

void DataLinkWidget::addFileName(const QString & fileName, const bool setCurrent)
{
    if (!isRecent(fileName))
    {
        m_ui->fileNameComboBox->blockSignals(true);
        m_ui->fileNameComboBox->addItem(fileName);
        m_ui->fileNameComboBox->blockSignals(false);
    }

    if (!setCurrent)
        return;

    const auto index = m_ui->fileNameComboBox->findText(fileName);

    m_ui->fileNameComboBox->setCurrentIndex(index);
}

void DataLinkWidget::setFileName(const QString & fileName)
{
    addFileName(fileName, true);
}

QString DataLinkWidget::fileName() const
{
    return m_ui->fileNameComboBox->currentText();
}

void DataLinkWidget::setFilter(const QString & filter)
{
    m_filter = filter;
}

void DataLinkWidget::setReadOnly(bool enabled)
{
    m_ui->savePushButton->setEnabled(!enabled);
}

bool DataLinkWidget::readOnly() const
{
    return !m_ui->savePushButton->isEnabled();
}

bool DataLinkWidget::isRecent(const QString & fileName) const
{
    // Note: file name and absolute file name might be intentionally used 
    // for referencing application relative and absolute files ... 

    return -1 != m_ui->fileNameComboBox->findText(fileName);
}

QCompleter * DataLinkWidget::completer()
{
    return m_ui->fileNameComboBox->completer();
}

void DataLinkWidget::updateWatcher()
{
    //if (m_watchFile && !m_watcher->files().isEmpty())
    //    m_watcher->removePaths(m_watcher->files());
    //else
    //    m_watcher->addPath(m_ui->fileNameComboBox->currentText()); 
}

bool DataLinkWidget::browse()
{
    const auto fileName = QFileDialog::getOpenFileName(this, windowTitle(), QString(), m_filter, nullptr, { QFileDialog::ExistingFile });

    if (fileName.isEmpty())
        return false;

    const auto fi = QFileInfo { fileName };

    auto comboBox = m_ui->fileNameComboBox;
    if (!isRecent(fileName))
        m_ui->fileNameComboBox->addItem(fileName, fi.absoluteFilePath());

    comboBox->setCurrentIndex(comboBox->findText(fileName));

    return true;
}

void DataLinkWidget::save()
{
    if (fileName().isEmpty())
        browse();

    emit save(m_ui->fileNameComboBox->currentText());
}

void DataLinkWidget::on_browsePushButton_clicked(bool)
{
    browse();
}

void DataLinkWidget::on_savePushButton_clicked(bool)
{
    save();
}

void DataLinkWidget::on_fileNameComboBox_currentIndexChanged(const QString & text)
{
    qWarning() << "index ... " << text;

    if (fileName().isEmpty() || m_fileName == fileName())
        return;

    qWarning() << fileName() << " (" << m_fileName << ")";

//    updateWatcher();

    emit fileChanged(fileName());
}

void DataLinkWidget::on_fileNameComboBox_editTextChanged(const QString & text)
{
    const auto fi = QFileInfo(text);
    const auto path = fi.path().isEmpty() ? QDir::currentPath() : fi.path();

    if (path == m_path)
        return;

    // replace fileNameComboBox completer model

    // add all files in current path
    m_path = path;
    QDirIterator iterator(m_path);

    QStringList list;
    while (iterator.hasNext())
    {
        const auto next = iterator.next();
        if (next.endsWith(".") || next.endsWith(".."))
            continue;

        if (next.startsWith("./"))
            list << next.right(next.length() - 2);

        list << next;
    }

    // add recent items contained in fileNameComboBox
    for (auto i = 0; i < m_ui->fileNameComboBox->count(); ++i)
    {
        const auto text = m_ui->fileNameComboBox->itemText(i);
        if (!list.contains(text))
            list << text;
    }

    completer()->setModel(new QStringListModel(list));
}

void DataLinkWidget::on_linkCheckBox_stateChanged(const int state)
{
    /*auto checkState = static_cast<Qt::CheckState>(state);
    m_watchFile = checkState == Qt::Checked;

    if (m_watchFile)
        emit fileChanged(m_ui->fileNameComboBox->currentText());

    updateWatcher();*/
}

} // namespace widgetzeug