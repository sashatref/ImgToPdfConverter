#pragma once

#include "project_pch.h"

class SettingsInfo :
        public IGadget,
        public PropertyBrowser3Qt::IPropertyBrowserBase
{
    Q_GADGET
    Q_PROPERTY(QSize pageSize MEMBER m_pageSize)
    Q_PROPERTY(QString lang MEMBER m_lang)
public:
    static void registerType();

    virtual void propertyInfoMap(PropertyInfoMapType &m) const override;
    virtual bool checkObject(QString &_errorStr) const override;
    virtual const QMetaObject *getMetaObject() const override;
    virtual IGadget *createNew() const override;

    QSize m_pageSize = QSize(3840, 2160);
    QString m_lang = "en";
};

using sgSettings = Singleton<SettingsInfo>;

Q_DECLARE_METATYPE(SettingsInfo)
