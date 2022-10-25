// Proyecto Shadows Mame Plus (Metal Slug Forever Special Edition Final)
// copyright-holders:Gaston90

#include "includes/neogeo.h"

#define MSLUG2_MAINCPU \
    ROM_FILL(0x100D,1,0x78)\
	ROM_FILL(0x1011,1,0x12)\
	ROM_FILL(0x1013,1,0x34)\
	ROM_FILL(0x100E,1,0x34)\
	ROM_FILL(0x1014,1,0x34)

#define MSLUG2RM_MAINCPU \
    ROM_FILL(0x100D,1,0x78)\
	ROM_FILL(0x1011,1,0x12)\
	ROM_FILL(0x1013,1,0x34)\
	ROM_FILL(0x100E,1,0x34)\
	ROM_FILL(0x1014,1,0x34)\
    ROM_FILL(0x100A,1,0x1A)

#define MSLUG2RMXE_MAINCPU \
    ROM_FILL(0x100D,1,0x78)\
	ROM_FILL(0x1011,1,0x12)\
	ROM_FILL(0x1013,1,0x34)\
	ROM_FILL(0x100E,1,0x34)\
	ROM_FILL(0x1014,1,0x34)\
    ROM_FILL(0x100A,1,0x98)

#define MSLUG2_YMSND \
	ROM_LOAD( "241.v1", 0x000000, 0x400000, CRC(99ec20e8) SHA1(80597707f1fe115eed1941bb0701fc00790ad504) )\
	ROM_LOAD( "241.v2", 0x400000, 0x400000, CRC(ecb16799) SHA1(b4b4ddc680836ed55942c66d7dfe756314e02211) )

#define MSLUG2_SPRITES \
	ROM_LOAD16_BYTE( "241.c1", 0x0000000, 0x800000, CRC(394b5e0d) SHA1(4549926f5054ee6aa7689cf920be0327e3908a50) )\
	ROM_LOAD16_BYTE( "241.c2", 0x0000001, 0x800000, CRC(e5806221) SHA1(1e5475cfab129c77acc610f09369ca42ba5aafa5) )\
	ROM_LOAD16_BYTE( "241.c3", 0x1000000, 0x800000, CRC(9f6bfa6f) SHA1(a4319b48004e723f81a980887678e3e296049a53) )\
	ROM_LOAD16_BYTE( "241.c4", 0x1000001, 0x800000, CRC(7d3e306f) SHA1(1499316fb381775218d897b81a6a0c3465d1a37c) )

#define MSLUG2FR_SPRITES \
	ROM_LOAD16_BYTE( "241_hacks04.c1", 0x0000000, 0x800000, CRC(7df74035) SHA1(08322a2f4e87cd125ebc5b7a98754c7a5b8e91d2) )\
	ROM_LOAD16_BYTE( "241_hacks04.c2", 0x0000001, 0x800000, CRC(97d9525d) SHA1(451a5bdafe1f2de63b76efb7d4afab454abdfff0) )\
	ROM_LOAD16_BYTE( "241.c3", 0x1000000, 0x800000, CRC(9f6bfa6f) SHA1(a4319b48004e723f81a980887678e3e296049a53) )\
	ROM_LOAD16_BYTE( "241.c4", 0x1000001, 0x800000, CRC(7d3e306f) SHA1(1499316fb381775218d897b81a6a0c3465d1a37c) )

#define MSLUG2DD_SPRITES \
	ROM_LOAD16_BYTE( "241.c1", 0x0000000, 0x800000, CRC(394b5e0d) SHA1(4549926f5054ee6aa7689cf920be0327e3908a50) )\
	ROM_LOAD16_BYTE( "241.c2", 0x0000001, 0x800000, CRC(e5806221) SHA1(1e5475cfab129c77acc610f09369ca42ba5aafa5) )\
	ROM_LOAD16_BYTE( "241_hacks21.c3", 0x1000000, 0x800000, CRC(c54c2548) SHA1(07045a7a004631b54ac35e02075ec8f6898a4b32) )\
	ROM_LOAD16_BYTE( "241_hacks21.c4", 0x1000001, 0x800000, CRC(f8168521) SHA1(3bb16caeced227c8bee95bfb92cd22f171ac86d3) )

#define MSLUG2EG_SPRITES \
	ROM_LOAD16_BYTE( "241.c1", 0x0000000, 0x800000, CRC(394b5e0d) SHA1(4549926f5054ee6aa7689cf920be0327e3908a50) )\
	ROM_LOAD16_BYTE( "241.c2", 0x0000001, 0x800000, CRC(e5806221) SHA1(1e5475cfab129c77acc610f09369ca42ba5aafa5) )\
	ROM_LOAD16_BYTE( "241.c3", 0x1000000, 0x800000, CRC(9f6bfa6f) SHA1(a4319b48004e723f81a980887678e3e296049a53) )\
	ROM_LOAD16_BYTE( "241.c4", 0x1000001, 0x800000, CRC(7d3e306f) SHA1(1499316fb381775218d897b81a6a0c3465d1a37c) )\
	ROM_LOAD16_BYTE( "241_hacks22.c5", 0x2000000, 0x800000, CRC(cae9af4f) SHA1(85f32cdc8069901f2f5fb628a2eda5e44f7994f7) )\
	ROM_LOAD16_BYTE( "241_hacks22.c6", 0x2000001, 0x800000, CRC(7cf51055) SHA1(ec5e78746190fc2bf087fa1b8efd9fc3433068d7) )

