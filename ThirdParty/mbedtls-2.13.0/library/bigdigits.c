/* $Id: bigdigits.c $ */

/***** BEGIN LICENSE BLOCK *****
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2001-16 David Ireland, D.I. Management Services Pty Limited
 * <http://www.di-mgt.com.au/bigdigits.html>. All rights reserved.
 *
 ***** END LICENSE BLOCK *****/
/*
 * Last updated:
 * $Date: 2016-03-31 09:51:00 $
 * $Revision: 2.6.1 $
 * $Author: dai $
 */

/* Core code for BigDigits library "mp" functions */

/* Sizes to match */
#define MAX_DIGIT         0xFFFFFFFFUL
#define MAX_HALF_DIGIT    0xFFFFUL  /* NB 'L' */
#define BITS_PER_DIGIT    32
#define HIBITMASK         0x80000000UL

#define MAX_FIXED_BIT_LENGTH    8192
#define MAX_FIXED_DIGITS        ((MAX_FIXED_BIT_LENGTH + BITS_PER_DIGIT - 1) / BITS_PER_DIGIT)

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

uint32_t   qq[MAX_FIXED_DIGITS*2];
uint32_t   rr[MAX_FIXED_DIGITS*2];


/** Returns number of significant digits in a */
int mpSizeof(const uint32_t a[], int ndigits)
{       
    while (ndigits--)
    {
        if (a[ndigits] != 0)
            return (++ndigits);
    }
    return 0;
}


int  mpBitLength(const uint32_t d[], int ndigits)
/* Returns no of significant bits in d */
{
    int        n, i, bits;
    uint32_t   mask;

    if (!d || ndigits == 0)
        return 0;

    n = mpSizeof(d, ndigits);
    if (0 == n) return 0;

    for (i = 0, mask = HIBITMASK; mask > 0; mask >>= 1, i++)
    {
        if (d[n-1] & mask)
            break;
    }
    bits = n * BITS_PER_DIGIT - i;
    return bits;
}

int mpGetBit(const uint32_t a[], int ndigits, int ibit)
    /* Returns value 1 or 0 of bit n (0..nbits-1); or -1 if out of range */
{
    int       idigit, bit_to_get;
    uint32_t  mask;

    /* Which digit? (0-based) */
    idigit = ibit / BITS_PER_DIGIT;
    if (idigit >= ndigits)
        return -1;

    /* Set mask */
    bit_to_get = ibit % BITS_PER_DIGIT;
    mask = 0x01 << bit_to_get;

    return ((a[idigit] & mask) ? 1 : 0);
}

uint32_t mpSetZero(volatile uint32_t a[], int ndigits)
{   /* Sets a = 0 */

    /* Prevent optimiser ignoring this */
    volatile uint32_t optdummy;
    volatile uint32_t *p = a;

    while (ndigits--)
        a[ndigits] = 0;
    
    optdummy = *p;
    return optdummy;
}

void mpSetEqual(uint32_t a[], const uint32_t b[], int ndigits)
{   /* Sets a = b */
    int i;
    
    for (i = 0; i < ndigits; i++)
    {
        a[i] = b[i];
    }
}

void mpSetDigit(uint32_t a[], uint32_t d, int ndigits)
{   /* Sets a = d where d is a single digit */
    int i;
    
    for (i = 1; i < ndigits; i++)
    {
        a[i] = 0;
    }
    a[0] = d;
}

/** Returns sign of (a - b) as 0, +1 or -1. Not constant-time. */
int mpCompare(const uint32_t a[], const uint32_t b[], int ndigits)
{
    /* if (ndigits == 0) return 0; // deleted [v2.5] */

    while (ndigits--)
    {
        if (a[ndigits] > b[ndigits])
            return 1;   /* GT */
        if (a[ndigits] < b[ndigits])
            return -1;  /* LT */
    }

    return 0;   /* EQ */
}

