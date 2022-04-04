#pragma once
namespace voctree {
	struct Word {
		char name[10];
		char translation[10];
		int counter=0;
		Word();
		Word(char* name,char* translation,int counter);
	};
	struct BinaryTree {
	private:
		struct Node {
			Node* left=nullptr;
			Node* right=nullptr;
			Word* data;
			Node(Word* data);
			~Node();
		};
		Node* head = nullptr;
	public:
		void add_word_by_alph(Word* w,Node* temp);
		void create_new_voc(BinaryTree* sech);
		Node* look_for_max(BinaryTree* z, Node* maxn,char* nametemp);
		void print_out_second(BinaryTree* root);
		void inorder(Node* z);
		~BinaryTree();
		void DestroyRec(Node* t);
	};
}
void startprog();