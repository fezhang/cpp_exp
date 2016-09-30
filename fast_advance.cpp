#include "cpp_exp_base.h"
#include <iostream>
#include <vector>
#include <set>

namespace {

	template<class Element> 
	class tree_iterator: public std::set<Element>::iterator
	{
	public:
		using real_iterator = typename std::set<Element>::iterator;
		using supports_plus = std::false_type;
		tree_iterator(real_iterator& base_): real_iterator(base_) {}
	};

	template<class Element>
	class vector_iterator: public std::vector<Element>::iterator
	{
	public:
		using real_iterator = typename std::vector<Element>::iterator;
		using supports_plus = std::true_type;
		vector_iterator(real_iterator& base_): real_iterator(base_) {}
	};

	template<class It>
	It advance_impl(It begin, int n, std::false_type) {
		for (int i = 0; i < n; ++i) ++begin;
		return begin;
	}
	template<class It>
	It advance_impl(It begin, int n, std::true_type) {
		return begin + n;
	}
	template<class Iter>
	auto advance(Iter begin, int n) {
		return advance_impl(begin, n, typename Iter::supports_plus{}); // create an object of that type
	}
}

void test_fast_advance()
{
	std::cout << " [test_fast_advance] Start ... \n";
	std::vector<int> i_vec{1,2,3,4,5,6,7,8,9,0,1,2,3,4,5};
	auto ret = advance(vector_iterator<int>(i_vec.begin()), 8);
	std::cout << " after advanced, obj is: " << (*ret) << "\n";

	std::set<double> f_set{ 1.1,2,2,3.3,4.4,5.5,6.6,7.7};
	auto ret1 = advance(tree_iterator<double>(f_set.begin()), 3);
	std::cout << " after advanced, obj is: " << (*ret1) << "\n";
	std::cout << " [test_fast_advance] End. \n";
};