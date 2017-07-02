/****************************************************************************
**
****************************************************************************/

#include "HantekDataSource.h"
#include <QtCharts/QLineSeries>

#include "Helpers.h"

#include <cstdlib>

#include <QTextStream>

// Temporary
#include <QtMultimedia/QAudioDeviceInfo>
#include <QtMultimedia/QAudioInput>

HantekDataSource::HantekDataSource(Series series, QObject * parent) :
    QIODevice(parent),
    series_(series),
    triggerMode_(TriggerMode::AUTO)
{
  QAudioFormat formatAudio;
  formatAudio.setSampleRate(8000);
  formatAudio.setChannelCount(1);
  formatAudio.setSampleSize(8);
  formatAudio.setCodec("audio/pcm");
  formatAudio.setByteOrder(QAudioFormat::LittleEndian);
  formatAudio.setSampleType(QAudioFormat::UnSignedInt);

  QAudioDeviceInfo inputDevices = QAudioDeviceInfo::defaultInputDevice();
  m_audioInput = new QAudioInput(inputDevices, formatAudio, this);

  m_audioInput->start(this);
  open(QIODevice::WriteOnly);
}

HantekDataSource::~HantekDataSource()
{
  close();
  m_audioInput->stop();
}

qint64 HantekDataSource::readData(char * data, qint64 maxSize)
{
  Q_UNUSED(data)
  Q_UNUSED(maxSize)
  return -1;
}

qint64 HantekDataSource::writeData(const char * data, qint64 maxSize)
{
  if (triggerMode_ == TriggerMode::SINGLE)
  {
    return maxSize;
  }
  qint64 range = 2000;

  qreal bias[] = {0.5, -0.5};

  for (int trace = 0; trace < 2; ++trace)
  {
    QVector<QPointF> oldPoints = series_[trace]->pointsVector();
    QVector<QPointF> points;
    int resolution = 4;

    if (oldPoints.count() < range)
    {
      points = series_[trace]->pointsVector();
    }
    else
    {
      for (int i = maxSize / resolution; i < oldPoints.count(); i++)
      {
        points.append(QPointF(i - maxSize / resolution, oldPoints.at(i).y()));
      }
    }

    qint64 size = points.count();
    for (int k = 0; k < maxSize / resolution; k++)
    {
      points.append(
        QPointF(k + size, bias[trace] + ((quint8)data[resolution * k] - 128) / 128.0));
    }

    series_[trace]->replace(points);
  }
  return maxSize;
}

void HantekDataSource::Acquire()
{
  qint64 range = 2000;

  qreal bias[] = {0.5, -0.5};

  for (int trace = 0; trace < 2; ++trace)
  {
    QVector<QPointF> points;

    for (int i = 0; i < range; ++i)
    {
      qreal v = bias[trace]
              + (0.8 * ((i / 100) % 2) - 0.4)
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

qreal HantekDataSource::timeBaseToValue(TimeBase timeBase)
{
  switch (timeBase)
  {
  case TimeBase::TB_100ns: return 100e-9;
  case TimeBase::TB_200ns: return 200e-9;
  case TimeBase::TB_500ns: return 500e-9;
  case TimeBase::TB_1us:   return   1e-6;
  case TimeBase::TB_2us:   return   2e-6;
  case TimeBase::TB_5us:   return   5e-6;
  case TimeBase::TB_10us:  return  10e-6;
  case TimeBase::TB_20us:  return  20e-6;
  case TimeBase::TB_50us:  return  50e-6;
  case TimeBase::TB_100us: return 100e-6;
  case TimeBase::TB_200us: return 200e-6;
  case TimeBase::TB_500us: return 500e-6;
  case TimeBase::TB_1ms:   return   1e-3;
  case TimeBase::TB_2ms:   return   2e-3;
  case TimeBase::TB_5ms:   return   5e-3;
  }
  return 0;
}

QString HantekDataSource::timeBaseToString(TimeBase timeBase)
{
  QString result;
  qreal value = timeBaseToValue(timeBase);

  switch (timeBase)
  {
  case TimeBase::TB_100ns:
  case TimeBase::TB_200ns:
  case TimeBase::TB_500ns:
    QTextStream(&result) << (value * 1e9) << " ns";
    break;
  case TimeBase::TB_1us:
  case TimeBase::TB_2us:
  case TimeBase::TB_5us:
  case TimeBase::TB_10us:
  case TimeBase::TB_20us:
  case TimeBase::TB_50us:
  case TimeBase::TB_100us:
  case TimeBase::TB_200us:
  case TimeBase::TB_500us:
    QTextStream(&result) << (value * 1e6) << " us";
    break;
  case TimeBase::TB_1ms:
  case TimeBase::TB_2ms:
  case TimeBase::TB_5ms:
    QTextStream(&result) << (value * 1e3) << " ms";
    break;
  }
  return result;
}
