//	Copyright (c) 2008-2023 Ryo Suzuki.
//	Copyright (c) 2016-2023 OpenSiv3D Project.
//	Licensed under the MIT License.

//
//	Textures
//
@group(2) @binding(0) var Sampler0: sampler;
@group(2) @binding(1) var Texture0: texture_2d<f32>;

//
//	Constant Buffer
//
struct PSConstants2DStruct
{
	colorAdd: vec4<f32>,
	sdfParam: vec4<f32>,
	sdfOutlineColor: vec4<f32>,
	sdfShadowColor: vec4<f32>,
	unused: vec4<f32>,
};

@group(1) @binding(0)
var<uniform> PSConstants2D: PSConstants2DStruct;

struct PSQuadWarpStruct
{
	invHomography: mat3x3<f32>,
	uvTransform: vec4<f32>,
};

@group(1) @binding(1)
var<uniform> PSQuadWarp: PSQuadWarpStruct;

fn Transform(pos: vec2<f32>, mat: mat3x3<f32>) -> vec2<f32>
{
	let s: f32 = (mat[0][2] * pos.x + mat[1][2] * pos.y + mat[2][2]);
	let x: f32 = (mat[0][0] * pos.x + mat[1][0] * pos.y + mat[2][0]) / s;
	let y: f32 = (mat[0][1] * pos.x + mat[1][1] * pos.y + mat[2][1]) / s;
	return vec2<f32>(x, y);
}

//
//	Functions
//
@fragment
fn main(
	@builtin(position) Position: vec4<f32>,
	@location(0) Color: vec4<f32>,
	@location(1) UV: vec2<f32>
) -> @location(0) vec4<f32> 
{
	let uv: vec2<f32> = (Transform(UV, PSQuadWarp.invHomography) * PSQuadWarp.uvTransform.xy + PSQuadWarp.uvTransform.zw);	

	let texColor: vec4<f32> = textureSample(Texture0, Sampler0, uv);

	return ((texColor * Color) + PSConstants2D.colorAdd);
}
