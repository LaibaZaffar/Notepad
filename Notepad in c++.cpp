#include<iostream>
#include<fstream>
#include<string>
#include"conio.h"
using namespace std;

ofstream input_obj1;
ifstream input_obj2;
ifstream my_reading;
ofstream my_writing;
ofstream tree_in_file;


struct node2
{
	int data;
	node2* next = NULL;
};
class stack
{
	node2* top;
public:
	stack()
	{
		top = NULL;
	}
	void push(int elem)
	{
		node2* newNode = new node2;
		newNode->data = elem;
		newNode->next = top;
		top = newNode;
	}
	int pop()
	{
		int n;
		if (empty())
		{
			cout << "\nUnderflow error" << endl;
		}
		node2* temp = top;
		n = top->data;
		top = top->next;
		return n;
		delete temp;
	}
	bool empty()
	{
		return (top == NULL);
	}
};



struct node
{
	bool isword;
	node* arr[26];
};

class trie_tree
{
public:
	node* root;
	string sugg_arr[10];
	int show_no_sugg;
	int index_of_sugg_string;

	trie_tree()                            //CONSTRUCTOR
	{
		root = NULL;
		index_of_sugg_string = 0;
		show_no_sugg = 0;
	}

	node* createnode()                      //CREATE NODE
	{
		node* temp_node = new node;
		temp_node->isword = false;
		for (int i = 0; i < 26; i++)
		{
			temp_node->arr[i] = NULL;
		}
		return temp_node;
	}

	bool check_string(string temp_str)         //CHECK STRING
	{
		bool flag = false;
		for (int i = 0; i < temp_str.length(); i++)
		{
			if ((temp_str[i] >= 'a') && (temp_str[i] <= 'z'))
			{
				flag = true;
			}
			else
			{
				flag = false;
				return flag;
			}
		}
		return flag;
	}

	void insert(node* root, string data)                 //INSERT
	{
		if (check_string(data))
		{
			node* temp_node = root;
			for (int i = 0; i < data.length(); i++)
			{
				int index = data[i] - 97;
				if (temp_node->arr[index] == NULL)
				{
					temp_node->arr[index] = createnode();
				}
				temp_node = temp_node->arr[index];
			}
			temp_node->isword = true;
		}
		else
		{
			return;
		}
	}

	bool search(node* root, string data)                       //SEARCH
	{
		struct node* temp_node = root;

		for (int i = 0; i < data.length(); i++)
		{
			int index = data[i] - 'a';
			if (!temp_node->arr[index])
			{
				return false;
			}
			temp_node = temp_node->arr[index];
		}

		return temp_node->isword;
	}

	bool isLastNode(node* root)                         //IS LAST NODE
	{
		for (int i = 0; i < 26; i++)
		{
			if (root->arr[i])
			{
				return 0;
			}
		}
		return 1;
	}

	void print_sugg_rec(node* root, string temp_str)                      //PRINT SUGGESTIONS
	{
		//FIND A STRING IN TRIE TREE WITH GIVEN PREFIX
		if (root->isword)
		{
			if (index_of_sugg_string < 10)
			{
				show_no_sugg++;
				cout << "\n" << show_no_sugg << ": " << temp_str;
				sugg_arr[index_of_sugg_string] = temp_str;
				index_of_sugg_string++;
			}
		}

		for (int i = 0; i < 26; i++)
		{
			if (root->arr[i])
			{
				char next_p_str = 'a' + i;           //NEXT PART OF STRING
				print_sugg_rec(root->arr[i], temp_str + next_p_str);
			}
		}
	}

	int func_suggestion(node* root, string temp_str)                           //FUNCTION OF SUGGESTION
	{
		node* temp_node = root;
		for (int i = 0; i < temp_str.length(); i++)
		{
			int index_of_ch = temp_str[i] - 'a';

			//NO STRING IN THE TRIE TREE HAS THAT PREFIX
			if (!temp_node->arr[index_of_ch])
			{
				return 0;
			}

			temp_node = temp_node->arr[index_of_ch];
		}

		//IF PREFIX IS PRESENT AS WORD, BUT THERE IS NO SUBTREE BELOW THE LAST MATCHING NODE
		if (isLastNode(temp_node))
		{
			cout << temp_str << endl;
			return -1;
		}

		print_sugg_rec(temp_node, temp_str);              //PRINTING HERE
		return 1;
	}

	string cmp_string(int count_of_sugg_arr)              //CMP_STRING
	{
		int i = 0;
		string str, temp_str, cont_cate;
		while (input_obj2 >> str);
		temp_str = sugg_arr[count_of_sugg_arr];
		for (i = 0; i < str.length(); i++)
		{
			if (str[i] != temp_str[i])
			{
				break;
			}
		}
		for (int j = i; j < temp_str.length(); j++)
		{
			cont_cate += temp_str[j];
		}
		return cont_cate;
	}
};


