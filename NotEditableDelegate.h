#ifndef NOTEDITABLEDELEGATE_H
#define NOTEDITABLEDELEGATE_H

#include <QStyledItemDelegate>
/**
 * @brief The NotEditableDelegate class  предназгачен для
 *          блокировки редактирования отдельных колонок
 *
 */
class NotEditableDelegate : public QStyledItemDelegate
{
public:
    NotEditableDelegate();
    QWidget* createEditor ( QWidget*, const QStyleOptionViewItem&, const QModelIndex& ) const;

};

#endif // NOTEDITABLEDELEGATE_H
