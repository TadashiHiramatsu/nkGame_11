/**
* プリコンパイル済みヘッダの定義.
*/
#pragma once



#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。

#define _XM_NO_INTRINSICS_

#define r_cast reinterpret_cast
#define	s_cast static_cast
#define	c_cast const_cast

//インクルード.
#include<SDKDDKVer.h>
#include<Windows.h>
#include<stdlib.h>
#include<malloc.h>
#include<memory>
#include<memory.h>
#include<tchar.h>
#include<stdio.h>
#include<cstdlib>
#include<stdarg.h>
#include<algorithm>
#include<time.h>
#include<sstream>

#include<shlwapi.h>

//STL
#include<map>
#include<vector>
#include<list>
#include<deque>

#include<string>

#include<thread>

using namespace std;

#include<d3d11.h>
#include<D3Dcompiler.h>
#include<DirectXMath.h>

#include<dinput.h>
#include<XInput.h>

#include<fbxsdk.h>

using namespace fbxsdk;

#include<DirectXTex\DirectXTex.h>

//自作ヘッダインクルード.
#include"_Debug\nkAssert.h"
#include"_Debug\nkLog.h"
#include"_Policy\nkNoncopyable.h"
#include"_Policy\nkScopedResource.h"

#include"_Math\nkMatrix.h"
#include"_Math\nkVector.h"

#include"_Graphics\nkColor.h"

#include"_Component\nkTransform.h"
#include"_GameObject\nkGameObjectManager.h"
#include"_Scene\nkSceneManager.h"

#include"_Graphics\nkRenderContext.h"
#include"nkEngine.h"

//タイマー
#include"_Timer\nkStopwatch.h"
#include"_Timer\nkTime.h"

#include"_Math\nkHash.h"
#include"_Math\nkRandom.h"

#include"_Input\nkInput.h"
#include"_Input\nkXinput.h"


//グラフィックス関係.
#include"_Graphics\nkShader.h"
#include"_Graphics\Buffer\nkVertexBuffer.h"
#include"_Graphics\Buffer\nkIndexBuffer.h"
#include"_Graphics\Buffer\nkConstantBuffer.h"

#include"_Graphics\View\nkShaderResourceView.h"

#include"_Graphics\nkTexture.h"

#include"_Graphics\3DObject\Camera\nkCamera.h"
#include"_Graphics\3DObject\nkLight.h"

#include"_Graphics\3DObject\Shape\nkBoxShape.h"
#include"_Graphics\3DObject\Model\nkModelRender.h"