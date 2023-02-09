#include "project_pch.h"
#include "settingsinfo.h"

using namespace PropertyBrowser3Qt;

PS_REGISTER_CONSTRUCTOR_FUNC(&SettingsInfo::registerType)

void SettingsInfo::registerType()
{
    GadgetHelper::registerToIGadgetConverter<SettingsInfo>();
}


void SettingsInfo::propertyInfoMap(PropertyInfoMapType &m) const
{
    QString currentgroup = "MySQL";

    m["appSettings"].m_isExpandable = true;

    m["loginInfo"].m_isHidden = true;

    m["mysqlAdress"] = PropertyInfo(tr("Адрес"), currentgroup, "", false, false, true);
    m["mysqlAdress"].m_description = tr("Адрес");

    m["mysqlDatabase"] = PropertyInfo(tr("База данных"), currentgroup, "", false, false, true);
    m["mysqlDatabase"].m_description = tr("База данных");

    m["mysqlLogin"] = PropertyInfo(tr("Имя пользователя"), currentgroup, "", false, false, true);
    m["mysqlLogin"].m_description = tr("Имя пользователя");

    m["mysqlServiceName"] = PropertyInfo(tr("Имя сервиса"), currentgroup);
    m["mysqlLogFile"] = PropertyInfo(tr("Лог файл"), currentgroup);
    m["mysqlLogFile"].m_properties[StringProperty::EditorType] = StringProperty::OpenFile;

    m["mysqlBinPath"] = PropertyInfo(tr("Каталог bin файлов"), currentgroup);
    m["mysqlBinPath"].m_properties[StringProperty::EditorType] = StringProperty::OpenDir;

    m["sqlBackupPath"] = PropertyInfo(tr("Каталог резевных копий БД"), currentgroup);
    m["sqlBackupPath"].m_properties[StringProperty::EditorType] = StringProperty::OpenDir;

    m["archiveLevels"] = PropertyInfo(tr("Архив"), currentgroup);
    m["studentGroup"] = PropertyInfo(tr("Группа студентов"), currentgroup);

    currentgroup = tr("Шрифты");

    m["manageStudentFont"] = PropertyInfo(tr("Шрифт окна управления студентом"), currentgroup, "", false, false);
    m["manageStudentFont"].m_description = tr("");

    m["loginFormPBFont"] = PropertyInfo(tr("Шрифт окна авторизации"), currentgroup, "", false, false);

    //currentgroup = tr("Обновление");

    m["autoUpdateEnable"] = PropertyInfo(tr("Проверка обновлений"), currentgroup, "", false, false);
    m["autoUpdateEnable"].m_description = tr("Проверка обновлений программы при запуске");

    m["autoUpdatePath"] = PropertyInfo(tr("Директория обновлений"), currentgroup, "", false, false);
    m["autoUpdatePath"].m_description = tr("Путь для проверки наличия обновления модулей ПО");
    m["autoUpdatePath"].m_properties[StringProperty::EditorType] = StringProperty::OpenDir;

    m["autoUpdateEnable"].m_isHidden = true;
    m["autoUpdatePath"].m_isHidden = true;

    currentgroup = tr("Локализация");

    m["language"] = PropertyInfo(tr("Язык"), currentgroup, "", true, false, true);
    m["language"].m_description = tr("Язык интерфейса");

    m["translatePath"] = PropertyInfo(tr("Директория локализаций"), currentgroup, "", false, false);
    m["translatePath"].m_description = tr("Путь для поиска файлов локализаций");
    m["translatePath"].m_properties[StringProperty::EditorType] = StringProperty::OpenDir;

    currentgroup = tr("Другое");

    m["lastUsers"] = PropertyInfo(tr("Список пользлвателей"), currentgroup, "", false, false);
    m["lastUsers"].m_description = tr("Список пользователей, который когда либо авторизировались");

    m["mysqlPassword"].m_isHidden = true;
    m["currentTableColumn"].m_isHidden = true;
    m["pluginEnableList"].m_isHidden = true;
    m["tableData"].m_isHidden = true;
    m["editTableState"].m_isHidden = true;
    m["widgetsState"].m_isHidden = true;

    currentgroup = tr("UPD соединение");
    m["updListeningEnable"] = PropertyInfo(tr("Слушать UPD сообщения"), currentgroup, "", false, false);
    m["networkInterfaceList"] = PropertyInfo(tr("Сетевой интерфейс"), currentgroup, "", false, false);
}

bool SettingsInfo::checkObject(QString &/*_errorStr*/) const
{
    return true;
}

const QMetaObject *SettingsInfo::getMetaObject() const
{
    return &SettingsInfo::staticMetaObject;
}

IGadget *SettingsInfo::createNew() const
{
    return new SettingsInfo();
}

