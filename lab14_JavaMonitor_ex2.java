import java.lang.Thread;
import java.util.concurrent.locks.*;

public class ex2
{
	public static Lock lock=new ReentrantLock();
	public static Condition cCond=lock.newCondition();
	public static Condition pCond=lock.newCondition();
	public static int product=0;
	static class Consumer implements Runnable
	{
		public void run()
		{
			try
			{
				while(true)
				{
					lock.lock();
					if(product==0)
					{
						System.out.println("Empty");
						cCond.await();
					}
					product-=1;
					System.out.println("CONSUMED: "+product);
					pCond.signal();
					lock.unlock();
				}
			}
			catch(Exception e)
			{
				System.out.println("Exception:"+e);
			}
		}
	}
	static class Producer implements Runnable
	{
		public void run()
		{
			try
                        {
                                while(true)
                                {
                                        lock.lock();
                                        if(product==10)
                                        {
                                                System.out.println("          full");
                                                pCond.await();
                                        }
                                        product+=1;
                                        System.out.println("          PRODUCED: "+product);
                                        cCond.signal();
                                        lock.unlock();
                                }
                        }
                        catch(Exception e)
                        {
                                System.out.println("Exception:"+e);
                        }
		}
	}
	public static void main(String args[])
	{
		Consumer c=new Consumer();
		Producer p=new Producer();
		Thread t0=new Thread(c);
		Thread t1=new Thread(p);
		t0.start();
		t1.start();
		try
		{
			t0.join();
			t1.join();
		}
		catch(InterruptedException e)
		{
			;
		}
	}
}
