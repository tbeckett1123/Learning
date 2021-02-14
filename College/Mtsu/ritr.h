# include <stdio.h>
# ifndef BOOLEAN
# define BOOLEAN
# define TRUE 1
# define FALSE 0
# endif
# ifndef RITR
# define RITR


struct rItr /*reverse itorator data type*/
{
	int mod, value, sum;
};

/*rItr initializer*/
void rItrInit(struct rItr* temp, int value)
{
	(*temp).mod = value;
	(*temp).sum = 0;
	(*temp).value = value - 1;
}

/*rItr assignment*/
int rItrAssign(struct rItr* temp, int value)
{
	if((*temp).mod < value)
		return FALSE;

	(*temp).value = value;
	(*temp).sum = (*temp).mod - 1 - value;

	return TRUE;
}

/*rItr increamentor*/
void rItrPP(struct rItr* temp)
{
	(*temp).sum = ((*temp).sum + 1) % (*temp).mod;
	(*temp).value = (*temp).mod - 1 - (*temp).sum;
}


/*rItr decreamentor*/
void rItrMM(struct rItr* temp)
{
	(*temp).sum = ((*temp).sum == 0) ? (*temp).mod - 1 : (*temp).sum - 1;
	(*temp).value = (*temp).mod - 1 - (*temp).sum;
}

/*rItr index value retreaver*/
int rItrValue(struct rItr temp)
{
	return temp.value;
}

/*rItr swap the two provided rItr items*/
void rItrSwap(struct rItr* one, struct rItr* two)
{
	struct rItr temp;

	temp = *one;
	*one = *two;
	*two = temp;
}

# endif
