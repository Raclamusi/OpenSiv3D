//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/MemoryViewReader.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "CClipboard.hpp"

namespace s3d
{
	namespace detail
	{
		__attribute__((import_name("siv3dSetClipboardText")))
		extern void siv3dSetClipboardText(const char* text);

		__attribute__((import_name("siv3dGetClipboardText")))
		extern char* siv3dGetClipboardText();

		using siv3dGetClipboardTextAsyncCallBack = void(*)(char* text, void* promise);

		__attribute__((import_name("siv3dGetClipboardTextAsync")))
		extern void siv3dGetClipboardTextAsync(siv3dGetClipboardTextAsyncCallBack, void*);

		__attribute__((import_name("siv3dSetClipboardImage")))
		extern void siv3dSetClipboardImage(const void* pngPtr, size_t pngSize);

		__attribute__((import_name("siv3dGetClipboardImage")))
		extern std::pair<void*, size_t> siv3dGetClipboardImage();
	}

	CClipboard::CClipboard() {}

	CClipboard::~CClipboard()
	{
		LOG_SCOPED_TRACE(U"CClipboard::~CClipboard()");
	}

	void CClipboard::init()
	{
		LOG_SCOPED_TRACE(U"CClipboard::init()");
	}

	bool CClipboard::hasChanged()
	{
		// [Siv3D ToDo]
		return false;
	}

	bool CClipboard::getText(String& text)
	{
		text.clear();

		if (auto rawClipBoardText = detail::siv3dGetClipboardText(); rawClipBoardText != nullptr)
		{
			text = Unicode::FromUTF8(rawClipBoardText);
			std::free(rawClipBoardText);
		}
		
		return (not text.isEmpty());
	}

	bool CClipboard::getImage(Image& image)
	{
		image.clear();

		const auto [pngPtr, pngSize] = detail::siv3dGetClipboardImage();
		if (pngPtr)
		{
			image = Image{ MemoryViewReader{ pngPtr, pngSize }, ImageFormat::PNG };
			std::free(pngPtr);
		}

		return (not image.isEmpty());
	}

	bool CClipboard::getFilePaths(Array<FilePath>& paths)
	{
		paths.clear();

		// [Siv3D ToDo]

		return (not paths.isEmpty());
	}

	void CClipboard::setText(const String& text)
	{
		detail::siv3dSetClipboardText(text.narrow().c_str());
	}

	void CClipboard::setImage(const Image& image)
	{
		const auto pngBlob = image.encodePNG();
		detail::siv3dSetClipboardImage(pngBlob.data(), pngBlob.size());
	}

	void CClipboard::clear()
	{
		setText(U"");
	}

	void CClipboard::OnGetClipboardText(char* text, void* userData)
	{
		auto& clipboard = *static_cast<CClipboard*>(userData);

		if (text)
		{
			clipboard.m_clibboardTexts << Unicode::FromUTF8(text);
		}
	}

	namespace Platform::Web::Clipboard 
	{
		namespace detail
		{
			void OnGetClipboardText(char* text, void* userData)
			{
				auto promise = static_cast<std::promise<s3d::String>*>(userData);

				if (text)
				{
					promise->set_value(Unicode::Widen(text));
				}
				else
				{
					promise->set_value(U"");
				}
			}
		}

		AsyncTask<String> GetText()
		{
			auto p = new std::promise<s3d::String>();
			auto result_future = p->get_future();

			s3d::detail::siv3dGetClipboardTextAsync(&detail::OnGetClipboardText, p);
			
			return std::move(result_future);
		}
	}
}
