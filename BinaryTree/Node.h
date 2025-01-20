#pragma once

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

