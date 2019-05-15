#ifndef QTOZWNODEMODEL_H
#define QTOZWNODEMODEL_H

#include <QObject>
#include <QAbstractItemModel>

class QTOZW_Nodes : public QAbstractTableModel {
    Q_OBJECT
public:
    enum NodeColumns {
        NodeID,
        NodeName,
        NodeLocation,
        NodeManufacturerName,
        NodeProductName,
        NodeBasicString,
        NodeBasic,
        NodeGenericString,
        NodeGeneric,
        NodeSpecificString,
        NodeSpecific,
        NodeDeviceTypeString,
        NodeDeviceType,
        NodeRole,
        NodeRoleString,
        NodePlusType,
        NodePlusTypeString,
        NodeQueryStage,
        NodeManufacturerID,
        NodeProductType,
        NodeProductID,
        NodeBaudRate,
        NodeVersion,
        NodeFlags,
        NodeCount
    };
    Q_ENUM(NodeColumns)

    enum nodeFlags {
        isListening,
        isFlirs,
        isBeaming,
        isRouting,
        isSecurityv1,
        isZWavePlus,
        isNIFRecieved,
        isAwake,
        isFailed,
        flagCount
    };

    Q_ENUM(nodeFlags);

    QTOZW_Nodes(QObject *parent=nullptr);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);

protected:
    QVariant getNodeData(uint8_t, NodeColumns);
    int32_t getNodeRow(uint8_t _node);

    QHash<int32_t, QHash<NodeColumns, QVariant> > m_nodeData;
};

class QTOZW_Nodes_internal : public QTOZW_Nodes {
    Q_OBJECT
public:
    QTOZW_Nodes_internal(QObject *parent=nullptr);
public Q_SLOTS:
    void addNode(uint8_t _nodeID);
    void setNodeData(uint8_t _nodeID, QTOZW_Nodes::NodeColumns column, QVariant data);
    void setNodeFlags(uint8_t _nodeID, QTOZW_Nodes::nodeFlags _flags, bool _value);

};

#endif // QTOZWNODEMODEL_H
