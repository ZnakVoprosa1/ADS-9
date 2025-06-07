// Copyright 2022 NNTU-CS
#include "tree.h"

#include <cstdio>
#include <cstdlib>
#include <locale>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

PMTreeNode::PMTreeNode(char v) : value(v) {}

static void buildTree(std::shared_ptr<PMTreeNode> node,
                      const std::vector<char>& remaining) {
  if (remaining.empty()) return;
  std::vector<char> sorted_rem = remaining;
  std::sort(sorted_rem.begin(), sorted_rem.end());
  for (size_t i = 0; i < sorted_rem.size(); ++i) {
    char val = sorted_rem[i];
    std::vector<char> next_rem(sorted_rem);
    next_rem.erase(next_rem.begin() + i);
    auto child = std::make_shared<PMTreeNode>(val);
    node->children.push_back(child);
    buildTree(child, next_rem);
  }
}

PMTree::PMTree(const std::vector<char>& elems) : elements(elems) {
  root = std::make_shared<PMTreeNode>(0);
  buildTree(root, elements);
}

static void collect(const std::shared_ptr<PMTreeNode>& node,
                    std::vector<char>& path,
                    std::vector<std::vector<char>>& res,
                    int depth, int max_depth) {
  if (depth == max_depth) {
    res.push_back(path);
    return;
  }
  for (const auto& c : node->children) {
    path.push_back(c->value);
    collect(c, path, res, depth + 1, max_depth);
    path.pop_back();
  }
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  std::vector<std::vector<char>> result;
  if (tree.elements.empty()) return result;
  std::vector<char> path;
  collect(tree.root, path, result, 0, tree.elements.size());
  return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  std::vector<std::vector<char>> perms = getAllPerms(tree);
  if (num < 1 || num > static_cast<int>(perms.size()))
    return {};
  return perms[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  int n = tree.elements.size();
  if (n == 0) return {};
  std::vector<char> elems = tree.elements;
  std::sort(elems.begin(), elems.end());
  std::vector<int> fact(n, 1);
  for (int i = 1; i < n; ++i) fact[i] = fact[i - 1] * i;

  int permNum = num - 1;
  if (permNum < 0)
    return {};

  std::vector<char> res;
  std::vector<char> temp = elems;
  for (int i = n - 1; i >= 0; --i) {
    int f = fact[i];
    int idx = permNum / f;
    if (idx >= static_cast<int>(temp.size())) return {};
    res.push_back(temp[idx]);
    temp.erase(temp.begin() + idx);
    permNum %= f;
  }
  return res;
}
