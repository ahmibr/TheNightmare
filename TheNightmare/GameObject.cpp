#include "GameObject.h"
#include "../include/learnopengl/model.h"

GameObject::GameObject()
{ }

bool GameObject::intersectPlaneX(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, float x, Ray bullet) {
	glm::vec3 n = glm::normalize(glm::cross(c - b, a - b));

	if (glm::dot(bullet.dir, n) == 0)
		return false;

	glm::vec3 po = glm::vec3(x, (c.y + b.y) / 2, (a.z + b.z) / 2);

	float distance = glm::dot((po - bullet.lo), n) / glm::dot(bullet.dir, n);

	glm::vec3 intersectionPoint = distance * bullet.dir + bullet.lo;

	if ((abs(intersectionPoint.x - x) <= EPSILON) && (intersectionPoint.y > b.y && intersectionPoint.y < c.y) && (intersectionPoint.z > a.z && intersectionPoint.z < b.z))
		return true;
	else
		return false;
}

bool GameObject::intersectPlaneY(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, float y, Ray bullet) {
	glm::vec3 n = glm::normalize(glm::cross(c - b, a - b));

	if (glm::dot(bullet.dir, n) == 0)
		return false;

	glm::vec3 po = glm::vec3((a.x + b.x) / 2, y, (c.y + b.y) / 2);

	float distance = glm::dot((po - bullet.lo), n) / glm::dot(bullet.dir, n);

	glm::vec3 intersectionPoint = distance * bullet.dir + bullet.lo;

	if ((intersectionPoint.x > b.x && intersectionPoint.x < c.x) && (abs(intersectionPoint.y - y) <= EPSILON) && (intersectionPoint.z > a.z && intersectionPoint.z < b.z))
		return true;
	else
		return false;
}

bool GameObject::intersectPlaneZ(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, float z, Ray bullet) {
	glm::vec3 n = glm::normalize(glm::cross(c - b, a - b));

	if (glm::dot(bullet.dir, n) == 0)
		return false;

	glm::vec3 po = glm::vec3((a.x + b.x) / 2, (c.y + b.y) / 2, a.z);

	float distance = glm::dot((po - bullet.lo), n) / glm::dot(bullet.dir, n);

	glm::vec3 intersectionPoint = distance * bullet.dir + bullet.lo;

	if ((intersectionPoint.x > a.x && intersectionPoint.x < b.x) && (intersectionPoint.z > b.z && intersectionPoint.z < c.z) && (abs(intersectionPoint.z - z) <= EPSILON))
		return true;
	else
		return false;
}

bool GameObject::intersectPlane(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, int flag, float value, Ray bullet) {
	if (flag == 1)
		return intersectPlaneX(a, b, c, d, value, bullet);
	else if (flag == 2)
		return intersectPlaneY(a, b, c, d, value, bullet);
	else if (flag == 3) {
		return intersectPlaneZ(a, b, c, d, value, bullet);
	}
}

bool GameObject::rayCast(Ray bullet) {
	glm::vec3 center = this->GetCenter();
	float x = abs(this->GetMaxVertex().x - this->GetMinVertex().x);
	float y = abs(this->GetMaxVertex().y - this->GetMinVertex().y);
	float z = abs(this->GetMaxVertex().z - this->GetMinVertex().z);

	glm::vec3 o = glm::vec3(center.x + x / 2, center.y - y / 2, center.z - z / 2);

	glm::vec3 a = glm::vec3(o.x - x, o.y, o.z);
	glm::vec3 b = glm::vec3(o.x - x, o.y, o.z + z);
	glm::vec3 c = glm::vec3(o.x - x, o.y + y, o.z);
	glm::vec3 d = glm::vec3(o.x - x, o.y + y, o.z + z);
	glm::vec3 e = glm::vec3(o.x, o.y, o.z + z);
	glm::vec3 f = glm::vec3(o.x, o.y + y, o.z + z);
	glm::vec3 g = glm::vec3(o.x, o.y + y, o.z);

	bool intersected = intersectPlane(a, b, c, d, 1, a.x, bullet);
	intersected = intersected || intersectPlane(d, c, f, g, 2, d.y, bullet);
	intersected = intersected || intersectPlane(b, e, f, c, 3, d.z, bullet);
	intersected = intersected || intersectPlane(o, a, d, g, 3, d.z, bullet);

	return intersected;
}

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

float GameObject::getMaxX()
{
	glm::vec3 center = this->GetCenter();
	float x = abs(this->GetMaxVertex().x - this->GetMinVertex().x);
	float y = abs(this->GetMaxVertex().y - this->GetMinVertex().y);
	float z = abs(this->GetMaxVertex().z - this->GetMinVertex().z);

	glm::vec3 o = glm::vec3(center.x + x / 2, center.y - y / 2, center.z - z / 2);

	return o.x - x;
}

void GameObject::Move()
{ }

void GameObject::Translate(glm::vec3 tran)
{
	ModelMatrix= glm::translate( ModelMatrix, tran);
	MinVertex += tran;
	MaxVertex += tran;
	ObjectCenter += tran;
}

void GameObject::Rotate(glm::vec3 RotationAxes, float degree)
{
	ModelMatrix=glm::rotate(ModelMatrix, glm::radians(degree), RotationAxes);
	//glm::rotate(ObjectCenter, glm::radians(degree), RotationAxes);
}


GameObject::~GameObject()
{ }