uint32_t mpShiftLeft(uint32_t a[], const uint32_t *b,
    int shift, int ndigits)
{   /* Computes a = b << shift */
    /* [v2.1] Modified to cope with shift > BITS_PERDIGIT */
    int i, y, nw, bits;
    uint32_t mask, carry, nextcarry;

    /* Do we shift whole digits? */
    if (shift >= BITS_PER_DIGIT)
    {
        nw = shift / BITS_PER_DIGIT;
        i = ndigits;
        while (i--)
        {
            if (i >= nw)
                a[i] = b[i-nw];
            else
                a[i] = 0;
        }
        /* Call again to shift bits inside digits */
        bits = shift % BITS_PER_DIGIT;
        carry = b[ndigits-nw] << bits;
        if (bits) 
            carry |= mpShiftLeft(a, a, bits, ndigits);
        return carry;
    }
    else
    {
        bits = shift;
    }

    /* Construct mask = high bits set */
    mask = ~(~(uint32_t)0 >> bits);
    
    y = BITS_PER_DIGIT - bits;
    carry = 0;
    for (i = 0; i < ndigits; i++)
    {
        nextcarry = (b[i] & mask) >> y;
        a[i] = b[i] << bits | carry;
        carry = nextcarry;
    }

    return carry;
}

uint32_t mpShiftRight(uint32_t a[], const uint32_t b[], int shift, int ndigits)
{   /* Computes a = b >> shift */
    /* [v2.1] Modified to cope with shift > BITS_PERDIGIT */
    int i, y, nw, bits;
    uint32_t mask, carry, nextcarry;

    /* Do we shift whole digits? */
    if (shift >= BITS_PER_DIGIT)
    {
        nw = shift / BITS_PER_DIGIT;
        for (i = 0; i < ndigits; i++)
        {
            if ((i+nw) < ndigits)
                a[i] = b[i+nw];
            else
                a[i] = 0;
        }
        /* Call again to shift bits inside digits */
        bits = shift % BITS_PER_DIGIT;
        carry = b[nw-1] >> bits;
        if (bits) 
            carry |= mpShiftRight(a, a, bits, ndigits);
        return carry;
    }
    else
    {
        bits = shift;
    }

    /* Construct mask to set low bits */
    /* (thanks to Jesse Chisholm for suggesting this improved technique) */
    mask = ~(~(uint32_t)0 << bits);
    
    y = BITS_PER_DIGIT - bits;
    carry = 0;
    i = ndigits;
    while (i--)
    {
        nextcarry = (b[i] & mask) << y;
        a[i] = b[i] >> bits | carry;
        carry = nextcarry;
    }

    return carry;
}

uint32_t spDivide(uint32_t *pq, uint32_t *pr, const uint32_t u[2], uint32_t v)
{
    uint64_t uu, q;
    uu = (uint64_t)u[1] << 32 | (uint64_t)u[0];
    q = uu / (uint64_t)v;
    //r = uu % (uint64_t)v;
    *pr = (uint32_t)(uu - q * v);
    *pq = (uint32_t)(q & 0xFFFFFFFF);
    return (uint32_t)(q >> 32);
}

int spMultiply(uint32_t p[2], uint32_t x, uint32_t y)
{
    /* Use a 64-bit temp for product */
    uint64_t t = (uint64_t)x * (uint64_t)y;
    /* then split into two parts */
    p[1] = (uint32_t)(t >> 32);
    p[0] = (uint32_t)(t & 0xFFFFFFFF);

    return 0;
}

static uint32_t mpMultSub(uint32_t wn, uint32_t w[], const uint32_t v[],
                       uint32_t q, int n)
{   /*  Compute w = w - qv
        where w = (WnW[n-1]...W[0])
        return modified Wn.
    */
    uint32_t k, t[4];
    int i;

    if (q == 0) /* No change */
        return wn;

    k = 0;

    for (i = 0; i < n; i++)
    {
        spMultiply(t, q, v[i]);
        w[i] -= k;
        if (w[i] > MAX_DIGIT - k)
            k = 1;
        else
            k = 0;
        w[i] -= t[0];
        if (w[i] > MAX_DIGIT - t[0])
            k++;
        k += t[1];
    }

    /* Cope with Wn not stored in array w[0..n-1] */
    wn -= k;

    return wn;
}

