#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"

Fried::Scene::Scene(const std::string& name) noexcept
	: m_Name(name) 
{
}

Fried::Scene::~Scene()
{
	const size_t size{ m_pObjects.size() };
	for (size_t i = 0; i < size; i++)
	{
		SafeDelete(m_pObjects[i]);
	}
	m_pObjects.clear();
}

void Fried::Scene::AddGameObject(GameObject* pObject)
{
	if (pObject != nullptr)
	{
#ifdef _DEBUG
		if (std::find(m_pObjects.cbegin(), m_pObjects.cend(), pObject) != m_pObjects.cend())
		{
			throw std::runtime_error(std::string("Scene::AddGameObject gameObject is already in the scene \n"));
		}
#endif // _DEBUG
		m_pObjects.push_back(pObject);
		pObject->SetScene(this);
		pObject->Initialize();
	}
	else
	{
		throw std::runtime_error(std::string("Scene::AddGameObject was a nullptr"));
	}
}

void Fried::Scene::RemoveGameObject(GameObject* object)
{
	UNREFERENCED_PARAMETER(object);
	auto it = std::find(m_pObjects.cbegin(), m_pObjects.cend(), object);
#ifdef _DEBUG
	if (std::find(m_pObjects.cbegin(), m_pObjects.cend(), object) != m_pObjects.cend())
	{
		throw std::runtime_error(std::string("Scene::RemoveGameObject gameObject was not in the scene \n"));
	}
#endif
	m_pObjects.erase(it);
	object->SetScene(nullptr);
}

void Fried::Scene::AddCollider(ColliderComponent* pCollider)
{
	if (pCollider->GetIsStatic())
	{
#ifdef _DEBUG
		if (std::find(m_StaticColliders.begin(), m_StaticColliders.end(), pCollider) != m_StaticColliders.end())
		{
			throw std::runtime_error(std::string("Collider is already in the scene \n"));
		}
#endif // _DEBUG
		m_StaticColliders.push_back(pCollider);
	}
	else
	{
#ifdef _DEBUG
		if (std::find(m_DynamicColliders.begin(), m_DynamicColliders.end(), pCollider) != m_DynamicColliders.cend())
		{
			throw std::runtime_error(std::string("Collider is already in the scene \n"));
		}
#endif // _DEBUG
		m_DynamicColliders.push_back(pCollider);
	}
}

void Fried::Scene::RemoveCollider(ColliderComponent* pCollider)
{
	if (pCollider->GetIsStatic())
	{
		auto it = std::find(m_StaticColliders.begin(), m_StaticColliders.end(), pCollider);
#ifdef _DEBUG
		if (it == m_StaticColliders.end())
		{
			throw std::runtime_error(std::string("Scene::RemoveCollider Collider is not in Vector\n"));
		}
#endif
		m_StaticColliders.erase(it);
	}
	else
	{
		auto it = std::find(m_DynamicColliders.begin(), m_DynamicColliders.end(), pCollider);
#ifdef _DEBUG
		if (it == m_StaticColliders.end())
		{
			throw std::runtime_error(std::string("Scene::RemoveCollider Collider is not in Vector\n"));
		}
#endif
		m_DynamicColliders.erase(it);
	}
}

void Fried::Scene::Update(float elapsedSec)
{
	for (const auto& object : m_pObjects)
	{
		object->Update(elapsedSec);
	}
}

void Fried::Scene::CollisionUpdate() noexcept
{
	const size_t dynamicSize{m_DynamicColliders.size()};
	const size_t staticSize{ m_StaticColliders.size() };
	HitInfo info{};
	//loop over the dynamic colliders
	for (size_t i = 0; i < dynamicSize; i++)
	{
		//get the collisionLines from the dynamic collider
		const std::vector<Fried::line> lines{ m_DynamicColliders[i]->GetLines() };
		const size_t lineSize{ lines.size() };
		//loop over the static colliders and the lines so i can see if they intersect
		for (size_t j = 0; j < staticSize; j++)
		{
			for (size_t l = 0; l < lineSize; l++)
			{
				// to be continued
				lines[l].intersect(m_StaticColliders[j]->GetCollisionRect(), info);
				if (info.hit)
				{
					const size_t hitinfoVectorSize{ info.intersectPoint.size() };
					for (size_t h = 0; h < hitinfoVectorSize; h++)
					{
						float2 move{};
						switch (info.collision[h])
						{
						case Collision::None:
							break;
						case Collision::Left:
							move.x = info.intersectPoint[h].x - lines[l].differenceVec.x;
							break;
						case Collision::Right:
							move.x = lines[l].differenceVec.x - info.intersectPoint[h].x;
							break;
						case Collision::Up:
							move.y = info.intersectPoint[h].y - lines[l].differenceVec.y;
							break;
						case Collision::Down:
							move.y = /*info.intersectPoint[h].y -*/ lines[l].differenceVec.y/*lines[l].differenceVec.y - info.intersectPoint[h].y*/;
							break;
						default:
							break;
						}
						m_DynamicColliders[i]->GetGameObject()->GetTransform()->Move(move);
						m_DynamicColliders[i]->Update(0);
					}
					info.hit = false; 
					info.collision.clear();
					info.intersectPoint.clear();
				}
			}
		}
	}
}

void Fried::Scene::Render() const noexcept
{
	for (const auto& object : m_pObjects)
	{
		object->Render();
	}
}

void Fried::Scene::RenderCollision() const noexcept
{
	for (const auto& object : m_pObjects)
	{
		object->RenderCollision();
	}
}

