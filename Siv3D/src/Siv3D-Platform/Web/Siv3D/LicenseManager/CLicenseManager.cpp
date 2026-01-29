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

# include <Siv3D/Keyboard.hpp>
# include <Siv3D/FileSystem.hpp>
# include "CLicenseManager.hpp"
# include <Siv3D/LicenseManager/LicenseList.hpp>
# include "LicenseList_Web.hpp"

namespace s3d
{
	CLicenseManager::CLicenseManager()
		: m_licenses(std::begin(detail::licenses), std::end(detail::licenses))
	{
		m_licenses.insert((m_licenses.begin() + 1), std::begin(detail::licenses_Web), std::end(detail::licenses_Web));
		m_applicationName = FileSystem::BaseName(FileSystem::ModulePath());
	}

	CLicenseManager::~CLicenseManager()
	{

	}

	void CLicenseManager::update()
	{
		if (m_openLicenseWithF1Key
			&& KeyF1.down())
		{
			LicenseManager::ShowInBrowser();
		}
	}

	void CLicenseManager::setApplicationLicense(const String& applicationName, const LicenseInfo& license)
	{
		if (not m_hasApplicationLicense)
		{
			const LicenseInfo info
			{
				.title		= license.title,
				.copyright	= license.copyright,
				.text		= license.text.xml_escaped()
			};
			m_licenses.push_front(info);

			++m_num_customLicenses;
			m_hasApplicationLicense = true;
		}
		else
		{
			m_licenses.front() = license;
		}

		m_applicationName = applicationName;
	}

	void CLicenseManager::addLicense(const LicenseInfo& license)
	{
		m_licenses.insert((m_licenses.begin() + m_num_customLicenses), license);

		++m_num_customLicenses;
	}

	const Array<LicenseInfo>& CLicenseManager::enumLicenses() const noexcept
	{
		return m_licenses;
	}

	const String& CLicenseManager::getApplicationName() const noexcept
	{
		return m_applicationName;
	}

	void CLicenseManager::setDefaultTriggerRnabled(const bool enabled) noexcept
	{
		m_openLicenseWithF1Key = enabled;
	}
}
