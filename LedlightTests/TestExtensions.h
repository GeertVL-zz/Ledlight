#pragma once

#include "stdafx.h"

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template <>
			static std::wstring ToString<uint16_t>(const uint16_t& t)
			{
				RETURN_WIDE_STRING(t);
			}
		}
	}
}
