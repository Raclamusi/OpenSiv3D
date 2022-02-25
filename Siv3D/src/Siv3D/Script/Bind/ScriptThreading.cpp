﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Script.hpp>
# include <Siv3D/Threading.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterThreading(asIScriptEngine* engine)
	{
		int32 r = 0;

		r = engine->SetDefaultNamespace("Threading"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("size_t GetConcurrency()", asFUNCTION(Threading::GetConcurrency), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
