/**************************************************************************//**
 * @file     main.c
 * @version  V1.10
 * @brief    Show Crypto IP ECC CDH secret Z generation.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"

typedef struct
{
    char     vecotr_name[16];             /* brief description of test vector             */
    E_ECC_CURVE  curve;                   /* NIST defined ECC curve                       */
    int      key_len;                     /* key length                                   */
    char     d[580];                      /* one's own private key                        */
    char     Qx[580];                     /* the party's public key 1                     */
    char     Qy[580];                     /* the party's public key 2                     */
    char     Z[580];                      /* expected answer secret Z                     */
}  ECDH_VECTOR_T;


static const ECDH_VECTOR_T   pattern[] =
{
    {
        "P-192", CURVE_P_192, 192,
        "f17d3fea367b74d340851ca4270dcb24c271f445bed9d527",
        "42ea6dd9969dd2a61fea1aac7f8e98edcc896c6e55857cc0",
        "dfbe5d7c61fac88b11811bde328e8a0d12bf01a9d204b523",
        "803d8ab2e5b6e6fca715737c3a82f7ce3c783124f6d51cd0"
    },
    {
        "P-224", CURVE_P_224, 224,
        "8346a60fc6f293ca5a0d2af68ba71d1dd389e5e40837942df3e43cbd",
        "af33cd0629bc7e996320a3f40368f74de8704fa37b8fab69abaae280",
        "882092ccbba7930f419a8a4f9bb16978bbc3838729992559a6f2e2d7",
        "7d96f9a3bd3c05cf5cc37feb8b9d5209d5c2597464dec3e9983743e8"
    },
    {
        "P-256", CURVE_P_256, 256,
        "7d7dc5f71eb29ddaf80d6214632eeae03d9058af1fb6d22ed80badb62bc1a534",
        "700c48f77f56584c5cc632ca65640db91b6bacce3a4df6b42ce7cc838833d287",
        "db71e509e3fd9b060ddb20ba5c51dcc5948d46fbf640dfe0441782cab85fa4ac",
        "46fc62106420ff012e54a434fbdd2d25ccc5852060561e68040dd7778997bd7b"
    },
    {
        "P-384", CURVE_P_384, 384,
        "3cc3122a68f0d95027ad38c067916ba0eb8c38894d22e1b15618b6818a661774ad463b205da88cf699ab4d43c9cf98a1",
        "a7c76b970c3b5fe8b05d2838ae04ab47697b9eaf52e764592efda27fe7513272734466b400091adbf2d68c58e0c50066",
        "ac68f19f2e1cb879aed43a9969b91a0839c4c38a49749b661efedf243451915ed0905a32b060992b468c64766fc8437a",
        "5f9d29dc5e31a163060356213669c8ce132e22f57c9a04f40ba7fcead493b457e5621e766c40a2e3d4d6a04b25e533f1"
    },
    {
        "P-521", CURVE_P_521, 521,
        "0000017eecc07ab4b329068fba65e56a1f8890aa935e57134ae0ffcce802735151f4eac6564f6ee9974c5e6887a1fefee5743ae2241bfeb95d5ce31ddcb6f9edb4d6fc47",
        "000000685a48e86c79f0f0875f7bc18d25eb5fc8c0b07e5da4f4370f3a9490340854334b1e1b87fa395464c60626124a4e70d0f785601d37c09870ebf176666877a2046d",
        "000001ba52c56fc8776d9e8f5db4f0cc27636d0b741bbe05400697942e80b739884a83bde99e0f6716939e632bc8986fa18dccd443a348b6c3e522497955a4f3c302f676",
        "005fc70477c3e63bc3954bd0df3ea0d1f41ee21746ed95fc5e1fdf90930d5e136672d72cc770742d1711c3c3a4c334a0ad9759436a4d3c5bf6e74b9578fac148c831"
    },
    {
        "K-163", CURVE_K_163, 163,
        "6653b6077398fadc7bf5e60158170148c3dc4527",
        "0000000574236f1428c432130946783a5b3aabb6c27ea5d6",
        "00000007908c251b8da021cbac281f123f7af4fac5b3dbb8",
        "00000004325bff38f1b0c83c27f554a6c972a80f14bc23bc"
    },
    {
        "K-233", CURVE_K_233, 233,
        "000000135a5b8c3ce047fbc5df26277d3bf83ac33ddadb5cf4a050ca82be48f0",
        "000001f40e34b3ed4a1b2d40c056fb75f2ad543c897cfd82f542cf746a0f202f",
        "000000c130a1abe92bc4c977c800777996ccc50b90df991a2e81dd515c188599",
        "000000a822b141ca1f5ad32899e68c54d1fec3df8100df485ebf1c5868a9ac89"
    },
    {
        "K-283", CURVE_K_283, 283,
        "015fde49b802542a52c70b23a0b1784e5f8780b56853f9a5f8c3a5266e8727dce97d4a17",
        "03f075c24c35a9dc9952be6fd32b761dce63f4720a22408e3a14bbd097e012b5694c22a0",
        "0675825b40202e95be7dab5a826147e04b8c51a09b0034577c1f31f8c16a70c8e1c85b89",
        "0745552817b5d729310b7dbebae687648714a9ae695dad20ca1ab6111c3d054670f21132"
    },
    {
        "K-409", CURVE_K_409, 409,
        "00084b711e3c60822e70fa6828b5abfb0e448888b35b0c8bb09f806616dc1ecf22dd86237d937c1bfde62b75ae655953fc6b2f7e",
        "0177f736f6116320cafbb5b4dec202d40508182fe011189b81e1f3998f5408607a46bb150ac47bcaaafde47b8a7b72f478bc22d2",
        "01df4ef4b37e0124e55b67f3586de24a88a6c5d98854007d4b0c4b4ccd68d51fafa7638bbe555d60b74def217c6a63c5b4068fb7",
        "0176bc5c4036ce5125493a58dd265f04d190f028366f7799f70aedf29ac67b5b37c37238593377a47944f5b639f43856dbd560ec"
    },
    {
        "K-571", CURVE_K_571, 571,
        "0173cd1631e18ece01b73b3572ffaa7495c4bc81f4078ae50d69cb1e338acf13469117112921166ddf2d29f3a9f8e10c67e88c9a99203a834565be76ac59126436739a6afa029cc5",
        "03106a5c1d923a0990ea8c6008c36c366b53e5622b98464044741fbc7840284db8bbf602866c30ccbf5f9b7e59cc1d9bfcc5b970fa624da9b15f6cb336f5dda7e6b9924d5dce4543",
        "005c5c7bbd5a789ac4c6283deb0d0d37c4852baa57d6bc2b0ac6337feb09704c44d1b385b70cc394fa235d83e6e7111787e57d0902c0cb132a190a6e62f398511c0c2c4cd50d4570",
        "003198a6b5d6cce847e24348a6a6ceff7a89ed3794d7acedc4e858c80ad04a74dbc02c7038e05ab26b2a299ec92ee0d2c7e66a81872a5157fbc5d4d37ad598d6ddee995ed28a2d74"
    },
    {
        "B-163", CURVE_B_163, 163,
        "00000003edae173de8fa0cf0412d6a7bdc81fdbd0617adf8",
        "00000003a647ba32dac71ec6780b0638a70cd24fc3bd4c8e",
        "00000002e69e961541844a4aa33769a7bce710f6640a560c",
        "0000000100fb42d177ffe6c31378e2e04e0da7376ffe8765"
    },
    {
        "B-233", CURVE_B_233, 233,
        "0000003c3ee474ac0d0bc1df567e3c35f5f766c5332b2d6730ff0e4d8e75aedb",
        "0000004756baddefc3dc337ab27b5452eb10affd9e31f5b55c330e90f0f686a2",
        "0000012a79f65232308a21c98c01555ccafc7dce15c8fed3025a760cbd6c2327",
        "000000e9f3d8c4f1bec0f920e763ea1bb7415899f01734609e7547dc425ec946"
    },
    {
        "B-283", CURVE_B_283, 283,
        "02f43455842246a2cc8ec068e9d6c6e4160f6ba4e3b5d831d93c1daa8fd3d5a9660c7bb1",
        "02504e1a17819d39f010a4a69a0568299402b58f944a384c7d1a62c9c93ea4d1ff300e13",
        "0265132f7b4c64b74b9179ed0f2e211f4328d625405022f554170da932b80fdf7c1aab12",
        "065194e26090e74047ee75f13f9769d20e1b52189650011e283daa090732cc53755dc366"
    },
    {
        "B-409", CURVE_B_409, 409,
        "00ace92103ffe262ac17ad42a46d4366f4cb4c580eff3ab1dde6bddfdbb7374811d52b1fa99320b4af5d4e9208c14eb8efa8916c",
        "0146989a50297be373dd665c45455a2ae4c221da5cd424007bd97f9e8e846f96740f3fa58c3c94129671cdd4d7ea650a2aade9d7",
        "01b42bffda843946a14ad6080f95b8fc6b7e173528d08ed36fe640aaf85aa00fb5edd5905a38b3c7961b7722b77b8dcb44bb25f5",
        "01d48a586be9285fa38dd3e70b0330b0ffebd327ceefef88fdc1521ef2fd61cbc9124e03b0c926e70fa56acb3edb54c3c48fab2b"
    },
    {
        "B-571", CURVE_B_571, 571,
        "0344f22be87999b95b2287f67430ea8fe646c62fe38b7ce61f1f956597c27bddd9902e20d4436abf3bebd8243ec29a00481a8a2c19f550e99641b5f14aafbb5bda953a7559f8653a",
        "03b63f5fa112ae6b5f113c765144fe4cbd6020e26d400c11609a3a634b9a325f416b0e3d3215734c68a1c2c8fad1d0bb9eb3939a41af22421f68781e7eb0664b9df5cea448deaa3b",
        "008e6cc77bcddc816e84cfc1f626824fa24d3d5fd33d8093cbfe1fc4d881b63b494123bc759670edcb1887bb3b9d5a8b516bc503828163709d4dacb594d277a15a92c064e5770d1b",
        "06775e1b99a236e02b020bc73666e5751c1210dcb6e9b02a69f4075376e49f7a1476d2209e861abb73f5e3ad189d268e035b1de93d47b3a64de5783c9a09bc223e1cc612f26dcdf1"
    },
};


