#include <iostream>
#include <iomanip>
#include <queue>
#include <stack>
#include<numeric>
#include<tuple>
#include<string>
#include <random>
#include "BinaryTreeIterator.h"
#include "BinaryTree.h"
#include "Node.h"


void generateInvalidBinaryTree(BinaryTree& tree) {
	//BinaryTree tree;
	tree.insert(50);
	tree.insert(75);
	tree.insert(25);
	tree.insert(12);
	tree.insert(20);

	// change Node with value 20 to 
	tree.getRootNode()->leftNode->leftNode->rightNode->value = 1000;
	//return tree;
}


void test_MinAndMax() {
	BinaryTree tree;
	int len = 12;
	std::vector<int> values(len);
	std::srand(std::time(nullptr)); // use current time as seed for random generator

	values[0] = std::rand() % 1000;
	int min = values[0];
	int max = values[0];
	tree.insert(values[0]);
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << __FUNCTION__ << " START MIN TEST : " << std::endl;

	std::cout << values[0] << " ";

	for (size_t i = 1; i < len; i++)
	{
		values[i] = std::rand() % 1000;
		tree.insert(values[i]);

		if (values[i] < min) { min = values[i]; }
		if (values[i] > max) { max = values[i]; }
		std::cout << values[i] << " ";
	}

	std::cout << std::endl;


	auto minNode = BinaryTree::min(tree.getRootNode());
	auto maxNode = BinaryTree::max(tree.getRootNode());
	if (minNode && (minNode->value == min)) {
		tree.printAndTag(min);
		std::cout << __FUNCTION__ << " MIN TEST PASSED " << std::endl;
	}
	else {
		std::cerr << __FUNCTION__ << " MIN TEST FAILED " << (minNode ? std::to_string(minNode->value) : " null ") << " ~ " << min << std::endl;
	}

	std::cout << std::endl << std::endl << std::endl << __FUNCTION__ << " START MAX TEST : " << std::endl;
	if (maxNode && (maxNode->value == max)) {
		tree.printAndTag(max);
		std::cout << __FUNCTION__ << " MAX TEST PASSED " << std::endl;
	}
	else {
		std::cerr << __FUNCTION__ << " MAX TEST FAILED " << std::endl;
	}
}

void test_search() {
	BinaryTree tree;
	int values[] = { 50, 30, 22, 49, 68, 54, 10, 3, 49, 6 };
	int len = sizeof(values) / sizeof(int);
	for (size_t i = 0; i < len; i++)
	{
		tree.insert(values[i]);
	}
	std::cerr << __FUNCTION__ << " START TEST : find " << values[2] << std::endl;
	tree.printAndTag(values[2]);

	for (size_t i = 0; i < len; i++)
	{
		auto node = tree.search(values[i]);
		if (node == nullptr) {
			std::cerr << __FUNCTION__ << " TEST FAILED " << std::endl;
			return;
		}
	}


	int not_included_values[] = { 0, -1, 21, 31, 8, 4, 1, };
	len = sizeof(not_included_values) / sizeof(int);
	for (size_t i = 0; i < len; i++)
	{
		auto node = tree.search(not_included_values[i]);
		if (node != nullptr) {
			std::cerr << __FUNCTION__ << " TEST FAILED " << std::endl;
			return;
		}
	}

	std::cout << __FUNCTION__ << " TEST PASSED!" << std::endl;
}


void test_is_binary_tree() {
	BinaryTree tree;
	int values[] = { 50, 30, 22, 49, 68, 54, 10, 3, 49, 6 };
	int len = sizeof(values) / sizeof(int);
	for (size_t i = 0; i < len; i++)
	{
		tree.insert(values[i]);
	}

	auto root = tree.getRootNode();
	bool isValid = BinaryTree::recursiveCheck(root);
	std::cerr << __FUNCTION__ << " START TEST " << std::endl;
	tree.print();

	if (!isValid) {
		std::cerr << __FUNCTION__ << ": test on valid tree. TEST FAILED " << std::endl;
	}
	else {
		std::cout << __FUNCTION__ << ": test on valid tree. TEST PASSED " << std::endl;
	}

	{
		// Invalid tree check
		BinaryTree invalidTree;
		//auto invalidTree = 
		generateInvalidBinaryTree(invalidTree);
		bool isValid = BinaryTree::recursiveCheck(invalidTree.getRootNode());
		std::cerr << __FUNCTION__ << " START TEST " << std::endl;
		invalidTree.print();
		if (!isValid) {
			std::cout << __FUNCTION__ << ": test on invalid tree. TEST PASSED " << std::endl;
		}
		else {
			std::cerr << __FUNCTION__ << ": test on invalid tree. TEST FAILED " << std::endl;
		}
	}

}

