/**
* ボックス形状クラスの実装.
*/
#include"nkstdafx.h"
#include"nkBoxShape.h"

namespace nkEngine
{

	/**
	* バッファの作成.
	*/
	void BoxShape::CreateBuffer()
	{
		static const UINT VECTEX_NUM = 24;

		//頂点バッファのソースデータ。
		VertexBufferS vertices[VECTEX_NUM] =
		{
			{ Vector4(-1.0f, 1.0f, -1.0f,1.0f), Vector3(0.0f, 1.0f, 0.0f) },
			{ Vector4(1.0f, 1.0f, -1.0f,1.0f), Vector3(0.0f, 1.0f, 0.0f) },
			{ Vector4(1.0f, 1.0f, 1.0f,1.0f), Vector3(0.0f, 1.0f, 0.0f) },
			{ Vector4(-1.0f, 1.0f, 1.0f,1.0f), Vector3(0.0f, 1.0f, 0.0f) },

			{ Vector4(-1.0f, -1.0f, -1.0f,1.0f), Vector3(0.0f, -1.0f, 0.0f) },
			{ Vector4(1.0f, -1.0f, -1.0f,1.0f), Vector3(0.0f, -1.0f, 0.0f) },
			{ Vector4(1.0f, -1.0f, 1.0f,1.0f), Vector3(0.0f, -1.0f, 0.0f) },
			{ Vector4(-1.0f, -1.0f, 1.0f,1.0f), Vector3(0.0f, -1.0f, 0.0f) },

			{ Vector4(-1.0f, -1.0f, 1.0f,1.0f), Vector3(-1.0f, 0.0f, 0.0f) },
			{ Vector4(-1.0f, -1.0f, -1.0f,1.0f), Vector3(-1.0f, 0.0f, 0.0f) },
			{ Vector4(-1.0f, 1.0f, -1.0f,1.0f), Vector3(-1.0f, 0.0f, 0.0f) },
			{ Vector4(-1.0f, 1.0f, 1.0f,1.0f), Vector3(-1.0f, 0.0f, 0.0f) },

			{ Vector4(1.0f, -1.0f, 1.0f,1.0f), Vector3(1.0f, 0.0f, 0.0f) },
			{ Vector4(1.0f, -1.0f, -1.0f,1.0f), Vector3(1.0f, 0.0f, 0.0f) },
			{ Vector4(1.0f, 1.0f, -1.0f,1.0f), Vector3(1.0f, 0.0f, 0.0f) },
			{ Vector4(1.0f, 1.0f, 1.0f,1.0f), Vector3(1.0f, 0.0f, 0.0f) },

			{ Vector4(-1.0f, -1.0f, -1.0f,1.0f), Vector3(0.0f, 0.0f, -1.0f) },
			{ Vector4(1.0f, -1.0f, -1.0f,1.0f), Vector3(0.0f, 0.0f, -1.0f) },
			{ Vector4(1.0f, 1.0f, -1.0f,1.0f), Vector3(0.0f, 0.0f, -1.0f) },
			{ Vector4(-1.0f, 1.0f, -1.0f,1.0f), Vector3(0.0f, 0.0f, -1.0f) },

			{ Vector4(-1.0f, -1.0f, 1.0f,1.0f), Vector3(0.0f, 0.0f, 1.0f) },
			{ Vector4(1.0f, -1.0f, 1.0f,1.0f), Vector3(0.0f, 0.0f, 1.0f) },
			{ Vector4(1.0f, 1.0f, 1.0f,1.0f), Vector3(0.0f, 0.0f, 1.0f) },
			{ Vector4(-1.0f, 1.0f, 1.0f,1.0f), Vector3(0.0f, 0.0f, 1.0f) },
		};

		//頂点バッファを作成。
		VertexBuffer_.Create(vertices, VECTEX_NUM, sizeof(VertexBufferS));

		USHORT indices[36] =
		{
			3,1,0,
			2,1,3,

			6,4,5,
			7,4,6,

			11,9,8,
			10,9,11,

			14,12,13,
			15,12,14,

			19,17,16,
			18,17,19,

			22,20,21,
			23,20,22
		};

		//インデックスバッファを作成.
		IndexBuffer_.Create(indices, 36);

		IShape::CreateBuffer();

	}

}