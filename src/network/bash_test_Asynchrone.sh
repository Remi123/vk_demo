#bash.sh

echo "Start---------------- "
./asyncserver&
parallel -j0 ./syncclient ::: {0..60}
echo "End---------------- "
pkill asyncserver
