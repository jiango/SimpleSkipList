// SkipList.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <iostream>
#include <time.h>

struct Node {
	explicit Node(int n) : key(n) {}

	int key;

	Node* next(int n) {
		return next_[n];
	}

	void setNext(int n, Node* x) {
		next_[n] = x;
	}
	

private:
	Node* next_[1];
};

class SkipList
{
public:
	SkipList() : head_(newNode(0, kMaxHeight)), maxHeight_(1), rand_(0xcccccccc) {
		for (int i = 0; i < kMaxHeight; i++) {
			head_->setNext(i, nullptr);
		}
	}

	void add(int key) {
		Node* prev[kMaxHeight];
		Node* x = findGreaterOrEqual(key, prev);

		int height = randomHeight();
		if (height > maxHeight_) {
			for (int i = maxHeight_; i < height; i++) {
				prev[i] = head_;
			}

			maxHeight_ = height;
		}

		x = newNode(key, height);
		for (int i = 0; i < height; i++) {
			x->setNext(i, prev[i]->next(i));
			prev[i]->setNext(i, x);
		}
	}

	bool search(int key) {
		Node* n = findGreaterOrEqual(key, 0);
		if (n != nullptr && n->key == key) {
			return true;
		}
		return false;
	}

	void del(int key) {
		Node* prev[kMaxHeight];
		Node* x = findGreaterOrEqual(key, prev);
		if (x != nullptr && x->key == key) {
			for (int i = 0; i < maxHeight_; i++) {
				prev[i]->setNext(i, x->next(i));
			}
		}
	}

private:
	Node* findGreaterOrEqual(int key, Node** prev) {
		Node* x = head_;
		int level = maxHeight_ - 1;

		while (true) {
			Node* next = x->next(level);

			if (keyIsAfterNode(key, next)) {
				x = next;
			}
			else {
				if (prev != nullptr) prev[level] = x;
				if (level == 0) {
					return next;
				}
				else {
					level--;
				}
			}
		}
	}

	bool keyIsAfterNode(int key, Node* n) {
		return (n != nullptr) && (n->key < key);
	}

	Node* newNode(int key, int height) {
		char* const node_mem = (char*)malloc(sizeof(Node) + sizeof(Node*) * (height - 1));
		return new (node_mem) Node(key);
	}

	int randomHeight() {
		const int kBranching = 4;

		int height = 1;

		while (height < kMaxHeight && (rand_.Next() % kBranching == 0)) {
			height++;
		}

		return height;
	}

private:
	enum { kMaxHeight = 12 };
	Node* const head_;
	int maxHeight_;
};

// TODO: 在此处引用程序需要的其他标头。
