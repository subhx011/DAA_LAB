#include <stdio.h>

int weighings = 0;

/* 
   Returns the index of the defective coin.
   Returns -1 if no defective coin exists.

   ref = index of a coin already known to be good.
   ref = -1 means we don't have a known-good coin yet.
*/
int findDefective(int coins[], int left, int right, int ref)
{
    int n = right - left + 1;

    /* Only one coin remains */
    if (n == 1)
    {
        if (ref != -1 && coins[left] < coins[ref])
            return left;

        return -1;
    }

    /* Two coins */
    if (n == 2)
    {
        weighings++;

        if (coins[left] < coins[right])
            return left;

        if (coins[right] < coins[left])
            return right;

        return -1;
    }

    int mid = (left + right) / 2;

    int leftCount = mid - left + 1;
    int rightCount = right - mid;

    /*
       If number of coins is odd, leave one coin aside.
    */
    if (leftCount != rightCount)
    {
        int extra = right;
        int sumLeft = 0;
        int sumRight = 0;

        for (int i = left; i < extra; i++)
            sumLeft += coins[i];

        for (int i = mid + 1; i < extra; i++)
            sumRight += coins[i];

        weighings++;

        if (sumLeft < sumRight)
        {
            /* Left group is lighter */
            return findDefective(coins, left, mid, ref);
        }
        else if (sumRight < sumLeft)
        {
            /* Right group is lighter */
            return findDefective(coins, mid + 1, extra - 1, ref);
        }
        else
        {
            /*
               Both groups are equal.
               Therefore the extra coin is either defective
               or there is no defective coin.
            */

            int goodCoin = left;

            weighings++;

            if (coins[extra] < coins[goodCoin])
                return extra;

            return -1;
        }
    }

    /*
       Even number of coins:
       divide into two equal groups.
    */
    int sumLeft = 0;
    int sumRight = 0;

    for (int i = left; i <= mid; i++)
        sumLeft += coins[i];

    for (int i = mid + 1; i <= right; i++)
        sumRight += coins[i];

    weighings++;

    if (sumLeft < sumRight)
    {
        /*
           Left side is lighter.
           Therefore defective coin is in left group.
           Right group is known to be good.
        */
        return findDefective(coins, left, mid, mid + 1);
    }

    else if (sumRight < sumLeft)
    {
        /*
           Right side is lighter.
           Therefore defective coin is in right group.
           Left group is known to be good.
        */
        return findDefective(coins, mid + 1, right, left);
    }

    else
    {
        /*
           Both sides are equal.
           Since all coins have equal-sized groups,
           there is no lighter defective coin.
        */
        return -1;
    }
}


int main()
{
    int n;

    printf("Enter number of coins: ");
    scanf("%d", &n);

    int coins[n];

    printf("Enter weights of %d coins:\n", n);

    for (int i = 0; i < n; i++)
    {
        printf("Coin %d: ", i + 1);
        scanf("%d", &coins[i]);
    }

    int result = findDefective(coins, 0, n - 1, -1);

    printf("\n-----------------------------\n");

    if (result == -1)
    {
        printf("No defective coin found.\n");
    }
    else
    {
        printf("Defective coin: Coin %d\n", result + 1);
        printf("Weight: %d\n", coins[result]);
    }

    printf("Number of weighings: %d\n", weighings);

    return 0;
}