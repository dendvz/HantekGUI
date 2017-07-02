/****************************************************************************
**
****************************************************************************/

#ifndef HANTEK_DATA_SOURCE_H
#define HANTEK_DATA_SOURCE_H

#include <QtCore/QIODevice>
#include <QtCharts/QChartGlobal>

#include <vector>

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE
class QAudioInput;
QT_END_NAMESPACE

class HantekDataSource : public QIODevice
{
  Q_OBJECT

public:
  using Series = std::vector<QLineSeries *>;

  enum class TimeBase
  {
    TB_100ns, TB_MIN = TimeBase::TB_100ns,
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
    TB_5ms,   TB_MAX = TimeBase::TB_5ms
  };

  enum class TriggerMode
  {
    AUTO,
    NORMAL,
    SINGLE,
    SOFTWARE
  };

  explicit HantekDataSource(Series series, QObject * parent = 0);
  ~HantekDataSource();

  int getChannelCount() const { return 2; }

  void setTriggerMode(TriggerMode mode) { triggerMode_ = mode; }

  static qreal   timeBaseToValue(TimeBase timeBase);
  static QString timeBaseToString(TimeBase timeBase);

  void Acquire();
protected:
  qint64 readData(char * data, qint64 maxSize);
  qint64 writeData(const char * data, qint64 maxSize);

private:
  Series series_;
  QAudioInput * m_audioInput;

  TriggerMode triggerMode_;
};

#endif // HANTEK_DATA_SOURCE_H
