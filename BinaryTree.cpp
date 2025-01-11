#include <iostream>
#include <iomanip>
#include <queue>
#include <stack>
#include<numeric>
#include<tuple>
#include<string>
#include <random>

struct Node {
	int value;
	Node* parent = nullptr;
	Node* leftNode = nullptr;
	Node* rightNode = nullptr;

	Node(int v)
		: value{ v }
	{}

	~Node() {
		if (leftNode) { delete leftNode; }
		if (rightNode) { delete rightNode; }
		leftNode = nullptr;
		rightNode = nullptr;
	}

	Node* search(int val) {
		if (val == this->value) {
			return this;
		}
		else if (val < this->value) {
			if (this->leftNode) { return this->leftNode->search(val); }
			else { return nullptr; }
		}
		else {
			if (this->rightNode) { return this->rightNode->search(val); }
			else { return nullptr; }
		}
	}

	Node* insert(int value, int* out_depth = nullptr, int depth = 0) {

		if (value == this->value) { return this; }
		if (value < this->value) {
			if (this->leftNode) { return this->leftNode->insert(value, out_depth, depth + 1); }
			auto node = new Node(value);
			depth = depth + 1;
			if (out_depth) { *out_depth = std::max(*out_depth, depth); }
			this->leftNode = node;
			this->leftNode->parent = this;

			return node;
		}
		if (value > this->value) {
			if (this->rightNode) { return this->rightNode->insert(value, out_depth, depth + 1); }
			auto node = new Node(value);
			this->rightNode = node;
			this->rightNode->parent = this;
			depth = depth + 1;
			if (out_depth) { *out_depth = std::max(*out_depth, depth); }
			return node;
		}
	}


	void flipRecursive() {
		auto l = this->leftNode;
		this->leftNode = this->rightNode;
		this->rightNode = l;

		if (this->leftNode) {
			this->leftNode->flipRecursive();
		}

		if (this->rightNode) {
			this->rightNode->flipRecursive();
		}
	}
};

struct BinaryTree {

public:
	BinaryTree() {

	}
	~BinaryTree() {
		delete m_root;
	}

	const Node* getRootNode() {
		return m_root;
	}

	void insert(int val) {

		if (m_root) { m_root->insert(val, &m_depth, 1); }
		else {
			m_root = new Node(val);
			m_depth = 1;
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

	void print() {
		if (!m_root) {
			std::cout << " Empty Tree \n";
			return;
		}
		int rootPadding = (1 << m_depth); // depth power of two

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
			int depth_padding = (1 << (m_depth - depth - 1)); // depth power of two

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
		int rootPadding = (1 << m_depth); // depth power of two

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
			int depth_padding = (1 << (m_depth - depth - 1)); // depth power of two

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


private:
	Node* m_root = nullptr;
	int m_depth = 0;
};




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
	std::cerr << __FUNCTION__ << " START TEST : Remove value " << removedValue << std::endl;

	tree.printAndTag(removedValue);
	auto c_node = tree.search(removedValue);
	Node* node = const_cast<Node*>(c_node);
	tree.remove(node);
	tree.print();

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

	std::cout << __FUNCTION__ << ": TEST START : Normal Tree" << std::endl;

	tree.print();
	std::cout << __FUNCTION__ << ": Flipped Tree" << std::endl;

	tree.flipRecursive();
	tree.print();
	std::cout << __FUNCTION__ << ": TEST END " << std::endl;
}

int main()
{
	//test_search();
	//test_is_binary_tree();
	//test_MinAndMax();
	//test_remove();
	test_flip();
	test_flip_loop();
}
