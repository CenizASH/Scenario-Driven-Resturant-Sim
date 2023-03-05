#include <iostream>
#include <sstream> //to use stringstream
#include <fstream> //to open the file
#include <string>
using namespace std;
struct ORDER
{
	int Time, foodorderid, expirytime, ingredients, preptime;
	string Meal;
	double price;
};

class Node//Making a node class
{
public:
	ORDER data;
	Node* next;
};
class P_Node//Making a Priority node class
{
public:
	ORDER data;
	double priority;
	P_Node* next;//stores address of next node
};
class Que//class for Queue
{
private:
	Node* Front;//Queue front element
	Node* Rear;//Queue rear element
public:
	Que()
	{
		Front = NULL;
		Rear = NULL;
	}
	bool Is_empty()//Method to check that queue is empty or not
	{
		if (Front == NULL)
		{
			return true;
		}
		else
			return false;
	}
	void Enqueue(ORDER data)//Method to Enqueue the data on the Queue
	{
		Node* newnode = new Node;
		newnode->data.Time = data.Time;
		newnode->data.foodorderid = data.foodorderid;
		newnode->data.expirytime = data.expirytime;
		newnode->data.preptime = data.preptime;
		newnode->data.ingredients = data.ingredients;
		newnode->data.price = data.price;
		newnode->data.Meal = data.Meal;
		if (Rear == NULL || Front == NULL)
		{
			newnode->next = NULL;
			Rear = newnode;
			Front = newnode;
		}
		else
		{
			newnode->next = NULL;
			Rear->next = newnode;
			Rear = newnode;
		}
	}
	void TOP(ORDER& data)//Function to check the data from the Queue
	{
		if (Front != NULL)
		{
			Node* temp = Front;
			data.Time = temp->data.Time;
			data.foodorderid = temp->data.foodorderid;
			data.expirytime = temp->data.expirytime;
			data.preptime = temp->data.preptime;
			data.ingredients = temp->data.ingredients;
			data.price = temp->data.price;
			data.Meal = temp->data.Meal;
		}
		else
		{
			data.expirytime = -1;
		}
	}
	ORDER Dequeue()//Function to Dequeue the data from the Queue
	{
		ORDER data;
		if (Front != NULL)
		{
			Node* temp = Front;
			data.Time = temp->data.Time;
			data.foodorderid = temp->data.foodorderid;
			data.expirytime = temp->data.expirytime;
			data.preptime = temp->data.preptime;
			data.ingredients = temp->data.ingredients;
			data.price = temp->data.price;
			data.Meal = temp->data.Meal;
			Front = Front->next;
			delete temp;
			return data;
		}
		else
			cout << "Que is empty\n";

	}
};
class Stack//Stack class
{
private:
	Node* top;//top node of stack
public:
	Stack()
	{
		top = NULL;
	}
	bool isempty()
	{
		if (top == NULL)
			return true;
		else
			return false;
	}
	void push(ORDER o)
	{
		Node* newnode = new Node;
		newnode->data = o;
		newnode->next = top;
		top = newnode;
	}
	ORDER pop()
	{
		if (isempty())
		{
			cout << "The Stack is empty\n";
		}
		else
		{
			Node* temp = new Node;
			temp = top;
			top = temp->next;
			return temp->data;
			free(temp);
		}
	}
	void TOP(ORDER& o)
	{
		if (isempty())
		{
			cout << "The Stack is empty\n";
		}
		else
		{
			o = top->data;
		}
	}
};
class Priority_Que//class for Priority Queue
{
private:
	P_Node* Front;//Queue front element
public:
	Priority_Que()
	{
		Front = NULL;
	}
	bool isempty()
	{
		if (Front == NULL)
		{
			return true;
		}
		else
			return false;
	}
	void Enqueue(ORDER data, double priority)
	{
		P_Node* temp;
		P_Node* q;
		temp = new P_Node;
		temp->data = data;
		temp->priority = priority;
		if (Front == NULL || priority > Front->priority)
		{
			temp->next = Front;
			Front = temp;
		}
		else
		{
			q = Front;
			while (q->next != NULL && q->next->priority >= priority)
				q = q->next;
			temp->next = q->next;
			q->next = temp;
		}
	}
	void TOP(ORDER& data)//Function to check the data from the Queue
	{
		if (Front != NULL)
		{
			P_Node* temp = Front;
			data.Time = temp->data.Time;
			data.foodorderid = temp->data.foodorderid;
			data.expirytime = temp->data.expirytime;
			data.preptime = temp->data.preptime;
			data.ingredients = temp->data.ingredients;
			data.price = temp->data.price;
			data.Meal = temp->data.Meal;
		}
		else
		{
			data.expirytime = -1;
		}
	}
	ORDER Dequeue()//Function to Dequeue the data from the Queue
	{
		ORDER data;
		if (Front != NULL)
		{//Deleting or accessing data from starting node
			P_Node* temp = Front;
			data.Time = temp->data.Time;
			data.foodorderid = temp->data.foodorderid;
			data.expirytime = temp->data.expirytime;
			data.preptime = temp->data.preptime;
			data.ingredients = temp->data.ingredients;
			data.price = temp->data.price;
			data.Meal = temp->data.Meal;
			Front = Front->next;
			delete temp;
			return data;
		}
		else
			cout << "Que is empty\n";

	}
};
void Prepare(int id, int start_time)
{
	cout << "TIME: " << start_time << ", FoodOrder " << id << " is getting prepared by the chef!\n";
}
int completeservice(int start_time, int preptime)
{
	return start_time + preptime;
}
int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "USAGE: FileReadingExample.exe filename simulationType" << endl;
		cout << "where simulationType is either 1, 2 or 3." << endl;
		system("pause");
		return 0;
	}

	string filename = argv[1];
	string version = argv[2];
	cout << "The filename is: " << filename << endl;
	cout << "The version selected is: " << version << endl;
	Que Event, Arrival, prepare;
	Stack Arrival2;
	Priority_Que Arrival3;

	//Opening the file, reading one line (just the first one of the file here), and parsing it

	ifstream inputFile;
	inputFile.open(filename);  // opening the file for reading
	string line;
	int id = 1;
	ORDER o1, o2;
	int total_order_completed = 0;
	double revenue = 0;
	int count = 0, TIME = 1;
	bool found = true;
	if (version == "1")
		cout << "Simulation begins (First-come first-served Simulation)...\n";
	if (version == "2")
		cout << "Simulation begins (Last-come first-served Simulation)...\n";
	if (version == "3")
		cout << "Simulation begins (Maximize revenue Simulation)...\n";
	if (inputFile.is_open())
	{
		while (!inputFile.eof() || !Arrival.Is_empty() || !prepare.Is_empty() || !Arrival2.isempty() || !Arrival3.isempty())
		{
			int counter = 0;
			int expiry = 0;
			string meal = "";
			int numIngredients = 0;
			int preptime = 0;
			double price = 0;
			int time = 0;
			if (found) //gets the next line from the file and saves it in 'line', if there is one
			{
				if (getline(inputFile, line))
				{
					stringstream sst(line);  //parsing the line token by token
					string token;
					while (sst >> token)  //grabing one token at a time, until there is no token left
					{
						if (counter == 0) //reading time
							time = stoi(token);
						else if (counter == 1) //reading expiry
							expiry = stoi(token);
						else if (counter == 2) //reading meal type
							meal = token;
						else //counting ingredients (if counter > 2)
						{
							numIngredients++;
						}
						counter++;
					}

					if (meal == "Salad")
					{
						price = 6.99;
						price = price + numIngredients;
						preptime = 3;
						preptime = preptime + numIngredients;
					}
					else if (meal == "Burger")
					{
						price = 8.99;
						price = price + numIngredients;
						preptime = 4;
						preptime = preptime + numIngredients;
					}
					else if (meal == "Pizza")
					{
						price = 12.99;
						price = price + numIngredients;
						preptime = 6;
						preptime = preptime + numIngredients;
					}
					else if (meal == "Stew")
					{
						price = 14.99;
						price = price + numIngredients;
						preptime = 7;
						preptime = preptime + numIngredients;
					}
					o1.Time = time;
					o1.foodorderid = id;
					o1.ingredients = numIngredients;
					o1.Meal = meal;
					o1.preptime = preptime;
					o1.price = price;
					o1.expirytime = expiry;
					Event.Enqueue(o1);
					id++;
				}
			}
			if (version == "1")
			{
				if ((count != 0 && found == true) || Event.Is_empty())
				{
					found = false;
					if (!Event.Is_empty())
					{
						o1 = Event.Dequeue();
						cout << "TIME: " << o1.Time << ", FoodOrder " << o1.foodorderid << " arrives->Expiry :" << o1.expirytime << " - Meal : " << o1.Meal << " - Ingredients :" << o1.ingredients << " - Prep.time : " << o1.preptime << " - Price : $" << o1.price << endl;
						Arrival.Enqueue(o1);
						if (prepare.Is_empty())
						{
							o1 = Arrival.Dequeue();
							if (o1.expirytime >= TIME)
							{
								Prepare(o1.foodorderid, TIME);
								o1.Time = TIME;
								prepare.Enqueue(o1);
							}
							else
								TIME--;
						}
					}
					else
					{
						if (prepare.Is_empty())
						{
							o1 = Arrival.Dequeue();
							if (o1.expirytime >= TIME)
							{
								Prepare(o1.foodorderid, TIME);
								o1.Time = TIME;
								prepare.Enqueue(o1);

							}
							else
								TIME--;
						}
					}
				}
				if (!Event.Is_empty())
				{
					Event.TOP(o2);
					if (TIME == o2.Time)
					{
						found = true;
						TIME--;
					}
				}
				TIME++;
				count++;
				if (!prepare.Is_empty())
				{
					prepare.TOP(o1);
					if (TIME == o1.Time + o1.preptime)
					{
						cout << "TIME: " << TIME << ", FoodOrder " << o1.foodorderid << " has been served!Revenue grew by : $" << o1.price << endl;
						prepare.Dequeue();
						total_order_completed = total_order_completed + 1;
						revenue = revenue + o1.price;
					}
					if (prepare.Is_empty())
					{
						if (!Arrival.Is_empty())
						{
							o1 = Arrival.Dequeue();
							if (o1.expirytime >= TIME)
							{
								Prepare(o1.foodorderid, TIME);
								o1.Time = TIME;
								prepare.Enqueue(o1);

							}
						}
					}
				}
			}
			if (version == "2")
			{
				if ((count != 0 && found == true) || Event.Is_empty())
				{
					found = false;
					if (!Event.Is_empty())
					{
						o1 = Event.Dequeue();
						cout << "TIME: " << o1.Time << ", FoodOrder " << o1.foodorderid << " arrives->Expiry :" << o1.expirytime << " - Meal : " << o1.Meal << " - Ingredients :" << o1.ingredients << " - Prep.time : " << o1.preptime << " - Price : $" << o1.price << endl;
						Arrival2.push(o1);
						if (prepare.Is_empty())
						{
							o1 = Arrival2.pop();
							if (o1.expirytime >= TIME)
							{
								Prepare(o1.foodorderid, TIME);
								o1.Time = TIME;
								prepare.Enqueue(o1);
							}
							else
								TIME--;
						}
					}
					else
					{
						if (prepare.Is_empty())
						{
							o1 = Arrival2.pop();
							if (o1.expirytime >= TIME)
							{
								Prepare(o1.foodorderid, TIME);
								o1.Time = TIME;
								prepare.Enqueue(o1);

							}
							else
								TIME--;
						}
					}
				}
				if (!Event.Is_empty())
				{
					Event.TOP(o2);
					if (TIME == o2.Time)
					{
						found = true;
						TIME--;
					}
				}
				TIME++;
				count++;
				if (!prepare.Is_empty())
				{
					prepare.TOP(o1);
					if (TIME == o1.Time + o1.preptime)
					{
						cout << "TIME: " << TIME << ", FoodOrder " << o1.foodorderid << " has been served!Revenue grew by : $" << o1.price << endl;
						prepare.Dequeue();
						total_order_completed = total_order_completed + 1;
						revenue = revenue + o1.price;
					}
					if (prepare.Is_empty())
					{
						if (!Arrival2.isempty())
						{
							o1 = Arrival2.pop();
							if (o1.expirytime >= TIME)
							{
								Prepare(o1.foodorderid, TIME);
								o1.Time = TIME;
								prepare.Enqueue(o1);

							}
						}
					}
				}
			}
			if (version == "3")
			{
				if ((count != 0 && found == true) || Event.Is_empty())
				{
					found = false;
					if (!Event.Is_empty())
					{
						o1 = Event.Dequeue();
						cout << "TIME: " << o1.Time << ", FoodOrder " << o1.foodorderid << " arrives->Expiry :" << o1.expirytime << " - Meal : " << o1.Meal << " - Ingredients :" << o1.ingredients << " - Prep.time : " << o1.preptime << " - Price : $" << o1.price << endl;
						Arrival3.Enqueue(o1, o1.price);
						if (prepare.Is_empty())
						{
							o1 = Arrival3.Dequeue();
							if (o1.expirytime >= TIME)
							{
								Prepare(o1.foodorderid, TIME);
								o1.Time = TIME;
								prepare.Enqueue(o1);
							}
							else
								TIME--;
						}
					}
					else
					{
						if (prepare.Is_empty())
						{
							o1 = Arrival3.Dequeue();
							if (o1.expirytime >= TIME)
							{
								Prepare(o1.foodorderid, TIME);
								o1.Time = TIME;
								prepare.Enqueue(o1);

							}
							else
								TIME--;
						}
					}
				}
				if (!Event.Is_empty())
				{
					Event.TOP(o2);
					if (TIME == o2.Time)
					{
						found = true;
						TIME--;
					}
				}
				TIME++;
				count++;
				if (!prepare.Is_empty())
				{
					prepare.TOP(o1);
					if (TIME == o1.Time + o1.preptime)
					{
						cout << "TIME: " << TIME << ", FoodOrder " << o1.foodorderid << " has been served!Revenue grew by : $" << o1.price << endl;
						prepare.Dequeue();
						total_order_completed = total_order_completed + 1;
						revenue = revenue + o1.price;
					}
					if (prepare.Is_empty())
					{
						if (!Arrival3.isempty())
						{
							o1 = Arrival3.Dequeue();
							if (o1.expirytime >= TIME)
							{
								Prepare(o1.foodorderid, TIME);
								o1.Time = TIME;
								prepare.Enqueue(o1);

							}
						}
					}
				}
			}
		}
		cout << "... simulation ended.\n";
		cout << " - Total number of orders completed : " << total_order_completed << endl;
		cout << " - Total revenue : $" << revenue << endl;
	}
	system("pause");
	return 0;
}