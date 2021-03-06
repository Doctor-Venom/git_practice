import math


def discrete():  # distributions of discrete RVs:
    e = 2.7182818284590452353602874713527
    choose = input("Enter the distribution-(BER/BIN/GEO/NB):")
    if choose == "BER":
        p = float(input("Enter Probability of success: P="))
        print("X:BER(" + str(p) + ")")
        print("f(x)= " + str(p) + "^x * (" + str(1 - p) + ")^(1-x) ; x= 0,1")
        x = int(input("Enter the value of X(1 for success and 0 for failure) to calculate the probability:"))
        print("f(x)= ", p ** x * (1 - p) ** (1 - x))
        print("E(X)= ", p)
        print("Var(X)= ", p * (1 - p))
        print("Std(X)= ", math.sqrt(p * (1 - p)))
        print("M(t)= (" + str(1 - p) + ")+" + str(p) + "e^t")
        print("M(1)= ", 1 - p + p * e ** 1)

    elif choose == "BIN":
        p, n = float(input("Enter Probability of success: P=")), int(
            input("Enter Number of independent bernoulli trials: n="))
        print("X:BIN(" + str(n) + "," + str(p) + ")")
        print("f(x) = (" + str(n) + " choose x) * " + str(p) + "^x * (" + str(1 - p) + ")^(" + str(
            n) + "-x) ; x = 0,1,2,3...," + str(n))
        x = int(input("Enter the value of X(number of successes in n trials) to calculate the probability:"))
        print("f(x)= ",
              (math.factorial(n) / (math.factorial(x) * math.factorial(n - x))) * (p ** x) * ((1 - p) ** (n - x)))
        print("E(X)= ", n * p)
        print("Var(X)= ", n * p * (1 - p))
        print("Std(X)= ", math.sqrt(n * p * (1 - p)))
        print("M(t)= (" + str(1 - p) + ")+" + str(p) + "e^t)^" + str(n))
        print("M(1)= ", (1 - p + p * e ** 1) ** n)
        if int(input("do you want to find probability in a range?(1/0)")):
            f = 0
            r1, r2 = int(input("range starts on:")), int(input("range ends on:"))
            for X in range(r1, r2 + 1):
                f += (math.factorial(n) / (math.factorial(X) * math.factorial(n - X))) * (p ** X) * ((1 - p) ** (n - X))
            print("P(" + str(r1) + " <= x <= " + str(r2) + ")= ", f)

    elif choose == "GEO":
        p = float(input("Enter Probability of success: P="))
        print("X:GEO(" + str(p) + ")")
        print("f(x)= " + str(p) + "(" + str(1 - p) + ")^(x-1) ; x= 1,2,3,.....")
        x = int(input("Enter the value of X(number of trials until the first success) to calculate the probability:"))
        print("f(x)= ", p * (1 - p) ** (x - 1))
        print("E(X)= ", 1 / p)
        print("Var(X)= ", (1 - p) / (p ** 2))
        print("Std(X)= ", math.sqrt((1 - p) / (p ** 2)))
        print("M(t)= (" + str(p) + "e^t)/(1-(" + str(1 - p) + ")e^t) ; t < -ln(" + str(1 - p) + ")")
        print("M(1)= ", (p * e ** 1) / (1 - (1 - p) * e ** 1))
        if int(input("do you want to find probability in a range?(1/0)")):
            f = 0
            r1, r2 = int(input("range starts on:")), int(input("range ends on:"))
            for X in range(r1, r2 + 1):
                f += (p * (1 - p) ** (X - 1))
            print("P(" + str(r1) + " <= x <= " + str(r2) + ")= ", f)

    elif choose == "NB":
        p = float(input("Enter Probability of success: P="))
        r = int(input("Enter number of successes: r="))
        print("X:NB(" + str(r) + "," + str(p) + ")")
        print("f(x)= ((x-1) choose (" + str(r - 1) + ")) * " + str(p) + "^" + str(r) + " * (" + str(
            1 - p) + ")^(x-" + str(r) + ") ; x= " + str(r) + ", " + str(r + 1) + ", " + str(r + 2) + ",.....")
        x = int(input("Enter the value of X(number of trials until the r-th success) to calculate the probability:"))
        print("f(x)= ",
              ((math.factorial(x - 1)) / (math.factorial(r - 1) * math.factorial(x - r))) * p ** r * (1 - p) ** (x - r))
        print("E(X)= ", r / p)
        print("Var(X)= ", r * ((1 - p) / (p ** 2)))
        print("M(t)= ",
              "((" + str(p) + "e^t)/(1-(" + str(1 - p) + ")e^t))^" + str(r) + " ; t < -ln(" + str(1 - p) + ")")
        print("M(1)= ", ((p * e ** 1) / (1 - (1 - p) * e ** 1)) ** r)
        if int(input("do you want to find probability in a range?(1/0)")):
            f = 0
            r1, r2 = int(input("range starts on:")), int(input("range ends on:"))
            for X in range(r1, r2 + 1):
                f += (((math.factorial(X - 1)) / (math.factorial(r - 1) * math.factorial(X - r))) * p ** r * (
                        1 - p) ** (X - r))
            print("P(" + str(r1) + " <= x <= " + str(r2) + ")= ", f)
    else:
        print("INVALID INPUT!")


