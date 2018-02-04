#define GCC TRUE  //change to false if using visual studio.

#if GCC == TRUE
#define __forceinline __attribute__((always_inline)) inline
#define nullptr NULL
#endif

//just a little way to shorten future checks.
#ifdef _WIN32
#elif defined(__linux__) || defined(linux) || defined(__linux)
#ifndef LINUX
#define LINUX
#else
#error "LINUX Already defined...  abort."
#endif
#elif defined(__APPLE__) || defined(__MAC__)
#ifndef APPLE
#define APPLE
#else
#error "APPLE Already defined...  abort."
#endif
#else 
#error "This OS is not defined."
#endif

//basic macros to help compile on different compilers.
#ifdef __GNUC__
#define __forceinline __attribute__((always_inline)) inline
#define nullptr NULL
#endif