#include "GameObject.h"
#include "../include/learnopengl/model.h"
vector<vector<vector<pair<GameObject*, int>>>> GameObject::SceneGraph;
float GameObject::skyradius = 0;

GameObject::GameObject()
{ }

glm::vec3 GameObject::GetCenter()
{
	return ObjectCenter;
}

glm::vec3 GameObject::GetMinVertex()
{
	return MinVertex;
}

glm::vec3 GameObject::GetMaxVertex()
{
	return MaxVertex;
}

void GameObject::Move()
{ }

void GameObject::Translate(glm::vec3 tran)
{
	ModelMatrix= glm::translate( ModelMatrix, tran);
	MinVertex += tran;
	MaxVertex += tran;
	ObjectCenter += tran;
	lasttrans = tran;
}

void GameObject::Rotate(glm::vec3 RotationAxes, float degree)
{
	ModelMatrix=glm::rotate(ModelMatrix, glm::radians(degree), RotationAxes);
	//glm::rotate(ObjectCenter, glm::radians(degree), RotationAxes);
}


GameObject::~GameObject()
{ }

void GameObject::AddToSceneG(GameObject* o,int rock)
{
	//our scene boundries hypothetically are 80x60 each block is 15x20 in z,y

	//we'd need to make special checks (collision with sky & wall)

	if (o->Gz < 8 && o->Gy < 8)
	{
		SceneGraph[o->Gz][o->Gy].push_back(make_pair(o, rock));
		o->index = SceneGraph[o->Gz][o->Gy].size() - 1;
	}


}

void GameObject:: CalculateGraphIndex()
{

	 Gz = (GetCenter().z) / (skyradius/4);
	Gy = (GetCenter().y) / (skyradius / 4);
	Gz += 2;
	Gy += 2;
}

void GameObject::InitializeScene()
{
	SceneGraph.resize(4);
	for (int i = 0; i < 4; i++)
		SceneGraph[i].resize(4);
}

