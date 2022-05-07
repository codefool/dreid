// Zobrist Hashing
//
// https://www.chessprogramming.org/Zobrist_Hashing
//
// Generate random numbers for each piece as each square.
//
// * 768 numbers for each piece *type* (12) at each square (64)
// * 1   number for black is on-move
// * 16  numbers for every combination of castling rights (4^2)
// * 8   numbers for en passant file
//   793 total numbers
//
// Zobrist Hash Table
//
// This table was generated with the following:
//
// #include <random>
// void init_zobrist() {
//     std::mt19937_64 gen(0xc0def001c0def001ULL);
//     std::uniform_int_distribution<uint64_t> dis;
//     for(int i = 1; i <= 64*34; i++) {
//         printf("0x%016lx, ", dis(gen));
//         if ((i%8) == 0)
//             printf("\n");
//     }
// }
//
// We hard-code the table here - rather than generating at run-time -
// so that we can guarantee that the hashes are consistent and independent
// of platform or std::random implementation.
//
// These are the numbers.
//
// Amen.
//
#pragma once

#include "dreid.h"

namespace dreid {

const uint64_t zob_pos_table[13][64] =
{   // Fa               Fb                  Fc                  Fd                  Fe                  Ff                  Fg                  Fh
    // White King
    {
    0x9a7b4c6c05e721e5, 0x25aa84c007a5c43f, 0x61ba65ed4548472d, 0xc08204caa6ae8765, 0x35bed27bb77282a0, 0x68ce1586a3b71d87, 0x090b15eb7eee60fd, 0xf6818e5a552e24ef, // R1
    0x179e2a7aa74c54db, 0x9dcd74a7b84ddaa6, 0x0d8cc5f337cc25db, 0x42a499ebb1ac7550, 0x729ca37bada0062e, 0x814159a4349e082f, 0xbd7cde6879e1b7a5, 0x8a575f1ed033d7a7, // R2
    0x054aea91d5026eea, 0x05a5e486ad1a2e5f, 0x569762d9a1d649ab, 0x34d72dc0aa9e0680, 0xda868509e1439471, 0xaf9b08136c58c550, 0xd89b1a405f7758f6, 0xb91ffd40a2fd7794, // R3
    0xd0a453d758a24c81, 0xd5ad14b2326f4635, 0x06d595457d639184, 0x40500f18a9601844, 0xa274bd8c99a690a3, 0x72dd1854f2825685, 0x789644670f03977f, 0xcc4ac72998c12d9e, // R4
    0x8f55a2bb44127baf, 0x1cb72dd441eb023a, 0xb49f1736b57e661e, 0x67cc57dcee6e813c, 0x995b382110610dbf, 0x533a7d6ed00dd92c, 0x88c882c1c0349be6, 0xb6950cf4d426a2d7, // R5
    0x1b358f8884f9dd27, 0x2ccfcec39d4514b2, 0xb05a59c5bfa457e4, 0xfdebbae0c422c998, 0xf7764e7a9c638452, 0x3c91c504c4f011ec, 0xc81a30b7cbb7e44a, 0x20b96d6c2bbfbb12, // R6
    0xe9d2cb2f9bdaf785, 0x2b5579841b13c1ec, 0xb1cb5fd42a0aafbd, 0xadbb242f408d26a2, 0xe9a1f15a6a672dd3, 0xb03c595d3172ace4, 0xc56104a083ea3784, 0x7bd7772ee8cf9fbb, // R7
    0x006ba0dae2bcc93d, 0xfbc130d446d36230, 0x4550b832e2b40760, 0x99c6083d8f4304d7, 0xf8c92453cb1bb31b, 0x41b18acdcee1ad46, 0xb63f6cc691176636, 0xd144e06a4df3091d, // R8
    },
    // White Queen
    {
    0x6a7038080c46890b, 0xf3a380cab7f3166b, 0xc9fa33bdfcf22a36, 0xc905ec4d60a6eb1c, 0x0b45029a3ea2e05c, 0x67992695290b7231, 0xc35cd7ca90dee092, 0x01e2a06ebc2603d0,
    0x9592294e23365333, 0x480dff235dd56b65, 0x804404b0de86ce4f, 0x75819cfd4a40761a, 0xb9760ac3a6c435ea, 0x75f1b9aaaa667a3a, 0x8e7bd5d00ac6a62d, 0xa683044bc3929eca,
    0x47cd4755707615aa, 0x630533c241ed1593, 0xcfd4709ad11eef58, 0x30d825773cd6f2da, 0xbecf9d7804140ca1, 0xc28b76d2537e852f, 0xc5332393729cac8f, 0x1f3e00201539b604,
    0xeb1fc3d018dc8d31, 0x277bd5e4ea22a171, 0xb81bf298a485c67d, 0x7e01652ed1245d2b, 0x951f73a078bcf590, 0xd868be81b8eeea48, 0x0d3f4c2b91c1e644, 0xc2977142e2fdc123,
    0x8d9d58066590f124, 0x14f1eab9b435216a, 0xc4f9c6c535d65a87, 0x37bdc562c71ff249, 0xa256be17b11f9d6c, 0xf31bd0269a666017, 0x200312065b68e41b, 0xe31df5eaace30100,
    0x0c35a7440b93db39, 0xa9d67fcbb3bcbf7e, 0x4c3b78668d6fa449, 0xa9890a8d6832e5e4, 0x8497985586c2e2ea, 0x65f8eb987c9168a7, 0x6fa9dee203d2fba0, 0x84b8af0d127dc948,
    0x1a14333259fbd1d6, 0x8bd3a7df1790181f, 0xce08d7f116f9f6c4, 0x36ed608556aab3aa, 0xba8a23e10f4faa00, 0xb338ba739a74b9c2, 0x9a81fa825afe8dd0, 0x5460d82bc30f1089,
    0xe7a1ed46a136d811, 0xf8c44133327479a7, 0xb7f607c547c92c06, 0x74126519bacea645, 0x6586fdc11acb69c9, 0x4b1dd1c8dc703705, 0xbd2a86317aa82219, 0x943c9fc802f1753c,
    },
    // White Bishop
    {
    0xe125069cdbabed2d, 0x5aeac3af6c6eaea3, 0x41de3b3114cdc7af, 0xba7d780c813d014c, 0xac837b7bfb522b90, 0x1f43d58960f9ca21, 0x0b365dbba957899f, 0xf7f25673068e0b26,
    0xc43f5fe29f34855f, 0xa6c8848494869fc0, 0xb26b17b963ebfac3, 0x91994dad339f6792, 0x70f595a4c0273dbc, 0x0e7390bb4999afed, 0x4852f0759ed6b648, 0x53e343e0a342487e,
    0xb853ffe0f261461b, 0x2babf32806625fef, 0x408e4dab1c3a0e5d, 0x73225cdab0ad7add, 0xe27daea3f21c6d50, 0xb0153f289f1e4562, 0x280bf14cfe95681c, 0xfb8bf08cb33a33a7,
    0xe6e15dd7b36188d5, 0xd4b7f4b8406e2605, 0x9ffe6062aecb4147, 0xf341c38eb69b33cc, 0xfb33711f15e5a672, 0x9635d28bdeec0e9c, 0x1be11c3e04c651bd, 0x37b15e518503ef3e,
    0xff29d358584d88cf, 0xa754a14100571fa2, 0x2c82af3c561944b0, 0x5ef6a9ba2493a2b9, 0x160b3618e86b8131, 0x2f9360b84c2a0db4, 0x577e03127c6f0528, 0xd66a3e53dd8cf0d3,
    0xe0239ad4e12bc781, 0xb795e78ac7f77400, 0xd74a6dd2a1a83b9b, 0xfdf1139afd331f76, 0xe810d738fe86b516, 0x98509779ee0c0d71, 0x9199d9dcbb47825a, 0x8e4be52326294852,
    0xff2c36a711962d57, 0xdeae3b4bb518838b, 0x2b63d7b1432ec007, 0xe9ba8517152bc8ae, 0xa27caf95b5aec645, 0xf62f51350ba3a7f8, 0xdf6ccd1bee53e38a, 0x24e010fa3690b200,
    0xfe3ac1608ad11ac9, 0x6b07c9e62bec6a85, 0xac5b2aff7ae9a474, 0x5903d296fc304840, 0xa755d2920b5e1fbf, 0xb371db16e57eeff6, 0x691e5d3f5095c402, 0x1743e2b13f037da7,
    },
    // White Knight
    {
    0x49ddd358b9cfc392, 0x73fcd8958c643f48, 0x66beb628ef637530, 0xa0850ab90405bab4, 0x868b4c4a2176fb9b, 0xf18d2944d33ed169, 0xebb93bf67d02752d, 0x43e41f5eb096ce51,
    0xde9aadd5f9128e4b, 0x40d0221be996e289, 0x16a0d4736fb683f2, 0x2b191a2607e60529, 0x0f0c383b43fb53d8, 0x30067bc236b3ae4b, 0x0b578ac660da8a36, 0x00759724228b41ae,
    0x9fc8d3200101554d, 0x17fee12e2656a2de, 0xafe8b04dbd486da4, 0x5fb6926a708aff97, 0x8af3fa2d318a4eb4, 0x34da97f891c5602e, 0xbaaa7686bcff4d4c, 0xcc2e11b5b9caf57b,
    0x260e7a83c7835b8c, 0x140bce29d3c0c0de, 0x1c49020e06324056, 0xaf7af19f8c601bc9, 0xbce0d80231a705f0, 0x05d31c00bdc98f7b, 0xb7c29fe2247bef5b, 0xefdca9da3f9e6de7,
    0x901be5f0477638af, 0x6df02c6e6d66d06f, 0x314c4eeb14b119f6, 0xc4bbd20e2646b17d, 0xdbb4104190a03dbd, 0x450d7ae5f71d2cfb, 0xe4215ce43288d2a0, 0x4c60f7d22464ae64,
    0x4a6c13ceed241603, 0xce3f846f3226a859, 0x8932494c72a44d1b, 0x43fa019f0c5f37d4, 0x3b37894b02cfa03e, 0xdc8bba9426300534, 0x94a26342eaab7196, 0x6073fa204b612fee,
    0xddd648cb49a05c3c, 0x1d685f4b496712b2, 0x47a178420e410644, 0xbde1846da309d05b, 0x97f88ea2f26756fa, 0xf731eaaf1432bb27, 0x297d45f2d3025ced, 0x494eab5e7736e95b,
    0x5f1c5a471644a115, 0x3b21dd2204297b2e, 0xf5145526d5a8dcb0, 0xd0c79322f17bed32, 0x0e5ad3a81cbe2f4b, 0x5ebf9ef9defecebf, 0x9109211f351d09ca, 0x77ba2d1debe194cf,
    },
    // White Rook
    {
    0xad3a87056061cb4b, 0x2ec49c18c2206f4e, 0xa7783616f51937fb, 0x3df56127ba1588b8, 0x7d7189947c218d44, 0xaa9924eea3e6a7e4, 0x3e0e891174f6678c, 0x12d28e22d42c4442,
    0x96dd30a7e4c81709, 0x2e0924287573bd3d, 0x84156cb24ba956a6, 0xe0d30574a071dd06, 0xa4c9399b13b37712, 0x45baa50bf67a9712, 0xa7b15dbaea1c18c7, 0x24dc5e0bfb05e4ad,
    0xc078e2092502c7a3, 0xc29c89344f8179bd, 0xedcbbef23cf7817d, 0xec83fca72e49f7d2, 0xb48fbc68e4391992, 0x92aa6243434a00ab, 0xbd4a3accc50bd98f, 0x023a3a470d725e47,
    0xbb767ed286c91829, 0xbc9bd990abad9f4e, 0x114c8471560813de, 0xd8361931e55a1b86, 0xf1fb289cb43d0ead, 0x4a3442f20548b365, 0xdfd6e933fa1100b4, 0xc20c946e52cb15f0,
    0x4aa1018fd29a6286, 0xc09246d9731b66f8, 0x4ea16607a7524058, 0x4edc5bad8d54060b, 0xa299b8075ce9c080, 0xd0c118dd8fa79679, 0x9ce521882de1c23e, 0x4d413dbf77572556,
    0xb13429c0fc07e280, 0x86140b8b4f64cf22, 0xa4791d52cb38a470, 0x3793fd06124cd1b7, 0x289af745dddda1e2, 0xd1fa48dfb6b345e7, 0xe73547f3586acdc1, 0x63221470de629702,
    0xdcac0625b2109ac4, 0xb62b5319f5eac44c, 0x2e30391fa8ed69df, 0x1a8662da37b75ebd, 0x50c020c01dcc7647, 0xed764e3e883dd0d1, 0x8f2bf54636dd265d, 0x2cc97cd0a0a6d08e,
    0xbc6cfadfff0c298f, 0x1b4fedcbabd100e8, 0x101e44ac6090ad66, 0x9b7a8a131a2132d3, 0xf30f4778a9492260, 0x6d3770e1642bd464, 0xe42e047d167ac028, 0x1afcd5561a9c452f,
    },
    // White Pawn
    {
    0x64c02a92a7675147, 0xbcbfbd975f9573e6, 0x85a3b746b33b0854, 0xfab486fdcf3f2465, 0xcce2db9e243896b2, 0x4999bff8e85b51f1, 0x592aa77a5aa0feb2, 0xda497ff1891e73e9,
    0xe48101efe31ad19b, 0x68e4f77e74685885, 0xe2913485c64964df, 0xda5a55c3ad14bf45, 0x4c1ebe429afbf742, 0x3dea3d18cfebb6ce, 0xe410e6b1d8f5de1c, 0x577e183cd152a347,
    0x83244cf8e8927eb8, 0xc5324685bd3c6917, 0xdfab7d77ebdb9f51, 0xdc95fd2c7d94cbab, 0xfd359a230fb4561e, 0xe58d7e486a601ea9, 0x7c3a7e9a9c544b6e, 0x36cf110f5e564e05,
    0x1f467b6becf5dd44, 0xd56df4b524cd0201, 0xe69d04d2949f2227, 0xd616aec791f77237, 0x48645d07d9d60fb4, 0xe4a41e5dcbc31d35, 0xac435cdd8638e73a, 0xd7b1a2567a14e681,
    0x2a5ad1f479795f5f, 0xaf4878e38eb5fa08, 0xa73bf6e0f477be9a, 0xa8c2e9b4135ee98a, 0x7a3940e9b5812b67, 0xe92e553f460c9278, 0xd54fc44e010fdf96, 0xfb3cbd4a7063f7a7,
    0x1539d213e448b668, 0x96c531ac1af704dd, 0x28a900f295659fb4, 0xb0e2ffdad88f2f64, 0xe472004722085f14, 0x4934c4f8cbb48ca3, 0x5592760a6820657e, 0x3a6e8d39a26fd1bd,
    0xc7cce94c9fd977f0, 0x241c983189c071ce, 0x2e3b552e052f89c8, 0xfc3841667caf59c9, 0xdbd1ac833852fe03, 0xddeaa1c468c9af55, 0x3b02230dd071477b, 0xc984490ddca243e2,
    0x02fdb352458cb7b4, 0xb84d7449a80322f5, 0x81b0fdae4c9598cd, 0xe3009d13b1a6f7c2, 0xeb69c4fb0ddede89, 0xf93d6108b2ce751d, 0xc63951c4f03a331c, 0x91dc79e78bde26b4,
    },
    // Black King
    {
    0xb91ad04bfa7d5f02, 0x447886fb53fc944e, 0xf04b78435e0e740a, 0xd91ff26ffd003c9f, 0x873f49fb50937847, 0xc8c40fbe3f967560, 0x4a290e230dbe2c5f, 0x47f02af74a4257af,
    0x7f2f064c31cec632, 0x53cf234a6e0a97c2, 0x744228caa168d4a2, 0xfc38c881301ff856, 0xad9c9c8ba8970ebc, 0x81d9a97e67618720, 0x76d9d47082bf4f48, 0x457cb174cb17f8ea,
    0x2a5cebcbcc58e232, 0x2e8b1c1a612281e9, 0x2709ca1a0391d3bd, 0xb9054adab1cf9fcb, 0x65627805ed9aea33, 0x3b98cd30505b744a, 0xba237e6d6a68b6bd, 0x184ef7795d572bfb,
    0xdc7a4ac767a638e4, 0xa4025d6f6b759c0f, 0x463f3a47e52fe99e, 0xce96c4923040c3d7, 0x4777da8d600fca61, 0xf87b9a91f95a2cd1, 0x0a59188c3636ad5d, 0xbf714ec31de2fcac,
    0x0148d52b14366b00, 0xd1f718009300e27b, 0x5ab57feb3b3142b2, 0x6189b4df7504182d, 0x4f0014deb96e398b, 0x27a6e0f7218b56a4, 0xd7b07e252166a8e1, 0xa84c8b8eb67504ba,
    0x9ccef38905c4a9e0, 0x6463938de3fac086, 0x622911980e29988b, 0x12cf028b261a649f, 0x43e6cab8f808a241, 0x30186a5c0bbe1005, 0x0a82356a3fe0875a, 0xd7c2be81a02a7a5f,
    0x3b3f50deb3161b6f, 0x3ff29d0fe3c725f1, 0x2e98ab12e0feb73b, 0x1319feeec2647553, 0xd52bd5766d03dade, 0xa9c7a1bc405dab89, 0xec58eee622554b9a, 0x4fd6a017c5fb13f2,
    0x00d78fe2eed1761a, 0x14f3b984eb80a7ac, 0x611b2c9f99f00310, 0x5b90ca26a30d065a, 0x13441979f30f4658, 0x12a5dee968b4e954, 0x1a87c2c3b8122cdd, 0xedea371830ced072,
    },
    // Black Queen
    {
    0xacceb940fc559ecc, 0xb2161305d102a77d, 0x7fdcd00c7cbefdcb, 0xe125e4d233e1c8b4, 0x30802f7f6ca871a8, 0x05cbcc5ba4ba0f76, 0xe6ef26318b22b30a, 0xf4ab41e7e983864f,
    0x9ded7c81049649ea, 0x8ccb612b78e8d18c, 0xad9be6dfab658358, 0x9c726ea450125821, 0x591363f2fbc0d956, 0xc77e538dc2065334, 0xbd62e05c1784ac65, 0xabd17dbf225e00b4,
    0x2c97ad5c6605146e, 0x0698c970a3727413, 0x257028c0c280fc88, 0xfc9c81b8e6f99f81, 0xc7e6ab7e6f8fd67a, 0x246383b2e141f75b, 0x18e467b75ad2a042, 0xb2bc7aeea61b0d29,
    0xe3c628b38f74d010, 0x3d6df2680e17c2c4, 0xe230c1b50fb7cdf8, 0x2aaada8738671b59, 0x70d7f34032cc5277, 0xc17bc931e3b8d183, 0x3d9fa7724aee8b5a, 0x4768d98f2671c176,
    0xd13c96bd57873857, 0x127009338ba1bd04, 0x946b514a803253d1, 0x8f2abb4088de0e38, 0x297a5d40bd8105ff, 0xcdd0f1a91f563703, 0x66c0cc3c1cbbc4b2, 0xfc6a8a1d4260e2c9,
    0x20315b36caef8aed, 0x3e81d39573276d28, 0xa52c79703ea0f546, 0x427b7fe23fa8ed79, 0x1f20779a967c7b3d, 0x1c113b7269a871fe, 0x4f3fa68a0271554a, 0x41ec355652bd9c2e,
    0x7cfde74046199143, 0x68a854834c0d6818, 0x53253212c1c3e297, 0xeb457e9093991650, 0xd115f46fc1a7af49, 0x7ba817325eba894e, 0x5de4d551d7de5860, 0x82632983aa8b16d6,
    0x32234ac6bee31f72, 0x8163b355267e90a4, 0xa65c6503c3210c86, 0x8ae76b48e5123be1, 0x61d324035bcd5803, 0x178698610e1e1969, 0x11a380d270bc9856, 0x4cd1b0bff76b3046,
    },
    // Black Bishop
    {
    0x794d95184100ef0f, 0x56bc6523aa23afe1, 0x39f3ae022db789e9, 0xcf19fe5af8d09eb8, 0x9b957562b6808ca3, 0x1cc79fc89f6da6d9, 0xb9d073ad2490fc76, 0xb9aa57965eed3206,
    0x45b04a6b1fa56be7, 0x7836bedb7b071b1b, 0x6874d30201986678, 0x8cee254cf39f89ec, 0x0916eb99067d535e, 0x05f37caa58f02c49, 0xfb620dbad6654fde, 0x11aecc7fb806b5fa,
    0xcd9d1b0a2e9427ee, 0x3a2a51abf4122473, 0x9ebcf2afce28adcf, 0x622c2bc3960976ce, 0x4b7c4f50cfe24f0d, 0x4d2503e67d4df98e, 0xefe92656454a8e8a, 0xe384fddd33d4d7f2,
    0x560317e9ccbc078c, 0x174473caaeab87f1, 0x4180363b9ec8df0b, 0x21f977beb358f54f, 0xc2fd6e6ed7fa5098, 0xe96f40a9837bcac9, 0xa90f5865b930201a, 0xef486980d2dfd884,
    0x841f8336f93c875c, 0xd3fcd956aa069684, 0xef5a82aa59b610e7, 0xac1e674b61416d67, 0x4319711154c53d98, 0x5e3852bc5166aec9, 0x1037f6bf262cb510, 0xad8b22d8e7c34c9e,
    0x89e27e37b25a4d60, 0x9c87af2855461267, 0xceca3e2f6f5b57e4, 0x7785c92ce3b727f3, 0xba5b3328168a1356, 0xfc7973703e642f73, 0xfbbe3bd3f965e75a, 0x3ab48b94cd71f5ae,
    0xe91db6f36bf39139, 0x60978acabd17f75f, 0xfe38f137e34fe4ad, 0x30a6722fc88b2ec5, 0x419bdf2ffc512b97, 0x167e9e0cd19c0c29, 0x01a13b9bf2f4f10e, 0xfa567f25c1c92fcf,
    0xa1288063d7a72dfb, 0x4f3799d4323a6662, 0xf3f33fc6c9f6ec19, 0x5f6a56637b48f3d4, 0x3c991b00763cdb78, 0x8daeb96cbafa7279, 0x51af628ac9e0cab3, 0x51c48ba49e9c8c21,
    },
    // Black Knight
    {
    0x632c6953cd59fc66, 0xe2c7d27fbdfaea30, 0x78bb3dc4b0a2670f, 0xfb7ffcc7487e9df5, 0x7e91e7b33ca7bb46, 0x9bab38f3bb192ff5, 0x35a1eaad1d448413, 0x5be33dbb0549d645,
    0x03b7f86533ce073d, 0x84c25d9f8c88dfff, 0x3ecb8b2acf8f0204, 0xfe8e98166bbc65e6, 0x1e53c3bee8b4f060, 0xc2da73ef98b31ff1, 0x53fca378ee04195b, 0xb5a22f39a8d9527f,
    0xf3b11aefbfb03f8a, 0x0b2e6ca5191d409f, 0xb7a522fdeca45f32, 0x8daf6296ca706e55, 0x9ba7e4e1eb876da6, 0xb717b5f122279ae8, 0x7b0be463bc354092, 0x5bd0fae4b4026420,
    0xf263f5165c381bd7, 0xe806efc98ffdafce, 0x9a0b4dcbb3b44768, 0xd2e85a7772ac1da4, 0x2adb5d9cc0c98cb3, 0x4b54a253644b78f4, 0x735d284446508ad1, 0x50d9b0a736a30431,
    0x916332a8045b8f9e, 0x770f2a4ee9a4af65, 0xcbe675fdeb09a9cc, 0x6be6a32be3fd3fd3, 0x0d79e787004f4e6f, 0xdc5494d58d1193c7, 0xdf8af98e14719392, 0x02e5079e112b4a59,
    0xe2f12d88135a88c2, 0xf873108c9cb2dee7, 0x55197731a85eca36, 0x5e967ec8fb36bf0b, 0x29219250b0e5d4a5, 0x5c8c6e29d00dc5d8, 0x2eef5ef24986517f, 0xe3fe766bd186a688,
    0xd3c02d7f4651140d, 0xf07f07d579130224, 0x29f48d0a8e318089, 0xa9ede0cf48db352f, 0x45351523e378e8f5, 0xffd11f5223bcfc2a, 0x0f319b45106816ec, 0xa00ed725c86bd2f4,
    0x5d1790ef3ce5c740, 0x46cbde9c36a7b8e7, 0xd64b5c1b3e26fdce, 0xfe1a9434a39f3daa, 0xcb4212086359fc1c, 0xc99819ba1306f69b, 0x5cd18fe0217a6dcf, 0x795faee89ed97a3e,
    },
    // Black Rook
    {
    0x44411e0d1efc27bd, 0x73095354f16ec334, 0x3035f10cb1c2942e, 0xd36e4856f8ba4452, 0xce6c68da80ad6ab4, 0x87d7b1360896a9d0, 0x7640872753cc0bab, 0xe27d2bada421a320,
    0xe0aea20a0bda819c, 0xe4a3f53dda918ea8, 0xef544e8e77f96777, 0x10932f10538850dd, 0xc45a29ffb6ce9664, 0x6319cc13abd4f8f3, 0x49cbaeed48ca9cab, 0x105ba10f08c16548,
    0x300a2bebb6b418f5, 0x3fa0f3cfd7a5dc60, 0xda6fee7a774c2488, 0x726418706397df54, 0x6612d8377d86fd61, 0x14b71b501fda4bbd, 0x6bbb8b9bc3d5fe34, 0xdf33c0dbb2c2086f,
    0xec50e7b23dae85d7, 0x03ebdd832d1aafab, 0x848f455a26a30b1e, 0x29170bc76f4f2692, 0x46d8c67774f84f91, 0xd867d4ca73cc98eb, 0xbe49b465584c583b, 0xf20876ebe2a4f35e,
    0xc6f3820b9419a26b, 0xb5c2ab7d93510caf, 0x6af80cafc20083b2, 0x713a52e0103fe302, 0x66eb53e14b45aa8a, 0x65f8fe5aa359bd74, 0x288a4a844294776f, 0x5ffc1cd3c3ed3c8a,
    0x44e2efd6acedb1d0, 0x3c8e813e290e257c, 0x796e38873f6d845e, 0xb27aa3fa4bc16af0, 0x6633d84b6dfbb2db, 0x1fbd44cde3482d94, 0x94a54f97e4e60250, 0x777a3dd6cdd25c57,
    0x522c87f0bda6388f, 0x5a282bd0fd1458e2, 0x57b757504ffefb0a, 0x518b2c69d74bd3e1, 0xed70185dad18ef65, 0x5eb598048e214af3, 0x917de0f94954fa33, 0x08f3058791f40151,
    0x2f9d8accde39e7fb, 0x4ef8270bfeb8a4dd, 0x3a5e51be92156981, 0x6a8c41ac286dbbbf, 0x59b871c5bf96ff14, 0xf2a977fc69a4b698, 0xcbdb45a4cb25b5a7, 0xd7c3de520dc78c88,
    },
    // Black Pawn
    {
    0xe93a7e0bbfb1dc4c, 0x6d725aca9d9126fa, 0x648b643543c0213f, 0x9e5df5817acec4e1, 0xf637e9eec439e5d5, 0xaeaa43b0924ba931, 0x1964f9b41e135257, 0x3e0534e7f644c8a5,
    0x95e44eedf77d389e, 0xae74e5e623bbe4ea, 0xf3fed9384a79843c, 0x951b8cc53d7cb87d, 0xca13af8cdc9cc17e, 0xf1dfeea2b90edd00, 0xe399fc1337120cf6, 0xcce1b1bc62989936,
    0x68b7c2b73dfaccd6, 0x2266ae93611bd0b1, 0x2be386a5bf0d6f42, 0xf7a637d0a79d711f, 0x938c28db1046a90d, 0xec9f30a1435c300a, 0xe7ec3ecf4a6f498f, 0x369b4d09d24530c0,
    0x19d1309a3a28a80d, 0xc09ce9badf3dae68, 0x413bfa66a3d82b61, 0xf4a543019dccd4f0, 0xd6f7e56b5e434d66, 0x62362b55e3b5637b, 0x73929c02eb520864, 0x8948dc0ae755e41b,
    0xe53d3ae2779cd38f, 0x1d5b2b03a51db1ad, 0x70b9826d209bb550, 0xf3420f83235663ce, 0x210041e884fd1016, 0xef06b9de74ce985b, 0x2c3aac4a61ed9f0e, 0x00d32843003b889a,
    0x2af02c516a739a85, 0x17daf949b232bdff, 0xe50f914b3e0f7f2d, 0xa84a861ab303c6ba, 0xa4938e3394d3dd57, 0x5c3be8d0a92c7156, 0xc9fdd991558cc846, 0xd2a09de7730c0d2a,
    0x32619e87c0d21e9a, 0x98f60ea9d5ea2947, 0x4af5042a6bea4cdb, 0xc07abf9b22297b3f, 0xd43ad769bba95608, 0xd1e61f0dd309ad7a, 0x332de9dd23a60d25, 0x5242fcb79f66a09a,
    0xa641c73c9b4a6393, 0x53363fc356c14bb7, 0x5aaded5d51d143c3, 0x557a7e0ddcfdc684, 0xc3525b26b179b907, 0xd0b0e79ace8fb0fe, 0xfd83e245059c19d6, 0xd1f6706be5677711,
    },
    // Empty Square (not used)
    {
    0x3cc88caf2552ee69, 0xc3852bbd7c26c3fe, 0x8f2122fdb7b56690, 0x44e997961a0f6c91, 0xd2fb59671d01f4f9, 0x69dc38d555b784c9, 0xa8876559306ab779, 0x0435296c48d789a9,
    0xdb39752f421980df, 0xfcc6700c244f3be0, 0xa24e8efe0fa258de, 0x60d2e84f2b63bfe1, 0x7fb2b63a332d3298, 0x9ba2bd2fc8b0827c, 0xc4a7c22c335d05d7, 0xc7d139d36a2811df,
    0x8ce535635d1a3397, 0xaf680b3fe22d3699, 0x7d75c777da218ae5, 0xadd7845a6b98af2f, 0x5723ad1fac8ffe91, 0x459ddfcea446a48c, 0x8084f04f295dafdd, 0x9fbe0a458aa1f19b,
    0x5a2c026ebe3950c2, 0x22dce1e018fc00b7, 0xa072a74355a0a451, 0xe571f3cbae4ee299, 0x7d2273dd444d5786, 0x40cdf31449ebd9f5, 0x4e134eb690b8046f, 0xcd987d6b396f0f08,
    0xc26a63f3a4f89faa, 0x8cb74a3d1763c487, 0xff6368606bd867f8, 0x45cd45a2e06f5019, 0x274dbf330a89092f, 0x1188349c75c83da7, 0x434669ce88ed98b7, 0xdd7a51834ee674d2,
    0x2c4259352190b97f, 0xb1192af62f73899e, 0xd3575d66ec7c51c5, 0x492cc688a7e6efc9, 0x1bc9a9c33eed3593, 0x99fea7ecc5b0f32f, 0x14a0816ece582efd, 0xa55a6f61d4233bfc,
    0x097531c15b35bf2d, 0x7cad322c8706aefe, 0x42415c870dff7928, 0xfad8de121cf4aa11, 0x37b5f9eaede70209, 0x573f987b5f5dd3b1, 0x5083d3b8f1ab8326, 0x459515210897dcb4,
    0x40a95951ffaee159, 0x8ce6d80151c035e6, 0x95e9604a8c636e5b, 0x201283879794b04e, 0xd89073401f219517, 0x43cb1bf3cc934201, 0x3e8ccf14cc2cd201, 0xbc8bcb6f59d5ba03,
    },
};

const uint64_t zob_black_on_move = 0x7d5ca2d124989d38;

// Castling rights
// There are four possible castle rights (white king side, white queen side, black
// king side, black queen side). For size we could use four numbers here, but then
// we'd have to research each castle right to see if it were valid. For speed we
// use 16 numbers (4^2), and just maintain a bitmap for each of the castle rights
// (see GameInfo).
const uint64_t zob_castle_rights[16] =
{
    0xf6ad2abe6e440319, 0x4cfa48fd46db27c4, 0xac6676736c728b0a, 0x403fedf081b4af6f, 0x1ffaa72ec6edc608, 0x7c9450809d4f8b30, 0x26f8a5ef63781519, 0x5d1196b4779d87ea,
    0xce61bf92cf236cd1, 0xf9bd6920cef88026, 0x9de517ad08b80a53, 0x62e9245ff4772554, 0x428b49ccd1c5fc06, 0xb44254d5c38c3ef1, 0xfc1cb11304df7c89, 0x3e5ad3ddf8dfc6a6,
};

// en passant
const uint64_t zob_en_passant[8] =
{
    0x5b876bdf3d3f548c, 0x72f3196b7cb10d2f, 0x5454f73fed4c3f73, 0xe37c11db71a20ced, 0xfa77eefbbee53f7a, 0x282bac46e249d4c6, 0x7995b24d1dd26a71, 0xe16a8e41fac6ca8c,
};

PositionHash Position::zobrist_hash()
{
    PositionHash hash = zob_castle_rights[ gi().getCastleRights() ];

    if ( gi().getOnMove() == SIDE_BLACK )
        hash ^= zob_black_on_move;

    if ( gi().hasEnPassant() )
        hash ^= zob_en_passant[ gi().getEnPassantFile() ];

    for (int square(0); square < 64; square++)
    {
        PiecePtr pp = _b[square];
        if (!pp->isEmpty())
            hash ^= zob_pos_table[pp->get_zob_idx()][square];
    }
    return hash;
}

} // namespace dreid