#include <iostream>
#include <iomanip>
#include <queue>
#include <stack>
#include<numeric>
#include<tuple>
#include<string>
#include <random>

#include "BinaryTreeIterator.h"
#include "Node.h"

struct BinaryTree {
	using iterator = BinaryTreePreOrderConstIterator<Node>;

public:
	BinaryTree() {

	}
	~BinaryTree() {
		delete m_root;
	}

	
	iterator begin() {
		return iterator(m_root);
	}
	
	iterator  end() {
		return iterator::nullIterator();
	}

	iterator  last() {
		return iterator(m_root).last();
	}

	const Node* getRootNode() {
		return m_root;
	}

	void insert(int val) {

		if (m_root) { m_root->insert(val, &m_maxDdepth, 1); }
		else {
			m_root = new Node(val);
			m_maxDdepth = 1;
		}
	}

	const Node* search(int value) const {
		return m_root->search(value);
	}

	void flipRecursive() {
		if (!m_root) { return; }
		m_root->flipRecursive();
	}

	void remove(Node* node) {
		if (!node) { return; }
		
		Node* substituteNode = nullptr;
		if (node->leftNode) {
			substituteNode = const_cast<Node*> (BinaryTree::max(node->leftNode));
		}
		else if (node->rightNode) {
			substituteNode = const_cast<Node*> (BinaryTree::min(node->rightNode));
		}
		if (!substituteNode) { return; }

		node->value = substituteNode->value;

		if (!substituteNode->parent) { return; }
		
		if (substituteNode->parent->leftNode == substituteNode) {
			substituteNode->parent->leftNode = nullptr;
		}
		else if (substituteNode->parent->rightNode == substituteNode) {
			substituteNode->parent->rightNode = nullptr;
		}
		
		
		node->leftNode	= substituteNode->leftNode;
		node->rightNode = substituteNode->rightNode;
		if (node->leftNode) {
			node->leftNode->parent = node;
		}
		if (node->rightNode)
		{
			node->rightNode->parent = node;
		}
		
		substituteNode->leftNode = nullptr;
		substituteNode->rightNode= nullptr;

		delete substituteNode;

	}

	static const Node* min(const Node* root) {
		if (!root) { return nullptr; }

		const Node* node = root;
		while (node->leftNode) {
			node = node->leftNode;
		}
		return node;
	}

	static const Node* max(const Node* root) {
		if (!root) { return nullptr; }

		const Node* node = root;
		while (node->rightNode) {
			node = node->rightNode;
		}
		return node;
	}

	float balancness() {
		if (!m_root) {
			std::cout << " Empty Tree \n";
			return 0;
		}
		
		//                       NODE*  depth
		typedef std::tuple<const Node*, int> type;
		std::queue<type> queue;

		type t = std::make_tuple(this->m_root, 0);
		queue.push(t);
		size_t minDepth = std::numeric_limits<size_t>::max();
		size_t maxDepth = 0;

		while (!queue.empty()) {
			auto t = queue.front();
			auto n = std::get<0>(t);
			auto depth = std::get<1>(t);
			queue.pop();
			if (n->leftNode) {
				queue.push(std::make_tuple(n->leftNode, depth + 1));
			}
			if (n->rightNode) {
				queue.push(std::make_tuple(n->rightNode, depth + 1));
			}

			if (!n->leftNode && !n->rightNode) {
				// leaf
				if (depth < minDepth) {
					minDepth = depth;
				}
				if (depth > maxDepth) {
					maxDepth = depth;
				}
			}
		}
		return (float) minDepth / (float) maxDepth;
	}


