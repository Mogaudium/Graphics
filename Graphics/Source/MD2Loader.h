#pragma once
#include "Model.h"

//MD2 loader function

class MD2Loader
{
	public:
		static bool Load_Model(const char* md2model , Model& model);
};
