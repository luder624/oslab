import java.lang.Thread;
public class ex1
{
	public static int c=0;
	static class add implements Runnable
	{
		public void run()
		{
			for(int i=0;i<2500000;i++)
				count(1);
		}
	}
	static class sub implements Runnable
        {
                public void run()
                {
			for(int i=0;i<2500000;i++)
                        	count(-1);
                }
        }
	static synchronized public void count(int n)
	{
		c+=n;
	}
	public static void main(String[] args)
	{
		add a=new add();
		sub b=new sub();
		Thread t1=new Thread(a);
		Thread t2=new Thread(b);
		t1.start();
		t2.start();
		try
		{
			t1.join();
			t2.join();
		}
		catch(InterruptedException e)
		{
			;
		}
		System.out.println(c);
	}

}
