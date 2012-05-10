#include "stdafx.h"
#include "DotNetUtilities.h"


void MarshalString(System::String^ s, std::string& os)
{
	using namespace System::Runtime::InteropServices;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(System::IntPtr((void*)chars));
}

std::wstring MQString2wstring(System::String^ IString)
{
	std::wstring Owstring;
	using namespace System::Runtime::InteropServices;
	const wchar_t *wchars = (const wchar_t*)(Marshal::StringToHGlobalUni(IString)).ToPointer();
	Owstring = wchars;
	Marshal::FreeHGlobal(System::IntPtr((void*)wchars));

	return Owstring;
}
