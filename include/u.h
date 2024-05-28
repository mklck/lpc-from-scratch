#ifndef U_H
#define U_H

typedef unsigned int  u32;
typedef unsigned char bool;
typedef unsigned char u8;

typedef u32 Port;
typedef u32 size_t;

typedef void (IrqFn)(void);

#define LEN(x) (sizeof(x)/sizeof(*(x)))

#ifndef false
#define false (0)
#endif

#ifndef true
#define true (!false)
#endif

#endif