uint32_t mpShortDiv(uint32_t q[], const uint32_t u[], uint32_t v, 
                   int ndigits)
{
    /*  Calculates quotient q = u div v
        Returns remainder r = u mod v
        where q, u are multiprecision integers of ndigits each
        and r, v are single precision digits.

        Makes no assumptions about normalisation.
        
        Ref: Knuth Vol 2 Ch 4.3.1 Exercise 16 p625
    */
    int j;
    uint32_t t[4], r;
    int shift;
    uint32_t bitmask, overflow, *uu;

    if (ndigits == 0) return 0;
    if (v == 0) return 0;   /* Divide by zero error */

    /*  Normalise first */
    /*  Requires high bit of V
        to be set, so find most signif. bit then shift left,
        i.e. d = 2^shift, u' = u * d, v' = v * d.
    */
    bitmask = HIBITMASK;
    for (shift = 0; shift < BITS_PER_DIGIT; shift++)
    {
        if (v & bitmask)
            break;
        bitmask >>= 1;
    }

    v <<= shift;
    overflow = mpShiftLeft(q, u, shift, ndigits);
    uu = q;
    
    /* Step S1 - modified for extra digit. */
    r = overflow;   /* New digit Un */
    j = ndigits;
    while (j--)
    {
        /* Step S2. */
        t[1] = r;
        t[0] = uu[j];
        overflow = spDivide(&q[j], &r, t, v);
    }

    /* Unnormalise */
    r >>= shift;
    
    return r;
}

static int QhatTooBig(uint32_t qhat, uint32_t rhat,
                      uint32_t vn2, uint32_t ujn2)
{   /*  Returns true if Qhat is too big
        i.e. if (Qhat * Vn-2) > (b.Rhat + Uj+n-2)
    */
    uint32_t t[4];

    spMultiply(t, qhat, vn2);
    if (t[1] < rhat)
        return 0;
    else if (t[1] > rhat)
        return 1;
    else if (t[0] > ujn2)
        return 1;

    return 0;
}

uint32_t mpAdd(uint32_t w[], const uint32_t u[], const uint32_t v[], int ndigits)
{
    /*  Calculates w = u + v
        where w, u, v are multiprecision integers of ndigits each
        Returns carry if overflow. Carry = 0 or 1.

        Ref: Knuth Vol 2 Ch 4.3.1 p 266 Algorithm A.
    */

    uint32_t k;
    int j;

    // assert(w != v);

    /* Step A1. Initialise */
    k = 0;

    for (j = 0; j < ndigits; j++)
    {
        /*  Step A2. Add digits w_j = (u_j + v_j + k)
            Set k = 1 if carry (overflow) occurs
        */
        w[j] = u[j] + k;
        if (w[j] < k)
            k = 1;
        else
            k = 0;
        
        w[j] += v[j];
        if (w[j] < v[j])
            k++;

    }   /* Step A3. Loop on j */

    return k;   /* w_n = k */
}

