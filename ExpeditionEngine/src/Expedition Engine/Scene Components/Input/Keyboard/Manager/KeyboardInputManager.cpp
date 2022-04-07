#include "KeyboardInputManager.h"

#include "../KeyboardInputComponent.h"

#include <Windows.h>

#include "../../Manager/ActionBindingSetting.h"

KeyboardInputManager::KeyboardInputManager()
{
	Initialize(userInputKeys[Input::Backspace], 0x08);
	Initialize(userInputKeys[Input::Tab], 0x09);
	Initialize(userInputKeys[Input::CLEAR], 0x0c);
	Initialize(userInputKeys[Input::Enter], 0x0d);
	Initialize(userInputKeys[Input::Shift], 0x10);
	Initialize(userInputKeys[Input::Control], 0x11);
	Initialize(userInputKeys[Input::Alt], 0x12);
	Initialize(userInputKeys[Input::Pause], 0x13);
	Initialize(userInputKeys[Input::CapsLock], 0x14);
	Initialize(userInputKeys[Input::Escape], 0x1b);
	Initialize(userInputKeys[Input::Spacebar], 0x20);
	Initialize(userInputKeys[Input::PageUp], 0x21);
	Initialize(userInputKeys[Input::PageDown], 0x22);
	Initialize(userInputKeys[Input::End], 0x23);
	Initialize(userInputKeys[Input::Home], 0x24);
	Initialize(userInputKeys[Input::ArrowLeft], 0x25);
	Initialize(userInputKeys[Input::ArrowUp], 0x26);
	Initialize(userInputKeys[Input::ArrowRight], 0x27);
	Initialize(userInputKeys[Input::ArrowDown], 0x28);
	Initialize(userInputKeys[Input::Select], 0x29);
	Initialize(userInputKeys[Input::Print], 0x2a);
	Initialize(userInputKeys[Input::Execute], 0x2b);
	Initialize(userInputKeys[Input::PrintScreen], 0x2c);
	Initialize(userInputKeys[Input::Insert], 0x2d);
	Initialize(userInputKeys[Input::Delete], 0x2e);
	Initialize(userInputKeys[Input::Help], 0x2f);
	Initialize(userInputKeys[Input::Number0], 0x30);
	Initialize(userInputKeys[Input::Number1], 0x31);
	Initialize(userInputKeys[Input::Number2], 0x32);
	Initialize(userInputKeys[Input::Number3], 0x33);
	Initialize(userInputKeys[Input::Number4], 0x34);
	Initialize(userInputKeys[Input::Number5], 0x35);
	Initialize(userInputKeys[Input::Number6], 0x36);
	Initialize(userInputKeys[Input::Number7], 0x37);
	Initialize(userInputKeys[Input::Number8], 0x38);
	Initialize(userInputKeys[Input::Number9], 0x39);
	Initialize(userInputKeys[Input::LetterKeyA], 0x41);
	Initialize(userInputKeys[Input::LetterKeyB], 0x42);
	Initialize(userInputKeys[Input::LetterKeyC], 0x43);
	Initialize(userInputKeys[Input::LetterKeyD], 0x44);
	Initialize(userInputKeys[Input::LetterKeyE], 0x45);
	Initialize(userInputKeys[Input::LetterKeyF], 0x46);
	Initialize(userInputKeys[Input::LetterKeyG], 0x47);
	Initialize(userInputKeys[Input::LetterKeyH], 0x48);
	Initialize(userInputKeys[Input::LetterKeyI], 0x49);
	Initialize(userInputKeys[Input::LetterKeyJ], 0x4a);
	Initialize(userInputKeys[Input::LetterKeyK], 0x4b);
	Initialize(userInputKeys[Input::LetterKeyL], 0x4c);
	Initialize(userInputKeys[Input::LetterKeyM], 0x4d);
	Initialize(userInputKeys[Input::LetterKeyN], 0x4e);
	Initialize(userInputKeys[Input::LetterKeyO], 0x4f);
	Initialize(userInputKeys[Input::LetterKeyP], 0x50);
	Initialize(userInputKeys[Input::LetterKeyQ], 0x51);
	Initialize(userInputKeys[Input::LetterKeyR], 0x52);
	Initialize(userInputKeys[Input::LetterKeyS], 0x53);
	Initialize(userInputKeys[Input::LetterKeyT], 0x54);
	Initialize(userInputKeys[Input::LetterKeyU], 0x55);
	Initialize(userInputKeys[Input::LetterKeyV], 0x56);
	Initialize(userInputKeys[Input::LetterKeyW], 0x57);
	Initialize(userInputKeys[Input::LetterKeyX], 0x58);
	Initialize(userInputKeys[Input::LetterKeyY], 0x59);
	Initialize(userInputKeys[Input::LetterKeyZ], 0x5a);
	Initialize(userInputKeys[Input::LeftWindows], 0x5b);
	Initialize(userInputKeys[Input::RightWindows], 0x5c);
	Initialize(userInputKeys[Input::ApplicationsKey], 0x5d);
	Initialize(userInputKeys[Input::Sleep], 0x5f);
	Initialize(userInputKeys[Input::NumPad0], 0x60);
	Initialize(userInputKeys[Input::NumPad2], 0x61);
	Initialize(userInputKeys[Input::NumPad1], 0x62);
	Initialize(userInputKeys[Input::NumPad3], 0x63);
	Initialize(userInputKeys[Input::NumPad4], 0x64);
	Initialize(userInputKeys[Input::NumPad5], 0x65);
	Initialize(userInputKeys[Input::NumPad6], 0x66);
	Initialize(userInputKeys[Input::NumPad7], 0x67);
	Initialize(userInputKeys[Input::NumPad8], 0x68);
	Initialize(userInputKeys[Input::NumPad9], 0x69);
	Initialize(userInputKeys[Input::Multiply], 0x6a);
	Initialize(userInputKeys[Input::Add], 0x6b);
	Initialize(userInputKeys[Input::Seperator], 0x6c);
	Initialize(userInputKeys[Input::Subtract], 0x6d);
	Initialize(userInputKeys[Input::Decimal], 0x6e);
	Initialize(userInputKeys[Input::Divide], 0x6f);
	Initialize(userInputKeys[Input::F1], 0x70);
	Initialize(userInputKeys[Input::F2], 0x71);
	Initialize(userInputKeys[Input::F3], 0x72);
	Initialize(userInputKeys[Input::F4], 0x73);
	Initialize(userInputKeys[Input::F5], 0x74);
	Initialize(userInputKeys[Input::F6], 0x75);
	Initialize(userInputKeys[Input::F7], 0x76);
	Initialize(userInputKeys[Input::F8], 0x77);
	Initialize(userInputKeys[Input::F9], 0x78);
	Initialize(userInputKeys[Input::F10], 0x79);
	Initialize(userInputKeys[Input::F11], 0x7a);
	Initialize(userInputKeys[Input::F12], 0x7b);
	Initialize(userInputKeys[Input::F13], 0x7c);
	Initialize(userInputKeys[Input::F14], 0x7d);
	Initialize(userInputKeys[Input::F15], 0x7e);
	Initialize(userInputKeys[Input::F16], 0x7f);
	Initialize(userInputKeys[Input::F17], 0x80);
	Initialize(userInputKeys[Input::F18], 0x81);
	Initialize(userInputKeys[Input::F19], 0x82);
	Initialize(userInputKeys[Input::F20], 0x83);
	Initialize(userInputKeys[Input::F21], 0x84);
	Initialize(userInputKeys[Input::F22], 0x85);
	Initialize(userInputKeys[Input::F23], 0x86);
	Initialize(userInputKeys[Input::F24], 0x87);
	Initialize(userInputKeys[Input::NumLock], 0x90);
	Initialize(userInputKeys[Input::ScrollLock], 0x91);
	Initialize(userInputKeys[Input::ShiftLeft], 0xa0);
	Initialize(userInputKeys[Input::ShiftRight], 0xa1);
	Initialize(userInputKeys[Input::ControlLeft], 0xa2);
	Initialize(userInputKeys[Input::ControlRight], 0xa3);
	Initialize(userInputKeys[Input::MenuLeft], 0xa4);
	Initialize(userInputKeys[Input::MenuRight], 0xa5);
	Initialize(userInputKeys[Input::BrowserBack], 0xa6);
	Initialize(userInputKeys[Input::BrowserForward], 0xa7);
	Initialize(userInputKeys[Input::BrowserRefresh], 0xa8);
	Initialize(userInputKeys[Input::BrowserStop], 0xa9);
	Initialize(userInputKeys[Input::BrowserSearch], 0xaa);
	Initialize(userInputKeys[Input::BrowserFavorites], 0xab);
	Initialize(userInputKeys[Input::BrowserStartAndHome], 0xac);
	Initialize(userInputKeys[Input::VolumeMute], 0xad);
	Initialize(userInputKeys[Input::VolumeDown], 0xae);
	Initialize(userInputKeys[Input::VolumeUp], 0xaf);
	Initialize(userInputKeys[Input::TrackNext], 0xb0);
	Initialize(userInputKeys[Input::TrackPrevious], 0xb1);
	Initialize(userInputKeys[Input::MediaStop], 0xb2);
	Initialize(userInputKeys[Input::MediaPlayAndPause], 0xb3);
	Initialize(userInputKeys[Input::MailStart], 0xb4);
	Initialize(userInputKeys[Input::MediaSelect], 0xb5);
	Initialize(userInputKeys[Input::ApplicationStart1], 0xb6);
	Initialize(userInputKeys[Input::ApplicationStart2], 0xb7);
	Initialize(userInputKeys[Input::Colon], 0xba);
	Initialize(userInputKeys[Input::Plus], 0xbb);
	Initialize(userInputKeys[Input::Comma], 0xbc);
	Initialize(userInputKeys[Input::Minus], 0xbd);
	Initialize(userInputKeys[Input::Period], 0xbe);
	Initialize(userInputKeys[Input::QuestionMark], 0xbf);
	Initialize(userInputKeys[Input::Tilada], 0xc0);
	Initialize(userInputKeys[Input::BracketLeft], 0xdb);
	Initialize(userInputKeys[Input::BackSlash], 0xdc);
	Initialize(userInputKeys[Input::BracketRight], 0xdd);
	Initialize(userInputKeys[Input::QuotationMark], 0xde);
	Initialize(userInputKeys[Input::Attention], 0xf6);
	Initialize(userInputKeys[Input::CrSel], 0xf7);
	Initialize(userInputKeys[Input::ExSel], 0xf8);
	Initialize(userInputKeys[Input::EraseEOF], 0xf9);
	Initialize(userInputKeys[Input::Play], 0xfa);
	Initialize(userInputKeys[Input::Zoom], 0xfb);
	Initialize(userInputKeys[Input::PA1], 0xfd);
	Initialize(userInputKeys[Input::Clear], 0xfe);	
}