void GameObject::CheckMoveValidity()
{
	float ra;
	bool valid = false;
	bool r = false, l = false, f = false,b=false;
	CalculateGraphIndex();
	//while (!valid)
	//{
	//	CalculateGraphIndex();
	//	for (int i = 0; i < SceneGraph[Gz][Gy].size(); i++)
	//	{
	//		if (CheckCollision(SceneGraph[Gz][Gy][i].first, ra) && SceneGraph[Gz][Gy][i].first->index< this->index && this->ObjectCenter.x < 35
	//			|| (Myradius + sqrt(pow(ObjectCenter.x, 2) + pow(ObjectCenter.y, 2) + pow(ObjectCenter.z, 2))) > skyradius)
	//		{
	//			//if (SceneGraph[Gz][Gy][i].second == 1)// is rock
	//			//	;
	//			//else
	//			//{
	//			//	if (!r)
	//			//	{
	//			//		this->Translate(-lasttrans);
	//			//		this->Translate(glm::vec3(0, 0, 1));
	//			//		r = true;
	//			//		break;
	//			//	}
	//			//	else if (!l)
	//			//	{
	//			//		this->Translate(-lasttrans);
	//			//		this->Translate(glm::vec3(0, 0, -1));
	//			//		l = true;
	//			//		break;
	//			//	}
	//			//	else if (!f)
	//			//	{
	//			//		this->Translate(-lasttrans);
	//			//		this->Translate(glm::vec3(-1, 0, 0));
	//			//		f = true;
	//			//		break;
	//			//	}
	//			//	else if (!b) {
	//			//		this->Translate(-lasttrans);
	//			//		this->Translate(glm::vec3(1, 0, 0));
	//			//		b = true;
	//			//		break;
	//			//	}
	//			//	else //nothing works, yo2of ba2a
	//			//	{
	//			//		this->Translate(-lasttrans);
	//			//		valid = true;
	//			//		break;

	//			//	}
	//			if (!valid)
	//			{
	//				this->Translate(-lasttrans);
	//			//	this->Translate(glm::vec3(-2, 0,0));
	//				valid = true;
	//			}
	//			}

	//		}


	//	}
	//	//valid = true;
	
	for (int i = 0; i < SceneGraph[Gz+1][Gy].size(); i++)
	{
		if (CheckCollision(SceneGraph[Gz+1][Gy][i].first, ra) /*&& (SceneGraph[Gz+1][Gy][i].first->index < this->index*/ /*|| SceneGraph[Gz][Gy][i].second ==1*/)
		{
			if (!valid)
			{
				this->Translate(-lasttrans); //awa2afo
				valid = true;
			}
			/*if (SceneGraph[Gz+1][Gy][i].second == 1)
			{
				RemoveFromSG(SceneGraph[Gz+1][Gy][i].first);
			}*/
		}
	}
	for (int i = 0; i < SceneGraph[Gz][Gy+1].size(); i++)
	{
		if (CheckCollision(SceneGraph[Gz][Gy+1][i].first, ra) /*&& (SceneGraph[Gz][Gy+1][i].first->index < this->index*/ /*|| SceneGraph[Gz][Gy][i].second ==1*/)
		{
			if (!valid)
			{
				this->Translate(-lasttrans); //awa2afo
				valid = true;
			}
			/*if (SceneGraph[Gz][Gy+1][i].second == 1)
			{
				RemoveFromSG(SceneGraph[Gz][Gy+1][i].first);
			}*/
		}
	}
	for (int i = 0; i < SceneGraph[Gz-1][Gy].size(); i++)
	{
		if (CheckCollision(SceneGraph[Gz-1][Gy][i].first, ra)/* && (SceneGraph[Gz-1][Gy][i].first->index < this->index*/ /*|| SceneGraph[Gz][Gy][i].second ==1*/)
		{
			if (!valid)
			{
				this->Translate(-lasttrans); //awa2afo
				valid = true;
			}
		/*	if (SceneGraph[Gz-1][Gy][i].second == 1)
			{
				RemoveFromSG(SceneGraph[Gz-1][Gy][i].first);
			}*/
		}
	}
	for (int i = 0; i < SceneGraph[Gz][Gy-1].size(); i++)
	{
		if (CheckCollision(SceneGraph[Gz][Gy-1][i].first, ra) /*&& (SceneGraph[Gz][Gy-1][i].first->index < this->index *//*|| SceneGraph[Gz][Gy][i].second ==1*/)
		{
			if (!valid)
			{
				this->Translate(-lasttrans); //awa2afo
				valid = true;
			}
		/*	if (SceneGraph[Gz][Gy-1][i].second == 1)
			{
				RemoveFromSG(SceneGraph[Gz][Gy-1][i].first);
			}*/
		}
	}
	for (int i = 0; i < SceneGraph[Gz][Gy].size(); i++)
	{
		if (CheckCollision(SceneGraph[Gz][Gy][i].first, ra)/* && (SceneGraph[Gz][Gy][i].first->index < this->index*/ /*|| SceneGraph[Gz][Gy][i].second ==1*/)
		{
			if (!valid)
			{
				this->Translate(-lasttrans); //awa2afo
				valid = true;
			}
		/*	if (SceneGraph[Gz][Gy][i].second == 1)
			{
				RemoveFromSG(SceneGraph[Gz][Gy][i].first);
			}*/
		}
	}

	//if ((Myradius + sqrt(pow(ObjectCenter.x, 2) + pow(ObjectCenter.y, 2) + pow(ObjectCenter.z, 2))) > skyradius-5)
	//{
	//	if (!valid)
	//	{
	//		this->Translate(-lasttrans); //awa2afo
	//		valid = true;
	//	}
	//}
	CalculateGraphIndex();
	AddToSceneG(this, 0);
		
	}


bool GameObject::CheckCollision(GameObject* o, float& r)
{
	glm::vec3 diff = o->ObjectCenter - this->ObjectCenter;
	float m = sqrt(pow(diff.x, 2) + pow(diff.y, 2) + pow(diff.z, 2));
	r = m - (o->Myradius + this->Myradius);
	
	return r<=0;

}

void GameObject::RemoveFromSG(GameObject*o)
{
	SceneGraph[o->Gz][o->Gy].erase(SceneGraph[o->Gz][o->Gy].begin() + o->index );
	for (int i = o->index; i < SceneGraph[o->Gz][o->Gy].size(); i++)
	{
		SceneGraph[o->Gz][o->Gy][i].first->index--;
	}

}


void GameObject::SetSR(glm::vec3 diff)
{
	skyradius = sqrt(pow(diff.x, 2) + pow(diff.y, 2) + pow(diff.z, 2));
}