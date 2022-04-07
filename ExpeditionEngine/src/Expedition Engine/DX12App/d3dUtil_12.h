//***************************************************************************************
// d3dUtil.h by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#ifndef D3DUTIL_H
#define D3DUTIL_H

#include <assert.h>
#include "../Math/Vector/Vector4F.h"
#include <d3d12.h>

// Convenience macro for releasing COM objects.
#define ReleaseAndDeleteCOMobject(x) { if(x){ x->Release(); x = 0; } }

// Convenience macro for checking failure state
//#define ThrowIfFailed(x){ assert(x >= 0 && "ThrowIfFailed: HRESULT was Failed"); }

// Hack to pass a Vect as a array of floats (only needed for ClearRenderTargetView)
#define VasA(v) { &v[x] }


namespace Colors
{
	 //Standard colors (Red/Green/Blue/Alpha)
	const Vector4F AliceBlue = { 0.941176534f, 0.972549081f, 1.000000000f, 1.000000000f };
	const Vector4F AntiqueWhite = { 0.980392218f, 0.921568692f, 0.843137324f, 1.000000000f };
	const Vector4F Aqua = { 0.000000000f, 1.000000000f, 1.000000000f, 1.000000000f };
	const Vector4F Aquamarine = { 0.498039246f, 1.000000000f, 0.831372619f, 1.000000000f };
	const Vector4F Azure = { 0.941176534f, 1.000000000f, 1.000000000f, 1.000000000f };
	const Vector4F Beige = { 0.960784376f, 0.960784376f, 0.862745166f, 1.000000000f };
	const Vector4F Bisque = { 1.000000000f, 0.894117713f, 0.768627524f, 1.000000000f };
	const Vector4F Black = { 0.000000000f, 0.000000000f, 0.000000000f, 1.000000000f };
	const Vector4F BlanchedAlmond = { 1.000000000f, 0.921568692f, 0.803921640f, 1.000000000f };
	const Vector4F Blue = { 0.000000000f, 0.000000000f, 1.000000000f, 1.000000000f };
	const Vector4F BlueViolet = { 0.541176498f, 0.168627456f, 0.886274576f, 1.000000000f };
	const Vector4F Brown = { 0.647058845f, 0.164705887f, 0.164705887f, 1.000000000f };
	const Vector4F BurlyWood = { 0.870588303f, 0.721568644f, 0.529411793f, 1.000000000f };
	const Vector4F CadetBlue = { 0.372549027f, 0.619607866f, 0.627451003f, 1.000000000f };
	const Vector4F Chartreuse = { 0.498039246f, 1.000000000f, 0.000000000f, 1.000000000f };
	const Vector4F Chocolate = { 0.823529482f, 0.411764741f, 0.117647067f, 1.000000000f };
	const Vector4F Coral = { 1.000000000f, 0.498039246f, 0.313725501f, 1.000000000f };
	const Vector4F CornflowerBlue = { 0.392156899f, 0.584313750f, 0.929411829f, 1.000000000f };
	const Vector4F Cornsilk = { 1.000000000f, 0.972549081f, 0.862745166f, 1.000000000f };
	const Vector4F Crimson = { 0.862745166f, 0.078431375f, 0.235294133f, 1.000000000f };
	const Vector4F Cyan = { 0.000000000f, 1.000000000f, 1.000000000f, 1.000000000f };
	const Vector4F DarkBlue = { 0.000000000f, 0.000000000f, 0.545098066f, 1.000000000f };
	const Vector4F DarkCyan = { 0.000000000f, 0.545098066f, 0.545098066f, 1.000000000f };
	const Vector4F DarkGoldenrod = { 0.721568644f, 0.525490224f, 0.043137256f, 1.000000000f };
	const Vector4F DarkGray = { 0.662745118f, 0.662745118f, 0.662745118f, 1.000000000f };
	const Vector4F DarkGreen = { 0.000000000f, 0.392156899f, 0.000000000f, 1.000000000f };
	const Vector4F DarkKhaki = { 0.741176486f, 0.717647076f, 0.419607878f, 1.000000000f };
	const Vector4F DarkMagenta = { 0.545098066f, 0.000000000f, 0.545098066f, 1.000000000f };
	const Vector4F DarkOliveGreen = { 0.333333343f, 0.419607878f, 0.184313729f, 1.000000000f };
	const Vector4F DarkOrange = { 1.000000000f, 0.549019635f, 0.000000000f, 1.000000000f };
	const Vector4F DarkOrchid = { 0.600000024f, 0.196078449f, 0.800000072f, 1.000000000f };
	const Vector4F DarkRed = { 0.545098066f, 0.000000000f, 0.000000000f, 1.000000000f };
	const Vector4F DarkSalmon = { 0.913725555f, 0.588235319f, 0.478431404f, 1.000000000f };
	const Vector4F DarkSeaGreen = { 0.560784340f, 0.737254918f, 0.545098066f, 1.000000000f };
	const Vector4F DarkSlateBlue = { 0.282352954f, 0.239215702f, 0.545098066f, 1.000000000f };
	const Vector4F DarkSlateGray = { 0.184313729f, 0.309803933f, 0.309803933f, 1.000000000f };
	const Vector4F DarkTurquoise = { 0.000000000f, 0.807843208f, 0.819607913f, 1.000000000f };
	const Vector4F DarkViolet = { 0.580392182f, 0.000000000f, 0.827451050f, 1.000000000f };
	const Vector4F DeepPink = { 1.000000000f, 0.078431375f, 0.576470613f, 1.000000000f };
	const Vector4F DeepSkyBlue = { 0.000000000f, 0.749019623f, 1.000000000f, 1.000000000f };
	const Vector4F DimGray = { 0.411764741f, 0.411764741f, 0.411764741f, 1.000000000f };
	const Vector4F DodgerBlue = { 0.117647067f, 0.564705908f, 1.000000000f, 1.000000000f };
	const Vector4F Firebrick = { 0.698039234f, 0.133333340f, 0.133333340f, 1.000000000f };
	const Vector4F FloralWhite = { 1.000000000f, 0.980392218f, 0.941176534f, 1.000000000f };
	const Vector4F ForestGreen = { 0.133333340f, 0.545098066f, 0.133333340f, 1.000000000f };
	const Vector4F Fuchsia = { 1.000000000f, 0.000000000f, 1.000000000f, 1.000000000f };
	const Vector4F Gainsboro = { 0.862745166f, 0.862745166f, 0.862745166f, 1.000000000f };
	const Vector4F GhostWhite = { 0.972549081f, 0.972549081f, 1.000000000f, 1.000000000f };
	const Vector4F Gold = { 1.000000000f, 0.843137324f, 0.000000000f, 1.000000000f };
	const Vector4F Goldenrod = { 0.854902029f, 0.647058845f, 0.125490203f, 1.000000000f };
	const Vector4F Gray = { 0.501960814f, 0.501960814f, 0.501960814f, 1.000000000f };
	const Vector4F Green = { 0.000000000f, 0.501960814f, 0.000000000f, 1.000000000f };
	const Vector4F GreenYellow = { 0.678431392f, 1.000000000f, 0.184313729f, 1.000000000f };
	const Vector4F Honeydew = { 0.941176534f, 1.000000000f, 0.941176534f, 1.000000000f };
	const Vector4F HotPink = { 1.000000000f, 0.411764741f, 0.705882370f, 1.000000000f };
	const Vector4F IndianRed = { 0.803921640f, 0.360784322f, 0.360784322f, 1.000000000f };
	const Vector4F Indigo = { 0.294117659f, 0.000000000f, 0.509803951f, 1.000000000f };
	const Vector4F Ivory = { 1.000000000f, 1.000000000f, 0.941176534f, 1.000000000f };
	const Vector4F Khaki = { 0.941176534f, 0.901960850f, 0.549019635f, 1.000000000f };
	const Vector4F Lavender = { 0.901960850f, 0.901960850f, 0.980392218f, 1.000000000f };
	const Vector4F LavenderBlush = { 1.000000000f, 0.941176534f, 0.960784376f, 1.000000000f };
	const Vector4F LawnGreen = { 0.486274540f, 0.988235354f, 0.000000000f, 1.000000000f };
	const Vector4F LemonChiffon = { 1.000000000f, 0.980392218f, 0.803921640f, 1.000000000f };
	const Vector4F LightBlue = { 0.678431392f, 0.847058892f, 0.901960850f, 1.000000000f };
	const Vector4F LightCoral = { 0.941176534f, 0.501960814f, 0.501960814f, 1.000000000f };
	const Vector4F LightCyan = { 0.878431439f, 1.000000000f, 1.000000000f, 1.000000000f };
	const Vector4F LightGoldenrodYellow = { 0.980392218f, 0.980392218f, 0.823529482f, 1.000000000f };
	const Vector4F LightGreen = { 0.564705908f, 0.933333397f, 0.564705908f, 1.000000000f };
	const Vector4F LightGray = { 0.827451050f, 0.827451050f, 0.827451050f, 1.000000000f };
	const Vector4F LightPink = { 1.000000000f, 0.713725507f, 0.756862819f, 1.000000000f };
	const Vector4F LightSalmon = { 1.000000000f, 0.627451003f, 0.478431404f, 1.000000000f };
	const Vector4F LightSeaGreen = { 0.125490203f, 0.698039234f, 0.666666687f, 1.000000000f };
	const Vector4F LightSkyBlue = { 0.529411793f, 0.807843208f, 0.980392218f, 1.000000000f };
	const Vector4F LightSlateGray = { 0.466666698f, 0.533333361f, 0.600000024f, 1.000000000f };
	const Vector4F LightSteelBlue = { 0.690196097f, 0.768627524f, 0.870588303f, 1.000000000f };
	const Vector4F LightYellow = { 1.000000000f, 1.000000000f, 0.878431439f, 1.000000000f };
	const Vector4F Lime = { 0.000000000f, 1.000000000f, 0.000000000f, 1.000000000f };
	const Vector4F LimeGreen = { 0.196078449f, 0.803921640f, 0.196078449f, 1.000000000f };
	const Vector4F Linen = { 0.980392218f, 0.941176534f, 0.901960850f, 1.000000000f };
	const Vector4F Magenta = { 1.000000000f, 0.000000000f, 1.000000000f, 1.000000000f };
	const Vector4F Maroon = { 0.501960814f, 0.000000000f, 0.000000000f, 1.000000000f };
	const Vector4F MediumAquamarine = { 0.400000036f, 0.803921640f, 0.666666687f, 1.000000000f };
	const Vector4F MediumBlue = { 0.000000000f, 0.000000000f, 0.803921640f, 1.000000000f };
	const Vector4F MediumOrchid = { 0.729411781f, 0.333333343f, 0.827451050f, 1.000000000f };
	const Vector4F MediumPurple = { 0.576470613f, 0.439215720f, 0.858823597f, 1.000000000f };
	const Vector4F MediumSeaGreen = { 0.235294133f, 0.701960802f, 0.443137288f, 1.000000000f };
	const Vector4F MediumSlateBlue = { 0.482352972f, 0.407843173f, 0.933333397f, 1.000000000f };
	const Vector4F MediumSpringGreen = { 0.000000000f, 0.980392218f, 0.603921592f, 1.000000000f };
	const Vector4F MediumTurquoise = { 0.282352954f, 0.819607913f, 0.800000072f, 1.000000000f };
	const Vector4F MediumVioletRed = { 0.780392230f, 0.082352944f, 0.521568656f, 1.000000000f };
	const Vector4F MidnightBlue = { 0.098039225f, 0.098039225f, 0.439215720f, 1.000000000f };
	const Vector4F MintCream = { 0.960784376f, 1.000000000f, 0.980392218f, 1.000000000f };
	const Vector4F MistyRose = { 1.000000000f, 0.894117713f, 0.882353008f, 1.000000000f };
	const Vector4F Moccasin = { 1.000000000f, 0.894117713f, 0.709803939f, 1.000000000f };
	const Vector4F NavajoWhite = { 1.000000000f, 0.870588303f, 0.678431392f, 1.000000000f };
	const Vector4F Navy = { 0.000000000f, 0.000000000f, 0.501960814f, 1.000000000f };
	const Vector4F OldLace = { 0.992156923f, 0.960784376f, 0.901960850f, 1.000000000f };
	const Vector4F Olive = { 0.501960814f, 0.501960814f, 0.000000000f, 1.000000000f };
	const Vector4F OliveDrab = { 0.419607878f, 0.556862772f, 0.137254909f, 1.000000000f };
	const Vector4F Orange = { 1.000000000f, 0.647058845f, 0.000000000f, 1.000000000f };
	const Vector4F OrangeRed = { 1.000000000f, 0.270588249f, 0.000000000f, 1.000000000f };
	const Vector4F Orchid = { 0.854902029f, 0.439215720f, 0.839215755f, 1.000000000f };
	const Vector4F PaleGoldenrod = { 0.933333397f, 0.909803987f, 0.666666687f, 1.000000000f };
	const Vector4F PaleGreen = { 0.596078455f, 0.984313786f, 0.596078455f, 1.000000000f };
	const Vector4F PaleTurquoise = { 0.686274529f, 0.933333397f, 0.933333397f, 1.000000000f };
	const Vector4F PaleVioletRed = { 0.858823597f, 0.439215720f, 0.576470613f, 1.000000000f };
	const Vector4F PapayaWhip = { 1.000000000f, 0.937254965f, 0.835294187f, 1.000000000f };
	const Vector4F PeachPuff = { 1.000000000f, 0.854902029f, 0.725490212f, 1.000000000f };
	const Vector4F Peru = { 0.803921640f, 0.521568656f, 0.247058839f, 1.000000000f };
	const Vector4F Pink = { 1.000000000f, 0.752941251f, 0.796078503f, 1.000000000f };
	const Vector4F Plum = { 0.866666734f, 0.627451003f, 0.866666734f, 1.000000000f };
	const Vector4F PowderBlue = { 0.690196097f, 0.878431439f, 0.901960850f, 1.000000000f };
	const Vector4F Purple = { 0.501960814f, 0.000000000f, 0.501960814f, 1.000000000f };
	const Vector4F Red = { 1.000000000f, 0.000000000f, 0.000000000f, 1.000000000f };
	const Vector4F RosyBrown = { 0.737254918f, 0.560784340f, 0.560784340f, 1.000000000f };
	const Vector4F RoyalBlue = { 0.254901975f, 0.411764741f, 0.882353008f, 1.000000000f };
	const Vector4F SaddleBrown = { 0.545098066f, 0.270588249f, 0.074509807f, 1.000000000f };
	const Vector4F Salmon = { 0.980392218f, 0.501960814f, 0.447058856f, 1.000000000f };
	const Vector4F SandyBrown = { 0.956862807f, 0.643137276f, 0.376470625f, 1.000000000f };
	const Vector4F SeaGreen = { 0.180392161f, 0.545098066f, 0.341176480f, 1.000000000f };
	const Vector4F SeaShell = { 1.000000000f, 0.960784376f, 0.933333397f, 1.000000000f };
	const Vector4F Sienna = { 0.627451003f, 0.321568638f, 0.176470593f, 1.000000000f };
	const Vector4F Silver = { 0.752941251f, 0.752941251f, 0.752941251f, 1.000000000f };
	const Vector4F SkyBlue = { 0.529411793f, 0.807843208f, 0.921568692f, 1.000000000f };
	const Vector4F SlateBlue = { 0.415686309f, 0.352941185f, 0.803921640f, 1.000000000f };
	const Vector4F SlateGray = { 0.439215720f, 0.501960814f, 0.564705908f, 1.000000000f };
	const Vector4F Snow = { 1.000000000f, 0.980392218f, 0.980392218f, 1.000000000f };
	const Vector4F SpringGreen = { 0.000000000f, 1.000000000f, 0.498039246f, 1.000000000f };
	const Vector4F SteelBlue = { 0.274509817f, 0.509803951f, 0.705882370f, 1.000000000f };
	const Vector4F Tan = { 0.823529482f, 0.705882370f, 0.549019635f, 1.000000000f };
	const Vector4F Teal = { 0.000000000f, 0.501960814f, 0.501960814f, 1.000000000f };
	const Vector4F Thistle = { 0.847058892f, 0.749019623f, 0.847058892f, 1.000000000f };
	const Vector4F Tomato = { 1.000000000f, 0.388235331f, 0.278431386f, 1.000000000f };
	const Vector4F Transparent = { 0.000000000f, 0.000000000f, 0.000000000f, 0.000000000f };
	const Vector4F Turquoise = { 0.250980407f, 0.878431439f, 0.815686345f, 1.000000000f };
	const Vector4F Violet = { 0.933333397f, 0.509803951f, 0.933333397f, 1.000000000f };
	const Vector4F Wheat = { 0.960784376f, 0.870588303f, 0.701960802f, 1.000000000f };
	const Vector4F White = { 1.000000000f, 1.000000000f, 1.000000000f, 1.000000000f };
	const Vector4F WhiteSmoke = { 0.960784376f, 0.960784376f, 0.960784376f, 1.000000000f };
	const Vector4F Yellow = { 1.000000000f, 1.000000000f, 0.000000000f, 1.000000000f };
	const Vector4F YellowGreen = { 0.603921592f, 0.803921640f, 0.196078449f, 1.000000000f };

}; // namespace Colors





#endif // D3DUTIL_H