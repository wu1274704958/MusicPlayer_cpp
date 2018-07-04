#pragma once

class MeshVAO
{
public:
	int VAO;
	int VBO;
	int VNum;
	
	MeshVAO()
	{
		this->VAO = 0;
		this->VBO = 0;
		this->VNum = 0;
	}

	MeshVAO(int VAO, int VBO, int VNum) 
	{
		this->VAO = VAO;
		this->VBO = VBO;
		this->VNum = VNum;
	};

	MeshVAO(const MeshVAO& mv)
	{
		this->VAO = mv.VAO;
		this->VBO = mv.VBO;
		this->VNum = mv.VNum;
	};

	MeshVAO( MeshVAO&& mv)
	{
		this->VAO = mv.VAO;
		this->VBO = mv.VBO;
		this->VNum = mv.VNum;

		mv.VAO = 0;
		mv.VBO = 0;
		mv.VNum = 0;
	};

	MeshVAO& operator=(const MeshVAO& mv)
	{
		this->VAO = mv.VAO;
		this->VBO = mv.VBO;
		this->VNum = mv.VNum;
		return (*this);
	}
} ;
