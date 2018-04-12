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
#include "..\include\StateMachine.h"
#include "..\include\BumperState.h"

int main()
{
	// Initialize the services
	romfsInit();
	sf2d_init();

	sf2d_set_clear_color(RGBA8(0x30, 0x30, 0x30, 0xFF));
	sf2d_set_3D(0);

	consoleInit(GFX_BOTTOM, NULL);

	// Set up state machine
	StateMachine _machine;
	BumperState* _title = new BumperState();
	_machine.ChangeState(_title);

	//Main loop
	while (aptMainLoop())
	{
		hidScanInput();

		if (_machine.Update() == 1)
			break;

		_machine.Render();

		sf2d_swapbuffers();
	}

	if (_machine.GetCurrentState())
		delete _machine.GetCurrentState();

	// Exit the services
	sf2d_fini();
	romfsExit();

	return 0;
}