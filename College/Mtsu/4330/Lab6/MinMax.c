# include <stdio.h>

int main(int agrc, char** argv)
{
	int current, min, max, i = 0;;
	FILE* fp;


	if(agrc != 2)
	{
		printf("<**********Error*********>\nIncorrect number of command line arguments\nex:MinMax filename\n");
	}
	else
	{
		if(fp = fopen(argv[1], "r"))
		{
			fscanf(fp, "%d", &current);

			max = min = current;
			
			while(feof(fp) == 0)
			{
				fscanf(fp, "%d", &current);

				if(current > max)
					max = current;

				if(current < min)
					min = current;

				i++;
			}

			printf("count: %d\nmax value: %d\nmin value: %d\n", i, max, min);
			
			fclose(fp);
		}
		else
		{
			printf("The file failed to open\n");
		}
				
	}
	
	return 0;
}
