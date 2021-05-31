#pragma once

//-------------------------------------------------------------------------------------------------
// CONSTEXPR MAPPINGS FOR LESS MACRO USAGE
//-------------------------------------------------------------------------------------------------
enum class OS { Linux, Mac, Windows };

#ifdef __linux__
constexpr auto the_os = OS::Linux;
#elif __APPLE__
constexpr auto the_os = OS::Mac;
#elif _WIN32
constexpr auto the_os = OS::Windows;
#endif

//-------------------------------------------------------------------------------------------------
#ifdef _DEBUG
constexpr auto debug_mode = true;
#else
constexpr auto debug_mode = false;
#endif

//-------------------------------------------------------------------------------------------------
enum class CompilerType { Clang, GCC, MSVC, Other };

#ifdef __clang__
constexpr auto the_compiler = CompilerType::Clang;
#elif __GNUC__
constexpr auto the_compiler = CompilerType::GCC;
#elif _MSC_VER
constexpr auto the_compiler = CompilerType::MSVC;
#else
constexpr auto the_compiler = CompilerType::Other;
#endif


//struct Foo
//{
//    inline static int i = 5;
//};
