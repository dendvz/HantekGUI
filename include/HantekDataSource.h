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

  enum class HScale_t
  {
    HS_5ms,   HS_MIN = HScale_t::HS_5ms,
    HS_2ms,
    HS_1ms,
    HS_500us,
    HS_200us,
    HS_100us,
    HS_50us,
    HS_20us,
    HS_10us,
    HS_5us,
    HS_2us,
    HS_1us,
    HS_500ns,
    HS_200ns,
    HS_100ns, HS_MAX = HScale_t::HS_100ns
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

  static qreal hScaleToValue(HScale_t hScale);
  static qreal vScaleToValue(VScale_t vScale);

  void Acquire();
  void setHScale(HScale_t hScale)               { hScale_ = hScale; }
  void setVScale(int channel, VScale_t vScale)  { vScale_[channel] = vScale; }

private:
  Series series_;

  HScale_t    hScale_;
  TriggerMode_t triggerMode_;
  std::vector<VScale_t> vScale_;
};

#endif // HANTEK_DATA_SOURCE_H
