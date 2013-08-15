#ifndef CONFIG_H
#define CONFIG_H

#define CONFIG_APPLICATION_VERSION_MAJOR 1
#define CONFIG_APPLICATION_VERSION_MINOR 0

#define CONFIG_PLATFORM_WIN32 1
#define CONFIG_PLATFORM_LINUX 2

#define CONFIG_COMPILER_MSVC 1
#define CONFIG_COMPILER_GNUC 2

#define CONFIG_LITTLE_ENDIAN 1
#define CONFIG_BIG_ENDIAN 2

#define CONFIG_ARCHITECTURE_32 1
#define CONFIG_ARCHITECTURE_64 2


/* Finds the compiler type and version.
*/
#if defined( _MSC_VER )
#   define CONFIG_COMPILER CONFIG_COMPILER_MSVC
#   define CONFIG__COMP_VER _MSC_VER
#elif defined( __GNUC__ )
#   define CONFIG_COMPILER CONFIG_COMPILER_GNUC
#   define CONFIG_COMP_VER (((__GNUC__)*100) + \
        (__GNUC_MINOR__*10) + \
        __GNUC_PATCHLEVEL__)
#else
#   pragma error "No known compiler. Abort! Abort!"

#endif

/* Finds the current platform */
#if defined( __WIN32__ ) || defined( _WIN32 )
#   define CONFIG_PLATFORM CONFIG_PLATFORM_WIN32
#else
#   define CONFIG_PLATFORM CONFIG_PLATFORM_LINUX
#endif

/* Find the arch type */
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)
#   define CONFIG_ARCH_TYPE CONFIG_ARCHITECTURE_64
#else
#   define CONFIG_ARCH_TYPE CONFIG_ARCHITECTURE_32
#endif

// Windows Settings
#if CONFIG_PLATFORM == CONFIG_PLATFORM_WIN32

#	if defined( CONFIG_STATIC_LIB )
		// Linux compilers don't have symbol import/export directives.
#   	define _SymbolExport
#   	define _SymbolPrivate
#   else
	// disable: "<type> needs to have dll-interface to be used by clients'
	// Happens on STL member variables which are not public therefore is ok
#		pragma warning ( disable : 4251 )
#		pragma warning ( disable : 4193 )
#		pragma warning ( disable : 4275 )
#   	if defined( CONFIG_NONCLIENT_BUILD )
#       	define _SymbolExport __declspec( dllexport )
#   	else
#           if defined( __MINGW32__ )
#               define _SymbolExport
#           else
#       	    define _SymbolExport __declspec( dllimport )
#           endif
#   	endif
#   	define _SymbolPrivate
#	endif

// Win32 compilers use _DEBUG for specifying debug builds.
#   if defined(_DEBUG)
#       define CONFIG_DEBUG_MODE 1
#   else
#       define CONFIG_DEBUG_MODE 0
#   endif

#  define CONFIG_UNICODE_SUPPORT 1

#endif 

//----------------------------------------------------------------------------
// Linux Settings
#if CONFIG_PLATFORM ==CONFIG_PLATFORM_LINUX

// On Linux debug builds aren't marked in any way unless
// you mark it yourself
#   ifdef DEBUG
#       define CONFIG_DEBUG_MODE 1
#   else
#       define CONFIG_DEBUG_MODE 0
#   endif

#endif

#endif