def continuous():  # distributions of continuous RVs:
    e = 2.7182818284590452353602874713527
    choose = input("Enter the distribution-(U/EXP/G/Chi/N):")
    if choose == "U":
        a, b = int(input("Enter the range of X:\nrange starts on:")), int(input("range ends on:"))
        print("X:U(" + str(a) + "," + str(b) + ")")
        x = float(input("Enter the value of x(the end of the range) to find the probability"))
        print("f(x)= 1/(b-a)= " + str(1 / (b - a)) + " ; a < x < b")
        print("F(x)= P(X <= " + str(x) + ")= (" + str(a) + "-a)/(a-b)= (x-" + str(a) + ")/" + str(
            b - a) + " ; a <= x < b")
        print("E(X)= ", (a + b) / 2)
        print("Var(X)= ", ((b - a) ** 2) / 12)
        print("M(t)= ((e^bt)-(e^at))/((b-a)t) ; t != 0")
        print("M(1)= ", ((e ** b) - (e ** a)) / (b - a))
    elif choose == "EXP":
        o = int(input("Enter the value of theta:"))
        print("X:EXP(" + str(o) + ")")
        x = float(input("Enter the value of x(the end of the range) to find the probability"))
        print("f(x)= (1/θ)e^(-x/θ)= " + str((1 / o) * e ** (-x / o)) + " ; x >= 0")
        print("F(x)= P(X <= " + str(x) + ")=" + str(1 - e ** (-x / o)) + " ; x >= 0")
        print("E(X)= ", o)
        print("Var(X)= ", o ** 2)
        print("M(t)= 1/(1-θt) ; t < 1/θ")
        print("M(1)= ", 1 / (1 - o))

    elif choose == "G":
        a, o = int(input("Enter the value of alpha:")), int(input("Enter the value of theta:"))
        print("X:G(" + str(a) + "," + str(o) + ")")
        x = float(input("Enter the value of x(the end of the range) to find the probability"))
        print("f(x)= 1/(Г(α)θ^α)*x^(α-1)*e^(-x/α)= " + str(
            ((1 / (math.factorial(a - 1))) * (o ** a)) * (x ** (a - 1)) * (e ** (-x / o))) + " ; x >= 0")
        print("E(X)= ", a * o)
        print("Var(X)= ", a * o ** 2)
        print("M(t)= (1/(1-θt))^α ; t < 1/θ")
        print("M(1)= ", (1 / (1 - o)) ** a)
    elif choose == "Chi":
        r = int(input("Enter the value of r (degree of freedom):"))
        print("X:χ(2," + str(r) + ")")
        x = float(input("Enter the value of x(the end of the range) to find the probability"))
        print("f(x)= 1/(Г(r/2)2^(r/2))*x^((r/2)-1)*e^(-x/2)= " + str(
            ((1 / (math.factorial((r / 2) - 1))) * (2 ** (r / 2))) * (x ** ((r / 2) - 1)) * (
                        e ** (-x / 2))) + " ; x >= 0, r= 1,2,3,.....")
        print("E(X)= ", r)
        print("Var(X)= ", 2 * r)
        print("M(t)= (1/(1-2t))^(r/2) ; t < 1/2")
        print("M(1)= ", (1 / (1 - 2)) ** (r / 2))

    elif choose == "N":
        m, s = int(input("Enter the mean:")), int(input("Enter the variance:"))
        print("X:N(" + str(m) + "," + str(s) + ")")
        x = float(input("Enter the value of x(the end of the range) to find the probability"))
        print("f(x)= (1/(σ√2π))e^((x-μ)^2/(2σ^2))= " + str(
            (1 / math.sqrt(s * 2 * math.pi)) * (e ** (((x - m) ** 2) / (2 * s)))) + " ; -∞ < x < ∞")
        print("E(X)= ", m)
        print("Var(X)= ", s)
        print("M(t)= e^(μt+((σ^2t^2)/2))")
        print("M(1)= ", e ** (m + (s / 2)))

    else:
        print("INVALID INPUT!")


discrete_or_continuous = input("Enter the type of the random variable X (discrete or continuous):")
if discrete_or_continuous == "discrete":
    discrete()
else:
    continuous()
