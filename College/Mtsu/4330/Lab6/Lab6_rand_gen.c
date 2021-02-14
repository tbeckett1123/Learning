# include <stdio.h>
# include <stdlib.h>
# include <time.h>

int main(int agrc, char** argv)
{
	int i, j, k, l[1000], m, n;
	FILE* fp;


	if(agrc != 3)
	{
		printf("<**********Error*********>\nIncorrect number of command line arguments\nex:RandNumGen filename number_of_numbers\n");
	}
	else
	{
		i = atoi(argv[2]);

		if( (i > 0) && (i < 1000) && (fp = fopen(argv[1], "w")) )
		{
			for(m = 0; m < 1000; m++)
				l[m] = 0;
			
			srand(time(NULL));

			for(j = 0, n = 0; j < i; j++)
			{
				k = rand() % 100 + 1;

				for(m = 0; m < n; m++)
					if(l[m] == k)
					{
						j--;
						m = n + 2;
					}

				if(m == n)
				{
					n++;
					
					l[m] = k;
						
					fprintf(fp, "%d ", k);

					printf("%d ", k);
				}
			}

			puts("\n");
			
			fclose(fp);
		}
		else
		{
			printf("The file failed to open or the number entered was out of range (1 - 1000)\n");
		}
				
	}
	
	return 0;
}
