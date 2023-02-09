#pragma once

#include "Models/settingsinfo.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public ExtendedMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void logMessage(const QString &_text, QtMsgType _logLevel);
    void addFiles(const QStringList &_files);

private:
    SettingsInfo *s = sgSettings::instance();
    Ui::MainWindow *ui;
    TrayMenu *m_trayMenu = nullptr;

    QString m_tempDir = qApp->applicationDirPath() + "/wwwTemp";
    QString m_lastSaveFile;

    void updateTemplate();
    void removeTempDir();

public:
    virtual void updateStyle() override;
    virtual void registerCustomTypes() override;
    virtual void loadState(const LayoutSaver &_saver) override;
    virtual void saveState(LayoutSaver &_saver) const override;

protected:
    virtual void initUiComponets() override;
    virtual void initConnections() override;
    virtual void settingsChanged() override;

private slots:
    void on_actionSaveToPdf_triggered();
    void on_actionConfigure_triggered();
    void on_actionExit_triggered();
    void on_actionAddToSendDialog_triggered();
};

