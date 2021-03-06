#pragma once

#include <memory>

#ifdef BE_PLATFORM_WINDOWS
	#if BE_DYNAMIC_LINK
		#ifdef BE_BUILD_DLL
			#define BE_API __declspec(dllexport)
		#else
			#define BE_API __declspec(dllimport)
		#endif
	#else
		#define BE_API
	#endif
#else
	#error Boss Engine ver 0.0.1 only support Windows x64 Platform!
#endif

#ifdef BE_DEBUG
	#define BE_ENABLE_ASSERTS
#endif

#ifdef BE_ENABLE_ASSERTS
	#define BE_ASSERT(x, ...) { if(!(x)) { BE_ERROR("Assertion Failed: {0}",__VA_ARGS__); __debugbreak(); } }
	#define BE_CORE_ASSERT(x, ...) { if(!(x)) { BE_CORE_ERROR("Assertion Failed: {0}",__VA_ARGS__); __debugbreak(); } }
#else
	#define BE_ASSERT(x, ...)
	#define BE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace BossEngine
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}