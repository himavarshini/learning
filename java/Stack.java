public class Stack
{
	private static int n_size = 10;
 	static int A[] = new int[n_size];
	static int top = -1 ;
	
	public void push(int x)
	{
		if(top == 10)
		{
			System.out.println("The stack is full");	
		}
		else
		{
			top += 1;
			A[top] = x;	
		}	
	}
	
	public void pop() 
	{
		if(top == -1)
		{
			System.out.println("The stack is empty");
			
		}
		A[top] = 0;
		top -= 1;
		displayElements();
	}
		
	public static void displayElements() 
	{
		System.out.println("The elements in stack are");
		for (int i = top; i >= 0; i--) 
		{
			System.out.println(A[i]);
		}
	}

	public static int getSize()
	{
		return top+1;
	}
	
	public static int getTop()
	{
		return A[top];
	}
	
	public boolean isEmpty()
	{
		if (top == -1)
			return true;
		else 
			return false;
	}
		
	public boolean isFull()
	{
		if(top == 10)
			return true;
		else 
			return false;
	}
	
	public static void main(String [] args)
	{
		Stack s = new Stack();		
		s.push(5);
		s.push(4);
		s.push(3);
		displayElements();
		System.out.println("Popping one element");
		s.pop();
		int n;
		n = getSize();
		System.out.println("The size is " + n);
		int m = getTop();
		System.out.println("The top element is " + m);	
	}
}
