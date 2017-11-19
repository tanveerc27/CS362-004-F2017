#ifndef myassert
#include "stdio.h"
#include "dominion.h"

#ifdef ASSERT_TRACK
	#define newassert(condition) \
	{ \
		if(!(condition)) \
		{ \
			fprintf(stderr, "Test failed at %s inside %s: \n\tCondition: %s\n",\
			__FILE__, __FUNCTION__, (#condition)); \
			asserttrack++; \
		} \
	}
#else
	#define newassert(condition) \
	{ \
		if(!(condition)) \
		{ \
			fprintf(stderr, "Test failed at %s inside %s: \n\tCondition: %s\n",\
			__FILE__, __FUNCTION__, (#condition)); \
		} \
	}
#endif

#endif