void test_remove() {
	BinaryTree tree;
	int values[] = { 50, 30, 22, 49, 68, 54, 10, 3, 49, 6 };
	int len = sizeof(values) / sizeof(int);
	for (size_t i = 0; i < len; i++)
	{
		tree.insert(values[i]);
	}
	int removedValue = 22;
	std::cerr << __FUNCTION__ << " START TEST : Remove value " << removedValue << "  : balancness= " << std::to_string(tree.balancness()) << std::endl;

	tree.printAndTag(removedValue);
	auto c_node = tree.search(removedValue);
	Node* node = const_cast<Node*>(c_node);
	tree.remove(node);
	tree.print();
	std::cerr << __FUNCTION__ << " TEST END : Removed value " << removedValue << "  : balancness= " << std::to_string(tree.balancness()) << std::endl;

	std::cout << __FUNCTION__ << ": TEST END " << std::endl;

}

void test_flip_loop() {
	BinaryTree tree;
	int values[] = { 100, 50, 150, 25, 125, 175, 75, 9, 63, 80, 35 };
	int len = sizeof(values) / sizeof(int);
	for (size_t i = 0; i < len; i++)
	{
		tree.insert(values[i]);
	}

	std::cout << __FUNCTION__ << ": TEST START : Normal Tree" << std::endl;

	tree.print();
	std::cout << __FUNCTION__ << ": Flipped Tree" << std::endl;

	std::queue<Node*> queue;

	queue.push(const_cast<Node*> (tree.getRootNode()));

	while (!queue.empty()) {
		auto n = queue.front();
		queue.pop();
		if (n->leftNode) { queue.push(n->leftNode); }
		if (n->rightNode) { queue.push(n->rightNode); }

		auto temp = n->rightNode;
		n->rightNode = n->leftNode;
		n->leftNode = temp;
	}

	tree.print();
	std::cout << __FUNCTION__ << ": TEST END " << std::endl;
}

void test_flip() {
	BinaryTree tree;
	int values[] = { 100, 50, 150, 25, 125, 175, 75, 9, 63, 80, 35 };
	int len = sizeof(values) / sizeof(int);
	for (size_t i = 0; i < len; i++)
	{
		tree.insert(values[i]);
	}

	std::cout << __FUNCTION__ << ": TEST START : Normal Tree  : balancness= " << std::to_string(tree.balancness()) << std::endl;

	tree.print();
	std::cout << __FUNCTION__ << ": Flipped Tree : balancness= " << std::to_string(tree.balancness()) << std::endl;

	tree.flipRecursive();
	tree.print();
	std::cout << __FUNCTION__ << ": TEST END " << std::endl;
}


void test_preOrderTraverse() {
	BinaryTree tree;
	tree.insert(5);
	tree.insert(3);
	tree.insert(7);
	tree.insert(2);
	tree.insert(4);
	tree.insert(6);
	tree.insert(8);

	std::cout << __FUNCTION__ << ": TEST START : Normal Tree" << std::endl;

	tree.print();
	BinaryTree::preOrderTraverse(tree.getRootNode());


}


void test_preOrderTraverse_TreeIterator() {
	BinaryTree tree;
	tree.insert(5);
	tree.insert(3);
	tree.insert(7);
	tree.insert(2);
	tree.insert(4);
	tree.insert(6);
	tree.insert(8);

	std::cout << __FUNCTION__ << ": TEST START : Normal Tree  : balancness= " << std::to_string(tree.balancness()) << std::endl;

	tree.print();


	int count = 0;

	std::cout << __FUNCTION__ << ": Iterator ++ " << std::endl;
	for (BinaryTreePreOrderConstIterator<Node> it = tree.begin(); it != tree.end(); it++)
	{
		std::cout << ": IT " << it->value << std::endl;
	}
	std::cout << __FUNCTION__ << ": Iterator -- " << std::endl;
	for (BinaryTreePreOrderConstIterator<Node> it = tree.last(); ; it--)
	{
		std::cout << ": IT " << it->value << std::endl;
		if (it == tree.begin()) {
			break;
		}
	}


}

int main()
{
	test_search();
	test_is_binary_tree();
	test_MinAndMax();
	test_remove();
	test_flip();
	test_flip_loop();
	test_preOrderTraverse();
	test_preOrderTraverse_TreeIterator();
	return 0;
}
