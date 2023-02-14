#include "project_pch.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "project_pch.h"
#include "buildNumber.h"

#include "Models/settingsinfo.h"

MainWindow::MainWindow(QWidget *parent) :
    ExtendedMainWindow      (parent),
    ui                      (new Ui::MainWindow)
{ 
    ui->setupUi(this);

    m_trayMenu = new TrayMenu(this, windowIcon());

    initAll();

    setCentralWidget(nullptr);
}


MainWindow::~MainWindow()
{
    removeTempDir();
    delete ui;
}

void MainWindow::removeTempDir()
{
    QDir dir(m_tempDir);
    if(dir.exists())
    {
        if(!dir.removeRecursively())
        {
            logMessage(tr("Ошибка удаления каталога [%1]")
                       .arg(dir.absolutePath()), QtWarningMsg);
            return;
        }
    }
}

void MainWindow::logMessage(const QString &_text, QtMsgType _logLevel)
{
    QMessageBox::warning(this, tr("Внимание!"), _text);
    qDebug() << _text;
}

void MainWindow::addFiles(const QStringList &_files)
{
    ui->fileList->addFiles(_files);
}

void MainWindow::updateTemplate()
{
    removeTempDir();

    if(!QDir().mkpath(m_tempDir))
    {
        logMessage(tr("Ошибка создания каталога [%1]").arg(m_tempDir), QtWarningMsg);
        return;
    }

    QStringList files = ui->fileList->getFiles();
    if(files.isEmpty())
    {
        logMessage(tr("Список файлов пуст, нечего экспортировать"), QtWarningMsg);
        return;
    }

    PdfExporter pdf;
    pdf.setPageSize(s->m_pageSize);

    QStringList outFiles;

    QSize printerSize = pdf.getPageRealSize();

    QProgressDialog progress(tr("Перекодируем файлы"), tr("Отмена"), 0, files.size(), this);
    progress.setWindowModality(Qt::WindowModal);

    int i = 1;
    for(auto &it : files)
    {
        progress.setValue(i);
        i++;

        if (progress.wasCanceled())
        {
            return;
        }

        QFileInfo fInfo(it);

        QString destPath = m_tempDir + "/" + fInfo.fileName();

        if(QFile::exists(destPath))
        {
            destPath = m_tempDir + "/" + QUuid::createUuid().toString() + "_" + fInfo.fileName();
        }

        QImage inImg(it);
        if(!inImg.scaled(printerSize, Qt::KeepAspectRatio, Qt::SmoothTransformation).save(destPath))
        {
            logMessage(tr("Ошибка копирования файла [%1] => [%2]").arg(it, destPath), QtWarningMsg);
        }

        outFiles << destPath;
    }

    QString path = QFileDialog::getSaveFileName(this, tr("Сохранить файл"), m_lastSaveFile, "*.pdf");
    if(path.isEmpty())
    {
        return;
    }

    m_lastSaveFile = path;
    pdf.exportFiles(outFiles, path);
    if(QMessageBox::question(this,
                             tr("Заверено"),
                             tr("Файл сохранен [%1]. Открыть для просмотра?")
                             .arg(path)) == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(path));
    }
}




void MainWindow::updateStyle()
{
    ui->actionExit->setIcon(IconsEnum::getIcon(IconsEnum::SP_AppExit));
    ui->actionConfigure->setIcon(IconsEnum::getIcon(IconsEnum::SP_Setting2));
    ui->actionSaveToPdf->setIcon(IconsEnum::getIcon(QStyle::SP_MediaPlay));
}


void MainWindow::registerCustomTypes()
{
    PropertyBrowser3::registerBaseTypes();
}

void MainWindow::initConnections()
{
    connect(ui->fileList, &FileListWidget::fileSelected, this, [=](const QString &_filePath)
    {
       ui->photoViewer->setPixmap(QPixmap(_filePath));
    }, Qt::QueuedConnection);
}

void MainWindow::settingsChanged()
{


}

void MainWindow::loadState(const LayoutSaver &_saver)
{
    _saver.loadMainWindow(this, "mw");
    _saver.load(ui->fileList, "fileList");
    _saver.load(m_lastSaveFile, "lastSaveFile");
}

void MainWindow::saveState(LayoutSaver &_saver) const
{
    _saver.saveMainWindow(this, "mw");
    _saver.save(ui->fileList, "fileList");
    _saver.save(m_lastSaveFile, "lastSaveFile");
}

void MainWindow::initUiComponets()
{
    //добавляет меню для переключения локализации программы
    qApp->langugeHelper()->createActions(ui->menuLanguage, sgSettings::ins().m_lang);
}


void MainWindow::on_actionSaveToPdf_triggered()
{
    updateTemplate();
}

void MainWindow::on_actionConfigure_triggered()
{
    SettingsForm form;
    form.setWindowTitle(tr("Настройки"));
    form.setValue(*s);
    if(form.exec() == QDialog::Accepted)
    {
        *s = form.getValue().value<SettingsInfo>();
        qApp->emitSettingChangeEvent();
    }
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionAddToSendDialog_triggered()
{

}


void MainWindow::updateLanguage()
{
    ui->retranslateUi(this);
    s->m_lang = qApp->langugeHelper()->getCurrentShortLanguageName();
    logMessage(QString(tr("Локализация <%1> загружена"))
               .arg(qApp->langugeHelper()->getCurrentFullLanguageName()), QtInfoMsg);
}
