#include "ConstrainedSpinBox.h"
#include "Helpers.h"

#include <QLineEdit>

ConstrainedSpinBox::ConstrainedSpinBox(const QStringList & items, QWidget * parent)
  : QSpinBox(parent),
    items_(items)
{
  setRange(0, items_.size() - 1);
  setAlignment(Qt::AlignRight);
  setMinimumWidth(120);
  setMinimumHeight(40);
  setWrapping(false);
  setFont(QFont("Courier", 16, QFont::Bold));

  setStyleSheet(
    "QSpinBox { border: 0px; padding: 5px; }\
     QSpinBox::up-button   { subcontrol-position: top right;    width: 40px; height: 19px; }\
     QSpinBox::down-button { subcontrol-position: bottom right; width: 40px; height: 19px; }"
  );

  findChild<QLineEdit *>()->setReadOnly(true);
}

int ConstrainedSpinBox::valueFromText(const QString & text) const
{
  return items_.indexOf(QRegExp(text, Qt::CaseSensitive, QRegExp::FixedString));
}

QString ConstrainedSpinBox::textFromValue(int value) const
{
  return items_.at(value);
}
