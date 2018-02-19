/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * This file is part of nsol <https://github.com/gmrvvis/nsol>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

/*
 * Example to show how to use stats and cached stats
 */

#include <nsol/nsol.h>

#ifdef Win32
#include < time.h >
#include <windows.h> //I've omitted this line.
#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif

struct timezone
{
  int  tz_minuteswest; /* minutes W of Greenwich */
  int  tz_dsttime;     /* type of dst correction */
};

int gettimeofday(struct timeval *tv, struct timezone *tz)
{
  FILETIME ft;
  unsigned __int64 tmpres = 0;
  static int tzflag;

  if (NULL != tv)
  {
    GetSystemTimeAsFileTime(&ft);

    tmpres |= ft.dwHighDateTime;
    tmpres <<= 32;
    tmpres |= ft.dwLowDateTime;

    /*converting file time to unix epoch*/
    tmpres -= DELTA_EPOCH_IN_MICROSECS;
    tmpres /= 10;  /*convert into microseconds*/
    tv->tv_sec = (long)(tmpres / 1000000UL);
    tv->tv_usec = (long)(tmpres % 1000000UL);
  }

  if (NULL != tz)
  {
    if (!tzflag)
    {
      _tzset();
      tzflag++;
    }

    long seconds;
    _get_timezone( &seconds );
    tz->tz_minuteswest =  seconds / 60;

    int hours;
    _get_daylight( &hours );
    tz->tz_dsttime = hours;
  }

  return 0;
}
#else
#include <sys/time.h>
#endif

void computeNeuronMorphologyStats( nsol::NeuronMorphologyPtr morphology );

void printNeuronMorphologyStats( nsol::NeuronMorphologyPtr morphology );


int main ( int argc, char ** argv )
{
  std::cout << std::endl;

  if ( argc < 2 )
  {
    std::cerr << "Error. Usage: " << argv[0]
              << " swc_input_file" << std::endl;
    return -1;
  }

  std::cout << "Reading neuron with stats" << std::endl;
  nsol::SwcReaderStats readerWithStats;
  nsol::NeuronPtr neuronWithStats = readerWithStats.readNeuron( argv[1] );

  std::cout << "Reading neuron with cached stats" << std::endl;
  nsol::SwcReaderCachedStats readerWithCachedStats;
  nsol::NeuronPtr neuronWithCachedStats =
    readerWithCachedStats.readNeuron( argv[1] );

  if ( ! neuronWithStats || ! neuronWithCachedStats )
  {
    std::cerr << "Could not read neurons" << std::endl;
    return -1;
  }

  std::cout << std::endl;

  std::cout << "Non-cached stats" << std::endl;
  printNeuronMorphologyStats( neuronWithStats->morphology( ));

  std::cout << "Cached stats" << std::endl;
  printNeuronMorphologyStats( neuronWithCachedStats->morphology( ));


  struct timeval startTime, endTime;
  long totalTime;

  gettimeofday(&startTime, NULL);
  for ( int i = 0; i < 10000; i++ )
    computeNeuronMorphologyStats( neuronWithStats->morphology( ));
  gettimeofday(&endTime, NULL);

  totalTime =  (endTime.tv_sec - startTime.tv_sec) * 1000000L;
  totalTime += (endTime.tv_usec - startTime.tv_usec);

  std::cout << "Compute non-cached stats 1000 times. Time elapsed: "
            << (totalTime/1000L) / 1000.0f << std::endl;

  gettimeofday(&startTime, NULL);
  for ( int i = 0; i < 1000; i++ )
    computeNeuronMorphologyStats( neuronWithCachedStats->morphology( ));
  gettimeofday(&endTime, NULL);

  totalTime =  (endTime.tv_sec - startTime.tv_sec) * 1000000L;
  totalTime += (endTime.tv_usec - startTime.tv_usec);

  std::cout << "Compute cached stats 1000 times. Time elapsed: "
            << (totalTime/1000L) / 1000.0f << std::endl;

  std::cout << std::endl;


  return 0;


}


void computeNeuronMorphologyStats( nsol::NeuronMorphologyPtr morphology )
{

  NSOL_DEBUG_CHECK( morphology , "morphology is null" );
  NSOL_DEBUG_CHECK( morphology->stats( ) , "no stats" );

  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::DENDRITIC_VOLUME );
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::AXON_VOLUME );
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::NEURITIC_VOLUME );
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::SOMA_VOLUME );
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::VOLUME );

  // Surface
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::DENDRITIC_SURFACE );
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::AXON_SURFACE );
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::NEURITIC_SURFACE );
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::SOMA_SURFACE );
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::SURFACE );

  // Length
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::DENDRITIC_LENGTH );
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::AXON_LENGTH );
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::NEURITIC_LENGTH
    );
  // Bifurcations
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::DENDRITIC_BIFURCATIONS );
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::AXON_BIFURCATIONS );
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::NEURITIC_BIFURCATIONS );

}

