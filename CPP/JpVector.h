//应该是2015.7左右编写的
//现在来看显然有许多的不完善，待重构.2016.3.7

namespace CjpSTL
{
	template<typename T>
	class JpVector
	{
		enum {DefaultCap = 10};
	private:
		T* array;
		int count;
		int capacity;
		class const_iterator
		{
		protected:
			friend class JpVector<T>;

			T* current;

			T& retrieve() const
			{
				if (current== nullptr)
					throw out_of_range("it's dereferable");

				return *current;
			}

			explicit const_iterator(T* newDes) : current(newDes)
			{
			}

		public:

			T& operator [](int index)
			{
				return array[index];
			}

			const T& operator [](int index)const
			{
				
				return this->operator[](index);
			}


			const_iterator() : current(nullptr)
			{
			}

			const T& operator *() const
			{
				return retrieve();
			}
#pragma region Operators


			const_iterator& operator++()
			{
				current = current + 1;
				return *this;
			}

			const_iterator& operator++(int)
			{
				const_iterator theOld = *this;
				current = current+1;
				return theOld;
			}

			bool operator ==(const const_iterator& rhs) const
			{
				return current == rhs.current;
			}

			bool operator !=(const const_iterator& rhs) const
			{
				return current != rhs.current;
			}

			const_iterator operator +(int index)
			{
				auto cur = const_iterator::current;
				for (int i = 0; i < index; ++i)
				{
					cur = cur->next;
				}
				return const_iterator(cur);
			}

#pragma endregion
		};

		class iterator :public const_iterator
		{
		protected:
			friend class JpVector;

			explicit iterator(T* newDes) : const_iterator(newDes)
			{
			}

		public:
			iterator() : const_iterator()
			{
			}

			iterator(const iterator& rhs)
			{
				const_iterator::current = rhs.current;
			}

			T& operator *()
			{
				return const_iterator::retrieve();
			}

			iterator operator++()
			{
				const_iterator::current = const_iterator::current +1;
				return *this;
			}

			iterator operator++(int)
			{
				iterator theOld = *this;
				const_iterator::current = const_iterator::current+1;
				return theOld;
			}

			bool operator ==(const iterator& rhs) const
			{
				return const_iterator::current == rhs.current;
			}

			bool operator !=(const iterator& rhs) const
			{
				return const_iterator::current != rhs.current;
			}

			
		};
		void resize()
		{
			capacity *= 2;
			T* newArray = new T[capacity];
			for (int i = 0; i < this->count; ++i)
				newArray[i] = array[i];
			delete array;
			array = newArray;

		}

	public:
		explicit JpVector(int newLength):array(new T[newLength*2]),count(0),capacity(newLength*2){}
		JpVector():array(new T[DefaultCap]),count(0),capacity(DefaultCap){}
		JpVector(std::initializer_list<int>lis)
		{
			array = new T[DefaultCap];
			for (const auto& i : lis)
				this->push_back(i);

		}

		T& operator [](int index)
		{
			return this->array[index];
		}


		void push_back(const T& val)
		{
			array[count] = val;
			++count;
			if (count == capacity)
				resize();			
		}
		void insert(const T& val,int index)
		{
			if (index<0 || index>count)
				throw new std::out_of_range("check your index");

			++count;
			if (count == capacity)
				resize();

			for (int i =count-1; i > 0;--i)
			{
				array[i] = array[i-1];
				
				
			}
			array[index] = val;


		}

		int size() const
		{
			return count;
		}
		iterator begin()
		{
			return iterator(array);
		}
		iterator end()
		{
			return iterator(&array[size()]);
		}



	};


	inline void testInsert()
	{
		std::cout << "testInsert:" << std::endl;
		JpVector<int>vec{ 1,2,3,4,5,6,7,8,9,10 };
		for(const auto& i : vec)
		{
			cout << i << " ";

		}
		cout << endl;
		vec.insert(0, 0);
		for (const auto& i : vec)
		{
			cout << i << " ";

		}
		cout << endl;
	}



}