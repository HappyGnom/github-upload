int power(int base, int exponent)
{
if (exponent == 1)
return base;
else
return base * power(base, exponent - 1);
}
int main(int argc, char const *argv[])
{
printf("%d\n", power(3, 4));
getch();
}