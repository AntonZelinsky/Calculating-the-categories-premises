#include "Noteditabledelegate.h"

NotEditableDelegate::NotEditableDelegate()
{
}
QWidget* NotEditableDelegate::createEditor ( QWidget*, const QStyleOptionViewItem&, const QModelIndex& ) const
{
    return 0;
}
