#include "Subject.h"
#include "Observer.h"

void Subject::AddObserver(Observer* pObserver)noexcept
{
	if (pObserver == nullptr)
	{
		return;
	}
	if (std::find(m_pObservers.cbegin(), m_pObservers.cend(), pObserver) == m_pObservers.cend())
	{
		m_pObservers.push_back(pObserver);
	}
}

void Subject::RemoveObserver(Observer* pObserver)noexcept
{
	const auto it = std::find(m_pObservers.cbegin(), m_pObservers.cend(), pObserver);
	if (it != m_pObservers.cend())
	{
		m_pObservers.erase(it);
	}
}

void Subject::Notify(Event event, GameObject* pObject)noexcept
{
	size_t size = m_pObservers.size();
	for (size_t i = 0; i < size; i++)
	{
		m_pObservers[i]->Notify(event, pObject);
	}
}
