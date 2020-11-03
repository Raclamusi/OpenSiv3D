﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include <mutex>
# include <Siv3D/Array.hpp>
# include <Siv3D/HashTable.hpp>
# include <Siv3D/UniqueResource.hpp>
# include <Siv3D/CursorStyle.hpp>
# include <Siv3D/Cursor/ICursor.hpp>
# include <Siv3D/Windows/Windows.hpp>

namespace s3d
{
	class CCursor final : public ISiv3DCursor
	{
	private:

		HWND m_hWnd = nullptr;

		std::mutex m_clientPosBufferMutex;
		Array<std::pair<uint64, Point>> m_clientPosBuffer;

		CursorState m_state;

		bool m_clippedToWindow = false;

		static void CursorDeleter(HICON h)
		{
			::DestroyIcon(h);
		}

		std::array<HCURSOR, 11> m_systemCursors;
		HICON m_currentCursor = nullptr;
		HICON m_defaultCursor = nullptr;
		HICON m_requestedCursor = nullptr;
		HashTable<String, unique_resource<HICON, decltype(&CursorDeleter)>> m_customCursors;

		void confineCursor();

	public:

		CCursor();

		~CCursor() override;

		void init() override;

		bool update() override;
		
		const CursorState& getState() const noexcept override;

		void setPos(Point pos) override;

		bool isClippedToWindow() const noexcept override;

		void clipToWindow(bool clip) override;

		void requestStyle(CursorStyle style) override;

		void setDefaultStyle(CursorStyle style) override;
	
		bool registerCursor(StringView name, const Image& image, Point hotSpot) override;

		void requestStyle(StringView name) override;

		////////////////////////////////////////////////////////////////
		//
		//	Windows
		//
		void handleMessage(UINT message, WPARAM wParam, LPARAM lParam);

		void onSetCursor();
	};
}

