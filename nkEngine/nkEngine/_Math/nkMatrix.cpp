/**
* �s��N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkMatrix.h"

namespace nkEngine
{

	/** �P�ʍs��. */
	const Matrix Matrix::Identity = 
	{
		1.0f, 0.0f, 0.0f, 0.0f ,
		0.0f, 1.0f, 0.0f, 0.0f ,
		0.0f, 0.0f, 1.0f, 0.0f ,
		0.0f, 0.0f, 0.0f, 1.0f
	};

}