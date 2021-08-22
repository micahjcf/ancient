#ifndef MJCF_DEBUG
#define MJCF_DEBUG

#include <assert.h>
#include <crtdbg.h>

#ifdef _DEBUG
	//#define ASSERT(e)   ( ((e) || assert(__FILE__, __LINE__) ) // I don't know why this doesn't work anymore.. it used to!
	#define ASSERT(e)		assert(e)
#else
	#define ASSERT(e)		(__assume(e))
#endif

#define Err(sz)	printf("%s():%d\020 '%s'\n", __FUNCTION__, __LINE__, sz);

#endif MJCF_DEBUG