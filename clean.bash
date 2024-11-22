set type output ping fuck log vi-perl test parse 

x=$#
for ((i=0;i<x;i++)) do
  set -- "$@" -o -name "$1"
  shift 
done
shift 1
echo "$@"

