namespace myFunctions 
{

	template <typename T> static int ArrayIndexOf(T** Array, T* toFind, int& ArraySize)
	{
		for (int i = 0; i < ArraySize; i++)
		{
			T* test = Array[i];
			if (Array[i] == toFind)
				return i;
		}
		return -1;
	};
	template <typename T> static T** ArrayAdd(T** Array, T* toAdd, int& ArraySize)
	{
		T** temp = new T * [ArraySize + 1];
		if (Array != nullptr)
		{
			for (int i = 0; i < ArraySize; i++)
			{
				temp[i] = Array[i];
			}
			delete[] Array;
		}
		temp[ArraySize] = toAdd;

		Array = new T * [ArraySize + 1];
		for (int i = 0; i < ArraySize + 1; i++)
		{
			Array[i] = temp[i];
		}
		ArraySize++;
		delete[] temp;
		return Array;
	};
	template <typename T> static T** InsertAt(T** Array, T* toAdd, int& ArraySize, int index)
	{

		T** temp = new T * [ArraySize + 1];
		if (Array != nullptr)
		{
			int arrayIndex = 0;
			for (int i = 0; i < ArraySize; i++)
			{
				if (i == index)
				{
					temp[i] = toAdd;
					continue;
				}
				temp[i] = Array[arrayIndex];

				arrayIndex++;
			}
			temp[ArraySize] = Array[arrayIndex];


			delete[] Array;
		}

		Array = new T * [ArraySize + 1];
		for (int i = 0; i < ArraySize + 1; i++)
		{
			Array[i] = temp[i];
		}
		ArraySize++;
		delete temp;
		return Array;
	};

	template <typename T> static T** ArrayRemove(T** Array, T* toRemove, int& ArraySize)
	{
		int indexToRemove = ArrayIndexOf(Array, toRemove, ArraySize);
		if (indexToRemove == -1)
			return Array;

		T** temp = new T * [ArraySize - 1];
		int loopIndex = 0;

		if (Array)
		{
			for (int i = 0; i < ArraySize; i++)
			{
				if (i == indexToRemove)
				{
					if (Array[i])
						delete Array[i];

					Array[i] = nullptr;
					continue;
				}
				temp[loopIndex] = Array[i];
				loopIndex++;
			}
			delete[] Array;
		}

		Array = new T * [ArraySize - 1];
		for (int i = 0; i < ArraySize - 1; i++)
		{
			Array[i] = temp[i];
		}
		ArraySize--;		
		delete[] temp;

		return Array;
	};
	template <typename T> static T** ArrayRemove(T** Array, T* toRemove, int& ArraySize, bool DontDelete)
	{
		int indexToRemove = ArrayIndexOf(Array, toRemove, ArraySize);
		if (indexToRemove == -1)
			return Array;

		T** temp = new T * [ArraySize - 1];
		int loopIndex = 0;

		if (Array)
		{
			for (int i = 0; i < ArraySize; i++)
			{
				if (i == indexToRemove)
				{
					//delete Array[i];
					continue;
				}
				temp[loopIndex] = Array[i];
				loopIndex++;
			}
			delete[] Array;
		}

		Array = new T * [ArraySize - 1];
		for (int i = 0; i < ArraySize - 1; i++)
		{
			Array[i] = temp[i];
		}
		ArraySize--;
		delete[] temp;
		return Array;
	};

}