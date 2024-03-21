#!/bin/bash
set +x

for i in {3..12}
do
  cp Zuckerman.sbatch Zuckerman$i.sbatch
  sed -i 's/job-name=Zuck/job-name=Zuck'$i'/g' Zuckerman$i.sbatch
  sed -i 's/output=Zuckerman.output/output=Zuckerman'$i'.output/g' Zuckerman$i.sbatch
  sed -i 's/error=Zuckerman.error/error=Zuckerman'$i'.error/g' Zuckerman$i.sbatch
  sed -i 's/.\/Zuckerman 10/.\/Zuckerman '$i'/g' Zuckerman$i.sbatch
done
