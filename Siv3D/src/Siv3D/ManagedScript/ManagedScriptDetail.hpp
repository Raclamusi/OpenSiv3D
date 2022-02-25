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

# pragma once
# include <Siv3D/ManagedScript.hpp>
# include <Siv3D/Script.hpp>

namespace s3d
{
	class ManagedScript::ManagedScriptDetail
	{
	public:

		ManagedScriptDetail();

		explicit ManagedScriptDetail(FilePathView path);

		~ManagedScriptDetail();

		[[nodiscard]]
		bool isEmpty() const;

		[[nodiscard]]
		bool compiled() const;

		void run();

		[[nodiscard]]
		bool hasException() const;

		void clearException();

	private:

		Script m_script;

		std::function<bool()> m_callback;

		ScriptFunction<void()> m_main;

		bool m_requestReload = false;

		bool m_hasException = false;
	};
}
