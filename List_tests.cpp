#include "List.hpp"
#include "unit_test_framework.hpp"
using namespace std;

TEST(test_empty_initial) {
  List<int> L;
  ASSERT_TRUE(L.empty());
  ASSERT_EQUAL(L.size(), 0);
}

TEST(test_push_front_back_size) {
  List<int> L;
  L.push_front(2);
  L.push_front(1);
  L.push_back(3);
  ASSERT_FALSE(L.empty());
  ASSERT_EQUAL(L.size(), 3);
  ASSERT_EQUAL(L.front(), 1);
  ASSERT_EQUAL(L.back(), 3);
}

TEST(test_pop_front) {
  List<int> L;
  L.push_back(1);
  L.push_back(2);
  L.push_back(3);
  L.pop_front();
  ASSERT_EQUAL(L.size(), 2);
  ASSERT_EQUAL(L.front(), 2);
}

TEST(test_pop_back) {
  List<int> L;
  L.push_back(1);
  L.push_back(2);
  L.push_back(3);
  L.pop_back();
  ASSERT_EQUAL(L.size(), 2);
  ASSERT_EQUAL(L.back(), 2);
}

TEST(test_clear) {
  List<int> L;
  for (int i = 0; i < 5; i++) L.push_back(i);
  L.clear();
  ASSERT_TRUE(L.empty());
  ASSERT_EQUAL(L.size(), 0);
}

TEST(test_copy_constructor) {
  List<int> L;
  L.push_back(1);
  L.push_back(2);
  List<int> C = L;
  ASSERT_EQUAL(C.size(), 2);
  ASSERT_EQUAL(C.front(), 1);
  ASSERT_EQUAL(C.back(), 2);
  C.pop_front();
  ASSERT_EQUAL(L.size(), 2);
}

TEST(test_assignment_operator) {
  List<int> A;
  A.push_back(1);
  A.push_back(2);
  List<int> B;
  B.push_back(10);
  B = A;
  ASSERT_EQUAL(B.size(), 2);
  ASSERT_EQUAL(B.front(), 1);
  ASSERT_EQUAL(B.back(), 2);
  B.pop_back();
  ASSERT_EQUAL(A.size(), 2);
}

TEST(test_iterator_basic) {
  List<int> L;
  L.push_back(1);
  L.push_back(2);
  L.push_back(3);
  auto it = L.begin();
  ASSERT_EQUAL(*it, 1);
  it++;
  ASSERT_EQUAL(*it, 2);
  ++it;
  ASSERT_EQUAL(*it, 3);
  it++;
  ASSERT_TRUE(it == L.end());
}

TEST(test_iterator_compare_default) {
  List<int>::Iterator a, b;
  ASSERT_TRUE(a == b);
}

TEST(test_iterator_compare_list_iterators) {
  List<int> L;
  L.push_back(1);
  L.push_back(2);
  auto it1 = L.begin();
  auto it2 = L.begin();
  ASSERT_TRUE(it1 == it2);
  it2++;
  ASSERT_TRUE(it1 != it2);
}

TEST(test_insert_middle) {
  List<int> L;
  L.push_back(1);
  L.push_back(3);
  auto it = L.begin();
  it++;
  L.insert(it, 2);
  ASSERT_EQUAL(L.size(), 3);
  int expected[3] = {1,2,3};
  int i = 0;
  for (auto x : L) {
    ASSERT_EQUAL(x, expected[i]);
    i++;
  }
}

TEST(test_erase_middle) {
  List<int> L;
  L.push_back(1);
  L.push_back(2);
  L.push_back(3);
  auto it = L.begin();
  it++;
  L.erase(it);
  ASSERT_EQUAL(L.size(), 2);
  ASSERT_EQUAL(L.front(), 1);
  ASSERT_EQUAL(L.back(), 3);
}

TEST(test_erase_front_back) {
  List<int> L;
  L.push_back(1);
  L.push_back(2);
  L.push_back(3);
  auto it1 = L.begin();
  L.erase(it1);
  ASSERT_EQUAL(L.front(), 2);
  auto it2 = L.begin();
  it2++;
  L.erase(it2);
  ASSERT_EQUAL(L.back(), 2);
}

TEST_MAIN()
