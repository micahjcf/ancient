bool inline wholenum(double d){
	return ((int)d>d)||((int)d<d);
}

template <typename Type>
void Randomize(Type* List, int nItems)
{
	int rs1;
	int rs2;
	Type s1;
						// * 2
	for(int n=0; n < (nItems << 2); n++)
	{
		rs1 = (rand() % nItems);
		rs2 = (rand() % nItems);
		s1 = List[rs1];
		List[rs1] = List[rs2];
		List[rs2] = s1;
	}
}

//Reduces expressions in the form of C * pow(X, 1/R)
void RadReduce(int* coef, int root, int* radicand)
{
	int factor, n;
	double temp, a;

	while(true)
	{
		factor = 0;

		//find a factor of the radicand that is a perfect root of root
		for(n = 2; n < (*radicand) / 2; n++)
		{
			temp = (double)(*radicand) / pow(n, root);

			if(modf(temp, &a) == 0)
			{
				factor = pow(n, root);
				break;
			}
		}

		if(factor == 0) //no factors found
			return;

		*coef = (*coef) * pow((double)factor, 1.0 / root);
		(*radicand) = (*radicand / factor);
	}
}