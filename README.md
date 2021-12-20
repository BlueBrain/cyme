# cyme
Framework to facilitate SIMD programming, without any tedious SIMD intrinsics.

Installation (need boost, doxygen, gcc >= 4.4, the doc provides tutorials, etc ... ).
There are a few variables to adjust Makefile generation with cmake (can be combined),
see next examples

    mkdir b
    cd b
    cmake .. # basic
    cmake .. # your machine supports slurm, specify the environment variable SLURM_ACCOUNT (export SLURM_ACCOUNT="--account=proj16") before !
    cmake .. -DSLURM_FOUND=false # your machine supports slurm but you do not care
    cmake .. -DCOMMON_LIBRARY_TYPE=STATIC # you prefer static library (boost lib, e.g. BG/Q)
    cmake .. -DCYME_POWER_VMX=true # force VMX backend for on BG/Q frontend ambiguity
    make doxygen

Compilation:

     -D__CYME_SIMD_VALUE__=sse -msse4.1 + optional -D__FMA__
     -D__CYME_SIMD_VALUE__=avx -msvx+ optional -D__FMA__
     -D__CYME_SIMD_VALUE__=qpx -D__FMA__
     -D__CYME_SIMD_VALUE__=vmx -D__FMA__ -mcpu=power7 -maltivec -mvsx

Know issues:

- BG/Q: bug Newton-Raphson algorithm (division/sqrt).

DEBUG mode:

1) the core engine test: core_operator_bracket_torture - Newton-Raphson algo for the
division fails:

    it_AoS = block_a.begin();
        for(; it_AoS != block_a.end(); ++it_AoS)
         (*it_AoS)[0]   = (((((*it_AoS)[1] /(*it_AoS)[2])/(*it_AoS)[3])/(*it_AoS)[4])/(*it_AoS)[5]);

    it_AoSoA_w = block_b.begin();
    it_AoSoA_r = block_b.begin();
    for(; it_AoSoA_r != block_b.end(); ++it_AoSoA_w,++it_AoSoA_r)
         (*it_AoSoA_w)[0] = (((((*it_AoSoA_r)[1]/(*it_AoSoA_r)[2])/(*it_AoSoA_r)[3])/(*it_AoSoA_r)[4])/(*it_AoSoA_r)[5]);

It fails for an unroll of 2 and double, only if the number of successive
division is larger than 3. I check the corresponding wrapper __mm__rec() and
_mm_nfma(), I do not find any issues. It works for float. Test works if I
perform the normal division

2) the validity test also fail for an unroll of 2

RELEASE:

The serial test unroll 4 fails, again for the division. It is very wierd
as the operator /= call the system division and not Newton-Raphson

Release 1.7.0
- Optimize the backend AVX to AVX2 if the processor supports it
- Tune log(x) and exp(x) solver using AVX2
- Complete and Optimize all inequalities <, >, <=, >= for the DAG and SSE/AVX backend, with corresponding tests
- Add support for bitwise operator for 32 bits integer SSE/AVX only, with corresponding tests
- Optimize operator ==
- Clang format and typos

Release 1.6.0
- More support of inequalities for SSE/AVX backend
- Support masking for inequalities for SSE/aVX backend
- Better compatibility with Intel compiler
- Implementation of power(x,y) (node in the DAG + backend), all backends
- Minor fixes  
- Swap boost by c++11

Release 1.5.0
- Merge rvec and wvec into vec
- fix bugs in the exponential all backends
- boundary limite for the exp with the new corresponding wrappers for integer manipulation
- Prepare work for the next release !

Release 1.4.0

- Google Summer code merge: work of Kai Langen
- 2^x, 10^x, log_2 and log_10 solver
- backend power7/power8 (with litle endian support)
- backend ARM 
- trigonometric function backend SSE/AVX/NEON and VMX (no mic and not BG/Q)
- fabs
- printing functions

Release 1.3.0

- New license lgpl 3.0
- Open Source Standard
- Add new elementary function (1/sqrt)
- Tiny optimization in the tree

Release 1.2.0

- Add new elementary function (sqrt)
- Fix bug in log
- Better DAG construction for operations with scalar operations
- Better catch of the FMA
- Simplification of the template expression when I mix float/double, implement unity concept
- Prepare for open source release
- Ameliorate CMake during the installation, configuration file is created with the needed define

Release 1.1.0

- Add new elementary function (pow/log)
- Ameliorate the tree creation by distinction Read/Write operators - const/ non const
- better DAG construction for --

Release 1.0.0

- First release of cyme

## Funding

The development of this software was supported by funding to the Blue Brain Project, a research center of the École polytechnique fédérale de Lausanne (EPFL), from the Swiss government’s ETH Board of the Swiss Federal Institutes of Technology.

Copyright (c) 2013-2021 Blue Brain Project/EPFL

