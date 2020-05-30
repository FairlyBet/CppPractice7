#include <iostream>
#include <ctime>
using namespace std;

struct Student
{
	string lastName;
	float avergeMark = 0;
	Student* prevStud = nullptr;

	void setInf()
	{
		cout << "Enter some infotmation: ";
		cin >> lastName >> avergeMark;
	}

	void getInf()
	{
		cout << lastName << " " << avergeMark << endl;
	}
};

struct StackOfStudents
{
	Student* currentStud = nullptr;
	Student* prevStud = nullptr;

	void add()
	{
		prevStud = currentStud;
		currentStud = new Student();
		currentStud->prevStud = prevStud;
		currentStud->setInf();
	}

	void show()
	{
		prevStud = currentStud;
		while (currentStud)
		{
			currentStud->getInf();
			currentStud = currentStud->prevStud;
		}
		currentStud = prevStud;
		prevStud = prevStud->prevStud;
	}

	void clear()
	{
		while (currentStud)
		{
			prevStud = currentStud->prevStud;
			delete currentStud;
			currentStud = prevStud;
		}
		prevStud = nullptr; //Возможно не стоит
	}
};

struct RealValue
{
	double value = 0;
	RealValue* nextValue = nullptr;

	void getVal()
	{
		cout << value << "  ";
	}
};

struct RealValuesQueue
{
	RealValue* firstValue = nullptr;
	RealValue* currentValue = nullptr;

	void enqueue(double num)
	{
		if (!firstValue)
		{
			firstValue = new RealValue();
			firstValue->value = num;
		}
		else if (!currentValue)
		{
			currentValue = new RealValue();
			currentValue->value = num;
			firstValue->nextValue = currentValue;
		}
		else
		{
			currentValue->nextValue = new RealValue();
			currentValue->nextValue->value = num;
			currentValue = currentValue->nextValue;
		}
	}

	void dequeue(/*float value = 0*/)
	{
		/*if (value != 0)
		{
			if (firstValue)
			{
				RealValue* saveValue;
				if (firstValue->value == value)
				{
					if (!firstValue->nextValue)
					{
						delete firstValue;
						firstValue = nullptr;
						return;
					}
					saveValue = firstValue->nextValue;
					delete firstValue;
					firstValue = saveValue;
				}
				else if (currentValue)
				{
					saveValue = firstValue;
					while (firstValue->nextValue)
					{
						if (firstValue->nextValue->value == value)
						{
							if (firstValue->nextValue == currentValue)
							{
								currentValue = firstValue;
								delete firstValue->nextValue;
								firstValue->nextValue = nullptr;
								break;
							}
							else
							{
								RealValue* valToSave = firstValue->nextValue->nextValue;
								delete firstValue->nextValue;
								firstValue->nextValue = valToSave;
								break;
							}
						}
						else
						{
							firstValue = firstValue->nextValue;
						}
					}
					firstValue = saveValue;
				}

				if (firstValue == currentValue)
				{
					currentValue = firstValue->nextValue;
				}
			}
		}*/

		if (firstValue)
		{
			RealValue* valueToDel = firstValue;
			if (!valueToDel->nextValue)
			{
				delete valueToDel;
				firstValue = nullptr;
				return;
			}
			while (valueToDel->nextValue != currentValue)
			{
				valueToDel = valueToDel->nextValue;
			}
			currentValue = valueToDel;
			delete currentValue->nextValue;
			currentValue->nextValue = nullptr;
			if (firstValue == currentValue)
				currentValue = nullptr;
		}
	}

	double show()
	{
		double sum = 0;
		if (!currentValue && firstValue)
		{
			firstValue->getVal();
			cout << endl;
			sum += firstValue->value;
		}
		else if (!firstValue)
			cout << 0 << endl;
		else
		{
			currentValue = firstValue;
			currentValue->getVal();
			sum += currentValue->value;
			while (currentValue->nextValue)
			{
				currentValue = currentValue->nextValue;
				currentValue->getVal();
				sum += currentValue->value;
			}
			cout << endl;
		}
		return sum;
	}
};

void lowLevel()
{
	StackOfStudents stack;
	stack.add();
	stack.add();
	stack.show();
	stack.clear();
}

void mediumLevel()
{
	RealValuesQueue queue;
	double nums[4] = { 2.2, 1.2, 2.0, 5.2 };
	for (size_t i = 0; i < 4; i++)
	{
		queue.enqueue(nums[i]);
	}
	cout << "queue: ";
	queue.show();
	queue.dequeue();
	queue.dequeue();
	queue.enqueue(2.9);
	cout << "queue: ";
	cout << "sum is " << queue.show();
}

void highLevel()
{
	int nums[10];
	RealValuesQueue OddQueue, EvenQueue;
	for (size_t i = 0; i < 10; i++)
	{
		nums[i] = rand() % 20 + 1;
		//nums[i] = 1;
		if (nums[i] % 2)
			OddQueue.enqueue(nums[i]);
		else EvenQueue.enqueue(nums[i]);
	}
	cout << "Odd queue pointers: " << OddQueue.firstValue << " " << OddQueue.currentValue << endl;
	cout << "Even queue pointers: " << EvenQueue.firstValue << " " << EvenQueue.currentValue;
}

int main()
{
	srand(time(0));
	//lowLevel();
	//mediumLevel();
	highLevel();
}