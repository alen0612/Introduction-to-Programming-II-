#include<iostream>
#include<string>
#include<cstddef>
#include<iosfwd>
/*#include"function.h"
#ifdef ONLINE_JUDGE
#include"NTHUOJLock"
#endif*/

using namespace std;

namespace oj
{
	class Memory_leak_count	//check whether the process has memory leak
	{
		friend void memory_leak_count_check();
		static unsigned count_;
	public:
		Memory_leak_count();
		~Memory_leak_count();
	};

	struct Int	//you can treat Int as int
	{
		int val;	//store int in val, you this val
		Int();
		Int(int val);
		Int(const Int &);	//copy constructor
		operator int&()	//treat Int as int, conversion function
		{
			return val;
		}
		operator int() const	//treat Int as int, conversion function
		{
			return val;
		}
		Int& operator=(const Int &);	//copy constructor
	private:
		Memory_leak_count count_;	//you don't have to pay attention on this
	};

	typedef Int data_t;

	class Vector
	{
	public:
		typedef std::size_t size_type;
		typedef Int value_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
	private:
		pointer begin_;	//begin of array
		pointer end_;	//end of array
		pointer last_;	//end of current element
	public:
		Vector();
		inline size_type capacity() const
		{
			return end_-begin_;
		}
		inline size_type size() const
		{
			return last_-begin_;
		}
		//ignore the keyword "inline"
		//operator[] makes Vector like a C-array, for example
		//int a[2]{2,1};
		//Vector vec;
		//vec.push_back(1);
		//vec.push_back(2);
		//vec[0] is equal to a[1]
		//vec[1] is equal to a[0]
		inline reference operator[](const size_type pos)
		{
			return begin_[pos];
		}
		inline const_reference operator[](const size_type pos) const
		{
			return begin_[pos];
		}

		void pop_back();
		void push_back(value_type val);

		void reserve(size_type new_capacity);

		~Vector();
	};

	std::ostream& operator<<(std::ostream &os,const Vector &vec);	//for cout

	void memory_leak_count_check();	//you don't have to pay attention on this
}

namespace oj
{
	Int::Int()
		:val(0){}	//set val as 0

	Int::Int(const int val_)
		:val(val_){}

	Int::Int(const Int &rhs)
		:val(rhs.val){}	//copy from rhs.val

	Int& Int::operator=(const Int &rhs)
	{
		val=rhs.val;	//copy from rhs.val
		return *this;
	}

	Vector::Vector()
		:begin_(NULL),end_(NULL),last_(NULL){}

	std::ostream& operator<<(std::ostream &os,const Vector &vec)
	{
		for(std::size_t i(0);i!=vec.size();++i){
			os<<vec[i]<<' ';
		}
		return os;
	}
}

void oj::Vector::pop_back(){
    last_--;
}

void oj::Vector::push_back(value_type input){
    if(begin_ == NULL && end_ == NULL){
        begin_ = new value_type[2];
        last_ = end_ = begin_+1;
        *begin_ = input;
    }
    else{
        if(size() < capacity()){
            last_++;
            (*this)[size()-1] = input;
        }
        else if(size() == capacity()){
            reserve(capacity()*3);
            last_++;
            (*this)[size()-1] = input;
        }
    }





























    /*if (begin_ == NULL && end_ == NULL){
        begin_ = new value_type[2];
		last_ = end_ = begin_ + 1;
        *begin_ = input;
		//std::cout << *begin_ << std::endl;

    }
    else{
        if (size() < capacity()){
            last_ = last_ + 1;
            (*this)[size() - 1] = input;

        }
        else if (size() == capacity()){
			reserve(capacity() * 3);
			last_ ++;
			//std::cout << val << std::endl;
			(*this)[size() - 1] = input;
			//std::cout << *last << std::

        }
    }*/
}

void oj::Vector::reserve(oj::Vector::size_type new_capacity){
    if(new_capacity > capacity()){
        pointer newarray = new Int[new_capacity+1];
        for(int i = 0; i < size(); i++){
            newarray[i] = (*this)[i];
        }


        pointer tmp = begin_;
        begin_ = newarray;
        last_ = &newarray[size()];
        end_ = newarray + new_capacity;

        delete [] tmp;
    }























    /*if (new_capacity > capacity()){
        pointer newarray = new Int[new_capacity + 1];
        for (int i = 0; i < capacity(); i ++){
        newarray[i] = (*this)[i];
    }

        pointer temp = begin_;
        last_ = &newarray[size()];
		begin_ = newarray;
		end_ = newarray + new_capacity;

		delete [] temp;
    }*/
}

oj::Vector::~Vector(){
    delete [] this->begin_;
}

int main()
{
	using namespace std;
	{
		oj::Vector v;
		string command;

		for(oj::data_t n;cin>>command;)
		{
			if(command=="pop_back")
			{
				v.pop_back();
				cout<<v<<endl;
			}
			else if(command=="push_back")
			{
				cin>>n;
				v.push_back(n);
				cout<<v<<endl;
			}
			else if(command=="capacity")
				cout<<v.capacity()<<endl;
			else if(command=="size")
				cout<<v.size()<<endl;
			else if(command=="reserve")
			{
				cin>>n;
				v.reserve(n);
				cout<<v<<endl;
			}
		}
		cout<<v<<endl;
	}
	oj::memory_leak_count_check();	//you don't have to pay attention on this
#ifdef ONLINE_JUDGE
	nthuoj_unlock();
#endif
}

namespace oj
{
	Memory_leak_count::Memory_leak_count()
	{
		++count_;	//memory request + 1
	}

	Memory_leak_count::~Memory_leak_count()
	{
		--count_;	//memory request - 1
	}

	unsigned Memory_leak_count::count_(0);

	void memory_leak_count_check()
	{
		if(Memory_leak_count::count_!=0)	//memory leak if count_ is not equal to 0
			std::cout<<"memory leak"<<std::endl;
	}
}
