
#include <QHeaderView>
#include <qt-openzwave/qtopenzwave.h>
#include <qt-openzwave/qtozwmanager.h>

#include "valuetable.h"
#include "value_delegate.h"
#include "ozwcore.h"
#include "util.h"

ValueTable::ValueTable(QTOZW_ValueIds::ValueIdGenres genre, QWidget *parent) :
    QTableView(parent)
{
	Value_Delegate *delegate = new Value_Delegate(this);
    this->m_genre = genre;

    this->m_proxyModel = new QTOZW_proxyValueModel(this);    
    this->m_proxyModel->setFilterGenre(this->m_genre);

	this->setItemDelegateForColumn(QTOZW_ValueIds::ValueIdColumns::Value, delegate);
	this->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->verticalHeader()->hide();
	this->setSelectionMode(QAbstractItemView::SingleSelection);
	this->setSortingEnabled(true);
	this->horizontalHeader()->setSectionsMovable(true);
}

void ValueTable::setModel(QAbstractItemModel *model, QItemSelectionModel *selectionModel)
{
    this->m_proxyModel->setSourceModel(model);
    this->m_proxyModel->setSelectionModel(selectionModel);
    connect(this->m_proxyModel, &QAbstractItemModel::rowsInserted, this, &ValueTable::resizeContents);
    connect(this->m_proxyModel, &QAbstractItemModel::rowsRemoved, this, &ValueTable::resizeContents);
    QTableView::setModel(this->m_proxyModel);

    for (int i = 0; i <= QTOZW_ValueIds::ValueIdColumns::ValueIdCount; i++) {
        switch (i) {
            case QTOZW_ValueIds::ValueIdColumns::Label:
            case QTOZW_ValueIds::ValueIdColumns::Value:
            case QTOZW_ValueIds::ValueIdColumns::Instance:
            case QTOZW_ValueIds::ValueIdColumns::Help:
            break;
        default:
            this->horizontalHeader()->hideSection(i);
        }
    }
    QTimer::singleShot(100, this, &ValueTable::resizeContents);
}

void ValueTable::resizeContents() {
    this->resizeColumnsToContents();
}
