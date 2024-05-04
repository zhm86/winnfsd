#include <windows.h>
#include "conv.h"
#include <string.h>

wchar_t* _conv_from_utf8(const char* s) {
	auto count = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, s, (int)strlen(s), NULL, 0);
	if (count == 0) {
		return NULL;
	}
	auto dest = new wchar_t[count + 1];
	auto err = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, s, (int)strlen(s), dest, count);
	if (err == 0) {
		return NULL;
	}
	dest[count] = 0;
	return dest;
}

wchar_t* _conv_from_acp(const char* s) {
	auto count = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, s, (int)strlen(s), NULL, 0);
	if (count == 0) {
		return NULL;
	}
	auto dest = new wchar_t[count + 1];
	auto err = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, s, (int)strlen(s), dest, count);
	if (err == 0) {
		return NULL;
	}
	dest[count] = 0;
	return dest;
}

char* _conv_to_acp(const wchar_t* s) {
	auto count = WideCharToMultiByte(CP_ACP, 0, s, (int)wcslen(s), NULL, 0, NULL, NULL);
	if (count == 0) {
		return NULL;
	}
	auto dest = new char[count + 1];
	auto err = WideCharToMultiByte(CP_ACP, 0, s, (int)wcslen(s), dest, count, NULL, NULL);
	if (err == 0) {
		return NULL;
	}
	dest[count] = 0;
	return dest;
}

char* _utf8_to_acp(const char* s){
    auto utf8 = _conv_from_utf8(s);
    auto sjis = _conv_to_acp(utf8);
    free(utf8);
    return sjis;
}

