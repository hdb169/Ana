#!/bin/bash
echo
home_dir=/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/alleff
rootoutdir="/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/alleff/addedRootfiles"
echo "$home_dir"
echo
echo
cd "$home_dir"
########
#shell script to add runs is in another file, these are all D2 and H2 runs only.


hadd kin11_d2_pos_6068.root coin_replay_production_6068_-1.root coin_replay_production_6070_-1.root coin_replay_production_6071_-1.root
hadd kin13_h2_pos_6065.root coin_replay_production_6065_-1.root coin_replay_production_6066_-1.root
hadd kin14_d2_pos_6073.root coin_replay_production_6073_-1.root coin_replay_production_6081_-1.root
hadd kin16_h2_pos_6082.root coin_replay_production_6082_-1.root coin_replay_production_6083_-1.root
hadd kin17_d2_pos_6088.root coin_replay_production_6088_-1.root coin_replay_production_6089_-1.root coin_replay_production_6090_-1.root
hadd kin19_h2_pos_6084.root coin_replay_production_6084_-1.root coin_replay_production_6085_-1.root coin_replay_production_6086_-1.root
hadd kin110_d2_pos_6091.root coin_replay_production_6091_-1.root coin_replay_production_6093_-1.root coin_replay_production_6096_-1.root
hadd kin112_h2_pos_6099.root coin_replay_production_6099_-1.root coin_replay_production_610[0-3]_-1.root 


hadd kin21_d2_neg_6020.root coin_replay_production_602[0-1]_-1.root
hadd kin23_h2_neg_6025.root coin_replay_production_602[3-5]_-1.root
hadd kin24_d2_neg_6029.root coin_replay_production_6029_-1.root coin_replay_production_603[0-2]_-1.root
hadd kin26_h2_neg_6033.root coin_replay_production_603[3-6]_-1.root
hadd kin27_d2_neg_6043.root coin_replay_production_604[3-5]_-1.root
hadd kin29_h2_neg_6038.root coin_replay_production_603[8-9]_-1.root coin_replay_production_604[0-2]_-1.root
hadd kin210_d2_neg_6049.root coin_replay_production_6049_-1.root coin_replay_production_605[0-5]_-1.root
hadd kin212_h2_neg_6059.root coin_replay_production_6059_-1.root coin_replay_production_606[0-4]_-1.root


hadd kin31_d2_pos_6537.root coin_replay_production_6537_-1.root
hadd kin33_d2_pos_6541.root coin_replay_production_6541_-1.root
hadd kin35_d2_pos_6542.root coin_replay_production_654[2-3]_-1.root

hadd kin41_d2_neg_6545.root coin_replay_production_6545_-1.root
hadd kin43_d2_neg_6548.root coin_replay_production_654[8-9]_-1.root
hadd kin45_d2_neg_6550.root coin_replay_production_655[0-1]_-1.root


hadd kin51_d2_neg_6111.root coin_replay_production_611[1-2]_-1.root coin_replay_production_6114_-1.root
hadd kin53_h2_neg_6104.root coin_replay_production_610[4-6]_-1.root
hadd kin54_d2_neg_6115.root coin_replay_production_611[5-6]_-1.root
hadd kin56_h2_neg_6117.root coin_replay_production_611[7-8]_-1.root coin_replay_production_6121_-1.root
hadd kin57_d2_neg_6124.root coin_replay_production_612[4-5]_-1.root
hadd kin59_h2_neg_6122.root coin_replay_production_612[2-3]_-1.root coin_replay_production_6126_-1.root
hadd kin510_d2_neg_6136.root coin_replay_production_613[6-8]_-1.root
hadd kin512_h2_neg_6140.root coin_replay_production_614[0-1]_-1.root coin_replay_production_6139_-1.root


hadd kin61_d2_pos_6145.root coin_replay_production_614[5-6]_-1.root coin_replay_production_6154_-1.root
hadd kin63_h2_pos_6142.root coin_replay_production_6142_-1.root coin_replay_production_6144_-1.root  coin_replay_production_6163_-1.root coin_replay_production_6164_-1.root
hadd kin64_d2_pos_6170.root coin_replay_production_617[0-1]_-1.root 
hadd kin66_h2_pos_6174.root coin_replay_production_617[4-5].root
hadd kin67_d2_pos_6179.root coin_replay_production_6179_-1.root  coin_replay_production_6180_-1.root
hadd kin69_h2_pos_6177.root coin_replay_production_617[7-8].root
hadd kin610_d2_pos_6185.root coin_replay_production_618[5-7]_-1.root 
hadd kin612_h2_pos_6188.root coin_replay_production_618[8-9].root coin_replay_production_6190_-1.root


hadd kin71_d2_pos_6500.root coin_replay_production_650[0-1]_-1.root
hadd kin73_d2_pos_6506.root coin_replay_production_650[6-7]_-1.root
hadd kin75_d2_pos_6509.root coin_replay_production_6509_-1.root coin_replay_production_6510_-1.root
hadd kin77_d2_pos_6514.root coin_replay_production_651[4-7]_-1.root 


