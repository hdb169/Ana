#!/usr/bin/csh

# -----------------------------------------------------------------------------
#  Change these if this if not where hallc_replay and hcana live
#setenv hcana_dir "/home/$USER/hcana"
#setenv hallc_replay_dir "/home/$USER/hallc_replay"


#export hcana_dir=/u/group/c-csv/$USER/test_april2020_branch/hcana
#export hallc_replay_dir=/u/group/c-csv/$USER/test_april2020_branch/hallc_replay_sidis_fall18

setenv hcana_dir=/u/group/c-csv/$USER/test_april2020_branch/hcana
setenv hallc_replay_dir=/u/group/c-csv/$USER/test_april2020_branch/hallc_replay_sidis_fall18

# -----------------------------------------------------------------------------
#  Change if this gives you the wrong version of root, evio, etc
source /site/12gev_phys/softenv.csh 2.1

#source /apps/root/6.10.02/setroot_CUE.csh

# -----------------------------------------------------------------------------
# Source setup scripts
set curdir=`pwd`
cd $hcana_dir
source setup.csh
setenv PATH "$hcana_dir/bin:$PATH"
echo Sourced $hcana_dir/setup.csh

cd $hallc_replay_dir
source setup.csh
echo Sourced $hallc_replay_dir/setup.csh

echo cd back to $curdir
cd $curdir