struct node1
{
	char data;
	int frequency;
	node1* left;
	node1* right;
	node1* next;

	node1()                   //DEFAULT CONSTRUCTOR
	{
		data = ' ';
		frequency = 0;
		left = NULL;
		right = NULL;
		next = NULL;
	}
	node1(char d, int f)      //PARAMETERIZED CONSTRUCTOR
	{
		data = d;
		frequency = f;
		left = NULL;
		right = NULL;
		next = NULL;
	}
	~node1()                  //DESTRUCTOR
	{
		delete left;
		delete right;
		next = NULL;
		left = NULL;
		right = NULL;
	}
};

class hauffman
{
private:
	node1* front;
	node1* rear;
	int count;
	stack s;
public:
	hauffman()               //DEFAUKT CONSTRUCTOR
	{
		front = NULL;
		rear = NULL;
		count = 0;           //FOR TOTAL NUMBER OF ELEMENTS
	}

	bool isEmpty()
	{
		if (front == NULL && rear == NULL)
		{
			return true;
		}
		return false;
	}

	bool search(char c)  //function to search an insert into the queue based on the frequencies
	{
		bool flag = false;
		node1* current = front;
		while (current != NULL)
		{
			if (current->data == c)
			{
				flag = true;
				current->frequency++;
			}
			current = current->next;
		}
		if (flag == false)
		{
			insert(1, c);
		}
		return false;
	}
	void instruction()
	{
		cout << "\t\t\t\t\t\t==>> INSTRUCTIONS <<== " << endl;
		cout << "\t\t\t\t===================================================" << endl;
		cout << "\t\t\t\t   ' / ' FOR MOVING ON TO NEXT SUGGESTION" << endl;
		cout << "\t\t\t\t   ' ; ' FOR SELECTING" << endl;
		cout << "\t\t\t\t   ' = ' FOR STOP TAKING INPUT AND ALSO FOR ENCODING" << endl;
		cout << "\t\t\t\t===================================================" << endl << endl;

	}

	void insert(int freq, char c, node1* l = NULL, node1* r = NULL)
	{
		node1* newNode = new node1;
		if (isEmpty())  //if it is 1st node
		{
			newNode->frequency = freq;
			newNode->data = c;
			newNode->left = l;
			newNode->right = r;
			rear = newNode;
			front = newNode;

			count++;
		}
		else
		{
			newNode->frequency = freq;
			newNode->data = c;
			newNode->left = l;
			newNode->right = r;
			rear->next = newNode;
			rear = newNode;

			count++;
		}
	}

	void Encoding()
	{
		char data[300];
		ifstream my_reading;

		////////////////////reading from file////////////////////
		my_reading.open("Input_File.txt", ios::app);
		if (!my_reading)
		{
			cout << "ERROR IN OPENING THE TEXT FILE for reading\n ";
			return;
		}
		cout << "\n\n==>> FILE IS ENCODED!!" << endl << endl;
		my_reading >> noskipws;  //a command to turn off the skip whitespace flag *_*
		for (int i = 0; !(my_reading.eof()); i++)
		{

			my_reading >> data[i];
			if (!my_reading.eof())
			{
				search(data[i]);
			}
		}
		my_reading.close();
		cout << endl << endl;
		huffman_tree();
	}



	void remove()
	{
		if (isEmpty())
		{
			cout << "\nQUEUE IS EMPTY!!" << endl;
			return;
		}
		if (front == rear)  //one node remaining
		{
			count--;
			delete front;
			delete rear;
			front = NULL;
			rear = NULL;
			return;
		}
		else
		{
			node1* temp = front;    				// Store previous front and move front one node next
			front = front->next;
			count--;
		}
	}
	void write_tree_in_file(node1* front)
	{
		if (front != NULL)
		{

			write_tree_in_file(front->left);
			if (front->data != 61)
			{
				tree_in_file << "DATA " << front->data << "  " << "FREQUENCY " << front->frequency << endl;
			}
			write_tree_in_file(front->right);
		}

	}

	void sort()              // Using a bubble sort variation in increasing order
	{
		node1* current1, * current2;
		current1 = front;
		current2 = front->next;
		for (int i = 0; i < count; i++)
		{
			while (!(current1 == NULL || current2 == NULL))
			{
				if (current1->frequency > current2->frequency)   //swapping
				{
					swap(current1->frequency, current2->frequency);
					swap(current1->data, current2->data);
				}
				current1 = current2;
				current2 = current1->next;
			}
			current1 = front;
			current2 = front->next;
		}

	}

