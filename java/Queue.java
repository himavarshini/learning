public class Queue
{
	private int [] queue = new int [20];
	public int front = -1 , rear = -1;
	
	public void Enqueue(int X)
	{
		if(IsEmpty())
			front = rear = 0 ;
			
		else
			rear += 1;
		queue[rear] = X;
	} 
	
	public void Dequeue()
	{
		if(IsEmpty())
			System.out.println("Queue is empty no elements to remove");
		else if(front == rear)
			front = rear = -1;
		else 
			front += 1;
	}
	
	public int Size()
	{
		if(IsEmpty())
			return 0;
		else if(front == rear)
			return 1;
		else
			return rear-front+1;
	}
		
	boolean IsEmpty()
	{
		if(front == -1 && rear == -1)
			return true;
		else 
			return false;
	}
	
	public int Front()
	{
		if(IsEmpty())
		{
			System.out.println("Queue is empty");
			return 0;
		}
		else 
			return queue[front];
	}

	public void DisplayQueue()
	{
		if(!(IsEmpty()) || front == rear)
		{
			if( !(IsEmpty()) )
			{
				int tmp = front;
				while(tmp < rear+1)
				{
					System.out.print(" " + queue[tmp]);
					tmp += 1;
				}
				System.out.println();
			}
			else
				System.out.println(queue[front]);
		}
		else
			System.out.println("Queue is Empty");		
	}
				 	 	
}
	
