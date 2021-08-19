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

# include <Siv3D/Script.hpp>
# include <Siv3D/ColorHSV.hpp>

namespace s3d
{
	using namespace AngelScript;

	using ValueType = ColorF;

	static void Construct(const ColorF& color, ValueType* self)
	{
		new(self) ValueType(color);
	}

	static void ConstructDD(double rgb, double a, ValueType* self)
	{
		new(self) ValueType(rgb, a);
	}

	static void ConstructDDDD(double r, double g, double b, double a, ValueType* self)
	{
		new(self) ValueType(r, g, b, a);
	}

	static void ConstructCD(const ColorF& rgb, double a, ValueType* self)
	{
		new(self) ValueType(rgb, a);
	}

	static void ConstructVD(const Vec3& rgb, double a, ValueType* self)
	{
		new(self) ValueType(rgb, a);
	}

	static void ConstructV4(const Vec4& rgba, ValueType* self)
	{
		new(self) ValueType(rgba);
	}

	static void ConstructC(const Color& color, ValueType* self)
	{
		new(self) ValueType(color);
	}

	static void ConstructCA(const Color& color, double a, ValueType* self)
	{
		new(self) ValueType(color, a);
	}

	static void ConstructH(const HSV& hsv, ValueType* self)
	{
		new(self) ValueType(hsv);
	}

	static void ConstructHA(const HSV& hsv, double a, ValueType* self)
	{
		new(self) ValueType(hsv, a);
	}

	static void ConstructS(const String& code, ValueType* self)
	{
		new(self) ValueType(code);
	}

	static ColorF MulColorF(double other, const ColorF& value)
	{
		return (value * other);
	}

	static bool EqualsColorF(const ColorF& other, const ColorF& value)
	{
		return (value == other);
	}