void printNeuronMorphologyStats( nsol::NeuronMorphologyPtr morphology )
{

  NSOL_DEBUG_CHECK( morphology , "morphology is null" );
  NSOL_DEBUG_CHECK( morphology->stats( ) , "no stats" );

  #define NMS morphology->stats( )

  std::cout << "\tDendritic surface:\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::DENDRITIC_SURFACE )
            << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::DENDRITIC_SURFACE,
                             nsol::/*TAggregation::*/MEAN ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::DENDRITIC_SURFACE,
                             nsol::/*TAggregation::*/VARIANCE ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::DENDRITIC_SURFACE,
                             nsol::/*TAggregation::*/STD_DEV ) << " "
            << std::endl;

  std::cout << "\tAxon surface:\t\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_SURFACE )
            << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_SURFACE,
                             nsol::/*TAggregation::*/MEAN ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_SURFACE,
                             nsol::/*TAggregation::*/VARIANCE ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_SURFACE,
                             nsol::/*TAggregation::*/STD_DEV ) << " "
             << std::endl;

  std::cout << "\tNeuritic surface:\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_SURFACE )
            << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_SURFACE,
                             nsol::/*TAggregation::*/MEAN ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_SURFACE,
                             nsol::/*TAggregation::*/VARIANCE ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_SURFACE,
                             nsol::/*TAggregation::*/STD_DEV ) << " "
             << std::endl;

  std::cout << "\tSoma surface:\t\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::SOMA_SURFACE )
            << std::endl;

  std::cout << "\tSurface:\t\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::SURFACE )
             << std::endl;

  std::cout << std::endl;

  std::cout << "\tDendritic volume:\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::DENDRITIC_VOLUME )
            << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::DENDRITIC_VOLUME,
                             nsol::/*TAggregation::*/MEAN ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::DENDRITIC_VOLUME,
                             nsol::/*TAggregation::*/VARIANCE ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::DENDRITIC_VOLUME,
                             nsol::/*TAggregation::*/STD_DEV ) << " "
            << std::endl;

  std::cout << "\tAxon volume:\t\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_VOLUME )
            << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_VOLUME,
                             nsol::/*TAggregation::*/MEAN ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_VOLUME,
                             nsol::/*TAggregation::*/VARIANCE ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_VOLUME,
                             nsol::/*TAggregation::*/STD_DEV ) << " "
             << std::endl;

  std::cout << "\tNeuritic volume:\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_VOLUME )
            << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_VOLUME,
                             nsol::/*TAggregation::*/MEAN ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_VOLUME,
                             nsol::/*TAggregation::*/VARIANCE ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_VOLUME,
                             nsol::/*TAggregation::*/STD_DEV ) << " "
             << std::endl;

  std::cout << "\tSoma volume:\t\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::SOMA_VOLUME )
            << std::endl;

  std::cout << "\tVolume:\t\t\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::VOLUME )
             << std::endl;

  std::cout << std::endl;

  std::cout << "\tDendritic length:\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::DENDRITIC_LENGTH )
            << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::DENDRITIC_LENGTH,
                             nsol::/*TAggregation::*/MEAN ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::DENDRITIC_LENGTH,
                             nsol::/*TAggregation::*/VARIANCE ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::DENDRITIC_LENGTH,
                             nsol::/*TAggregation::*/STD_DEV ) << " "
            << std::endl;

  std::cout << "\tAxon length:\t\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_LENGTH )
            << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_LENGTH,
                             nsol::/*TAggregation::*/MEAN ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_LENGTH,
                             nsol::/*TAggregation::*/VARIANCE ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_LENGTH,
                             nsol::/*TAggregation::*/STD_DEV ) << " "
             << std::endl;

  std::cout << "\tNeuritic length:\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_LENGTH )
            << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_LENGTH,
                             nsol::/*TAggregation::*/MEAN ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_LENGTH,
                             nsol::/*TAggregation::*/VARIANCE ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_LENGTH,
                             nsol::/*TAggregation::*/STD_DEV ) << " "
             << std::endl;

  std::cout << std::endl;

  std::cout << "\tDendritic bifurcations:\t"
            << NMS->getStat(
              nsol::NeuronMorphologyStats::DENDRITIC_BIFURCATIONS )
            << " "
            << NMS->getStat(
              nsol::NeuronMorphologyStats::DENDRITIC_BIFURCATIONS,
              nsol::/*TAggregation::*/MEAN ) << " "
            << NMS->getStat(
              nsol::NeuronMorphologyStats::DENDRITIC_BIFURCATIONS,
              nsol::/*TAggregation::*/VARIANCE ) << " "
            << NMS->getStat(
              nsol::NeuronMorphologyStats::DENDRITIC_BIFURCATIONS,
              nsol::/*TAggregation::*/STD_DEV ) << " "
            << std::endl;

  std::cout << "\tAxon bifurcations:\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_BIFURCATIONS )
            << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_BIFURCATIONS,
                             nsol::/*TAggregation::*/MEAN ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_BIFURCATIONS,
                             nsol::/*TAggregation::*/VARIANCE ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_BIFURCATIONS,
                             nsol::/*TAggregation::*/STD_DEV ) << " "
             << std::endl;

  std::cout << "\tNeuritic bifurcations:\t"
            << NMS->getStat(
              nsol::NeuronMorphologyStats::NEURITIC_BIFURCATIONS )
            << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_BIFURCATIONS,
                             nsol::/*TAggregation::*/MEAN ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_BIFURCATIONS,
                             nsol::/*TAggregation::*/VARIANCE ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_BIFURCATIONS,
                             nsol::/*TAggregation::*/STD_DEV ) << " "
            << std::endl;

  std::cout << std::endl;

}
