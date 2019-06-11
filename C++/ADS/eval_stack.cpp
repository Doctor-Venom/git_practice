int evaluation_stack(string expr)//variables and operators must be separated by a space in the expr string
{
	stack<int> vars;
	string var = "";
	for (int i = 0; i < expr.length(); i++)
	{
		if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/' || expr[i] == '%')
		{
			int v2 = vars.top(); vars.pop();
			int v1 = vars.top(); vars.pop();
			if (static_cast<int>(expr[i]) == 43)
				vars.push(v1 + v2);
			else if (static_cast<int>(expr[i]) == 45)
				vars.push(v1 - v2);
			else if (static_cast<int>(expr[i]) == 42)
				vars.push(v1 * v2);
			else if (static_cast<int>(expr[i]) == 47)
				vars.push(v1 / v2);
			else if (static_cast<int>(expr[i]) == 37)
				vars.push(v1 % v2);
			else
			{
				cerr << "INVALID EXPRESSION!" << endl;
				exit(1);
			}
		}
		else
		{
			if (expr[i] != ' ') var += expr[i];
			else
				if (var.length() != 0) { vars.push(stoi(var)); var = ""; }
		}
	}
	int result = vars.top(); vars.pop();
	if (!vars.empty()) { cerr << "INVALID EXPRESSION!" << endl; exit(1); }
	else cout << "DONE!, the result of the expression [" << expr << "] is: " << result << endl;
}