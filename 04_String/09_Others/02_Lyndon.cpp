void duval(char s[])
{
	int n = strlen(s), i = 0;
	vector<int> res; //Lyndon串的开头
	while(i < n)
	{
		int j = i, k = i + 1;
		while(j < n && s[j] <= s[k])
		{
			if(s[j] < s[k]) j = i;
			else j ++;
			k ++;
		}
		while(i <= j) 
		{
			res.push_back(i);
			i += k - j;
		}
	}
}