hadd kin81_d2_neg_6486.root coin_replay_production_6486_-1.root
hadd kin83_d2_neg_6489.root coin_replay_production_6489_-1.root
hadd kin85_d2_neg_6490.root coin_replay_production_649[0-1]_-1.root coin_replay_production_6493_-1.root
hadd kin87_d2_neg_6496.root coin_replay_production_649[6-9]_-1.root 



hadd kin91_d2_neg_6245.root coin_replay_production_624[5-7]_-1.root
hadd kin93_h2_neg_6237.root coin_replay_production_6237_-1.root  coin_replay_production_624[0-1]_-1.root
hadd kin94_d2_neg_6248.root coin_replay_production_624[8-9]_-1.root coin_replay_production_6250_-1.root
hadd kin96_h2_neg_6253.root coin_replay_production_625[3-5]_-1.root 
hadd kin97_d2_neg_6263.root coin_replay_production_626[3-7]_-1.root
hadd kin99_h2_neg_6256.root coin_replay_production_625[6-9]_-1.root coin_replay_production_6260_-1.root
hadd kin910_d2_neg_6270.root coin_replay_production_627[0-3]_-1.root
hadd kin912_h2_neg_6277.root coin_replay_production_6277_-1.root coin_replay_production_6281_-1.root coin_replay_production_6282_-1.root coin_replay_production_6284_-1.root


hadd kin101_d2_pos_6194.root coin_replay_production_619[4-5]_-1.root
hadd kin103_h2_pos_6292.root coin_replay_production_629[2-3]_-1.root 
hadd kin104_d2_pos_6198.root coin_replay_production_619[8-9]_-1.root 
hadd kin106_h2_pos_6200.root coin_replay_production_620[0-1]_-1.root 
hadd kin107_d2_pos_6205.root coin_replay_production_6205_-1.root coin_replay_production_620[8-9]_-1.root coin_replay_production_6210_-1.root
hadd kin109_h2_pos_6202.root coin_replay_production_620[2-4]_-1.root 
hadd kin1010_d2_pos_6215.root coin_replay_production_621[5-7]_-1.root coin_replay_production_6219_-1.root coin_replay_production_6229_-1.root
hadd kin1012_h2_pos_6221.root coin_replay_production_622[1-5]_-1.root 


hadd kin111_d2_pos_6419.root coin_replay_production_6419_-1.root coin_replay_production_642[1-2]_-1.root 
hadd kin113_d2_pos_6429.root coin_replay_production_6429_-1.root coin_replay_production_643[0-3]_-1.root
hadd kin115_d2_pos_6434.root coin_replay_production_643[4-6]_-1.root
hadd kin117_d2_pos_6443.root coin_replay_production_644[3-8]_-1.root 



hadd kin121_d2_neg_6451.root coin_replay_production_645[1-3]_-1.root 
hadd kin123_d2_neg_6459.root coin_replay_production_6459_-1.root coin_replay_production_646[0-4]_-1.root
hadd kin125_d2_neg_6465.root coin_replay_production_646[5-7]_-1.root
hadd kin127_d2_neg_6473.root coin_replay_production_647[3-9]_-1.root 


hadd kin131_d2_neg_6290.root coin_replay_production_629[0-1]_-1.root
hadd kin133_h2_neg_6285.root coin_replay_production_628[5-7]_-1.root
hadd kin134_d2_neg_6292.root coin_replay_production_629[2-3]_-1.root
hadd kin136_h2_neg_7297.root coin_replay_production_629[7-9]_-1.root 
hadd kin137_d2_neg_6306.root coin_replay_production_630[6-8]_-1.root
hadd kin139_h2_neg_6200.root coin_replay_production_620[0-2]_-1.root 
hadd kin1310_d2_neg_6348.root coin_replay_production_634[8-9]_-1.root coin_replay_production_635[0-1]_-1.root
hadd kin1312_h2_neg_6355.root coin_replay_production_635[5-8]_-1.root


hadd kin141_d2_pos_6309.root coin_replay_production_6309_-1.root  coin_replay_production_6310_-1.root
hadd kin143_h2_pos_6213.root coin_replay_production_621[3-4]_-1.root
hadd kin144_d2_pos_6322.root coin_replay_production_632[2-3]_-1.root
hadd kin146_h2_pos_6315.root coin_replay_production_631[7-8]_-1.root 
hadd kin147_d2_pos_6315.root coin_replay_production_631[5-6]_-1.root
hadd kin149_h2_pos_6324.root coin_replay_production_632[4-7]_-1.root 
hadd kin1410_d2_pos_6340.root coin_replay_production_634[0-4]_-1.root  coin_replay_production_6347_-1.root
hadd kin1412_h2_pos_6334.root coin_replay_production_633[4-8]_-1.root


hadd kin151_d2_pos_6387.root coin_replay_production_638[7-8]_-1.root coin_replay_production_639[7-8]_-1.root 
hadd kin153_d2_pos_6393.root coin_replay_production_639[3-6]_-1.root
hadd kin155_d2_pos_6399.root coin_replay_production_6399_-1.root coin_replay_production_640[2-4]_-1.root
hadd kin157_d2_pos_6410.root coin_replay_production_641[0-3]_-1.root  coin_replay_production_641[5-7]_-1.root