	//function to make tree from the given queue
	void huffman_tree()                                                  //HUFFMAN TREE
	{
		sort();  //first sort the queue in ascendig order

		int freq = 0;
		node1* n1 = front;  //1st node
		node1* n2 = front->next;	  //2nd node
		while (n1 != NULL && n2 != NULL)
		{
			freq = n1->frequency + n2->frequency;  //add the frequencies of both nodes
			insert(freq, '$', n1, n2);      //new node containing the sum of frequencies of it's childrens
			remove(); //remove 1st node that has been added to tree
			remove();  //remove the second node
			sort();	 //again sort the queue as new node has been added to the queue

			n1 = front;
			n2 = front->next;

		}
		tree_in_file.open("tree.txt");
		if (!tree_in_file)
		{
			cout << "Error in openning tree in file" << endl;
		}
		else
		{
			write_tree_in_file(front);
		}
		tree_in_file.close();
		tree_traversal(front, " ");
	}
	bool search_key(node1* root, char key)  //a function to find the specific character
	{
		if (root != NULL)
		{
			if (root->data == key)
			{
				return 1;
			}
			if (search_key(root->right, key))
			{
				s.push(1);
				return 1;
			}
			else if (search_key(root->left, key))
			{
				s.push(0);
				return 1;
			}
		}
		else
		{
			return 0;
		}
	}


	//NOTE: in hauffman tree, leaf nodes are the actual nodes that are containing the characters of the given string 
	void  tree_traversal(node1* rooot, string str)
	{
		string data;
		ofstream my_writing;
		ifstream my_reading;

		////////////////////writing into file////////////////////
		my_writing.open("Encoded_File.txt");
		if (!my_writing)
		{
			cout << "ERROR IN OPENING THE TEXT FILE for writing\n ";
			return;
		}

		////////////////////reading from file////////////////////
		my_reading.open("Input_File.txt", ios::app);
		if (!my_reading)
		{
			cout << "ERROR IN OPENING THE TEXT FILE for reading\n ";
			return;
		}
		else
		{
			while (!my_reading.eof())
			{
				getline(my_reading, data);  //aik character uthaao text file mein say
				for (int i = 0; i < data.length(); i++)
				{
					if (data[i] != 61)             //for ignorong =
					{
						search_key(front, data[i]);   //go and search in the tree
						while (!s.empty())
						{
							int x = s.pop();
							my_writing << x;
						}
						my_writing << " ";
					}
				}
			}
		}

		my_writing.close();
		my_reading.close();
	}



	//----------------------------------------------------- ==>> DECODING <<== -----------------------------------------------//


	char search_key1(node1* root, string key, int n, int i)
	{
		if (root != NULL)
		{
			if (root->data == key[i] || i >= n)
			{
				return root->data;
			}
			else if (key[i] == '1')
			{
				return search_key1(root->right, key, n, i + 1);
			}
			else if (key[i] == '0')
			{
				return search_key1(root->left, key, n, i + 1);
			}
		}
		else
		{
			return '0';
		}
	}

	void Decoding()
	{
		string data;

		my_writing.open("Decoded_File.txt");
		if (!my_writing)
		{
			cout << "ERROR IN OPENING THE DECODE TEXT FILE for writing\n ";
			return;
		}

		my_reading.open("Encoded_File.txt");
		if (!my_reading)
		{
			cout << "\nERROR IN OPENING THE ENCODED FILE FOR READING\n " << endl;
			return;
		}
		else
		{
			cout << endl << endl;
			while (!my_reading.eof())
			{
				my_reading >> data;
				if (!my_reading.eof())
				{
					char c = search_key1(front, data, data.length(), 0);
					if (c != 36)//for ignoring $
					{
						my_writing << c;
					}
				}
			}
		}
		my_reading.close();
	}

	//----------------------------------------------------- ==>> DECODING <<== -----------------------------------------------//
};


