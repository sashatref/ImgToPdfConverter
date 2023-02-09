#include "FileListWidget.h"
#include "ui_FileListWidget.h"

FileListWidget::FileListWidget(QWidget *parent) :
    ExtendedWidget(parent),
    ui(new Ui::FileListWidget)
{
    ui->setupUi(this);

    ui->addFileBtn->setIcon(IconsEnum::getIcon(IconsEnum::SP_Plus1));
    ui->clearAllBtn->setIcon(IconsEnum::getIcon(IconsEnum::SP_Delete1));
}

FileListWidget::~FileListWidget()
{
    delete ui;
}

QStringList FileListWidget::getFiles() const
{
    QStringList out;

    for(int i = 0 ; i < ui->listWidget->count(); i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        out << item->data(Qt::UserRole).toString();
    }

    return out;
}

void FileListWidget::addFiles(const QStringList &_files)
{
    for(auto &it : _files)
    {
        addFile(it);
    }
}

void FileListWidget::dropEvent(QDropEvent *event)
{
    const QStringList files = getFilesUrl(event);
    if(files.isEmpty())
    {
        event->ignore();
        return;
    }

    for(auto &it : files)
    {
        addFile(it);
    }
}

void FileListWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if(!getFilesUrl(event).isEmpty())
    {
        event->acceptProposedAction();
        return;
    }

    event->ignore();
}

void FileListWidget::dragMoveEvent(QDragMoveEvent *event)
{

}

void FileListWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}

void FileListWidget::on_addFileBtn_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Выберите файлы"), m_lastPath);
    if(files.size() == 0)
    {
        return;
    }

    m_lastPath = QFileInfo(files.first()).absolutePath();

    addFiles(files);
}

void FileListWidget::on_clearAllBtn_clicked()
{
    if(QMessageBox::question(this, tr("Уверены?"), tr("Очистить список?")) == QMessageBox::Yes)
    {
        ui->listWidget->clear();
    }
}

void FileListWidget::addFile(const QString &_path)
{
    QListWidgetItem *item = new QListWidgetItem();
    item->setData(Qt::UserRole, _path);
    item->setText(QFileInfo(_path).fileName());

    ui->listWidget->addItem(item);
}

void FileListWidget::loadState(const LayoutSaver &_saver)
{
    _saver.load(m_lastPath, "lastPath");
}

void FileListWidget::saveState(LayoutSaver &_saver) const
{
    _saver.save(m_lastPath, "lastPath");
}

void FileListWidget::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    Q_UNUSED(previous);

    if(current == nullptr)
    {
        emit fileSelected(QString());
        return;
    }

    emit fileSelected(current->data(Qt::UserRole).toString());
}

void FileListWidget::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    QMenu menu;

    QList<QListWidgetItem*> selected = ui->listWidget->selectedItems();
    if(selected.size() == 0)
    {
        return;
    }

    menu.addAction(tr("Удалить"), this, [=]
    {
        if(QMessageBox::question(this, tr("Уверены?"), tr("Удалить выбранные элементы из списка?")) == QMessageBox::Yes)
        {
            qDeleteAll(selected);
        }
    });

    menu.exec(ui->listWidget->mapToGlobal(pos));
}

QStringList FileListWidget::getFilesUrl(QDropEvent *event)
{
    const QMimeData* mimeData = event->mimeData();

    QStringList out;

    if (mimeData->hasUrls())
    {
        for(auto &it : mimeData->urls())
        {
            out << it.toLocalFile();
        }
    }

    return out;
}
