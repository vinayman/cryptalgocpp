srcdir=`dirname "$BASH_SOURCE"`

builddir="${srcdir}/build"

echo "Build dir: ${builddir}"
echo "Script dir: ${srcdir}"

mkdir -p "${srcdir}/build"

cmake -B $srcdir/build -D CMAKE_C_COMPILER=gcc-11 -D CMAKE_CXX_COMPILER=g++-11 -S $srcdir

cd "${srcdir}/build"

make -j3
