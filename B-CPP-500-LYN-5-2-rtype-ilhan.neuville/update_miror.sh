#!/bin/bash

ORIGINAL_REPO_URL="https://github.com/EpitechPromo2026/B-CPP-500-LYN-5-2-rtype-ilhan.neuville.git"

MIRROR_REPO_URL="https://github.com/IlhanTech/MIROR-RTYPE.git"

MIRROR_REPO_DIR="mirror_repo_temp"

BRANCH_TO_SYNC="main"

git clone $MIRROR_REPO_URL $MIRROR_REPO_DIR

cd $MIRROR_REPO_DIR

git remote add original $ORIGINAL_REPO_URL || true

git fetch original

git checkout $BRANCH_TO_SYNC
git merge original/$BRANCH_TO_SYNC

git push origin $BRANCH_TO_SYNC

cd ..
rm -rf $MIRROR_REPO_DIR
