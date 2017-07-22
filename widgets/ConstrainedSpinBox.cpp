#include "ConstrainedSpinBox.h"
#include "Helpers.h"

#include <QLineEdit>

ConstrainedSpinBox::ConstrainedSpinBox(QWidget * parent, const QStringList & items)
  : QSpinBox(parent),
    items_(items)
{
  setRange(0, items_.size() - 1);
  setAlignment(Qt::AlignRight);
  setWrapping(false);
  setFont(QFont("Courier", 14, QFont::Bold));
  setMaximumHeight(30);

  setStyleSheet(
    "QSpinBox { border: 0px; padding: 5px 0px 5px 0px; }\
     QSpinBox::up-button   { subcontrol-position: top right;    width: 28px; height: 15px; }\
     QSpinBox::down-button { subcontrol-position: bottom right; width: 28px; height: 15px; }"
  );

  QLineEdit * edit = findChild<QLineEdit *>();
  edit->setReadOnly(true);
  edit->setStyleSheet("QLineEdit { selection-color: black; selection-background-color: white; }");
}

int ConstrainedSpinBox::valueFromText(const QString & text) const
{
  return items_.indexOf(QRegExp(text, Qt::CaseSensitive, QRegExp::FixedString));
}

QString ConstrainedSpinBox::textFromValue(int value) const
{
  return items_.at(value);
}
