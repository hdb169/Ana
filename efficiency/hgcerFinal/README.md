/u/group/c-csv/hdbhatt/my_analysis/efficiency/hgcer/shortest_rootfile

ROOTfile Path

I added all the ROOTfiles with mom > 2.8 and grouped into 3, pi+,pi-, and all.
Also, from -ve polarity, electron sample was chhosen to get electron efficiency.

Script path
/u/group/c-csv/hdbhatt/my_analysis/efficiency/hgcer/FinalEFF


//easy scripts

ROOT skills
 piplus_piminus_hgcer_eff.C
 piminus_hgcer_eff.C
 electrons_piminus_hgcer_eff.C
 piplus_hgcer_eff.C

Most of the cuts were already applied before adding ROOTfiles.

The scrippt to get the small ROOTfiles is hem_hgcer.cxx

This does apply all the cuts and get ROOtfiles or each runs> 2.8 (or any other, just change the momentum)

Also, the other script hem_hgcer_alladdRoot.cxx adds the sililar types +,-, or mixed (see details)

////new ROOTFiles in hcana
