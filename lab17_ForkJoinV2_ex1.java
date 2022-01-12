import java.util.concurrent.ExecutionException;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;
import java.util.Arrays;

public class ex1
{
	private ForkJoinPool pool;
	private static class sortTask extends RecursiveTask<int[]>
	{
		private int[] arr;
		private int from;
		private int to;

		public sortTask(int[] arr, int from, int to)
		{
			this.arr=arr;
			this.from=from;
			this.to=to;
		}
		public int[]  merge(int[] a, int[] b)
		{
			int narr[]=new int[a.length+b.length];
			int la=0,lb=0;
			for(int i=0;i<narr.length;i++)
			{
				if(la<a.length&&lb<b.length)
				{
					if(a[la]<b[lb])
						narr[i]=a[la++];
					else
						narr[i]=b[lb++];
				}
				else if(la<a.length)
					narr[i]=a[la++];
				else
					narr[i]=b[lb++];
			}

			return narr;
		}
		protected int[] compute()
		{
			if(to-from<2)
			{
				int narr[]=new int[to-from+1];
				for(int i=0,j=from;i<narr.length;i++)
					narr[i]=arr[j++];
				Arrays.sort(narr);
				return narr;
			}
			else
			{
				int spilt=(from+to)/2;
				sortTask f1=new sortTask(arr, from, spilt);
				sortTask f2=new sortTask(arr, spilt+1, to);
				f1.fork();
				return merge(f2.compute(),f1.join());
			}
		}
	}
	public ex1()
	{
		pool=new ForkJoinPool();
	}
	public int[] doSort(int[] arr)
	{
		return pool.invoke(new sortTask(arr,0,arr.length-1));
	}

	public static void main(String argv[])
	{
		ex1 obj=new ex1();
		int arr[]=new int[100];
		int sortedArr[];
		for(int i=0;i<arr.length;i++)
			arr[i]=(int)(Math.random()*1000);
		sortedArr=obj.doSort(arr);
		for(int i=0;i<sortedArr.length;i++)
			System.out.println(sortedArr[i]);
	}
}





















