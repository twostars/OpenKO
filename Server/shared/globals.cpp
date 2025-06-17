#include "stdafx.h"
#include <random>
#include <mutex>

static std::mt19937 s_randomNumberGenerator;
static std::recursive_mutex s_rngLock;
static bool s_rngSeeded = false;

INLINE void SeedRNG()
{
	if (!s_rngSeeded)
	{
		s_randomNumberGenerator.seed((uint32_t) getMSTime());
		s_rngSeeded = true;
	}
}

int32_t myrand(int32_t min, int32_t max)
{
	std::lock_guard<std::recursive_mutex> lock(s_rngLock);
	SeedRNG();
	if (min > max) std::swap(min, max);
	std::uniform_int_distribution<int32_t> dist(min, max);
	return dist(s_randomNumberGenerator);
}

uint64_t RandUInt64()
{
	std::lock_guard<std::recursive_mutex> lock(s_rngLock);
	SeedRNG();
	std::uniform_int_distribution<uint64_t> dist;
	return dist(s_randomNumberGenerator);
}

bool CheckPercent(int16_t percent)
{
	if (percent < 0 || percent > 1000) 
		return false;

	return (percent > myrand(0, 1000));
}

time_t getMSTime()
{
#ifdef _WIN32
#if WINVER >= 0x0600
	typedef ULONGLONG(WINAPI* GetTickCount64_t)(void);
	static GetTickCount64_t pGetTickCount64 = nullptr;

	if (!pGetTickCount64)
	{
		HMODULE hModule = LoadLibraryA("KERNEL32.DLL");
		pGetTickCount64 = (GetTickCount64_t) GetProcAddress(hModule, "GetTickCount64");
		if (!pGetTickCount64)
			pGetTickCount64 = (GetTickCount64_t) GetTickCount;
		FreeLibrary(hModule);
	}

	return pGetTickCount64();
#else
	return GetTickCount();
#endif
#else
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	return (tv.tv_sec * SECOND) + (tv.tv_usec / SECOND);
#endif
}
