#include "project_pch.h"

#include "mainwindow.h"
#include "buildNumber.h"
#include "Models/settingsinfo.h"

using SerializerQt::Serializer;

static void registerTypes();

Q_IMPORT_PLUGIN(CustomStylePlugin)

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts, true);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    Q_INIT_RESOURCE(CustomStylePlugin);

#ifdef STATIC
    Q_INIT_RESOURCE(Propertybrowser3_images);
    Q_INIT_RESOURCE(CustomWidgets_images);
    Q_INIT_RESOURCE(loggertemplate);
#endif


    registerTypes();

    ExtendApp a(argc, argv);
    a.setApplicationVersion(FULL_VER);

    a.setStyle(QStyleFactory::create("customStyle"));

    a.getCmdParser()->addPositionalArgument("files", "files");

    a.parseCommandLine();

    SettingsInfo *s = sgSettings::instance();

    a.loadSettings(s);

    int res = 0;
    {
        //запускаем окно авторизации
        MainWindow w;
        w.setObjectName("MainWindow");
        a.loadLayout();
        w.loadWidgetState(a.getLayoutSaver()->value(w.objectName()));
        w.show();
        w.addFiles(a.getCmdParser()->positionalArguments());

        QObject::connect(&a, &ExtendApp::aboutToQuit, [&] { a.saveSettings(s); });
        QObject::connect(&a, &ExtendApp::onExceptionMsg, [](const QString &_msg) {
            qCritical() << _msg;
        });

        w.setOnSaveCallback([&](const QVariant &_val)
        {
            a.getLayoutSaver()->insert(w.objectName(), _val);
        });

        res = a.exec();
    }

    return res;
}



static void registerTypes()
{
    SettingsInfo::registerType();
    PropertyBrowser3::registerBaseTypes();
}
