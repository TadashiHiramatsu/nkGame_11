/**
 * アサート出力関数の定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * アサート.
	 *
	 * @param flag   True to flag.
	 * @param format Describes the format to use.
	 * @param file   The file.
	 * @param line   The line.
	 * @param ...    Variable arguments providing additional information.
	 */
	static inline void Assert(bool flag,const char* format,const char*file,long line,...)
	{
		if (!flag) {
			va_list va;
			va_start(va, flag);
			vprintf(format, va);
			char fileLineInfo[256];
			sprintf(fileLineInfo, "%s, %d行目", file, line);
			char assertMessage[256];
			vsprintf(assertMessage, format, va);
			strcat(assertMessage, fileLineInfo);
			MessageBox(nullptr, assertMessage, "アサート", MB_OK);
			va_end(va);
			abort();
		}
	}

}

#ifdef _DEBUG
#define 	NK_ASSERT( flg, format, ... )	Assert( flg, format, __FILE__, __LINE__, __VA_ARGS__)
#else
#define 	NK_ASSERT( flg, format, ... )
#endif // !_DEBUG