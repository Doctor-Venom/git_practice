#!/bin/python2
# -*- coding: UTF-8 -*-
def find_invpow(x,n):
    high = 1
    while high ** n <= x:
        high *= 2
    low = high/2
    while low < high:
        mid = (low + high) // 2
        if low < mid and mid**n < x:
            low = mid
        elif high > mid and mid**n > x:
            high = mid
        else:
            return mid
    return mid + 1

def exgcd(m, n):
  if n>0:
    y,x,d = exgcd(n, m%n)
    return x, y-(m//n)*x, d
  else:
    return 1, 0, m

def first_prime(begin):
    def isPrime(n) : 
        if (n <= 1) :return False
        if (n <= 3) :return True
        if (n % 2 == 0 or n % 3 == 0) :return False
        i = 5
        while(i * i <= n) : 
            if (n % i == 0 or n % (i + 2) == 0) : return False
            i = i + 6
        return True
    while 1:
        if isPrime(begin):
            return begin
        begin+=1

p,q,n,totient,e,d,PT,CT=0,0,0,0,0,0,0,0
print('''what is given?
(1)[p,q]
(2)[p,n]
(3)[q,n]
(4)[PT,e,n]
(5)[CT,d,n]
(6)[e=3 or 5, CT==PT**e] in other words the CT didnt exceed n after exponentiation
(7)[totient,e]
(8)[p,q,e]''')
choice=int(input())
if choice==1:
    p=int(input('p='))
    q=int(input('q='))
    n=p*q
    totient=(p-1)*(q-1)
    e=[3,5,17,257,65537, int(first_prime(max(p,q)+1))]
    d=[exgcd(i, totient)[0] % (totient) for i in e]
    print 'n=',n
    print 'totient=', totient
    print 'e=', e
    print 'd=', d
elif choice==2:
    p=int(input('p='))
    n=int(input('n='))
    q=n//p
    totient=(p-1)*(q-1)
    e=[3,5,17,257,65537, int(first_prime(max(p,q)+1))]
    d=[exgcd(i, totient)[0] % (totient) for i in e]
    print 'q=',q
    print 'totient=', totient
    print 'e=', e
    print 'd=', d
elif choice==3:
    q=int(input('q='))
    n=int(input('n='))
    p=n//q
    totient=(p-1)*(q-1)
    e=[3,5,17,257,65537, int(first_prime(max(p,q)+1))]
    d=[exgcd(i, totient)[0] % (totient) for i in e]
    print 'p=',p
    print 'totient=', totient
    print 'e=', e
    print 'd=', d
elif choice==4:
    PT=int(input('PT='))
    e=int(input('e='))
    n=int(input('n='))
    CT=pow(PT, e, n)
    print'CT=',CT
    print 'decoded:',("%x"%CT).strip('L').decode("hex")
elif choice==5:
    CT=int(input('CT='))
    d=int(input('d='))
    n=int(input('n='))
    PT=pow(CT, d, n)
    print 'PT=',PT
    print 'decoded:',("%x"%PT).strip('L').decode("hex")
elif choice==6:
    e=int(input('e='))
    CT=int(input('CT='))
    PT=find_invpow(CT,e)
    print(CT)
    print 'PT=',PT
    print 'decoded:',("%x"%PT).strip('L').decode("hex")
elif choice==7:
    totient=int(input('totient='))
    e=int(input())
    d=exgcd(e, totient)[0] % (totient)
    print 'd=',d
elif choice==8:
    p=int(input('p='))
    q=int(input('q='))
    e=int(input('e='))
    n=p*q
    totient=(p-1)*(q-1)
    d=exgcd(e, totient)[0] % (totient)
    print 'n=',n
    print 'totient=',totient
    print 'd=', d
else:
    print('Invalid choice!')