	void print() {
		if (!m_root) {
			std::cout << " Empty Tree \n";
			return;
		}
		int rootPadding = (1 << m_maxDdepth); // depth power of two

		//                       NODE*     padding  depth
		typedef std::tuple<const Node*, int, int> type;
		std::queue<type> queue;

		type t = std::make_tuple(this->m_root, rootPadding, 0);
		queue.push(t);
		int charsCount = 1;
		int prevDepth = 0;
		int lineOffset = 0;
		std::vector<int> order;
		std::vector<int> paddings;
		while (!queue.empty()) {
			auto t = queue.front();
			auto n = std::get<0>(t);
			auto padding = std::get<1>(t);
			auto depth = std::get<2>(t);
			int depth_padding = (1 << (m_maxDdepth - depth - 1)); // depth power of two

			queue.pop();

			auto delta_padding = depth_padding;

			if (n->leftNode) {
				queue.push(std::make_tuple(n->leftNode, padding - delta_padding, depth + 1));
			}
			if (n->rightNode) {
				queue.push(std::make_tuple(n->rightNode, padding + delta_padding, depth + 1));
			}
			if (prevDepth != depth) {
				// new line
				prevDepth = depth;
				std::cout << std::endl << std::endl;
				lineOffset = 0;
			}
			int digitsCount = std::to_string(n->value).length();
			order.push_back(n->value);
			paddings.push_back(padding);
			auto lineWidth = padding * charsCount + digitsCount - lineOffset;
			std::cout << std::setw(lineWidth) << std::setfill(' ') << n->value;
			lineOffset += lineWidth;
		}

		/* std::cout << std::endl;
		 for (size_t i = 0; i < order.size(); i++)
		 {
			 std::cout << order[i] << " ";
		 }
		 std::cout << std::endl;
		 for (size_t i = 0; i < paddings.size(); i++)
		 {
			 std::cout << paddings[i] << " ";
		 }*/
		std::cout << std::endl;
	}

	void printAndTag(int taggedValue) {
		if (!m_root) {
			std::cout << " Empty Tree \n";
			return;
		}
		int rootPadding = (1 << m_maxDdepth); // depth power of two

		//                       NODE*     padding  depth
		typedef std::tuple<const Node*, int, int> type;
		std::queue<type> queue;

		type t = std::make_tuple(this->m_root, rootPadding, 0);
		queue.push(t);
		int charsCount = 1;
		int prevDepth = 0;
		int lineOffset = 0;
		std::vector<int> order;
		std::vector<int> paddings;
		while (!queue.empty()) {
			auto t = queue.front();
			auto n = std::get<0>(t);
			auto padding = std::get<1>(t);
			auto depth = std::get<2>(t);
			int depth_padding = (1 << (m_maxDdepth - depth - 1)); // depth power of two

			queue.pop();

			auto delta_padding = depth_padding;

			if (n->leftNode) {
				queue.push(std::make_tuple(n->leftNode, padding - delta_padding, depth + 1));
			}
			if (n->rightNode) {
				queue.push(std::make_tuple(n->rightNode, padding + delta_padding, depth + 1));
			}
			if (prevDepth != depth) {
				// new line
				prevDepth = depth;
				std::cout << std::endl << std::endl;
				lineOffset = 0;
			}
			int digitsCount = std::to_string(n->value).length();
			order.push_back(n->value);
			paddings.push_back(padding);
			auto lineWidth = padding * charsCount + digitsCount - lineOffset;
			if (n->value != taggedValue)
			{
				std::cout << std::setw(lineWidth) << std::setfill(' ') << n->value;
			}
			else {
				std::cout << std::setw(lineWidth) << std::setfill(' ') << '{' << n->value << '}';
			}
			lineOffset += lineWidth;
		}

		std::cout << std::endl;
	}


	static bool recursiveCheck(const Node* node,
		int leftLimit = std::numeric_limits<int>::min(),
		int rightLimit = std::numeric_limits<int>::max())
	{
		if (!(node->value > leftLimit && node->value < rightLimit)) { return false; }

		bool isRightValid = true;
		if (node->rightNode) {
			isRightValid = recursiveCheck(node->rightNode, node->value, rightLimit);
		}

		bool isLeftValid = true;
		if (node->leftNode) {
			isLeftValid = recursiveCheck(node->leftNode, leftLimit, node->value);
		}

		return isRightValid && isLeftValid;

		bool ok = true;
		if (node->leftNode) {
			ok = recursiveCheck(node->leftNode);
		}
		if (node->rightNode) {
			ok = ok && recursiveCheck(node->rightNode);
		}
		return ok;
	}


	static void preOrderTraverse(const Node* root) {
		std::stack<const Node*> stack;
		std::vector<const Node*> preOrderTraversalArray;
		const Node* node = root;
		stack.push(node);
		while (!stack.empty()) {

			auto n = stack.top();
			stack.pop();
			preOrderTraversalArray.push_back(n);
			if (n->rightNode) { stack.push(n->rightNode); }
			if (n->leftNode) { stack.push(n->leftNode); }
		}

		std::cout << std::endl << "Pre Order Traversal Array " << std::endl;
		for (size_t i = 0; i < preOrderTraversalArray.size(); i++)
		{
			std::cout << preOrderTraversalArray[i]->value << " ";
		}
		std::cout << std::endl;
	}


private:
	Node* m_root = nullptr;
	int m_maxDdepth = 0;
};
