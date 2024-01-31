#ifndef OWNER_H
#define OWNER_H

namespace Memory
{
	#ifdef SAFE_UNIQUE
		#include <memory>
		#include <exception>
		template<class T>
		class owned_safe_ptr
		{
		private:
			std::unique_ptr<T> m_ptr;
		public:
			T* operator->()
			{
				return this->get();
			}

			T* get()
			{
				if(!m_ptr)
					throw std::logic_excpetion()
				return m_ptr.get();
			}

			const T* get() const
			{
				if(!m_ptr)
					throw std::logic_excpetion()
				return m_ptr.get();
			}

			const T* operator->() const
			{
				return this->get();
			}
		};

		template<class T>
		class unowned_safe_ptr
		{
			private:
				T* m_ptr;
			public:
				unowned_safe_ptr() = delete;
				unowned_safe_ptr(unowned_safe_ptr& ptr) m_ptr(ptr)
				{
				}
				unowned_safe_ptr(unowned_safe_ptr&&) = delete;
			
				T* operator->()
				{
					return this->get();
				}

				T* operator(T*)()
				{
					return m_ptr;
				}

				const T* operator->() const
				{
					return this->get();
				}	
		};
	#else
		#include <memory>

		template<class T>
		using Owned = std::unique_ptr<T>;

		template<class T>
		using Unowned = T*;
	#endif
}


#endif //OWNER_H