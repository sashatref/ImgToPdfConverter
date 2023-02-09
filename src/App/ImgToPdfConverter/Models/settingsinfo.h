#pragma once

#include "project_pch.h"

class SettingsInfo :
        public IGadget,
        public PropertyBrowser3Qt::IPropertyBrowserBase
{
    Q_GADGET
public:
    buildPropertyD(QSize,           pageSize, QSize(3840, 2160))

    static void registerType();

    virtual void propertyInfoMap(PropertyInfoMapType &m) const override;
    virtual bool checkObject(QString &_errorStr) const override;
    virtual const QMetaObject *getMetaObject() const override;
    virtual IGadget *createNew() const override;
};

using sgSettings = Singleton<SettingsInfo>;

Q_DECLARE_METATYPE(SettingsInfo)
