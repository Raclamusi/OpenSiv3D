﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include "IXInput.hpp"

namespace s3d
{
	class CXInput : public ISiv3DXInput
	{
	private:

		const std::array<detail::XInput_impl, 4> m_inputs;

	public:

		CXInput();

		~CXInput() override;

		bool init();

		void update(bool deviceChanged);

		bool isConnected(size_t userIndex) const;

		void setDeadZone(size_t userIndex, DeadZoneIndex inputIndex, const DeadZone& deadZone);

		void setVibration(size_t userIndex, double leftMotorSpeed, double rightMotorSpeed);

		std::pair<double, double> getVibration(size_t userIndex) const;

		void pauseVibration(size_t userIndex);

		void resumeVibration(size_t userIndex);

		bool down(size_t userIndex, uint32 index) const;

		bool pressed(size_t userIndex, uint32 index) const;

		bool up(size_t userIndex, uint32 index) const;

		MillisecondsF pressedDuration(size_t userIndex, uint32 index) const;

		const detail::XInput_impl& getInput(size_t userIndex) const;
	};
}

# endif
