p=$(pwd)
mkdir -p packages
cd packages
cd freetype2
git clone https://git.savannah.gnu.org/git/freetype/freetype2.git
./autogen.sh
./configure
cmake .
make
cd $p
