

if(NOT SLURM_FOUND) # can be disabled if SLURM_FOUND=false
     find_program(SLURM_SBATCH_COMMAND sbatch DOC "Path to the SLURM sbatch executable")
     find_program(SLURM_SRUN_COMMAND srun DOC "Path to the SLURM srun executable")
     mark_as_advanced(SLURM_SRUN_COMMAND SLURM_SBATCH_COMMAND)

     if(SLURM_SRUN_COMMAND AND SLURM_SBATCH_COMMAND)
         set(SLURM_FOUND true  CACHE BOOL "SLURM available")
     else(SLURM_SRUN_COMMAND AND SLURM_SBATCH_COMMAND)
         set(SLURM_FOUND false  CACHE BOOL "SLURM available")
     endif(SLURM_SRUN_COMMAND AND SLURM_SBATCH_COMMAND)
endif(NOT SLURM_FOUND)

if(NOT SLURM_FOUND)
      MESSAGE(STATUS "Could not find SLURM scheduler on this machine.")
endif(NOT SLURM_FOUND)
