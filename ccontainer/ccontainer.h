#pragma once

#ifdef CCONTAINER_EXPORTS
#define CCONTAINER_API __declspec(dllexport)
#else
#define CCONTAINER_API __declspec(dllimport)
#endif

#include <iterator>
#include <random>
#include <d2d1.h>

#pragma comment(lib, "d2d1.lib")

constexpr int BAD_PTR{ 5001 };
constexpr int BAD_INDEX{ 5002 };
constexpr int BAD_PARAM{ 5003 };
constexpr int BAD_ERR{ 5004 };

namespace contlib
{
	class CCONTAINER_API RAND
	{
	private:
		std::mt19937* twister{ nullptr };

	public:
		RAND();
		~RAND();

		int operator()(int min, int max);
		float operator()(float min, float max);
	};
	class CCONTAINER_API EXCEPTION
	{
	private:
		int what{ BAD_ERR };

	public:

		EXCEPTION(int err);

		const wchar_t* eGet()const;
	};

	template<typename T> class BAG
	{
	private:
		T* mPtr{ nullptr };
		size_t max_size{ 1 };
		size_t next_pos{ 0 };

	public:

		BAG()
		{
			mPtr = reinterpret_cast<T*>(calloc(max_size, sizeof(T)));
		}
		BAG(size_t lenght)
		{
			max_size = lenght;
			mPtr = reinterpret_cast<T*>(calloc(max_size, sizeof(T)));
		}
		BAG(BAG& other)
		{
			if (other.mPtr == nullptr || other.max_size == 1)mPtr = reinterpret_cast<T*>(calloc(max_size, sizeof(T)));
			else
			{
				max_size = other.max_size;
				next_pos = other.next_pos;
				
				mPtr = reinterpret_cast<T*>(calloc(max_size, sizeof(T)));

				if (mPtr == nullptr)throw EXCEPTION(BAD_PTR);
				else for (size_t count = 0; count < next_pos; ++count)mPtr[count] = other.mPtr[count];
			}
		}
		BAG(BAG&& other)
		{
			if (other.mPtr == nullptr || other.max_size == 1)mPtr = reinterpret_cast<T*>(calloc(max_size, sizeof(T)));
			else
			{
				max_size = other.max_size;
				next_pos = other.next_pos;
				mPtr = other.mPtr;

				other.mPtr = nullptr;
			}
		}

		~BAG()
		{
			free(mPtr);
		}

		size_t size() const
		{
			return next_pos;
		}
		size_t capacity() const
		{
			return max_size;
		}

		bool empty() const
		{
			return (next_pos == 0);
		}

		bool operator==(BAG& other)
		{
			return (mPtr == other.mPtr);
		}
		bool operator!=(BAG& other)
		{
			return (mPtr != other.mPtr);
		}

		T& operator[] (size_t index)
		{
			if (index < 0 || index >= next_pos)throw EXCEPTION(BAD_INDEX);

			if (!mPtr)throw EXCEPTION(BAD_PTR);
			
			return mPtr[index];	
		}

		T& front()
		{
			if (!mPtr)throw EXCEPTION(BAD_PTR);
			if (empty())throw EXCEPTION(BAD_INDEX);

			return (*mPtr);
		}
		T& back()
		{
			if (!mPtr)throw EXCEPTION(BAD_PTR);
			if (empty())throw EXCEPTION(BAD_INDEX);

			return mPtr[next_pos - 1];
		}

		BAG& operator= (BAG& other)
		{
			free(mPtr);

			if (!other.mPtr)throw EXCEPTION(BAD_PARAM);
			else
			{
				if (mPtr == other.mPtr)throw EXCEPTION(BAD_PARAM);
				else
				{
					max_size = other.max_size;
					next_pos = other.next_pos;

					if (other.empty())mPtr = reinterpret_cast<T*>(calloc(max_size, sizeof(T)));
					else
					{
						mPtr = reinterpret_cast<T*>(calloc(max_size, sizeof(T)));

						if (!mPtr)throw EXCEPTION(BAD_PTR);
						else for (size_t count = 0; count < next_pos; ++count)mPtr[count] = other.mPtr[count];
					}
				}
			}

			return (*this);
		}
		BAG& operator= (BAG&& other)
		{
			if (other.mPtr == nullptr)throw EXCEPTION(BAD_PTR);
			else
			{
				max_size = other.max_size;
				next_pos = other.next_pos;

				mPtr = other.mPtr;

				other.mPtr = nullptr;
			}

			return (*this);
		}

		void push_back(T element)
		{
			if (!mPtr)throw EXCEPTION(BAD_PTR);
			else
			{
				if (next_pos + 1 <= max_size)
				{
					mPtr[next_pos] = element;
					++next_pos;
				}
				else
				{
					++max_size;

					mPtr = reinterpret_cast<T*>(realloc(mPtr, max_size * sizeof(T)));
					if (!mPtr)throw EXCEPTION(BAD_PTR);
					else
					{
						mPtr[next_pos] = element;
						++next_pos;
					}
				}

			}
		}
		void push_back(T* element)
		{
			if (!mPtr)throw EXCEPTION(BAD_PTR);
			else
			{
				if (next_pos + 1 <= max_size)
				{
					mPtr[next_pos] = *element;
					++next_pos;
				}
				else
				{
					++max_size;

					mPtr = reinterpret_cast<T*>(realloc(mPtr, max_size * sizeof(T)));
					if (!mPtr)throw EXCEPTION(BAD_PTR);
					else
					{
						mPtr[next_pos] = *element;
						++next_pos;
					}
				}
			}
		}


	};





}