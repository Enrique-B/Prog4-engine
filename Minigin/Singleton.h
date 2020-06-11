#pragma once
namespace Fried
{
	template <class T>
	class Singleton
	{
	public:
		static T* GetInstance()
		{
			if (m_pInstance == nullptr)
			{
				m_pInstance = new T{};
			}
			return m_pInstance;
		}
		virtual ~Singleton() = default;
		Singleton(const Singleton& other) = delete;
		Singleton(Singleton&& other) = delete;
		Singleton& operator=(const Singleton& other) = delete;
		Singleton& operator=(Singleton&& other) = delete;

	protected:
		Singleton() = default;
		static T* m_pInstance;

	};
	template <class T>
	T* Singleton<T>::m_pInstance = nullptr;
}