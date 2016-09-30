#include "cpp_exp_base.h"
#include <iostream>

namespace {

	class Animal {
	public:
		virtual ~Animal() {}
	protected:
		virtual void speak() = 0;
		void speaktwice() { speak(); speak(); }
		void sayhello(bool say_twice) {
			std::cout << "hello, ";
			if (say_twice) speaktwice();
			else speak(); 
			std::cout << "\n";
		}
	};
	class Cat : public Animal{
	public:
		Cat(int m) { sayhello(false); }
		Cat(int m, int n){ sayhello(true); }
	protected:
		void speak() override { std::cout<<"meow "; }
	};
	class Dog : public Animal {
	public:
		Dog(int m) { sayhello(false); }
		Dog(int m, int n) { sayhello(true); }
	protected:
		void speak() override { std::cout << "woof "; }
	};

	template<class T, class... Args>
	void mcdonald(void *where, Args&&... args) {
		new (where) T(std::forward<Args>(args)...);
	}
	void populate(void *here, void *there, int meow) {
		mcdonald<Cat>(here, meow); 
		mcdonald<Cat>(there, meow, meow); 

		mcdonald<Dog>(here, meow);
		mcdonald<Dog>(there, meow, meow);
	}
}

void test_variadic_template()
{
	static_assert(sizeof(Cat) == sizeof(Dog), "Cat and Dog share same byte.");
	signed char* cat1 = new signed char[sizeof(Cat)];
	signed char* cat2 = new signed char[sizeof(Cat)];
	
	populate(cat1, cat2, 1);

	delete[] cat1;
	delete[] cat2;
};