#include "qtopenzwave.h"


QTOpenZwave::QTOpenZwave
(
    QObject *parent
) :
    QObject (parent),
    m_manager(nullptr)
{
    this->m_websockserver = new WebSocketServer(1984, this);

    this->m_srcNode = new QRemoteObjectHost(QUrl(QStringLiteral("tcp://0.0.0.0:1983")));
    //this->m_srcNode->setHostUrl(QUrl(QStringLiteral("ws://0.0.0.0:1984")), QRemoteObjectHost::AllowExternalRegistration);
    this->m_srcNode->setHeartbeatInterval(1000);
    connect(this->m_websockserver, &WebSocketServer::newConnection, this, &QTOpenZwave::newWSConnection);
}
void QTOpenZwave::newWSConnection
(
)
{
    qDebug() << "New WS Connection";
    this->m_srcNode->addHostSideConnection(this->m_websockserver->nextPendingConnection());
}

QTOZWManager *QTOpenZwave::GetManager
(
)
{
    if (m_manager == nullptr) {
        this->m_manager = new QTOZWManager();
        this->m_srcNode->enableRemoting(this->m_manager, "Manager");
        QVector<int> roles;
        roles << Qt::DisplayRole << Qt::BackgroundRole << Qt::EditRole;
        this->m_srcNode->enableRemoting(this->m_manager->getNodeModel(), "nodeModel", roles);
    }
    return this->m_manager;
}