	void RegisterColorF(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "ColorF";

		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "double r", asOFFSET(ColorF, r)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double g", asOFFSET(ColorF, g)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double b", asOFFSET(ColorF, b)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double a", asOFFSET(ColorF, a)); assert(r >= 0);

		//
		//	Constructor
		//
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const ColorF& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double r, double g, double b, double a = 1.0)", asFUNCTION(ConstructDDDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double rgb, double a = 1.0) explicit", asFUNCTION(ConstructDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const ColorF& in, double)", asFUNCTION(ConstructCD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec3& in, double a = 1.0) explicit", asFUNCTION(ConstructVD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec4& in) explicit", asFUNCTION(ConstructV4), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Color& in)", asFUNCTION(ConstructC), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Color& in, double a)", asFUNCTION(ConstructCA), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const HSV& in)", asFUNCTION(ConstructH), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const HSV& in, double a)", asFUNCTION(ConstructHA), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in) explicit", asFUNCTION(ConstructS), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		// elem
		//
		r = engine->RegisterObjectMethod(TypeName, "double elem(size_t) const", asMETHOD(ColorF, elem), asCALL_THISCALL); assert(r >= 0);

		//
		// =
		//
		r = engine->RegisterObjectMethod(TypeName, "ColorF& opAssign(const ColorF& in)", asMETHODPR(ColorF, operator=, (const ColorF&), ColorF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& opAssign(Color)", asMETHODPR(ColorF, operator=, (Color), ColorF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& opAssign(const HSV& in)", asMETHODPR(ColorF, operator=, (const HSV&), ColorF&), asCALL_THISCALL); assert(r >= 0);

		//
		//	+, +=, -, -=
		//
		r = engine->RegisterObjectMethod(TypeName, "ColorF opAdd(const ColorF& in) const", asMETHODPR(ColorF, operator+, (const ColorF&) const, ColorF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& opAddAssign(const ColorF& in)", asMETHODPR(ColorF, operator+=, (const ColorF&), ColorF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF opSub(const ColorF& in) const", asMETHODPR(ColorF, operator-, (const ColorF&) const, ColorF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& oopSubAssign(const ColorF& in)", asMETHODPR(ColorF, operator-=, (const ColorF&), ColorF&), asCALL_THISCALL); assert(r >= 0);

		//
		//	*, *=
		//
		r = engine->RegisterObjectMethod(TypeName, "ColorF opMul(double) const", asMETHODPR(ColorF, operator*, (double) const, ColorF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& opMulAssign(double)", asMETHODPR(ColorF, operator*=, (double), ColorF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF opMul(const ColorF &in) const", asMETHODPR(ColorF, operator*, (const ColorF&) const, ColorF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& opMulAssign(const ColorF &in)", asMETHODPR(ColorF, operator*=, (const ColorF&), ColorF&), asCALL_THISCALL); assert(r >= 0);	
		r = engine->RegisterObjectMethod(TypeName, "ColorF opMul_r(double) const", asFUNCTION(MulColorF), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		//	==, !=
		//
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const ColorF& in) const", asFUNCTION(EqualsColorF), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		//	set
		//
		r = engine->RegisterObjectMethod(TypeName, "ColorF& setR(double r)", asMETHOD(ColorF, setR), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& setG(double g)", asMETHOD(ColorF, setG), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& setB(double b)", asMETHOD(ColorF, setB), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& setA(double a)", asMETHOD(ColorF, setA), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& setRGB(double rgb)", asMETHODPR(ColorF, setRGB, (double), ColorF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& setRGB(double r, double g, double b)", asMETHODPR(ColorF, setRGB, (double, double, double), ColorF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& set(double rgb, double a = 1.0)", asMETHODPR(ColorF, set, (double, double), ColorF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& set(double r, double g, double b, double a = 1.0)", asMETHODPR(ColorF, set, (double, double, double, double), ColorF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& set(const ColorF& in)", asMETHODPR(ColorF, set, (const ColorF&), ColorF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF withAlpha(double a)", asMETHOD(ColorF, withAlpha), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double grayscale() const", asMETHOD(ColorF, grayscale), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double minRGBComponent() const", asMETHOD(ColorF, minRGBComponent), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double maxRGBComponent() const", asMETHOD(ColorF, maxRGBComponent), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double minComponent() const", asMETHOD(ColorF, minComponent), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double maxComponent() const", asMETHOD(ColorF, maxComponent), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF lerp(const ColorF& in, double) const", asMETHOD(ColorF, lerp), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF gamma(double) const", asMETHOD(ColorF, gamma), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF removeSRGBCurve() const", asMETHOD(ColorF, removeSRGBCurve), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF applySRGBCurve() const", asMETHOD(ColorF, applySRGBCurve), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "size_t hash() const", asMETHOD(ColorF, hash), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Color toColor() const", asMETHOD(ColorF, toColor), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4 toFloat4() const", asMETHOD(ColorF, toFloat4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 toVec4() const", asMETHOD(ColorF, toVec4), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 rg() const", asMETHOD(ColorF, rg), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 gb() const", asMETHOD(ColorF, gb), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 ba() const", asMETHOD(ColorF, ba), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec3 rgb() const", asMETHOD(ColorF, rgb), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 gba() const", asMETHOD(ColorF, gba), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 bgr() const", asMETHOD(ColorF, bgr), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec4 rgba() const", asMETHOD(ColorF, rgba), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 rgb0() const", asMETHOD(ColorF, rgb0), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 rgb1() const", asMETHOD(ColorF, rgb1), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 argb() const", asMETHOD(ColorF, argb), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 abgr() const", asMETHOD(ColorF, abgr), asCALL_THISCALL); assert(r >= 0);

		r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("ColorF Zero()", asFUNCTION(ColorF::Zero), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("ColorF One()", asFUNCTION(ColorF::One), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);

		r = engine->RegisterGlobalFunction("ColorF AlphaF(double)", asFUNCTION(AlphaF), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("ColorF Transparency(double)", asFUNCTION(Transparency), asCALL_CDECL); assert(r >= 0);

		//r = engine->RegisterObjectMethod(TypeName, "Color opImplConv() const", asMETHOD(ColorF, toColor), asCALL_THISCALL); assert(r >= 0);
	}
}
