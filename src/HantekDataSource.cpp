/****************************************************************************
**
****************************************************************************/

#include "HantekDataSource.h"
#include <QtCharts/QLineSeries>

#include "Helpers.h"

#include <cstdlib>

#include <QTextStream>

HantekDataSource::HantekDataSource(Series series, QObject * parent)
  : QObject(parent),
    series_(series),
    hScale_(HScale_t::HS_MIN),
    triggerMode_(TriggerMode_t::AUTO)
{
  vScale_.reserve(getChannelCount());
}

HantekDataSource::~HantekDataSource()
{
}

void HantekDataSource::Acquire()
{
  int range = 2000;

  qreal bias[] = {0.5, -0.5};

  qreal calibratorPeriod = 1e-3; // 1kHz

  // samples, assuming 10 divs along X axis
  int period = int(floor(calibratorPeriod * range / (10 * hScaleToValue(hScale_))));

  for (int trace = 0; trace < 2; ++trace)
  {
    QVector<QPointF> points;

    for (int i = 0; i < range; ++i)
    {
      qreal v = bias[trace]
              + (0.4 * ((2 * i / period) % 2))
              + (0.05 * (rand() / qreal(RAND_MAX) - 0.5));
      points.append(QPointF(i, v));
    }

    series_[trace]->replace(points);
  }
}

/*
H_SCALE = [
  # tb_value,  tb_text,    sample_rate
  (   5E-03, '  5 ms', 100E+03 ), // 0
  (   2E-03, '  2 ms', 100E+03 ), // 1
  (   1E-03, '  1 ms', 100E+03 ), // 2
  ( 500E-06, '500 us', 200E+03 ), // 3
  ( 200E-06, '200 us', 500E+03 ), // 4
  ( 100E-06, '100 us',   1E+06 ), // 5
  (  50E-06, ' 50 us',   1E+06 ), // 6
  (  20E-06, ' 20 us',   4E+06 ), // 7
  (  10E-06, ' 10 us',   8E+06 ), // 8
  (   5E-06, '  5 us',  16E+06 ), // 9
  (   2E-06, '  2 us',  24E+06 ), // 10
  (   1E-06, '  1 us',  24E+06 ), // 11
  ( 500E-09, '500 ns',  24E+06 ), // 12
  ( 200E-09, '200 ns',  24E+06 ), // 13
  ( 100E-09, '100 ns',  24E+06 )  // 14
]
  */

qreal HantekDataSource::hScaleToValue(HScale_t hScale)
{
  switch (hScale)
  {
  case HScale_t::HS_100ns: return 100e-9;
  case HScale_t::HS_200ns: return 200e-9;
  case HScale_t::HS_500ns: return 500e-9;
  case HScale_t::HS_1us:   return   1e-6;
  case HScale_t::HS_2us:   return   2e-6;
  case HScale_t::HS_5us:   return   5e-6;
  case HScale_t::HS_10us:  return  10e-6;
  case HScale_t::HS_20us:  return  20e-6;
  case HScale_t::HS_50us:  return  50e-6;
  case HScale_t::HS_100us: return 100e-6;
  case HScale_t::HS_200us: return 200e-6;
  case HScale_t::HS_500us: return 500e-6;
  case HScale_t::HS_1ms:   return   1e-3;
  case HScale_t::HS_2ms:   return   2e-3;
  case HScale_t::HS_5ms:   return   5e-3;
  }
  return 0.0;
}

qreal HantekDataSource::vScaleToValue(VScale_t vScale)
{
  switch (vScale)
  {
  case VScale_t::VS_100mV:  return 0.1;
  case VScale_t::VS_200mV:  return 0.2;
  case VScale_t::VS_500mV:  return 0.5;
  case VScale_t::VS_1V:     return 1.0;
  case VScale_t::VS_2V:     return 2.0;
  case VScale_t::VS_5V:     return 5.0;
  }
  return 0.0;
}
