#pragma once

//#include "GLib\GLib.h"
#include "..\Messaging\Delegates.h"

namespace Engine
{
	namespace InputSystem
	{
		bool StartUp();

		typedef unsigned int button_t;
		typedef Delegate<button_t, bool> ButtonChangeReceiver_t;
		extern MultiCastDelegate<button_t, bool> * ButtonChangeReceivers;

		void ButtonChangeCallback(unsigned int i_VKeyID, bool bWentDown);
		MultiCastDelegate<button_t, bool> & GetButtonChangeReceivers();

		bool ShutDown();
	}
}

//#include "InputSystem.cpp"