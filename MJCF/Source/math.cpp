int gcd(int x, int y)
{
	UINT g;

	if(x < 0) x = -x;
	if(y < 0) y = -y;

	g = y;

	while(x > 0)
	{
		g = x;
		x = y % x;
		y = g;
	}
	return g;
}

//returns n!
unsigned __int64 fact(int n)
{
	if( n == 1)
		return n;

	return fact(n-1) * n;
}

double e(int x)
{
	double res = 2;

	for(int n = 2; n < x; n++)
	{
		res += (double)1 / (double)fact(n);
	}

	return res;
}