KeyboardInputManager::~KeyboardInputManager()
{
}

void KeyboardInputManager::ProcessKeyboardInput()
{
	inputKeysToTrack.SetFront(iterator);
	while (!iterator.IsOutOfNodes())
	{
		iterator.GetCurrentObject()->UpdateState(GetKeyState(iterator.GetCurrentObject()->GetCode()) & 0x80);
		++iterator;
	}
}

void KeyboardInputManager::RegisterComponentOnPressedKey(KeyboardInputComponent*& pKeyboardInputComponent, const int& keyIndex)
{
	userInputKeys[keyIndex].RegisterForOnPressed(pKeyboardInputComponent);
}

void KeyboardInputManager::RegisterComponentOnHeldKey(KeyboardInputComponent*& pKeyboardInputComponent, const int& keyIndex)
{
	userInputKeys[keyIndex].RegisterForOnHeld(pKeyboardInputComponent);
}

void KeyboardInputManager::RegisterComponentOnReleasedKey(KeyboardInputComponent*& pKeyboardInputComponent, const int& keyIndex)
{
	userInputKeys[keyIndex].RegisterForOnReleased(pKeyboardInputComponent);
}

void KeyboardInputManager::RegisterComponentOnPressedAction(KeyboardInputComponent*& pKeyboardInputComponent, const int& actionIndex)
{
	userActions[actionIndex].RegisterForOnPressed(pKeyboardInputComponent);
}

