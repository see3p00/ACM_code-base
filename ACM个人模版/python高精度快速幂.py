def fastExpMod(b, e, m):
    result = 1
    while e != 0:
        if (e&1) == 1:
            # ei = 1, then mul
            result = (result * b) % m
        e >>= 1
        # b, b^2, b^4, b^8, ... , b^(2^n)
        b = (b*b) % m
    return result
t=int(input())
while t:
	t-=1
	a, b, c = map(int, input().split())
	print(fastExpMod(a,b,c))