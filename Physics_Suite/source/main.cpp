#if __INTELLISENSE__
typedef unsigned int __SIZE_TYPE__;
typedef unsigned long __PTRDIFF_TYPE__;
#define __attribute__(q)
#define __builtin_strcmp(a,b) 0
#define __builtin_strlen(a) 0
#define __builtin_memcpy(a,b) 0
#define __builtin_va_list void*
#define __builtin_va_start(a,b)
#define __extension__
#endif

#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#include <3ds.h>
#include <sf2d.h>
#include <stdio.h>

int main()
{
	// Initialize the services
	romfsInit();
	sf2d_init();

	sf2d_set_clear_color(RGBA8(0x30, 0x30, 0x30, 0xFF));
	sf2d_set_3D(0);

	//Main loop
	while (aptMainLoop())
	{
		hidScanInput();

		// If Start button is pressed, we exit
		if (hidKeysDown() & KEY_START)
		{
			break;
		}

		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_fill_circle(0, 0, 50, RGBA8(0xFF, 0, 0, 0xFF));
		sf2d_end_frame();

		sf2d_swapbuffers();
	}

	// Exit the services
	sf2d_fini();
	romfsExit();

	return 0;
}