/**
* 行列クラスの実装.
*/
#include"nkstdafx.h"
#include"nkMatrix.h"

namespace nkEngine
{

	/** 単位行列. */
	const Matrix Matrix::Identity = 
	{
		1.0f, 0.0f, 0.0f, 0.0f ,
		0.0f, 1.0f, 0.0f, 0.0f ,
		0.0f, 0.0f, 1.0f, 0.0f ,
		0.0f, 0.0f, 0.0f, 1.0f
	};

}