char  my_z[580];                         /* temporary buffer used to keep output secret Z        */


void CRYPTO_IRQHandler()
{
    ECC_Complete(CRPT);
}


void  dump_buff_hex(uint8_t *pucBuff, int nBytes)
{
    int     nIdx, i;

    nIdx = 0;
    while (nBytes > 0)
    {
        printf("0x%04X  ", nIdx);
        for (i = 0; i < 16; i++)
            printf("%02x ", pucBuff[nIdx + i]);
        printf("  ");
        for (i = 0; i < 16; i++)
        {
            if ((pucBuff[nIdx + i] >= 0x20) && (pucBuff[nIdx + i] < 127))
                printf("%c", pucBuff[nIdx + i]);
            else
                printf(".");
            nBytes--;
        }
        nIdx += 16;
        printf("\n");
    }
    printf("\n");
}


void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable HXT clock */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Wait for HXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Switch HCLK clock source to HXT */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HXT,CLK_CLKDIV0_HCLK(1));

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Enable CRYPTO module clock */
    CLK_EnableModuleClock(CRPT_MODULE);

    /* Update System Core Clock */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Lock protected registers */
    SYS_LockReg();
}

void UART0_Init(void)
{

    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}


int32_t main (void)
{
    int    p, i;
    char   *pz, *pZ;

    SYS_Init();                        /* Init System, IP clock and multi-function I/O */

    UART0_Init();                      /* Initialize UART0 */

    SYS_UnlockReg();                   /* Unlock register lock protect */

    printf("+---------------------------------------------+\n");
    printf("|   Crypto ECC CDH Secret Z Generation Demo   |\n");
    printf("+---------------------------------------------+\n");

    NVIC_EnableIRQ(CRPT_IRQn);
    ECC_ENABLE_INT(CRPT);

    for (p = 0; p < sizeof(pattern)/sizeof(ECDH_VECTOR_T); p++)
    {
        if (((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x1) &&
                (pattern[p].key_len > 256))  /* M480LD supports maximum ECC 256 bits. */
            continue;

        printf("Run ECC CDH pattern %s => ", pattern[p].vecotr_name);

        if (ECC_GenerateSecretZ(CRPT, pattern[p].curve, (char *)pattern[p].d, (char *)pattern[p].Qx, (char *)pattern[p].Qy, my_z) < 0)
        {
            printf("ECC CDH secret Z generation failed!!\n");
            while (1);
        }

        for (pz = &my_z[0]; *pz == '0'; pz++);   /* truncate leading zeros                */

        for (pZ = (char *)&pattern[p].Z[0]; *pZ == '0'; pZ++); /* truncate leading zeros  */

        if (strcmp(pz, pZ))
        {
            printf("Secret Z [%s] is not matched with expected [%s]!\n", my_z, pattern[p].Z);
            for (i = 0; pz[i] != 0; i++)
            {
                if (pz[i] != pZ[i])
                    printf("%d - 0x%x 0x%x\n", i, pz[i], pZ[i]);
            }
            while (1);
        }
        printf("PASS.\n");
    }

    printf("ECC CDH all test patterns passed.\n");

    while (1);
}