void KeyboardInputManager::RegisterComponentOnHeldAction(KeyboardInputComponent*& pKeyboardInputComponent, const int& actionIndex)
{
	userActions[actionIndex].RegisterForOnHeld(pKeyboardInputComponent);
}

void KeyboardInputManager::RegisterComponentOnReleasedAction(KeyboardInputComponent*& pKeyboardInputComponent, const int& actionIndex)
{
	userActions[actionIndex].RegisterForOnReleased(pKeyboardInputComponent);
}

void KeyboardInputManager::DeregisterComponentOnPressedKey(KeyboardInputComponent*& pKeyboardInputComponent, const int& keyIndex)
{
	userInputKeys[keyIndex].DeregisterFromOnPressed(pKeyboardInputComponent);
}

void KeyboardInputManager::DeregisterComponentOnHeldKey(KeyboardInputComponent*& pKeyboardInputComponent, const int& keyIndex)
{
	userInputKeys[keyIndex].DeregisterFromOnHeld(pKeyboardInputComponent);
}

void KeyboardInputManager::DeregisterComponentOnReleasedKey(KeyboardInputComponent*& pKeyboardInputComponent, const int& keyIndex)
{
	userInputKeys[keyIndex].DeregisterFromOnReleased(pKeyboardInputComponent);
}

