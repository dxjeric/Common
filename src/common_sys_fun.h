#ifdef _WIN32
#include <time.h>
// tms : tm*
// tt  : time_t
#define csf_gettime(tms, tt) localtime_s(tms, tt)
#define csf_sprintf sprintf_s
// n : ∫¡√Î
#define csf_sleep(n) Sleep(n)
#define csf_vsnprintf _vsnprintf
#endif // _win32

#ifdef linux
#include <sys/time.h>
// tms : tm*
// tt  : time_t
#define csf_gettime(tms, tt) localtime_r(tt, tms)
#define csf_sprintf snprintf
#define csf_vsnprintf vsnprintf
// n : ∫¡√Î
#define csf_sleep(n) usleep(n)
#endif //linux