/*************
 Metal Slug 2
***************/

ROM_START( mslug2hacks01 ) //mslug2r
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hacks01.p1", 0x000000, 0x100000, CRC(f882d50d) SHA1(77fa3169a5631de0a89ef3170bfbe2b45294e8cf) )
	ROM_LOAD16_WORD_SWAP( "241.p2", 0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hacks02 ) //mslug21v2
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hacks02.p1", 0x000000, 0x100000, CRC(c3efed6c) SHA1(ae11a5abf75548271bf26acb645e8b0e5fc22eaa) )
	ROM_LOAD16_WORD_SWAP( "241.p2", 0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hacks03 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hacks03.p1", 0x000000, 0x100000, CRC(f680d167) SHA1(ebeed513de07928679ac4083fd705af51e21078d) )
	ROM_LOAD16_WORD_SWAP( "241.p2", 0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hacks04 ) //mslug2fr
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hacks04.p1", 0x000000, 0x100000, CRC(d1b10ed0) SHA1(db992fa93d1afb4adea30d63903fcd7d0e6ce9dd) )
	ROM_LOAD16_WORD_SWAP( "241.p2", 0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241_hacks04.s1", CRC(e22801a7) SHA1(24120adfbc5e35efcea98cfb30a936b6630da7c5) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2hacks05 ) //mslug2t, mslug2pt
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hacks05.p1", 0x000000, 0x100000, CRC(df5d6fbc) SHA1(b9cc3e29afc12dc98daac9afb4f94e2cdd8b455c) )
	ROM_LOAD16_WORD_SWAP( "241.p2", 0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hacks06 ) //mslug2sh
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hacks06.p1", 0x000000, 0x100000, CRC(4e4c8d1d) SHA1(bdb30f68fa1345511cbe1afcdf04c5f59d8965a1) )
	ROM_LOAD16_WORD_SWAP( "241.p2", 0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hacks07 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hacks07.p1", 0x000000, 0x100000, CRC(300d800b) SHA1(3896179061b4025d717cdcc213699a0a9d6183ab) )
	ROM_LOAD16_WORD_SWAP( "241.p2", 0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hacks08 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hacks08.p1", 0x000000, 0x100000, CRC(882310fb) SHA1(1ed0d6d3a6d37c95cbc0012bf55d32fc75b4d827) )
	ROM_LOAD16_WORD_SWAP( "241.p2", 0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hacks09 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hacks09.p1", 0x000000, 0x100000, CRC(7080ed64) SHA1(f028273a636f3d82481cbb5325657acf59c3b455) )
	ROM_LOAD16_WORD_SWAP( "241.p2", 0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hacks10 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hacks10.p1", 0x000000, 0x100000, CRC(6d309ec1) SHA1(a9554d41f8d5bd96530ca441e5b68a3fa1ecb2c8) )
	ROM_LOAD16_WORD_SWAP( "241.p2", 0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hacks11 ) //mslug2dg
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hacks11.p1", 0x000000, 0x100000, CRC(00c455e7) SHA1(8a20c06a5f92032c0dc1ebd1e8a2709abd725330) )
	ROM_LOAD16_WORD_SWAP( "241_hacks11.p2", 0x100000, 0x200000, CRC(1bf6b12a) SHA1(bdf1cee93c7cf1e57f61797ed4f176fe2a6ebf73) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hacks12 ) //mslug2ct
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hacks12.p1", 0x000000, 0x100000, CRC(78ad6864) SHA1(d84b0b3fc5991d2ab9d04712d4df3b4318e65923) )
	ROM_LOAD16_WORD_SWAP( "241_hacks12.p2", 0x100000, 0x200000, CRC(fe36f353) SHA1(61df20c7cd9f904552ec672dec11b679122bc5fe) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hacks13 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hacks13.p1", 0x000000, 0x100000, CRC(2061e49c) SHA1(F2f6069dc8bc3f10b46baf1a9fa19117fe340417) )
	ROM_LOAD16_WORD_SWAP( "241.p2", 0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hacks14 )
	ROM_REGION( 0x400000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hacks14.p1",  0x000000, 0x100000, CRC(aab0c2a7) SHA1(8501f543ec2a26a870195ead3dd531133390f203) )
	ROM_LOAD16_WORD_SWAP( "241_hacks22.p2",  0x100000, 0x300000, CRC(abf37360) SHA1(09347f0502fba4965dc14fd6db89bb3cabdeea1f) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241_hacks22.s1", CRC(d983067f) SHA1(b9da5e7e2064bf11baa601773413192c3694710a) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x3000000, "sprites", 0 )
    MSLUG2EG_SPRITES
ROM_END

ROM_START( mslug2hacks15 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hacks15.p1", 0x000000, 0x100000, CRC(34233c1f) SHA1(eb137f71bbbdd06672cbb761bc37d39bc06d3d86) )
	ROM_LOAD16_WORD_SWAP( "241.p2", 0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hacks16 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hacks16.p1", 0x000000, 0x100000, CRC(f565b5c5) SHA1(5dba416c97dbd0ff679a1544bc9c43eee3f1c71a) )
	ROM_LOAD16_WORD_SWAP( "241.p2", 0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hacks17 ) //mslug2fm
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hacks17.p1", 0x000000, 0x100000, CRC(487173f6) SHA1(7d86f25ea5b99df0fff94954a79793e7b7098f94) )
	ROM_LOAD16_WORD_SWAP( "241_hacks17.p2", 0x100000, 0x200000, CRC(37a118fc) SHA1(37c913c3d6736362ad83b8aaadf94b9112669a52) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hacks18 ) //mslug2unity
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hacks18.p1", 0x000000, 0x100000, CRC(1562cf23) SHA1(dfa2d7ea10f9eac6cd3b1a7a2f2c2f867edc28d1) )
	ROM_LOAD16_WORD_SWAP( "241.p2", 0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hacks19 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241.p1", 0x000000, 0x100000, CRC(2a53c5da) SHA1(5a6aba482cac588a6c2c51179c95b487c6e11899) )
	ROM_LOAD16_WORD_SWAP( "241.p2", 0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

	NEO_BIOS_AUDIO_128K( "241_hacks19.m1", CRC(aa3f889e) SHA1(c0c51d5f9fbbe96aeca9a352a9b2da42102c3399) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hacks20 ) //mslug2f1
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hacks20.p1",  0x000000, 0x100000, CRC(56f2c248) SHA1(688685dc3703885279d2e3f95538272474ee3e08) )
	ROM_LOAD16_WORD_SWAP( "241_hacks17.p2",  0x100000, 0x200000, CRC(37a118fc) SHA1(37c913c3d6736362ad83b8aaadf94b9112669a52) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2hacks21 ) //mslug2dd
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hacks21.p1",  0x000000, 0x100000, CRC(da22fd32) SHA1(7ecbf665f3d6af1b8f658e22f8df32463d3b9e2d) )
	ROM_LOAD16_WORD_SWAP( "241_hacks21.p2",  0x100000, 0x200000, CRC(89adbf97) SHA1(98b5382d51c7fd0b5ad52dd9649ef847a163a78a) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2DD_SPRITES
ROM_END

ROM_START( mslug2hacks22 ) //mslug2eg
	ROM_REGION( 0x400000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_hacks22.p1",  0x000000, 0x100000, CRC(bb312904) SHA1(08766b1ffb8686aa4d07370dc825c9f09a100fa6) )
	ROM_LOAD16_WORD_SWAP( "241_hacks22.p2",  0x100000, 0x300000, CRC(abf37360) SHA1(09347f0502fba4965dc14fd6db89bb3cabdeea1f) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241_hacks22.s1", CRC(d983067f) SHA1(b9da5e7e2064bf11baa601773413192c3694710a) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x3000000, "sprites", 0 )
    MSLUG2EG_SPRITES
ROM_END

/**********************
 Decrypted And Bootleg
************************/

/***************
 Only exclusive
*****************/

/************************
 Version Remastering
**************************/

ROM_START( mslug2er01 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_er01.p1", 0x000000, 0x100000, CRC(cc1802f5) SHA1(ed2198d3d0390f597a91b35938ec2fac9bbf289e) )
	ROM_LOAD16_WORD_SWAP( "241_er01.p2", 0x100000, 0x200000, CRC(120b31f0) SHA1(7f76db3a9ff1a515d06cc59a814e4b1b4049baed) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241_hacks04.s1", CRC(e22801a7) SHA1(24120adfbc5e35efcea98cfb30a936b6630da7c5) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2er02 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_er02.p1", 0x000000, 0x100000, CRC(bb25d215) SHA1(e035e63d51d9c55fdf8d4ac31ade41a6b24ce6ef) )
	ROM_LOAD16_WORD_SWAP( "241_er02.p2", 0x100000, 0x200000, CRC(19c995b2) SHA1(76cdd0d7d7cb0888646b3689e71fdb6066c0271a) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241_hacks04.s1", CRC(e22801a7) SHA1(24120adfbc5e35efcea98cfb30a936b6630da7c5) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2er03 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_er03.p1", 0x000000, 0x100000, CRC(c0fa4a7b) SHA1(e5d484d93aaf8fa25bfab280a4c6eb47e9daef8f) )
	ROM_LOAD16_WORD_SWAP( "241_er03.p2", 0x100000, 0x200000, CRC(fc09d7cb) SHA1(4730b18a518029a1736b57d7ab4bb72653404085) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241_hacks04.s1", CRC(e22801a7) SHA1(24120adfbc5e35efcea98cfb30a936b6630da7c5) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
	MSLUG2FR_SPRITES
ROM_END

/**************************
 Apocalyptic Time Edition
*****************************/

ROM_START( mslug2at01 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_at01.p1",     0x000000, 0x100000, CRC(0f8db35d) SHA1(ae65513586703ef373fcef45368549404e8422f0) )
	ROM_LOAD16_WORD_SWAP( "241_at01.p2",     0x100000, 0x200000, CRC(83931ab6) SHA1(bd5b527180b3a01eda89d862c08f5414d538fab9) )
    MSLUG2_MAINCPU

	NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2_SPRITES
ROM_END

/********************************
 Revised Remix Standard Edition
************************************/

ROM_START( mslug2la01 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_la01.p1", 0x000000, 0x100000, CRC(43d90a8f) SHA1(28e3a19f3e312fec7c01335949c665183dfea787) )
	ROM_LOAD16_WORD_SWAP( "241_la01.p2", 0x100000, 0x200000, CRC(3a55eb87) SHA1(b82c41988f3d6752bd5de78eef254f924785f6a1) )
    MSLUG2RM_MAINCPU

	NEO_SFIX_128K( "241_hacks04.s1", CRC(e22801a7) SHA1(24120adfbc5e35efcea98cfb30a936b6630da7c5) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2la02 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_la02.p1", 0x000000, 0x100000, CRC(0c8d3fe2) SHA1(7b6e686eb01ea36ea9a2d8d67f3863c85b9b31a4) )
	ROM_LOAD16_WORD_SWAP( "241_la02.p2", 0x100000, 0x200000, CRC(192b65e9) SHA1(40b8380306f96a95abe6b638eb786400655535b1) )
    MSLUG2RM_MAINCPU

	NEO_SFIX_128K( "241_hacks04.s1", CRC(e22801a7) SHA1(24120adfbc5e35efcea98cfb30a936b6630da7c5) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2la03 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_la03.p1", 0x000000, 0x100000, CRC(15299911) SHA1(413427710210a263c93ab985a455832d2b4b5400) )
	ROM_LOAD16_WORD_SWAP( "241_la03.p2", 0x100000, 0x200000, CRC(fceb2790) SHA1(6ed39a7b521ee32df92ac7ec580734128b8ad5ee) )
    MSLUG2RM_MAINCPU

	NEO_SFIX_128K( "241_hacks04.s1", CRC(e22801a7) SHA1(24120adfbc5e35efcea98cfb30a936b6630da7c5) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2la04 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_la04.p1", 0x000000, 0x100000, CRC(dfb83ffb) SHA1(1c88d3690cd8886226e0a87b34f6ffb97ee2a8f8) )
	ROM_LOAD16_WORD_SWAP( "241_la03.p2", 0x100000, 0x200000, CRC(fceb2790) SHA1(6ed39a7b521ee32df92ac7ec580734128b8ad5ee) )
    MSLUG2RM_MAINCPU

	NEO_SFIX_128K( "241_hacks04.s1", CRC(e22801a7) SHA1(24120adfbc5e35efcea98cfb30a936b6630da7c5) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2la05 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_la05.p1", 0x000000, 0x100000, CRC(ec3b7d94) SHA1(68934a1748acac8d6f6376fb3615c7bf95c0b283) )
	ROM_LOAD16_WORD_SWAP( "241_la01.p2", 0x100000, 0x200000, CRC(3a55eb87) SHA1(b82c41988f3d6752bd5de78eef254f924785f6a1) )
    MSLUG2RM_MAINCPU

	NEO_SFIX_128K( "241_hacks04.s1", CRC(e22801a7) SHA1(24120adfbc5e35efcea98cfb30a936b6630da7c5) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2lb01 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_lb01.p1", 0x000000, 0x100000, CRC(67737321) SHA1(3cd316d7b2eb08943010b2b24973516c1af7112e) )
	ROM_LOAD16_WORD_SWAP( "241_la01.p2", 0x100000, 0x200000, CRC(3a55eb87) SHA1(b82c41988f3d6752bd5de78eef254f924785f6a1) )
    MSLUG2RM_MAINCPU

	NEO_SFIX_128K( "241_hacks04.s1", CRC(e22801a7) SHA1(24120adfbc5e35efcea98cfb30a936b6630da7c5) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2lb02 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_lb02.p1", 0x000000, 0x100000, CRC(d9200f50) SHA1(fa1f6c0f94130517f513f86a8fe30961c6509bb4) )
	ROM_LOAD16_WORD_SWAP( "241_la02.p2", 0x100000, 0x200000, CRC(192b65e9) SHA1(40b8380306f96a95abe6b638eb786400655535b1) )
    MSLUG2RM_MAINCPU

	NEO_SFIX_128K( "241_hacks04.s1", CRC(e22801a7) SHA1(24120adfbc5e35efcea98cfb30a936b6630da7c5) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2lb03 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_lb03.p1", 0x000000, 0x100000, CRC(3183e0bf) SHA1(9a098652664ea707d2764056fcbfe0e96df1ef95) )
	ROM_LOAD16_WORD_SWAP( "241_la03.p2", 0x100000, 0x200000, CRC(fceb2790) SHA1(6ed39a7b521ee32df92ac7ec580734128b8ad5ee) )
    MSLUG2RM_MAINCPU

	NEO_SFIX_128K( "241_hacks04.s1", CRC(e22801a7) SHA1(24120adfbc5e35efcea98cfb30a936b6630da7c5) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2lb04 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_lb04.p1", 0x000000, 0x100000, CRC(9f2b60ed) SHA1(824e3ef25ad6b50c4ce05db4ba99ca378426749d) )
	ROM_LOAD16_WORD_SWAP( "241_la03.p2", 0x100000, 0x200000, CRC(fceb2790) SHA1(6ed39a7b521ee32df92ac7ec580734128b8ad5ee) )
    MSLUG2RM_MAINCPU

	NEO_SFIX_128K( "241_hacks04.s1", CRC(e22801a7) SHA1(24120adfbc5e35efcea98cfb30a936b6630da7c5) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2lb05 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_lb05.p1", 0x000000, 0x100000, CRC(d6e6ef92) SHA1(8d601ca57168e20b5e19a06fe9d801cb1cbab44a) )
	ROM_LOAD16_WORD_SWAP( "241_la01.p2", 0x100000, 0x200000, CRC(3a55eb87) SHA1(b82c41988f3d6752bd5de78eef254f924785f6a1) )
    MSLUG2RM_MAINCPU

	NEO_SFIX_128K( "241_hacks04.s1", CRC(e22801a7) SHA1(24120adfbc5e35efcea98cfb30a936b6630da7c5) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
	MSLUG2FR_SPRITES
ROM_END

/*************************
 Extreme MegaMods Edition
****************************/

ROM_START( mslug2rmxe0s01 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_rmxe0s01.p1", 0x000000, 0x100000, CRC(3084b681) SHA1(30e504d52baa6dafaed99d78e895be7b9a062a18) )
	ROM_LOAD16_WORD_SWAP( "241_rmxe0s01.p2", 0x100000, 0x200000, CRC(287f541b) SHA1(3f30846026edc499b0c6126f117e1cb859976dd4) )
    MSLUG2RMXE_MAINCPU

	NEO_SFIX_128K( "241_hacks04.s1", CRC(e22801a7) SHA1(24120adfbc5e35efcea98cfb30a936b6630da7c5) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2rmxe0s02 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_rmxe0s02.p1", 0x000000, 0x100000, CRC(3888fd3e) SHA1(fdb44079e3d77385a662ad1125d622cf95d7cb26) )
	ROM_LOAD16_WORD_SWAP( "241_rmxe0s02.p2", 0x100000, 0x200000, CRC(0b01da75) SHA1(f7b658fddae967a0ddd3a1f71235824c62bc53de) )
    MSLUG2RMXE_MAINCPU

	NEO_SFIX_128K( "241_hacks04.s1", CRC(e22801a7) SHA1(24120adfbc5e35efcea98cfb30a936b6630da7c5) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2rmxe0s03 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_rmxe0s03.p1", 0x000000, 0x100000, CRC(9904a213) SHA1(9af7eb0ea16ce82cd3498ae547143def4800f09a) )
	ROM_LOAD16_WORD_SWAP( "241_rmxe0s03.p2", 0x100000, 0x200000, CRC(eec1980c) SHA1(557529010fba8ed728aa0a89474d0af3b9fd2b50) )
    MSLUG2RMXE_MAINCPU

	NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2rmxe0s04 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_rmxe0s04.p1", 0x000000, 0x100000, CRC(3f3b5d28) SHA1(051b2d2ccb333de7f4808e3de39bd487991c28eb) )
	ROM_LOAD16_WORD_SWAP( "241_rmxe0s03.p2", 0x100000, 0x200000, CRC(eec1980c) SHA1(557529010fba8ed728aa0a89474d0af3b9fd2b50) )
    MSLUG2RMXE_MAINCPU

	NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2rmxe0s05 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_rmxe0s05.p1", 0x000000, 0x100000, CRC(8ce50c6b) SHA1(1374d95d71abfbece81115b2a9d932765ce39fe2) )
	ROM_LOAD16_WORD_SWAP( "241_rmxe0s01.p2", 0x100000, 0x200000, CRC(287f541b) SHA1(3f30846026edc499b0c6126f117e1cb859976dd4) )
    MSLUG2RMXE_MAINCPU

	NEO_SFIX_128K( "241_hacks04.s1", CRC(e22801a7) SHA1(24120adfbc5e35efcea98cfb30a936b6630da7c5) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2rmxe1s01 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_rmxe1s01.p1", 0x000000, 0x100000, CRC(142ecf2f) SHA1(b30a3d7dd0370e0a627c7262ea0d5491ac31358e) )
	ROM_LOAD16_WORD_SWAP( "241_rmxe0s01.p2", 0x100000, 0x200000, CRC(287f541b) SHA1(3f30846026edc499b0c6126f117e1cb859976dd4) )
    MSLUG2RMXE_MAINCPU

	NEO_SFIX_128K( "241_hacks04.s1", CRC(e22801a7) SHA1(24120adfbc5e35efcea98cfb30a936b6630da7c5) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
	MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2rmxe1s02 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_rmxe1s02.p1", 0x000000, 0x100000, CRC(ed25cd8c) SHA1(1615799f7931bb8480763ee21e6763906359d929) )
	ROM_LOAD16_WORD_SWAP( "241_rmxe0s02.p2", 0x100000, 0x200000, CRC(0b01da75) SHA1(f7b658fddae967a0ddd3a1f71235824c62bc53de) )
    MSLUG2RMXE_MAINCPU

	NEO_SFIX_128K( "241_hacks04.s1", CRC(e22801a7) SHA1(24120adfbc5e35efcea98cfb30a936b6630da7c5) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2FR_SPRITES
ROM_END

ROM_START( mslug2rmxe1s03 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_rmxe1s03.p1", 0x000000, 0x100000, CRC(bdaedbbd) SHA1(295d326c684707449e3aa791e612b9b97228dc01) )
	ROM_LOAD16_WORD_SWAP( "241_rmxe0s03.p2", 0x100000, 0x200000, CRC(eec1980c) SHA1(557529010fba8ed728aa0a89474d0af3b9fd2b50) )
    MSLUG2RMXE_MAINCPU

	NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2rmxe1s04 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_rmxe1s04.p1", 0x000000, 0x100000, CRC(05e6cf2e) SHA1(ce9f9172d5f3fa00dc6c87dde105db416fde2fc9) )
	ROM_LOAD16_WORD_SWAP( "241_rmxe0s03.p2", 0x100000, 0x200000, CRC(eec1980c) SHA1(557529010fba8ed728aa0a89474d0af3b9fd2b50) )
    MSLUG2RMXE_MAINCPU

	NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2_SPRITES
ROM_END

ROM_START( mslug2rmxe1s05 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241_rmxe1s05.p1", 0x000000, 0x100000, CRC(b6389e6d) SHA1(9c4db358f9714b733e0ed2a186aac8ce73e97777) )
	ROM_LOAD16_WORD_SWAP( "241_rmxe0s01.p2", 0x100000, 0x200000, CRC(287f541b) SHA1(3f30846026edc499b0c6126f117e1cb859976dd4) )
    MSLUG2RMXE_MAINCPU

	NEO_SFIX_128K( "241_hacks04.s1", CRC(e22801a7) SHA1(24120adfbc5e35efcea98cfb30a936b6630da7c5) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
    MSLUG2_YMSND

	ROM_REGION( 0x2000000, "sprites", 0 )
    MSLUG2FR_SPRITES
ROM_END

/*    YEAR  NAME            PARENT    MACHINE        INPUT       INIT             MONITOR COMPANY                 FULLNAME FLAGS */
// Metal Slug 2
GAME( 2014, mslug2hacks01,      mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "hack",            "Metal Slug 2 (Enemies Resetting Version 2014-09-14)", MACHINE_SUPPORTS_SAVE )
GAME( 2019, mslug2hacks02,      mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "hack",            "Metal Slug 2 (Generation 1V2 2019-05-11)", MACHINE_SUPPORTS_SAVE )
GAME( 2016, mslug2hacks03,      mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "DDJ",             "Metal Slug 2 (Stage Select 2016-10-19)", MACHINE_SUPPORTS_SAVE )
GAME( 2006, mslug2hacks04,      mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "Shyma.X",         "Metal Slug 2 (Traduction French Version 2004)", MACHINE_SUPPORTS_SAVE )
GAME( 2015, mslug2hacks05,      mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "System11",        "Metal Slug 2 (Turbo) ", MACHINE_SUPPORTS_SAVE )
GAME( 2008, mslug2hacks06,      mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "hack",            "Metal Slug 2 (Hybrid bullets version 2008-12-04)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 2017, mslug2hacks07,      mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "DDJ",             "Metal Slug 2 (Jump In Mid Air 2017-08-24)", MACHINE_SUPPORTS_SAVE )
GAME( 2018, mslug2hacks08,      mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "DDJ",             "Metal Slug 2 (Ward Charior 2018-01-25)", MACHINE_SUPPORTS_SAVE )
GAME( 2018, mslug2hacks09,      mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "DDJ",             "Metal Slug 2 (Change Weapon And Mummy 2018-08-25)", MACHINE_SUPPORTS_SAVE ) //The game crashes when you press the 1 + D button.
GAME( 2021, mslug2hacks10,      mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "I love Nimes",    "Metal Slug 2 (Burst Enhanced Edition 2021-04-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2017, mslug2hacks11,      mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "hack",            "Metal Slug 2 (Multi-Function Version 2017-05-09)", MACHINE_SUPPORTS_SAVE )
GAME( 2018, mslug2hacks12,      mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "hack",            "Metal Slug 2 (Survival Version 2018-07-31)", MACHINE_SUPPORTS_SAVE )//To enable Mods random you need to apply a command you have to press the Stars + D button to change Stars + C.
GAME( 2006, mslug2hacks13,      mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "DDJ",             "Metal Slug 2 (Violence Edition 2016-03-10)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslug2hacks14,      mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "hack",            "Metal Slug 2 (Enemies Resetting Extraction Green Turbo 2021-09-16)", MACHINE_SUPPORTS_SAVE )
GAME( 2018, mslug2hacks15,      mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "hack",            "Metal Slug 2 (Easy Mode Difficulty 2018-11-26)", MACHINE_SUPPORTS_SAVE )
GAME( 2013, mslug2hacks16,      mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "lb70",            "Metal Slug 2 (Crazy Fire Edition 2013-02-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslug2hacks17,      mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "CZXINC",          "Metal Slug 2 (Fightcade 2 2021-04-15)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslug2hacks18,      mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "KofKill, Wang Hua, Czk",  "Metal Slug 2 (Unity Time 2021-01-22)", MACHINE_SUPPORTS_SAVE )
GAME( 2018, mslug2hacks19,      mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "hack",            "Metal Slug 2 (Removal Of Background Music 2018-08-16)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslug2hacks20,      mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "hack",            "Metal Slug 2 (Friendly Injury Edition 2021-04-23)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug2hacks21,      mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "hack",            "Metal Slug 2 (Early Summer Starry Sky 2022-05-11)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslug2hacks22,      mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "hack",            "Metal Slug 2 (Extraction Green Turbo 2021-09-16)", MACHINE_SUPPORTS_SAVE )

// Decrypted And Bootleg

/***************
 Only exclusive
*****************/
/*********************************************************************************
* This game sector is exclusive, its modifications that load have been customized
  241.p1 and 241.p2 files. Therefore, a unique and distinctive game will be displayed 
  from the rest, we have been working to Optimize performance and avoid any type of crash 
  that occurs during the game. This it just means there are some details of the roms that 
  still need to be improved, things to add and things that could later be updated or 
  permanently removed if some kind a problem is detected that cannot be solved ...
********************************************************************************************/
/*********************************************************************************************************
  A definitive solution has been found in the hacks of roms called Version Hybrid Bullets, 
  which has been included in HBMAME around 8 years ago, this rom hacks have a very serious problem 
  that generates a crash in mission 2 / phase 2 and phaseROM_LOAD16_WORD_SWAP( "250_la03.p1", 0x000000, 0x100000, CRC(81ea65d6) SHA1(2af69efc6ba86cbdf94114c3d02837db11231626) ) 3 , its way of manifesting is to make the 
  torso disappear from the body that if the button is pressed shooting, the game crashes immediately 
  and will restart the game from scratch and will not allow you to continue playing at level 2, 
  now you can skip level 2 playing Normally, the mission will be finished at the beginning of level 2 
  of phase 2 and phase 3, the rest of the levels work normally, it will no longer be an impediment to 
  continue playing until the end of the game.
 ***********************************************************************************************************/

//Version Remastering
GAME( 2022, mslug2er01,        mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "Team Remix (Gaston90, kof1996, System11)",                                              "Metal Slug 2 Turbo (Enemies Resetting Version 2014-09-14)(Revised XR Improved Edition Remastering 2022-10-17)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug2er02,        mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "Team Remix (Gaston90, kof1996, System11)",                                              "Metal Slug 2 Turbo (Enemies Resetting Version 2014-09-14)(Revised XR Multi-Function Remix Standard Edition Remastering 2022-10-17)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug2er03,        mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "Team Remix (Gaston90, kof1996, System11)",                                              "Metal Slug 2 Turbo (Enemies Resetting Version 2014-09-14)(Revised XR Survival Version Remix Standard Edition Remastering 2022-10-17)", MACHINE_SUPPORTS_SAVE )//To enable Mods random you need to apply a command you have to press the Stars + D button to change Stars + C.

//All Apocalyptic Time Edition
GAME( 2021, mslug2at01,        mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "Gaston90",                                                                              "Metal Slug 2 Turbo (Apocalyptic Time Ports 0.2 2021-07-17)", MACHINE_SUPPORTS_SAVE )

// Revised Remix Standard Edition
GAME( 2021, mslug2la01,        mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "Team Remix (Gaston90, Ydmis, kof1996, System11 And I love Nimes)",                      "Metal Slug 2 Turbo (Revised XR Remix Standard Edition 2021-11-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslug2la02,        mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "Team Remix (Gaston90, Ydmis, kof1996, System11 And I love Nimes)",                      "Metal Slug 2 Turbo (Revised XR Multi-Function Remix Standard Edition 2021-11-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslug2la03,        mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "Team Remix (Gaston90, Ydmis, kof1996, System11 And I love Nimes)",                      "Metal Slug 2 Turbo (Revised XR Survival Version Remix Standard Edition 2021-11-21)", MACHINE_SUPPORTS_SAVE )//To enable Mods random you need to apply a command you have to press the Stars + D button to change Stars + C.
GAME( 2021, mslug2la04,        mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "Team Remix (Gaston90, Ydmis, kof1996, System11 And I love Nimes)",                      "Metal Slug 2 Turbo (Revised XR Survival Hybrid Bullets Version Remix Standard Edition 2021-11-21)", MACHINE_SUPPORTS_SAVE )//To enable Mods random you need to apply a command you have to press the Stars + D button to change Stars + C.
GAME( 2021, mslug2la05,        mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "Team Remix (Gaston90, Ydmis, kof1996, System11 And I love Nimes)",                      "Metal Slug 2 Turbo (Revised XR Hybrid Bullets Remix Standard Edition 2021-11-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug2lb01,        mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "Team Remix (Gaston90, Ydmis, kof1996, System11 And I love Nimes)",                      "Metal Slug 2 Turbo (Enemies Resetting Version 2014-09-14)(Revised XR Improved Edition 2021-11-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug2lb02,        mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "Team Remix (Gaston90, Ydmis, kof1996, System11 And I love Nimes)",                      "Metal Slug 2 Turbo (Enemies Resetting Version 2014-09-14)(Revised XR Multi-Function Remix Standard Edition 2021-11-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug2lb03,        mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "Team Remix (Gaston90, Ydmis, kof1996, System11 And I love Nimes)",                      "Metal Slug 2 Turbo (Enemies Resetting Version 2014-09-14)(Revised XR Survival Version Remix Standard Edition 2021-11-21)", MACHINE_SUPPORTS_SAVE )//To enable Mods random you need to apply a command you have to press the Stars + D button to change Stars + C.
GAME( 2022, mslug2lb04,        mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "Team Remix (Gaston90, Ydmis, kof1996, System11 And I love Nimes)",                      "Metal Slug 2 Turbo (Enemies Resetting Version 2014-09-14)(Revised XR Survival Hybrid Bullets Version Remix Standard Edition 2021-11-21)", MACHINE_SUPPORTS_SAVE )//To enable Mods random you need to apply a command you have to press the Stars + D button to change Stars + C.
GAME( 2022, mslug2lb05,        mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "Team Remix (Gaston90, Ydmis, kof1996, System11 And I love Nimes)",                      "Metal Slug 2 Turbo (Enemies Resetting Version 2014-09-14)(Revised XR Hybrid Bullets Remix Standard Edition 2021-11-21)", MACHINE_SUPPORTS_SAVE )

// Extreme MegaMods Edition
GAME( 2021, mslug2rmxe0s01,    mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "Team Remix (Gaston90, Shyma.X, kof1996, Ydmis, DDJ, System11 And I love Nimes)",        "Metal Slug 2 Turbo (Revised XR Heavy Machine Gun Extreme MegaMods Edition 2021-11-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslug2rmxe0s02,    mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "Team Remix (Gaston90, Shyma.X, kof1996, Ydmis, DDJ, System11 And I love Nimes)",        "Metal Slug 2 Turbo (Revised XR Multi-Function Version 2017-05-09)(Revised Extreme MegaMods Edition 2021-11-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, mslug2rmxe0s03,    mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "Team Remix (Gaston90, kof1996, Ydmis, DDJ, System11 And I love Nimes)",                 "Metal Slug 2 Turbo (Revised XR Survival Version 2018-07-31)(Revised Extreme MegaMods Edition 2021-11-21)", MACHINE_SUPPORTS_SAVE )//To enable Mods random you need to apply a command you have to press the Stars + D button to change Stars + C.
GAME( 2021, mslug2rmxe0s04,    mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "Team Remix (Gaston90, kof1996, Ydmis, DDJ, System11 And I love Nimes)",                 "Metal Slug 2 Turbo (Revised XR Survival Version 2018-07-31)(Hybrid Bullets Extreme MegaMods Edition 2021-11-21)", MACHINE_SUPPORTS_SAVE )//To enable Mods random you need to apply a command you have to press the Stars + D button to change Stars + C.
GAME( 2021, mslug2rmxe0s05,    mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "Team Remix (Gaston90, kof1996, Ydmis, DDJ, System11 And I love Nimes)",                 "Metal Slug 2 Turbo (Revised XR Hybrid Bullets Extreme MegaMods Edition 2021-11-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug2rmxe1s01,    mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "Team Remix (Gaston90, Shyma.X, kof1996, Ydmis, DDJ, System11 And I love Nimes)",        "Metal Slug 2 Turbo (Enemies Resetting Version 2014-09-14)(Revised XR Version Heavy Machine Gun Extreme MegaMods Edition 2021-11-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug2rmxe1s02,    mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "Team Remix (Gaston90, Shyma.X, kof1996, Ydmis, DDJ, System11 And I love Nimes)",        "Metal Slug 2 Turbo (Enemies Resetting Version 2014-09-14)(Revised XR Multi-Function Extreme MegaMods Edition 2021-11-21)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, mslug2rmxe1s03,    mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "Team Remix (Gaston90, kof1996, Ydmis, DDJ, System11 And I love Nimes)",                 "Metal Slug 2 Turbo (Enemies Resetting Version 2014-09-14)(Revised XR Survival Extreme MegaMods Edition 2021-11-21)", MACHINE_SUPPORTS_SAVE ) //To enable Mods random you need to apply a command you have to press the Stars + D button to change Stars + C.
GAME( 2022, mslug2rmxe1s04,    mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "Team Remix (Gaston90, kof1996, Ydmis, DDJ, System11 And I love Nimes)",                 "Metal Slug 2 Turbo (Enemies Resetting Version 2014-09-14)(Revised XR Survival Hybrid Bullets Extreme MegaMods Edition 2021-11-21)", MACHINE_SUPPORTS_SAVE ) //To enable Mods random you need to apply a command you have to press the Stars + D button to change Stars + C.
GAME( 2022, mslug2rmxe1s05,    mslug2,   neogeo_noslot, neogeo, neogeo_state,         init_neogeo,    ROT0, "Team Remix (Gaston90, kof1996, Ydmis, DDJ, System11 And I love Nimes)",                 "Metal Slug 2 Turbo (Enemies Resetting Version 2014-09-14)(Revised XR Hybrid Bullets Extreme MegaMods Edition 2021-11-21)", MACHINE_SUPPORTS_SAVE )
