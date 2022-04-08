#include "Header.h"
#include<iostream>
#include <queue>

voctree::BinaryTree::Node::Node(Word* data)
{
	this->data = data;
}

voctree::BinaryTree::Node::~Node()
{
	delete data,left,right;
}

voctree::Word::Word()
{
	this->counter = 0;
	strcpy_s(this->name," ");
	strcpy_s(this->translation, " ");

}

voctree::Word::Word(char* name, char* translation, int counter)
{
	this->counter = counter;
	strcpy_s(this->name, name);
	strcpy_s(this->translation, translation);
}

void voctree::BinaryTree::add_word_by_alph(Word* w,Node* temp)
{
	Node* cur = new Node(w);
	if (temp == NULL) {
		temp = head;
	}
	if (head==nullptr) {
		head = cur;
		return;
	}
	for (int i = 0; i < 10; i++) {
		if (int(temp->data->name[i]) == int(w->name[i]))
			continue;
		else if (int(temp->data->name[i]) > int(w->name[i])) {
			if (temp->left == nullptr) {
				temp->left = cur;
				return;
			}
			add_word_by_alph(w,temp->left);
			return;
		}
		else if (int(temp->data->name[i]) < int(w->name[i])) {
			if (temp->right == nullptr) {
				temp->right = cur;
				return;
			}
			add_word_by_alph(w, temp->right);
			return;
		}
	}
	std::cout << "Such word already exist \n";
	return;
}

void voctree::BinaryTree::create_new_voc(BinaryTree* sech)
{
	sech->print_out_second(sech);
	std::cout << std::endl;
	sech->inorder(sech->head);

	char nametemp[10]="sdsadsa";
	std::queue<Node*> q;
	int headtimes=0;
	//std::cout << "  Test  " ;
	
	while (true) {
		Word* dattemp = new Word();
		dattemp->counter -= 1;
		
		Node* nodeuseless = new Node(dattemp);
		nodeuseless= look_for_max(sech,nodeuseless,nametemp);
		strcpy_s(nametemp, nodeuseless->data->name);
		if (nodeuseless->data->counter==-1)
			break;

		Word* temprnewword =new Word();
		strcpy_s(temprnewword->name, nodeuseless->data->name);
		strcpy_s(temprnewword->translation, nodeuseless->data->translation);
		temprnewword->counter = nodeuseless->data->counter;
		Node* node = new Node(temprnewword);
		
		if (headtimes == 0) {
			head = node;
			q.push(head);
			headtimes = 1;
			continue;
		}
		if (q.front()->left == nullptr) {
			q.front()->left = node;
		}
		else if (q.front()->right == nullptr) {
			q.front()->right = node;
			q.pop();
		}
		
		q.push(node);
	}

	return;
}

voctree::BinaryTree::Node* voctree::BinaryTree::look_for_max(BinaryTree* sech,Node* maxn,char* nametemp)
{
	Node* root = sech->head;
	if (root == nullptr)
		return NULL;

	int localmax=-1;

	std::queue<Node*> q2;
	q2.push(root);

	while (q2.empty() == false) {

		Node* node = q2.front();
		if (node->data->counter > localmax) {
			if (!strcmp(nametemp, node->data->name)) {
				node->data->counter = -1;
			}
			else {
				maxn->data = node->data;
				localmax = maxn->data->counter;
			}
		}
		q2.pop();

		if (node->left != nullptr)
			q2.push(node->left);


		if (node->right != nullptr)
			q2.push(node->right);
	}
	return maxn;
}
void voctree::BinaryTree::print_out_second(BinaryTree* roots)
{
	Node* root = roots->head;
	if (root == NULL)
		return;


	std::queue<Node*> q1;
	q1.push(root);

	while (q1.empty() == false) {

		Node* node = q1.front();
		std::cout << node->data->name << " ";
		std::cout << node->data->translation << " ";
		std::cout << node->data->counter << " ";
		std::cout << " \n";
		q1.pop();


		if (node->left != NULL)
			q1.push(node->left);


		if (node->right != NULL)
			q1.push(node->right);
	}
	return;
}

void voctree::BinaryTree::inorder(Node* z)
{
	if (z == nullptr) {
		return;
	}
	inorder(z->left);
	std::cout << z->data->name << " " << z->data->counter << "\n";
	inorder(z->right);
	

}
voctree::BinaryTree::~BinaryTree()
{
	DestroyRec(head);
	
}

void voctree::BinaryTree::DestroyRec(Node* node)
{
	if (node) {
		DestroyRec(node->left);
		DestroyRec(node->right);
		delete node;
	}
}

void startprog() {

	voctree::BinaryTree binarytree = voctree::BinaryTree();
	voctree::BinaryTree binarytree2 = voctree::BinaryTree();

	int ink;
	char name[10];
	char translation[10];
	int counter;

	std::cout << "Enter 1 to add new node by alph \n";
	std::cout << "Enter 2 to create new voc by counter \n";
	std::cout << "Enter 3 to print out \n";

	while (true) {
		std::cin >> ink;
		if (ink == 1) {
			std::cout << "Enter name:  ";
			std::cin >> name;
			std::cout << "\n";
			std::cout << "Enter translation:  ";
			std::cin >> translation;
			std::cout << "\n";
			std::cout << "Enter counter:  ";
			std::cin >> counter;
			voctree::Word* word = new voctree::Word(name,translation,counter);
			binarytree.add_word_by_alph(word,NULL);
			std::cout << "What`s next ? \n";
			continue;
		}
		else if (ink == 2) {
			binarytree2.create_new_voc(&binarytree);
			std::cout << "What`s next ? \n";
			continue;
		}
		else if (ink == 3) {
			binarytree2.print_out_second(&binarytree2);
			std::cout << "\n";
			std::cout << "What`s next ? \n";
			continue;
		}
	}
}