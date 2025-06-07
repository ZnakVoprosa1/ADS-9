// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <memory>

class PMTreeNode {
 public:
  char value;
  std::vector<std::shared_ptr<PMTreeNode>> children;
  explicit PMTreeNode(char v);
};

class PMTree {
 public:
  std::shared_ptr<PMTreeNode> root;
  std::vector<char> elements;
  explicit PMTree(const std::vector<char>& elems);
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