int mpDivide(uint32_t q[], uint32_t r[], const uint32_t u[],
    int udigits, uint32_t v[], int vdigits)
{   /*  Computes quotient q = u / v and remainder r = u mod v
        where q, r, u are multiple precision digits
        all of udigits and the divisor v is vdigits.

        Ref: Knuth Vol 2 Ch 4.3.1 p 272 Algorithm D.

        Do without extra storage space, i.e. use r[] for
        normalised u[], unnormalise v[] at end, and cope with
        extra digit Uj+n added to u after normalisation.

        WARNING: this trashes q and r first, so cannot do
        u = u / v or v = u mod v.
        It also changes v temporarily so cannot make it const.
    */
    int shift;
    int n, m, j;
    uint32_t bitmask, overflow;
    uint32_t qhat, rhat, t[4];
    uint32_t *uu, *ww;
    int qhatOK, cmp;

    /* Clear q and r */
    mpSetZero(q, udigits);
    mpSetZero(r, udigits);

    /* Work out exact sizes of u and v */
    n = (int)mpSizeof(v, vdigits);
    m = (int)mpSizeof(u, udigits);
    m -= n;

    /* Catch special cases */
    if (n == 0)
        return -1;  /* Error: divide by zero */

    if (n == 1)
    {   /* Use short division instead */
        r[0] = mpShortDiv(q, u, v[0], udigits);
        return 0;
    }

    if (m < 0)
    {   /* v > u, so just set q = 0 and r = u */
        mpSetEqual(r, u, udigits);
        return 0;
    }

    if (m == 0)
    {   /* u and v are the same length */
        cmp = mpCompare(u, v, (int)n);
        if (cmp < 0)
        {   /* v > u, as above */
            mpSetEqual(r, u, udigits);
            return 0;
        }
        else if (cmp == 0)
        {   /* v == u, so set q = 1 and r = 0 */
            mpSetDigit(q, 1, udigits);
            return 0;
        }
    }

    /*  In Knuth notation, we have:
        Given
        u = (Um+n-1 ... U1U0)
        v = (Vn-1 ... V1V0)
        Compute
        q = u/v = (QmQm-1 ... Q0)
        r = u mod v = (Rn-1 ... R1R0)
    */

    /*  Step D1. Normalise */
    /*  Requires high bit of Vn-1
        to be set, so find most signif. bit then shift left,
        i.e. d = 2^shift, u' = u * d, v' = v * d.
    */
    bitmask = HIBITMASK;
    for (shift = 0; shift < BITS_PER_DIGIT; shift++)
    {
        if (v[n-1] & bitmask)
            break;
        bitmask >>= 1;
    }

    /* Normalise v in situ - NB only shift non-zero digits */
    overflow = mpShiftLeft(v, v, shift, n);

    /* Copy normalised dividend u*d into r */
    overflow = mpShiftLeft(r, u, shift, n + m);
    uu = r; /* Use ptr to keep notation constant */

    t[0] = overflow;    /* Extra digit Um+n */

    /* Step D2. Initialise j. Set j = m */
    for (j = m; j >= 0; j--)
    {
        /* Step D3. Set Qhat = [(b.Uj+n + Uj+n-1)/Vn-1] 
           and Rhat = remainder */
        qhatOK = 0;
        t[1] = t[0];    /* This is Uj+n */
        t[0] = uu[j+n-1];
        overflow = spDivide(&qhat, &rhat, t, v[n-1]);

        /* Test Qhat */
        if (overflow)
        {   /* Qhat == b so set Qhat = b - 1 */
            qhat = MAX_DIGIT;
            rhat = uu[j+n-1];
            rhat += v[n-1];
            if (rhat < v[n-1])  /* Rhat >= b, so no re-test */
                qhatOK = 1;
        }
        /* [VERSION 2: Added extra test "qhat && "] */
        if (qhat && !qhatOK && QhatTooBig(qhat, rhat, v[n-2], uu[j+n-2]))
        {   /* If Qhat.Vn-2 > b.Rhat + Uj+n-2 
               decrease Qhat by one, increase Rhat by Vn-1
            */
            qhat--;
            rhat += v[n-1];
            /* Repeat this test if Rhat < b */
            if (!(rhat < v[n-1]))
                if (QhatTooBig(qhat, rhat, v[n-2], uu[j+n-2]))
                    qhat--;
        }


        /* Step D4. Multiply and subtract */
        ww = &uu[j];
        overflow = mpMultSub(t[1], ww, v, qhat, (int)n);

        /* Step D5. Test remainder. Set Qj = Qhat */
        q[j] = qhat;
        if (overflow)
        {   /* Step D6. Add back if D4 was negative */
            q[j]--;
            overflow = mpAdd(ww, ww, v, (int)n);
        }

        t[0] = uu[j+n-1];   /* Uj+n on next round */

    }   /* Step D7. Loop on j */

    /* Clear high digits in uu */
    for (j = n; j < m+n; j++)
        uu[j] = 0;

    /* Step D8. Unnormalise. */

    mpShiftRight(r, r, shift, n);
    mpShiftRight(v, v, shift, n);

    return 0;
}

/***************************/
int mpModulo(uint32_t r[], const uint32_t u[], int udigits, 
             uint32_t v[], int vdigits)
{
    /*  Computes r = u mod v
        where r, v are multiprecision integers of length vdigits
        and u is a multiprecision integer of length udigits.
        r may overlap v.

        Note that r here is only vdigits long, 
        whereas in mpDivide it is udigits long.

        Use remainder from mpDivide function.
    */

    int nn = max(udigits, vdigits);

    // [v2.6] increased to two times
    if (nn > (MAX_FIXED_DIGITS*2))
    {
    	printf("Error!! mpModulo nn overflow!\n");
    	return -1;
    }

    /* rr[nn] = u mod v */
    mpDivide(qq, rr, u, udigits, v, vdigits);

    /* Final r is only vdigits long */
    mpSetEqual(r, rr, vdigits);
    return 0;
}

