#pragma once

#include <QWidget>

namespace Ui {
class FileListWidget;
}

class FileListWidget : public ExtendedWidget
{
    Q_OBJECT

public:
    explicit FileListWidget(QWidget *parent = nullptr);
    ~FileListWidget();

    QStringList getFiles() const;
    void addFiles(const QStringList &_files);


    virtual void dropEvent(QDropEvent *event) override;
    virtual void dragEnterEvent(QDragEnterEvent *event) override;
    virtual void dragMoveEvent(QDragMoveEvent *event) override;
    virtual void dragLeaveEvent(QDragLeaveEvent *event) override;

private slots:
    void on_addFileBtn_clicked();
    void on_clearAllBtn_clicked();

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_listWidget_customContextMenuRequested(const QPoint &pos);

signals:
    void fileSelected(const QString &_path);

private:
    QStringList getFilesUrl(QDropEvent *event);

    void addFile(const QString &_path);

    Ui::FileListWidget *ui;
    QString m_lastPath;

    virtual void loadState(const LayoutSaver &_saver) override;
    virtual void saveState(LayoutSaver &_saver) const override;
};

