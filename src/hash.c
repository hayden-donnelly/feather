int hash(int key, int array_length)
{
    long l = 2654435769;
    return (key * l >> 32) % array_length;
}