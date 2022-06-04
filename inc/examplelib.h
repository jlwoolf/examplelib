#ifndef __JLWOOLF_EXAMPLELIB_H
#define __JLWOOLF_EXAMPLELIB_H

#ifdef _WIN64
// Windows (64-bit)
#elif _WIN32
// Windows (32-bit)
#elif __APPLE__
// apple
#elif __linux
// linux
#elif __unix
// Unix
#elif __posix
// POSIX
#endif
void hello_name(char* name);

#endif //__JLWOOLF_EXAMPLELIB_H
