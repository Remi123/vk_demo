#bash.sh

echo "Start---------------- "
./asyncserver&
parallel -j0 ./syncclient ::: {0..5}
echo "End---------------- "
pkill asyncserver
