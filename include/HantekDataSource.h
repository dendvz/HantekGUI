/****************************************************************************
**
****************************************************************************/

#ifndef HANTEK_DATA_SOURCE_H
#define HANTEK_DATA_SOURCE_H

#include <QObject>
#include <QChartGlobal>

#include <vector>

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class HantekDataSource : public QObject
{
  Q_OBJECT

public:
  using Series = std::vector<QLineSeries *>;

  enum class TimeBase_t
  {
    TB_100ns, TB_MIN = TimeBase_t::TB_100ns,
    TB_200ns,
    TB_500ns,
    TB_1us,
    TB_2us,
    TB_5us,
    TB_10us,
    TB_20us,
    TB_50us,
    TB_100us,
    TB_200us,
    TB_500us,
    TB_1ms,
    TB_2ms,
    TB_5ms,   TB_MAX = TimeBase_t::TB_5ms
  };

  enum class TriggerMode_t
  {
    AUTO,
    NORMAL,
    SINGLE,
    SOFTWARE
  };

  explicit HantekDataSource(Series series, QObject * parent = nullptr);
  ~HantekDataSource();

  int getChannelCount() const { return 2; }

  void setTriggerMode(TriggerMode_t mode) { triggerMode_ = mode; }

  static qreal   timeBaseToValue(TimeBase_t timeBase);
  static QString timeBaseToString(TimeBase_t timeBase);

  void Acquire();
  void setTimeBase(TimeBase_t timeBase) { timeBase_ = timeBase; }

private:
  Series series_;

  TimeBase_t    timeBase_;
  TriggerMode_t triggerMode_;
};

#endif // HANTEK_DATA_SOURCE_H
