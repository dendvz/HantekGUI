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
    TB_5ms,   TB_MIN = TimeBase_t::TB_5ms,
    TB_2ms,
    TB_1ms,
    TB_500us,
    TB_200us,
    TB_100us,
    TB_50us,
    TB_20us,
    TB_10us,
    TB_5us,
    TB_2us,
    TB_1us,
    TB_500ns,
    TB_200ns,
    TB_100ns, TB_MAX = TimeBase_t::TB_100ns
  };

  enum class TriggerMode_t
  {
    AUTO,
    NORMAL,
    SINGLE,
    SOFTWARE
  };

/*
   VOLTAGE_RANGES = {0x01: ('+/- 5V', 0.0390625, 2.5),
                      0x02: ('+/- 2.5V', 0.01953125, 1.25),
                      0x05: ('+/- 1V', 0.0078125, 0.5),
                      0x0a: ('+/- 500mV', 0.00390625, 0.25)}

 */

  /*
  ** Volts / div
  */
  enum class VScale_t
  {
    VS_5V,    VS_MIN = VScale_t::VS_5V,
    VS_2V,
    VS_1V,
    VS_500mV,
    VS_200mV,
    VS_100mV, VS_MAX = VScale_t::VS_100mV
  };

  explicit HantekDataSource(Series series, QObject * parent = nullptr);
  ~HantekDataSource();

  int getChannelCount() const { return 2; }

  void setTriggerMode(TriggerMode_t mode) { triggerMode_ = mode; }

  static qreal   timeBaseToValue(TimeBase_t timeBase);
  static QString timeBaseToString(TimeBase_t timeBase);

  static qreal   vScaleToValue(VScale_t vScale);
  static QString vScaleToString(VScale_t vScale);

  void Acquire();
  void setTimeBase(TimeBase_t timeBase)         { timeBase_ = timeBase; }
  void setVScale(int channel, VScale_t vScale)  { vScale_[channel] = vScale; }

private:
  Series series_;

  TimeBase_t    timeBase_;
  TriggerMode_t triggerMode_;
  std::vector<VScale_t> vScale_;
};

#endif // HANTEK_DATA_SOURCE_H