int main()
{
	int count1 = 0;
	bool flag = false;
	char ch = 'o', input_str;
	int check_space = 0, count_of_sugg_arr = 0, count = 0, check_any_sugg = 0, choice_in_notepad = 0;
	string str, cmp_r_str;
	trie_tree obj;
	hauffman h_obj;

	obj.root = obj.createnode();

	ifstream outline_obj;
	outline_obj.open("OutFile.txt");

	if (!outline_obj)
	{
		cout << "OOPS!! OUTFILE IS NOT OPEN!!" << endl;
		return -1;
	}
	else
	{
		while (!outline_obj.eof())
		{
			getline(outline_obj, str);                            //INSERTING DICTIONARY
			obj.insert(obj.root, str);
		}
	}
	outline_obj.close();
	input_obj1.open("Input_File.txt", ios::trunc);
	input_obj1.close();
	int ascii_space = 32;
	h_obj.instruction();
	system("pause");
	system("cls");
	cout << "\t\t\t\t=============================================" << endl;
	cout << "\t\t\t\t\tSTART WRITING ON YOUR NOTEPAD" << endl;
	cout << "\t\t\t\t=============================================" << endl;
	my_reading.open("Decoded_File.txt", ios::app);
	if (!my_reading)
	{
		cout << "\nERROR IN OPENING THE ENCODED FILE FOR READING\n " << endl;
		return 0;
	}
	else
	{
		while (my_reading.get(ch))
		{
			if (ch != 61)
			{
				cout << ch;
			}
		}
	}
	my_reading.close();
	/////////////////////////////////////////////////////////////////////////
	my_reading.open("Decoded_File.txt", ios::app);
	if (!my_reading)
	{
		cout << "\nERROR IN OPENING THE ENCODED FILE FOR READING\n " << endl;
		return 0;
	}
	else
	{
		input_obj1.open("Input_File.txt", ios::app);
		if (!input_obj1)
		{
			cout << "INPUT FILE AFTER TRUNC MODE IS NOT OPEN" << endl;
		}
		else
		{
			while (my_reading.get(ch))
			{
				if (ch != 61)
				{
					input_obj1 << ch;
				}
			}

		}
		input_obj1.close();
		my_reading.close();
	}
	while (ch != 61)
	{
		input_obj1.open("Input_File.txt", ios::app);
		if (!input_obj1)
		{
			cout << "OOPS!! INPUT FILE IS NOT OPEN!!" << endl;
			return -1;
		}
		else
		{
			input_str = _getch();
			input_obj1 << input_str;
			input_obj1.close();
			system("cls");
			input_obj2.open("Input_File.txt", ios::app);
			if (!input_obj2)
			{
				cout << "OOPS!! INPUT FILE IS NOT OPEN!!" << endl;
				return -1;
			}
			else
			{
				while (input_obj2.get(ch))
				{
					if (ch != 61)
					{
						cout << ch;
					}
				}
			}
			ascii_space = input_str;
			input_obj2.close();
			input_obj2.open("Input_File.txt", ios::app);
			if (!input_obj2)
			{
				cout << "OOPS!! INPUT FILE IS NOT OPEN!!" << endl;
				return -1;
			}
			else
			{
				while (input_obj2 >> str);
				if ((input_str != 32) && (ch != 61))
				{
					cout << "\n\n\t\t\t\t\t\t==>> \\ SUGGESTIONS \\ <<==\n\n" << endl;
					obj.func_suggestion(obj.root, str);
					input_obj2.close();
					input_obj2.open("Input_File.txt", ios::app);
					if (!input_obj2)
					{
						cout << "OOPS!! INPUT FILE IS NOT OPEN!!" << endl;
						return -1;
					}
					else
					{
						input_str = _getch();
						if (input_str == 47)                              //  '/' FOR MOVING ON NEXT SUGGESTION
						{
							count1++;
							cout << "\nYOU ARE NOW ON " << count_of_sugg_arr + 1 << " WORD IN SUGGESTION" << endl;
						}
						while (input_str != 59 && count_of_sugg_arr < 9) //  ';' FOR ENDING TAKIING INPUT OR SELECTING
						{
							input_str = _getch();
							if (input_str == 47)                          //  '/' FOR MOVING ON NEXT SUGGESTION
							{
								count1++;
								count_of_sugg_arr++;
								cout << "\nYOU ARE NOW ON " << count_of_sugg_arr + 1 << " WORD IN SUGGESTION" << endl;
							}
						}
						if (count_of_sugg_arr > 9)
						{
							cout << "\nSORRY!! MORE SUGGESTION DONOT EXIST!!" << endl;
							system("pause");
						}
						else if (count1 >= 1)
						{
							if (count_of_sugg_arr >= 0 && count_of_sugg_arr < 10)
							{
								cmp_r_str = obj.cmp_string(count_of_sugg_arr);
								input_obj2.close();
								input_obj1.open("Input_File.txt", ios::app);
								if (!input_obj1)
								{
									cout << "OOPS!! INPUT FILE IS NOT OPEN!!" << endl;
									return -1;
								}
								else
								{
									input_obj1 << cmp_r_str;
								}
							}
						}
					}
					count1 = 0;
					obj.index_of_sugg_string = 0;
					count_of_sugg_arr = 0;
					obj.show_no_sugg = 0;
				}
				input_obj1.close();
				input_obj2.close();
			}
			system("cls");
			input_obj2.open("Input_File.txt", ios::app);
			if (!input_obj2)
			{
				cout << "OOPS!! INPUT FILE IN READIN MODE IS NOT OPEN!!" << endl;
			}
			else
			{
				while (input_obj2.get(ch))
				{
					if (ch != 61)
					{
						cout << ch;
					}
				}
			}
			input_obj2.close();
			continue;
		}
	}
	cout << endl;
	h_obj.Encoding();
	cout << endl << endl;
	h_obj.Decoding();
	system("pause");
	return 0;
}
