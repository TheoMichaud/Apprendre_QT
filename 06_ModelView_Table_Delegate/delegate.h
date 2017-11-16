#ifndef DELEGATE_H
#define DELEGATE_H

#include <QItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QSize>
#include <QSpinBox>

// Notre classe Delegate hérite de la classe virtuelle QItemDelegate
class Delegate : public QItemDelegate

{
    Q_OBJECT
public:

    explicit Delegate(QObject *parent=0);
    // redefinition de la virtuelle createEditor
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    // redefinition de la virtuelle setEditorData
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    // redefinition de la virtuelle setModelData
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    // redefinition de la virtuelle updateEditorGeometry
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;




};

#endif // DELEGATE_H