hadd kin161_d2_neg_6359.root coin_replay_production_6359_-1.root coin_replay_production_6360_-1.root 
hadd kin163_d2_neg_6367.root coin_replay_production_636[7-8]_-1.root coin_replay_production_6370_-1.root
hadd kin165_d2_neg_6375.root coin_replay_production_637[5-7]_-1.root
hadd kin167_d2_neg_6378.root coin_replay_production_637[8-9]_-1.root  coin_replay_production_638[0-1]_-1.root


hadd kin171_d2_neg_6524.root coin_replay_production_652[4-6]_-1.root 
hadd kin173_d2_pos_6518.root coin_replay_production_651[8-9]_-1.root coin_replay_production_6520_-1.root


hadd kin181_d2_neg_6535.root coin_replay_production_653[5-6]_-1.root 
hadd kin183_d2_pos_6527.root coin_replay_production_652[7-9]_-1.root



hadd kin331_d2_neg_7593.root coin_replay_production_759[3-7]_-1.root
hadd kin333_d2_neg_7608.root coin_replay_production_760[8-9]_-1.root coin_replay_production_7610_-1.root
hadd kin335_d2_neg_7611.root coin_replay_production_761[1-6]_-1.root
hadd kin337_d2_neg_7625.root coin_replay_production_762[5-9]_-1.root coin_replay_production_763[0-4]_-1.root



hadd kin341_d2_pos_7637.root coin_replay_production_763[5-7]_-1.root
hadd kin343_d2_pos_7642.root coin_replay_production_764[2-5]_-1.root
hadd kin345_d2_pos_7646.root coin_replay_production_764[6-9]_-1.root coin_replay_production_765[0-2]_-1.roo
hadd kin347_d2_pos_7661.root coin_replay_production_766[1-9]_-1.root coin_replay_production_7670_-1.root


hadd kin351_d2_neg_7671.root coin_replay_production_767[1-2]_-1.root
hadd kin353_d2_neg_7679.root coin_replay_production_7679_-1.root coin_replay_production_768[0-2]_-1.root
hadd kin355_d2_neg_7684.root coin_replay_production_768[4-9]_-1.root coin_replay_production_769[0-2]_-1.root


hadd kin361_d2_pos_7699.root coin_replay_production_7699_-1.root coin_replay_production_770[2-3]_-1.root
hadd kin363_d2_pos_7706.root coin_replay_production_770[6-9]_-1.root coin_replay_production_7710_-1.root
hadd kin365_d2_pos_7716.root coin_replay_production_771[6-9]_-1.root coin_replay_production_772[0-2]_-1.root


hadd kin374_h2_neg_7729.root coin_replay_production_7729_-1.root coin_replay_production_773[0-3]_-1.root
hadd kin375_d2_neg_7735.root coin_replay_production_773[5-6]_-1.root
hadd kin377_h2_neg_7741.root coin_replay_production_774[1-3]_-1.root 
hadd kin378_d2_neg_7737.root coin_replay_production_773[7-9]_-1.root coin_replay_production_7740_-1.root
hadd kin3710_h2_neg_7753.root coin_replay_production_775[3-5]_-1.root 
hadd kin3711_d2_neg_7757.root coin_replay_production_775[7-9]_-1.root 


hadd kin384_h2_pos_7765.root coin_replay_production_776[5-6]_-1.root
hadd kin385_d2_pos_7767.root coin_replay_production_776[7-9]_-1.root coin_replay_production_777[0-1]_-1.root
hadd kin387_h2_pos_7778.root coin_replay_production_777[8-9]_-1.root 
hadd kin388_d2_pos_7775.root coin_replay_production_777[5-7]_-1.root 
hadd kin3810_h2_pos_7781.root coin_replay_production_778[1-2]_-1.root 
hadd kin3811_d2_pos_7783.root coin_replay_production_778[3-7]_-1.root 


hadd kin391_d2_neg_7796.root coin_replay_production_779[6-7]_-1.root
hadd kin393_d2_neg_7798.root coin_replay_production_779[8-9]_-1.root coin_replay_production_7800_-1.root
hadd kin395_d2_neg_7805.root coin_replay_production_780[5-7]_-1.root


hadd kin401_d2_pos_7808.root coin_replay_production_780[8-9]_-1.root
hadd kin403_d2_pos_7813.root coin_replay_production_781[3-4]_-1.root
hadd kin405_d2_pos_7815.root coin_replay_production_781[5-7]_-1.root

#Note
#11/1 6490 :added (A), 6418 not added (NA), 6420 NA
#12/1 6449, 6450 Added
#14/7 6324 added
#14/10 6339 Not added
#15/5 6399 added, 6400, 6401 not added
#38/5 7767 added
#12/1 6449, 50 not added




############
eval "mv *kin*.root addedRootfiles"
eval "ls -ltrh addedRootfiles/*.root"