void KeyboardInputManager::DeregisterComponentOnPressedAction(KeyboardInputComponent*& pKeyboardInputComponent, const int& actionIndex)
{
	userActions[actionIndex].DeregisterFromOnPressed(pKeyboardInputComponent);
}

void KeyboardInputManager::DeregisterComponentOnHeldAction(KeyboardInputComponent*& pKeyboardInputComponent, const int& actionIndex)
{
	userActions[actionIndex].DeregisterFromOnHeld(pKeyboardInputComponent);
}

void KeyboardInputManager::DeregisterComponentOnReleasedAction(KeyboardInputComponent*& pKeyboardInputComponent, const int& actionIndex)
{
	userActions[actionIndex].DeregisterFromOnReleased(pKeyboardInputComponent);
}

void KeyboardInputManager::RegisterKeyMonitorToTracking(KeyboardKeyMonitor& pKeyMonitor)
{
	inputKeysToTrack.PushBack(&pKeyMonitor, pKeyMonitor.GetStorageIterator());
}

void KeyboardInputManager::DeregisterKeyMonitorFromTracking(KeyboardKeyMonitor& pKeyMonitor)
{
	inputKeysToTrack.Remove(pKeyMonitor.GetStorageIterator());
}

void KeyboardInputManager::BindAction(const int& actionIndex, const ActionBindingSetting& actionBindingSetting)
{
	if (actionBindingSetting.actionBindingType == ActionBindingSetting::Type::Keyboard)
	{
		userActions[actionIndex].BindToKey(&userInputKeys[actionBindingSetting.index]);
	}
	else
	{
		userActions[actionIndex].UnBindFromKey();
	}
}

void KeyboardInputManager::Initialize(KeyboardKeyMonitor& keyboardKeyMonitor, const int& keyCode)
{
	keyboardKeyMonitor.SetInputManager(this);
	keyboardKeyMonitor.SetKeyCode(keyCode);
}
