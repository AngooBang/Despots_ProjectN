#pragma once

// ------------------------------------------
// CRASH
// -----------------------------------------

#define CRASH(cause)						\
{											\
	UINT32* crash = nullptr;				\
	__analysis_assume(crash != nullptr);	\
	*crash = 0xDEADBEEF;					\
}

#define ASSERT_CRASH(expr)							\
{													\
	if (!(expr))									\
	{												\
		CRASH("ASSERT_CRASH");						\
		__analysis_assume(expr);					\
	}												\
}

#define WIN_SIZE_X 1280
#define WIN_SIZE_Y 720

#define FIND_IMG ImageManagerD2::GetInstance()->FindImage

#define INPUT_KEY_DOWN Input::GetButtonDown
#define INPUT_KEY_UP Input::GetButtonUp
#define INPUT_KEY_STAY Input::GetButton