/**
 * @file    SegmentStats.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_SEGMENT_STATS__
#define __NSOL_SEGMENT_STATS__

#include <nsol/api.h>
#include "../NsolTypes.h"
#include "../Node.h"

namespace nsol
{

	class SegmentStats
	{

	public:

		//! Stats that can be computed for a segment
		typedef enum
		{
		  SURFACE = 0,
		  VOLUME,
		  LENGTH,
		  RADIUS,
		  SEGMENT_NUM_STATS
		} TSegmentStat;


		NSOL_API
		SegmentStats * stats( void );

		NSOL_API
    static float getStat( TSegmentStat stat,
							  const NodePtr begin,
							  const NodePtr end);
	}; // class SegmentStats


} // namespace nsol

#endif // __NSOL_SEGMENT_STATS__
