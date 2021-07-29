﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Cone.hpp>
# include <Siv3D/Mesh.hpp>
# include <Siv3D/Quaternion.hpp>
# include <Siv3D/PrimitiveMesh/IPrimitiveMesh.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	Cone::Cone(const Vec3& from, const Vec3& to, const double _r) noexcept
	{
		const Vec3 v = (to - from);
		const double length = v.length();

		if (length == 0.0)
		{
			*this = Cone{ 0.0, 0.0 };
			return;
		}

		const Vec3 direction = (v / length);

		*this = Cone{ from, _r, length, Quaternion::FromUnitVectors(Vec3::Up(), direction) };
	}

	const Cone& Cone::draw(const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Cone)
			.draw(Mat4x4::Scale(Float3{ r, h, r }).rotated(orientation).translated(center), color);

		return *this;
	}

	const Cone& Cone::draw(const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Cone)
			.draw(Mat4x4::Scale(Float3{ r, h, r }).rotated(orientation).translated(center), texture, color);

		return *this;
	}

	const Cone& Cone::draw(const Quaternion& rotation, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Cone)
			.draw(Mat4x4::Scale(Float3{ r, h, r }).rotated(orientation * rotation).translated(center), color);

		return *this;
	}

	const Cone& Cone::draw(const Quaternion& rotation, const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Cone)
			.draw(Mat4x4::Scale(Float3{ r, h, r }).rotated(orientation * rotation).translated(center), texture, color);

		return *this;
	}

	const Cone& Cone::draw(const Mat4x4& mat, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Cone)
			.draw((Mat4x4::Scale(Float3{ r, h, r }).translated(center) * mat), color);

		return *this;
	}

	const Cone& Cone::draw(const Mat4x4& mat, const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Cone)
			.draw((Mat4x4::Scale(Float3{ r, h, r }).rotated(orientation).translated(center) * mat), texture, color);

		return *this;
	}
}
