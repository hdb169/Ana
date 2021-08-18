#!/usr/bin/bash

# -----------------------------------------------------------------------------
#  Change these if this if not where hallc_replay and hcana live
export hcana_dir=/u/group/c-csv/$USER/test_april2020_branch/hcana
export hallc_replay_dir=/u/group/c-csv/$USER/test_april2020_branch/hallc_replay_sidis_fall18

# -----------------------------------------------------------------------------
#  Change if this gives you the wrong version of root, evio, etc
source /site/12gev_phys/softenv.sh 2.1

#source /apps/root/6.10.02/setroot_CUE.sh 
# -----------------------------------------------------------------------------
# Source setup scripts
curdir=`pwd`
cd $hcana_dir
source setup.sh
export PATH=$hcana_dir/bin:$PATH
echo Sourced $hcana_dir/setup.sh

cd $hallc_replay_dir
source setup.sh
echo Sourced $hallc_replay_dir/setup.sh

echo cd back to $curdir
cd $curdir

