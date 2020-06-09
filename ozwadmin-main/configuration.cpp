#include <QDate>
#include <QDebug>

#include "configuration.h"
#include "ui_configuration.h"
#include "ozwcore.h"
#include "util.h"

#include "propertybrowser/qtvariantproperty.h"
#include "propertybrowser/qtpropertymanager.h"
#include "propertybrowser/qttreepropertybrowser.h"
#include "propertybrowser/qteditorfactory.h"


Configuration::Configuration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Configuration)
{
    ui->setupUi(this);
    connect(this->ui->buttonBox, &QDialogButtonBox::accepted, this, &Configuration::saveConfiguration);

    QTOZWManager *manager = OZWCore::get()->getQTOZWManager();
    m_options = manager->getOptions();
    QCoreApplication::processEvents();
    if (m_options)
        m_options->setReady(true);
    else
        qCDebug(ozwadmin) << "No m_options";

    { 
        QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory(this);
        QtEnumEditorFactory *enumFactory = new QtEnumEditorFactory(this);
        variantManager = new QtVariantPropertyManager(this);
        enumManager = new QtEnumPropertyManager(this);


        this->m_variantEditor = new QtTreePropertyBrowser(this);
        m_variantEditor->setFactoryForManager(variantManager, variantFactory);
        m_variantEditor->setFactoryForManager(enumManager, enumFactory);
        m_variantEditor->setPropertiesWithoutValueMarked(true);
        m_variantEditor->setRootIsDecorated(false);

        QtProperty *topItem = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),
                    QLatin1String(" Paths"));

        QtVariantProperty *variantitem;
        QtProperty *enumitem;


        {
            variantitem = variantManager->addProperty(QVariant::String, "ConfigPath");
            variantitem->setValue(m_options->ConfigPath());
            variantitem->setBold(settings.contains("openzwave/ConfigPath"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("ConfigPath", variantitem);
        }
        {
            variantitem = variantManager->addProperty(QVariant::String, "UserPath");
            variantitem->setValue(m_options->UserPath());
            variantitem->setBold(settings.contains("openzwave/UserPath"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("UserPath", variantitem);
        }

        m_variantEditor->addProperty(topItem);

        topItem = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),
                                            QLatin1String("Logging"));

        {
            variantitem = variantManager->addProperty(QVariant::Bool, "Logging");
            variantitem->setValue(m_options->Logging());
            variantitem->setBold(settings.contains("openzwave/Logging"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("Logging", variantitem);
        }

        {
            variantitem = variantManager->addProperty(QVariant::String, "LogFileName");
            variantitem->setValue(m_options->LogFileName());
            variantitem->setBold(settings.contains("openzwave/LogFileName"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("LogFileName", variantitem);
        }

        {
            variantitem = variantManager->addProperty(QVariant::Bool, "AppendLogFile");
            variantitem->setValue(m_options->AppendLogFile());
            variantitem->setBold(settings.contains("openzwave/AppendLogFile"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("AppendLogFile", variantitem);
        }

        {
            variantitem = variantManager->addProperty(QVariant::Bool, "ConsoleOutput");
            variantitem->setValue(m_options->ConsoleOutput());
            variantitem->setBold(settings.contains("openzwave/ConsoleOutput"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("ConsoleOutput", variantitem);
        }

        {
            enumitem = enumManager->addProperty("SaveLogLevel");
            enumManager->setEnumNames(enumitem, m_options->SaveLogLevel().getEnums());
            enumManager->setValue(enumitem, m_options->SaveLogLevel().getSelected());
            enumitem->setBold(settings.contains("openzwave/SaveLogLevel"));
            enumitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(enumitem);
            this->m_variantToProperty.insert("SaveLogLevel", enumitem);
        }

        {
            enumitem = enumManager->addProperty("QueueLogLevel");
            enumManager->setEnumNames(enumitem, m_options->QueueLogLevel().getEnums());
            enumManager->setValue(enumitem, m_options->QueueLogLevel().getSelected());
            enumitem->setBold(settings.contains("openzwave/QueueLogLevel"));
            enumitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(enumitem);
            this->m_variantToProperty.insert("QueueLogLevel", enumitem);
        }

        {
            enumitem = enumManager->addProperty("DumpTriggerLevel");
            enumManager->setEnumNames(enumitem, m_options->DumpTriggerLevel().getEnums());
            enumManager->setValue(enumitem, m_options->DumpTriggerLevel().getSelected());
            enumitem->setBold(settings.contains("openzwave/DumpTriggerLevel"));
            enumitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(enumitem);
            this->m_variantToProperty.insert("DumpTriggerLevel", enumitem);
        }

        m_variantEditor->addProperty(topItem);

        topItem = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),
                                            QLatin1String("Driver"));

        {
            variantitem = variantManager->addProperty(QVariant::Bool, "NotifyTransactions");
            variantitem->setValue(m_options->NotifyTransactions());
            variantitem->setBold(settings.contains("openzwave/NotifyTransactions"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("NotifyTransactions", variantitem);
        }

        {
            variantitem = variantManager->addProperty(QVariant::String, "SaveConfiguration");
            variantitem->setValue(m_options->SaveConfiguration());
            variantitem->setBold(settings.contains("openzwave/SaveConfiguration"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("SaveConfiguration", variantitem);
        }

        {
            variantitem = variantManager->addProperty(QVariant::Int, "DriverMaxAttempts");
            variantitem->setValue(m_options->DriverMaxAttempts());
            variantitem->setBold(settings.contains("openzwave/DriverMaxAttempts"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("DriverMaxAttempts", variantitem);
        }

        {
            variantitem = variantManager->addProperty(QVariant::Bool, "SuppressValueRefresh");
            variantitem->setValue(m_options->SuppressValueRefresh());
            variantitem->setBold(settings.contains("openzwave/SuppressValueRefresh"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("SuppressValueRefresh", variantitem);
        }

        {
            variantitem = variantManager->addProperty(QVariant::Int, "RetryTimeout");
            variantitem->setValue(m_options->RetryTimeout());
            variantitem->setBold(settings.contains("openzwave/RetryTimeout"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("RetryTimeout", variantitem);
        }

        {
            variantitem = variantManager->addProperty(QVariant::Bool, "EnableSIS");
            variantitem->setValue(m_options->EnableSIS());
            variantitem->setBold(settings.contains("openzwave/EnableSIS"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("EnableSIS", variantitem);
        }

        {
            variantitem = variantManager->addProperty(QVariant::Bool, "NotifyOnDriverUnload");
            variantitem->setValue(m_options->NotifyOnDriverUnload());
            variantitem->setBold(settings.contains("openzwave/NotifyOnDriverUnload"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("NotifyOnDriverUnload", variantitem);
        }

        m_variantEditor->addProperty(topItem);

        topItem = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),
                                            QLatin1String("Associations"));

        {
            variantitem = variantManager->addProperty(QVariant::Bool, "Associate");
            variantitem->setValue(m_options->Associate());
            variantitem->setBold(settings.contains("openzwave/Associate"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("Associate", variantitem);
        }

        {
            variantitem = variantManager->addProperty(QVariant::Bool, "PerformReturnRoutes");
            variantitem->setValue(m_options->PerformReturnRoutes());
            variantitem->setBold(settings.contains("openzwave/PerformReturnRoutes"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("PerformReturnRoutes", variantitem);
        }


        m_variantEditor->addProperty(topItem);

        topItem = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),
                                            QLatin1String("Polling"));

        {
            variantitem = variantManager->addProperty(QVariant::Int, "PollInterval");
            variantitem->setValue(m_options->PollInterval());
            variantitem->setBold(settings.contains("openzwave/PollInterval"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("PollInterval", variantitem);
        }

        {
            variantitem = variantManager->addProperty(QVariant::Bool, "IntervalBetweenPolls");
            variantitem->setValue(m_options->IntervalBetweenPolls());
            variantitem->setBold(settings.contains("openzwave/IntervalBetweenPolls"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("IntervalBetweenPolls", variantitem);
        }

        m_variantEditor->addProperty(topItem);

        topItem = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),
                                            QLatin1String("CommandClasses"));

        {
            variantitem = variantManager->addProperty(QVariant::String, "Exclude");
            variantitem->setValue(m_options->Exclude());
            variantitem->setBold(settings.contains("openzwave/Exclude"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("Exclude", variantitem);
        }

        {
            variantitem = variantManager->addProperty(QVariant::String, "Include");
            variantitem->setValue(m_options->Include());
            variantitem->setBold(settings.contains("openzwave/Include"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("Include", variantitem);
        }


        m_variantEditor->addProperty(topItem);

        topItem = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),
                                            QLatin1String("Security"));

        {
            enumitem = enumManager->addProperty("SecurityStrategy");
            enumManager->setEnumNames(enumitem, m_options->SecurityStrategy().getEnums());
            enumManager->setValue(enumitem, m_options->SecurityStrategy().getSelected());
            enumitem->setBold(settings.contains("openzwave/SecurityStrategy"));
            enumitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(enumitem);
            this->m_variantToProperty.insert("SecurityStrategy", enumitem);
        }

        {
            variantitem = variantManager->addProperty(QVariant::Bool, "CustomSecuredCC");
            variantitem->setValue(m_options->CustomSecuredCC());
            variantitem->setBold(settings.contains("openzwave/CustomSecuredCC"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("CustomSecuredCC", variantitem);
        }

        {
            variantitem = variantManager->addProperty(QVariant::String, "EnforceSecureReception");
            variantitem->setValue(m_options->EnforceSecureReception());
            variantitem->setBold(settings.contains("openzwave/EnforceSecureReception"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("EnforceSecureReception", variantitem);
        }

        {
            variantitem = variantManager->addProperty(QVariant::String, "NetworkKey");
            variantitem->setValue(m_options->NetworkKey());
            variantitem->setBold(settings.contains("openzwave/NetworkKey"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("NetworkKey", variantitem);
        }


        m_variantEditor->addProperty(topItem);

        topItem = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),
                                            QLatin1String("Sleeping Devices"));

        {
            variantitem = variantManager->addProperty(QVariant::Bool, "AssumeAwake");
            variantitem->setValue(m_options->AssumeAwake());
            variantitem->setBold(settings.contains("openzwave/AssumeAwake"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("AssumeAwake", variantitem);
        }

        m_variantEditor->addProperty(topItem);

        topItem = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),
                                            QLatin1String("UserCode CommandClass"));


        {
            variantitem = variantManager->addProperty(QVariant::Bool, "RefreshAllUserCodes");
            variantitem->setValue(m_options->RefreshAllUserCodes());
            variantitem->setBold(settings.contains("openzwave/RefreshAllUserCodes"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("RefreshAllUserCodes", variantitem);
        }

        m_variantEditor->addProperty(topItem);

        topItem = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),
                                            QLatin1String("Device Database"));


        {
            variantitem = variantManager->addProperty(QVariant::String, "AutoUpdateConfigFile");
            variantitem->setValue(m_options->AutoUpdateConfigFile());
            variantitem->setBold(settings.contains("openzwave/AutoUpdateConfigFile"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("AutoUpdateConfigFile", variantitem);
        }

        {
            enumitem = enumManager->addProperty("ReloadAfterUpdate");
            enumManager->setEnumNames(enumitem, m_options->ReloadAfterUpdate().getEnums());
            enumManager->setValue(enumitem, m_options->ReloadAfterUpdate().getSelected());
            enumitem->setBold(settings.contains("openzwave/ReloadAfterUpdate"));
            enumitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(enumitem);
            this->m_variantToProperty.insert("ReloadAfterUpdate", enumitem);
        }


        m_variantEditor->addProperty(topItem);

        topItem = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),
                                            QLatin1String("Lanaguage"));


        {
            variantitem = variantManager->addProperty(QVariant::String, "Language");
            variantitem->setValue(m_options->Language());
            variantitem->setBold(settings.contains("openzwave/Language"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("Language", variantitem);
        }

        m_variantEditor->addProperty(topItem);

        topItem = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),
                                            QLatin1String("Multi Channel Devices"));


        {
            variantitem = variantManager->addProperty(QVariant::Bool, "IncludeInstanceLabels");
            variantitem->setValue(m_options->IncludeInstanceLabels());
            variantitem->setBold(settings.contains("openzwave/IncludeInstanceLabels"));
            variantitem->setEnabled(!m_options->isLocked());
            topItem->addSubProperty(variantitem);
            this->m_variantToProperty.insert("IncludeInstanceLabels", variantitem);
        }
        m_variantEditor->addProperty(topItem);

        //m_variantEditor->setEnabled(!m_options->isLocked());
        this->ui->config_ozw->layout()->addWidget(m_variantEditor);
    }
}

Configuration::~Configuration()
{
    delete ui;
}

void Configuration::saveConfiguration() {

    QtVariantProperty *property;
    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["Logging"]);
    if (property->value().toBool() != m_options->Logging()) {
        m_options->setLogging(property->value().toBool());
        settings.setValue("openzwave/Logging", property->value().toBool());
        qDebug() << "Saved Logging Param with " << property->value();
    }

    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["LogFileName"]);
    if (property->value()  != m_options->LogFileName()) {
        m_options->setLogFileName(property->value().toString());
        settings.setValue("openzwave/LogFileName", property->value().toString());
        qDebug() << "Saved LogFileName Param with " << property->value();
    }

    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["AppendLogFile"]);
    if (property->value() != m_options->AppendLogFile()) {
        m_options->setAppendLogFile(property->value().toBool());
        settings.setValue("openzwave/AppendLogFile", property->value().toString());
        qDebug() << "Saved AppendLogFile Param with " << property->value();
    }

    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["ConsoleOutput"]);
    if (property->value() != m_options->ConsoleOutput()) {
        m_options->setConsoleOutput(property->value().toBool());
        settings.setValue("openzwave/ConsoleOutput", property->value().toBool());
        qDebug() << "Saved ConsoleOutput Param with " << property->value();
    }

    /* enums - Come back to this */
    QtProperty *property1 = dynamic_cast<QtProperty *>(this->m_variantToProperty["SaveLogLevel"]);
    OptionList SaveLogLevel = m_options->SaveLogLevel();
    if (property1->valueText() != SaveLogLevel.getSelectedName()) {
        SaveLogLevel.setSelected(property1->valueText());
        m_options->setSaveLogLevel(SaveLogLevel);
        settings.setValue("openzwave/SaveLogLevel", SaveLogLevel.getSelectedName());
        qDebug() << "Saved SaveLogLevel Param with " << SaveLogLevel.getSelectedName();
    }

    property1 = dynamic_cast<QtProperty *>(this->m_variantToProperty["QueueLogLevel"]);
    OptionList QueueLogLevel = m_options->SaveLogLevel();
    if (property1->valueText() != QueueLogLevel.getSelectedName()) {
        QueueLogLevel.setSelected(property1->valueText());
        m_options->setQueueLogLevel(QueueLogLevel);
        settings.setValue("openzwave/QueueLogLevel", QueueLogLevel.getSelectedName());
        qDebug() << "Saved QueueLogLevel Param with " << QueueLogLevel.getSelectedName();
    }

    property1 = dynamic_cast<QtProperty *>(this->m_variantToProperty["DumpTriggerLevel"]);
    OptionList DumpTriggerLevel = m_options->DumpTriggerLevel();
    if (property1->valueText() != DumpTriggerLevel.getSelectedName()) {
        DumpTriggerLevel.setSelected(property1->valueText());
        m_options->setQueueLogLevel(DumpTriggerLevel);
        settings.setValue("openzwave/DumpTriggerLevel", DumpTriggerLevel.getSelectedName());
        qDebug() << "Saved DumpTriggerLevel Param with " << DumpTriggerLevel.getSelectedName();
    }


    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["Associate"]);
    if (property->value() != m_options->Associate()) {
        m_options->setAssociate(property->value().toBool());
        settings.setValue("openzwave/Associate", property->value().toBool());
        qDebug() << "Saved Associate Param with " << property->value();
    }

    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["Exclude"]);
    if (property->value() != m_options->Exclude()) {
        m_options->setExclude(property->value().toString());
        settings.setValue("openzwave/Exclude", property->value().toString());
        qDebug() << "Saved Exclude Param with " << property->value();
    }

    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["Include"]);
    if (property->value() != m_options->Include()) {
        m_options->setInclude(property->value().toString());
        settings.setValue("openzwave/Include", property->value().toString());
        qDebug() << "Saved Include Param with " << property->value();
    }

    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["NotifyTransactions"]);
    if (property->value() != m_options->NotifyTransactions()) {
        m_options->setNotifyTransactions(property->value().toBool());
        settings.setValue("openzwave/NotifyTransactions", property->value().toBool());
        qDebug() << "Saved NotifyTransactions Param with " << property->value();
    }

    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["SaveConfiguration"]);
    if (property->value() != m_options->SaveConfiguration()) {
        m_options->setSaveConfiguration(property->value().toBool());
        settings.setValue("openzwave/SaveConfiguration", property->value().toBool());
        qDebug() << "Saved SaveConfiguration Param with " << property->value();
    }

    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["DriverMaxAttempts"]);
    if (property->value() != m_options->DriverMaxAttempts()) {
        m_options->setDriverMaxAttempts(property->value().toInt());
        settings.setValue("openzwave/DriverMaxAttempts", property->value().toInt());
        qDebug() << "Saved DriverMaxAttempts Param with " << property->value();
    }

    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["PollInterval"]);
    if (property->value()  != m_options->PollInterval()) {
        m_options->setPollInterval(property->value().toInt());
        settings.setValue("openzwave/PollInterval", property->value().toInt());
        qDebug() << "Saved PollInterval Param with " << property->value();
    }

    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["IntervalBetweenPolls"]);
    if (property->value()  != m_options->IntervalBetweenPolls()) {
        m_options->setIntervalBetweenPolls(property->value().toBool());
        settings.setValue("openzwave/IntervalBetweenPolls", property->value().toBool());
        qDebug() << "Saved IntervalBetweenPolls Param with " << property->value();
    }

    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["SuppressValueRefresh"]);
    if (property->value()  != m_options->SuppressValueRefresh()) {
        m_options->setSuppressValueRefresh(property->value().toBool());
        settings.setValue("openzwave/SuppressValueRefresh", property->value().toBool());
        qDebug() << "Saved SuppressValueRefresh Param with " << property->value();
    }

    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["PerformReturnRoutes"]);
    if (property->value() != m_options->PerformReturnRoutes()) {
        m_options->setPerformReturnRoutes(property->value().toBool());
        settings.setValue("openzwave/PerformReturnRoutes", property->value().toBool());
        qDebug() << "Saved PerformReturnRoutes Param with " << property->value();
    }

    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["IntervalBetweenPolls"]);
    if (property->value() != m_options->IntervalBetweenPolls()) {
        m_options->setIntervalBetweenPolls(property->value().toBool());
        settings.setValue("openzwave/IntervalBetweenPolls", property->value().toBool());
        qDebug() << "Saved IntervalBetweenPolls Param with " << property->value();
    }

    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["NetworkKey"]);
    if (property->value() != m_options->NetworkKey()) {
        m_options->setNetworkKey(property->value().toString());
        /* we don't save the Network Key */
        qDebug() << "Not Saving Network Key";
    }

    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["RefreshAllUserCodes"]);
    if (property->value() != m_options->RefreshAllUserCodes()) {
        m_options->setRefreshAllUserCodes(property->value().toBool());
        settings.setValue("openzwave/RefreshAllUserCodes", property->value().toBool());
        qDebug() << "Saved RefreshAllUserCodes Param with " << property->value();
    }

    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["RetryTimeout"]);
    if (property->value() != m_options->RetryTimeout()) {
        m_options->setRetryTimeout(property->value().toInt());
        settings.setValue("openzwave/RetryTimeout", property->value().toInt());
        qDebug() << "Saved RetryTimeout Param with " << property->value();
    }

    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["EnableSIS"]);
    if (property->value()  != m_options->EnableSIS()) {
        m_options->setEnableSIS(property->value().toBool());
        settings.setValue("openzwave/EnableSIS", property->value().toBool());
        qDebug() << "Saved EnableSIS Param with " << property->value();
    }

    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["AssumeAwake"]);
    if (property->value() != m_options->AssumeAwake()) {
        m_options->setAssumeAwake(property->value().toBool());
        settings.setValue("openzwave/AssumeAwake", property->value().toBool());
        qDebug() << "Saved AssumeAwake Param with " << property->value();
    }

    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["NotifyOnDriverUnload"]);
    if (property->value() != m_options->NotifyOnDriverUnload()) {
        m_options->setNotifyOnDriverUnload(property->value().toBool());
        settings.setValue("openzwave/NotifyOnDriverUnload", property->value().toBool());
        qDebug() << "Saved NotifyOnDriverUnload Param with " << property->value();
    }

    property1 = dynamic_cast<QtProperty *>(this->m_variantToProperty["SecurityStrategy"]);
    OptionList SecurityStrategy = m_options->SecurityStrategy();
    if (property1->valueText() != SecurityStrategy.getSelectedName()) {
        SecurityStrategy.setSelected(property1->valueText());
        m_options->setSecurityStrategy(SecurityStrategy);
        settings.setValue("openzwave/SecurityStrategy", SecurityStrategy.getSelectedName());
        qDebug() << "Saved SecurityStrategy Param with " << SecurityStrategy.getSelectedName();
    }

    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["CustomSecuredCC"]);
    if (property->value() != m_options->CustomSecuredCC()) {
        m_options->setCustomSecuredCC(property->value().toString());
        settings.setValue("openzwave/CustomSecuredCC", property->value().toString());
        qDebug() << "Saved CustomSecuredCC Param with " << property->value();
    }

    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["EnforceSecureReception"]);
    if (property->value() != m_options->EnforceSecureReception()) {
        m_options->setEnforceSecureReception(property->value().toBool());
        settings.setValue("openzwave/EnforceSecureReception", property->value().toBool());
        qDebug() << "Saved EnforceSecureReception Param with " << property->value();
    }

    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["AutoUpdateConfigFile"]);
    if (property->value() != m_options->AutoUpdateConfigFile()) {
        m_options->setAutoUpdateConfigFile(property->value().toBool());
        settings.setValue("openzwave/AutoUpdateConfigFile", property->value().toBool());
        qDebug() << "Saved AutoUpdateConfigFile Param with " << property->value();
    }

    property1 = dynamic_cast<QtProperty *>(this->m_variantToProperty["ReloadAfterUpdate"]);
    OptionList ReloadAfterUpdate = m_options->ReloadAfterUpdate();
    if (property1->valueText() != ReloadAfterUpdate.getSelectedName()) {
        ReloadAfterUpdate.setSelected(property1->valueText());
        m_options->setReloadAfterUpdate(ReloadAfterUpdate);
        settings.setValue("openzwave/SecurityStrategy", ReloadAfterUpdate.getSelectedName());
        qDebug() << "Saved ReloadAfterUpdate Param with " << ReloadAfterUpdate.getSelectedName();
    }

    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["Language"]);
    if (property->value() != m_options->Language()) {
        m_options->setLanguage(property->value().toString());
        settings.setValue("openzwave/Language", property->value().toString());
        qDebug() << "Saved Language Param with " << property->value();
    }

    property = dynamic_cast<QtVariantProperty *>(this->m_variantToProperty["IncludeInstanceLabels"]);
    if (property->value() != m_options->IncludeInstanceLabels()) {
        m_options->setIncludeInstanceLabels(property->value().toBool());
        settings.setValue("openzwave/IncludeInstanceLabels", property->value().toBool());
        qDebug() << "Saved IncludeInstanceLabels Param with " << property->value();
    }
}
