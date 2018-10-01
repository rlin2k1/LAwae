#!/bin/bash 


cd "FitBit API Call"

python setup.py install

touch test.txt

python main.py >> test.txt

distance=`tail --lines=1 test.txt` 

pip install geocoder

python3 loc.py

cd ..

pip install gmplot

python plotter.py

open my_map.html

#echo tail --lines==1 test.txt
