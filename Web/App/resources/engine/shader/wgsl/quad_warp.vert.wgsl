//	Copyright (c) 2008-2023 Ryo Suzuki.
//	Copyright (c) 2016-2023 OpenSiv3D Project.
//	Licensed under the MIT License.

//
//	VSOutput
//
struct VertexOutput
{
	@builtin(position) Position: vec4<f32>,
	@location(0) Color: vec4<f32>,
   	@location(1) UV: vec2<f32>,
};

//
//	Siv3D Functions
//
fn s3d_Transform2D(pos: vec2<f32>, t: array<vec4<f32>, 2>) -> vec4<f32>
{
	return vec4<f32>(t[0].zw + (pos.x * t[0].xy) + (pos.y * t[1].xy), t[1].zw);
}

//
//	Constant Buffer
//
struct VSConstants2DStruct
{
	transform: array<vec4<f32>, 2>,
	colorMul: vec4<f32>,
};

@group(0) @binding(0)
var<uniform> VSConstants2D: VSConstants2DStruct;

struct VSQuadWarpStruct
{
	homography: mat3x3<f32>,
};

@group(0) @binding(1)
var<uniform> VSQuadWarp: VSQuadWarpStruct;

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
@vertex
fn main(
	@location(0) VertexPosition: vec2<f32>,
	@location(1) VertexUV: vec2<f32>,
	@location(2) VertexColor: vec4<f32>
) -> VertexOutput
{
	var output: VertexOutput;

	let position: vec2<f32> = Transform(VertexPosition, VSQuadWarp.homography);

	output.Position = s3d_Transform2D(position, VSConstants2D.transform);

	output.Color = (VertexColor * VSConstants2D.colorMul).xyz;

	output.UV = position;

	return output;
}
