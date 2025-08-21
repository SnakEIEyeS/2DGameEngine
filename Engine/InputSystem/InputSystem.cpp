#include "InputSystem.h"

#include "..\GLib\GLib.h"

namespace Engine
{
	namespace InputSystem
	{
		MultiCastDelegate<button_t, bool> * ButtonChangeReceivers = nullptr;

		void ButtonChangeCallback(unsigned int i_VKeyID, bool bWentDown)
		{
			GetButtonChangeReceivers().ExecuteOnBound(i_VKeyID, bWentDown);
		}
		
		bool StartUp()
		{
			if (ButtonChangeReceivers == nullptr)
			{
				ButtonChangeReceivers = new MultiCastDelegate<button_t, bool>();
			}
			// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
			GLib::SetKeyStateChangeCallback(ButtonChangeCallback);
			return true;
		}

		MultiCastDelegate<button_t, bool> & GetButtonChangeReceivers()
		{
			assert(ButtonChangeReceivers != nullptr);

			return *ButtonChangeReceivers;
		}

		bool ShutDown()
		{
			assert(ButtonChangeReceivers != nullptr);
			delete ButtonChangeReceivers;
			//ButtonChangeReceivers.clearReceivers();
			return true;
		}
	}
}