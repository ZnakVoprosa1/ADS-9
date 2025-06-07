// Copyright 2022 NNTU-CS
#define _CRT_SECURE_NO_WARNINGS

#include "tree.h"
#include <vector>
#include <cstdio>
#include <iostream>
#include <chrono>
#include <random>

void printPerm(const std::vector<char>& p) {
  for (auto c : p) std::cout << c;
  std::cout << std::endl;
}

int main() {
  std::vector<char> in = {'1', '2', '3', '4'};
  PMTree tree(in);

  std::cout << "All permutations:" << std::endl;
  auto perms = getAllPerms(tree);
  for (const auto& perm : perms) {
    printPerm(perm);
  }

  std::cout << "getPerm1(2): ";
  auto p1 = getPerm1(tree, 2);
  printPerm(p1);

  std::cout << "getPerm2(2): ";
  auto p2 = getPerm2(tree, 2);
  printPerm(p2);

  using std::cout;
  using std::endl;

  std::cout << "\nTime measurements:" << std::endl;
  std::vector<int> ns{3, 4, 5, 6, 7, 8};
  std::vector<double> t1, t2, tAll;

  std::mt19937 gen{42};
  for (int n : ns) {
    std::vector<char> in;
    for (int i = 0; i < n; ++i) in.push_back('1' + i);
    PMTree t(in);
    int sz = 1;
    for (int i = 2; i <= n; ++i) sz *= i;

    std::uniform_int_distribution<> d(1, sz);

    auto s1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; ++i) getAllPerms(t);
    auto e1 = std::chrono::high_resolution_clock::now();
    tAll.push_back(
        std::chrono::duration<double>(e1 - s1).count() / 100);

    int randIdx = d(gen);
    auto s2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; ++i) getPerm1(t, randIdx);
    auto e2 = std::chrono::high_resolution_clock::now();
    t1.push_back(
        std::chrono::duration<double>(e2 - s2).count() / 100);

    auto s3 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; ++i) getPerm2(t, randIdx);
    auto e3 = std::chrono::high_resolution_clock::now();
    t2.push_back(
        std::chrono::duration<double>(e3 - s3).count() / 100);
  }

  FILE* f = fopen("result/times.txt", "w");
  for (size_t i = 0; i < ns.size(); ++i) {
    fprintf(f, "%d %lf %lf %lf\n", ns[i], tAll[i], t1[i], t2[i]);
  }
  fclose(f);
  std::cout << "The data for the graph is saved in result/times.txt"
            << std::endl;
}
