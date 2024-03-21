#!/usr/bin/env bash

#SBATCH --job-name=Zuck
#SBATCH --output=Zuckerman.output
#SBATCH --error=Zuckerman.error
#SBACTH --account=crypto
#SBATCH --partition=crypto
#SBATCH --ntasks=1
#SBATCH --nodes=1
#SBATCH --cpus-per-task=32
#SBATCH --mem=184
#SBATCH --time=48:00:00

module purge
module load slurm

omp_threads=$SLURM_CPUS_PER_TASK
export OMP_NUM_THREADS=$omp_threads

./Zuckerman 10

